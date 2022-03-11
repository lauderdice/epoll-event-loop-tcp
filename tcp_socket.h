//
// Created by lauderdice on 05.03.22.
//

#ifndef EPOLL_SERVER_TCP_SOCKET_H
#define EPOLL_SERVER_TCP_SOCKET_H


class TCPSocket {

public:
    TCPSocket();
    TCPSocket(short int port);
    ~TCPSocket();
    int get_socketfd();
    void set_nonblocking();
    void make_listen();

    void close_connection();

private:
    short int port;
    int socketfd;
};


#endif //EPOLL_SERVER_TCP_SOCKET_H
