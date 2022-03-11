
#include "epoll_tcpsingleconnection.h"
#include <sys/epoll.h>
#include <string>
#include <iostream>
#include <unistd.h>
#include <fcntl.h>

#define BUFFER_SIZE 64

EpollTCPSingleConnectionDescriptor::EpollTCPSingleConnectionDescriptor(int fd, EpollSysUtil &e) : EpollFileDescriptor(fd, e) {
    std::cout << "Registering EpollTCPSingleConnectionDescriptor to epoll..." << std::endl;
    registerFd(EPOLLIN);
}

EpollTCPSingleConnectionDescriptor::~EpollTCPSingleConnectionDescriptor(){
    std:: cout << "Unregistering EpollTCPSingleConnectionDescriptor from epoll..." << std::endl;
    epollInstance.unregisterFd(*this);

};

void EpollTCPSingleConnectionDescriptor::handleEvent(uint32_t events) {
    int count_wrote;
    int count_read;
    while(true){
        char buffer[BUFFER_SIZE];
        count_read = read(fd, buffer, BUFFER_SIZE-1);
        if (count_read == -1) {
            if (errno == EAGAIN || errno == EWOULDBLOCK)
            {
                std::cout << "[TCP Server] No more available data to read for FD "<< fd <<". Keeping connection open.." << std::endl;
                break;
            }
            std::cout << "[TCP Server] Unrecognized errno for FD "<< fd <<". Keeping connection open.." << std::endl;
            break;
        } else if (count_read == 0)
        {
            std::cout << "[TCP Server] EOF Detected for FD "<< fd <<" - closing and deleting connection with client.." << std::endl;
            delete this;
            break;
        } else {
            std::cout <<"[TCP Server] Client (FD "<< fd <<") - sent " << count_read << " characters" << std::endl;
            for (int i = 0; i < count_read; ++i) {
                if(buffer[i] == '\n'){
                    if (received_message_len > 0){
                        std::string to_send = std::to_string(received_message_len) + '\n';
//                        std::cout << "Data to send: " << to_send << std::endl;
                        count_wrote = write(fd, to_send.data(), to_send.size());
                        std::cout << "[TCP Server] Sent to client (FD "<< fd <<"): " << received_message_len <<
                        ", totally " << count_wrote << " bytes sent.." << std::endl;
                        received_message_len = 0;
                    } //else do nothing just iterate over the new line char
                } else {
                    received_message_len += 1;
                }
            }
        }
    }


}

void EpollTCPSingleConnectionDescriptor::set_nonblocking() {
    int flags = fcntl(this->fd, F_GETFL, 0);
    flags |= O_NONBLOCK;
    fcntl(this->fd, F_SETFL, flags);
}

