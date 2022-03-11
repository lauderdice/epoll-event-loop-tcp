//
// This class representing the Epoll instance
// is based on the template project of Efficient Software course on CTU
//
#ifndef EPOLLINSTANCE_H
#define EPOLLINSTANCE_H

#include <stdint.h>

#define EPOLL_MAX_EVENTS 64

class EpollFileDescriptor;

class EpollSysUtil
{
public:
    EpollSysUtil();
    ~EpollSysUtil();
    void registerFd(EpollFileDescriptor &fd, uint32_t events);
    void unregisterFd(EpollFileDescriptor &fd);
    void waitAndHandleEvents();
private:
    int epollFd;
};

#endif // EPOLLINSTANCE_H
