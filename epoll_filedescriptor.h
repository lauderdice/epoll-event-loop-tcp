#ifndef EPOLLFD_H
#define EPOLLFD_H

#include <stdint.h>
#include "epoll_sysutility.h"

class EpollFileDescriptor
{
public:
    EpollFileDescriptor(int fd, EpollSysUtil &e);
    virtual ~EpollFileDescriptor();
    void registerFd(uint32_t events);
    void unregisterFd();
    virtual void handleEvent(uint32_t events) = 0;
protected:
    int fd;
    EpollSysUtil &epollInstance;
    friend class EpollInstance;
};

#endif // EPOLLFD_H
