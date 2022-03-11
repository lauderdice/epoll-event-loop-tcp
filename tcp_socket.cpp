//
// Created by lauderdice on 05.03.22.
//
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <cstring>
#include <stdexcept>
#include <iostream>
#include <unistd.h>
#include "tcp_socket.h"

TCPSocket::~TCPSocket(){
    close_connection();
}

TCPSocket::TCPSocket(short int port) {
    this->port = port;
    this->socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if(this->socketfd > 0)
        std::cout << "Sucessfully created socket on port "<< port << ".."<< std::endl;
    else
        throw std::runtime_error(std::string("Failed to establish socket connection: ") + std::strerror(errno));
    struct sockaddr_in saddr;
    memset(&saddr, 0, sizeof(saddr));
    saddr.sin_family      = AF_INET;
    saddr.sin_addr.s_addr = htonl(INADDR_ANY);
    saddr.sin_port        = htons(this->port);
    int socket_is_bound = bind(this->socketfd, (struct sockaddr *) &saddr, sizeof(saddr));
    if (socket_is_bound < 0)
        throw std::runtime_error(std::string("Error in binding the socket: ") + std::strerror(errno));
}

int  TCPSocket::get_socketfd() {
    return this->socketfd;
}

void TCPSocket::set_nonblocking() {
    int flags = fcntl(this->socketfd, F_GETFL, 0);
    flags |= O_NONBLOCK;
    fcntl(this->socketfd, F_SETFL, flags);
}

void TCPSocket::make_listen(){
    listen(this->socketfd, SOMAXCONN);
    std::cout << "Listening on socket started.." << std::endl;
}

void TCPSocket::close_connection() {
    close(this->socketfd);
}

TCPSocket::TCPSocket() = default;
