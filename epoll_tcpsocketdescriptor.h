//
// Created by lauderdice on 05.03.22.
//

#ifndef EPOLL_SERVER_EPOLL_TCPSOCKETDESCRIPTOR_H
#define EPOLL_SERVER_EPOLL_TCPSOCKETDESCRIPTOR_H

#include "epoll_filedescriptor.h"
#include "tcp_socket.h"
#include "epoll_tcpsingleconnection.h"

class EpollTCPSocketDescriptor : public EpollFileDescriptor
{
public:
    EpollTCPSocketDescriptor(TCPSocket &tcpsocket, EpollSysUtil &e);
    ~EpollTCPSocketDescriptor();
    void handleEvent(uint32_t events);
    void accept_new_connection();

protected:
    TCPSocket &tcpSocket;

};



#endif //EPOLL_SERVER_EPOLL_TCPSOCKETDESCRIPTOR_H
