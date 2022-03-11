
#ifndef EPOLL_SERVER_EPOLL_TCPSINGLECONNECTION_H
#define EPOLL_SERVER_EPOLL_TCPSINGLECONNECTION_H


#include "epoll_filedescriptor.h"

class EpollTCPSingleConnectionDescriptor : EpollFileDescriptor{
public:
    EpollTCPSingleConnectionDescriptor(int fd, EpollSysUtil &e);
    ~EpollTCPSingleConnectionDescriptor();
    void handleEvent(uint32_t events) override;
    void set_nonblocking();

protected:
    int received_message_len = 0;
};


#endif //EPOLL_SERVER_EPOLL_TCPSINGLECONNECTION_H
