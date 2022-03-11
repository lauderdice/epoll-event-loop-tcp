
#include <sys/epoll.h>
#include <string>
#include <iostream>
#include <sys/socket.h>
#include <netdb.h>
#include <cstring>
#include "epoll_tcpsocketdescriptor.h"
#include "tcp_socket.h"
#include "epoll_tcpsingleconnection.h"

EpollTCPSocketDescriptor::EpollTCPSocketDescriptor(TCPSocket &tcpsocket, EpollSysUtil &e) :
        EpollFileDescriptor(tcpsocket.get_socketfd(), e), tcpSocket(tcpsocket) {
    registerFd(EPOLLIN | EPOLLOUT | EPOLLHUP);
}


void EpollTCPSocketDescriptor::handleEvent(uint32_t events)
{
    std::string line;
    if(events & EPOLLIN){
        accept_new_connection();
    }
    else if ((events & EPOLLERR) || (events & EPOLLHUP) || !(events & EPOLLIN)) {
        unregisterFd();
        tcpSocket.close_connection();
    } else {
        std::cout << "Unknown event combination was triggered: " << events << std::endl;
    }
}

EpollTCPSocketDescriptor::~EpollTCPSocketDescriptor() {
    EpollFileDescriptor::unregisterFd();
}

void EpollTCPSocketDescriptor::accept_new_connection() {
    struct sockaddr in_addr;
    socklen_t in_len = sizeof(in_addr);
    int infd = accept(this->tcpSocket.get_socketfd(), &in_addr, &in_len);
    if (infd < 0) {
        throw std::runtime_error(std::string("[Server] Connection could not be accepted: ") + std::strerror(errno));
    }
    std::string hbuf(NI_MAXHOST, '\0');
    std::string sbuf(NI_MAXSERV, '\0');
    if (getnameinfo(&in_addr, in_len,
                    const_cast<char *>(hbuf.data()), hbuf.size(),
                    const_cast<char *>(sbuf.data()), sbuf.size(),
                    NI_NUMERICHOST | NI_NUMERICSERV) == 0) {
        std::cout << "[Server] Accepted connection (host=" << hbuf << ", port=" << sbuf << ")" << "\n";
    }
    auto single_conn = new EpollTCPSingleConnectionDescriptor(infd, epollInstance);
    single_conn->set_nonblocking();
}


