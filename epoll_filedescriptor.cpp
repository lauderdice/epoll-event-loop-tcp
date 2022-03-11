#include <iostream>
#include "epoll_filedescriptor.h"

EpollFileDescriptor::EpollFileDescriptor(int fd, EpollSysUtil &e)
    : fd(fd), epollInstance(e)
{
}

EpollFileDescriptor::~EpollFileDescriptor()
{
}

void EpollFileDescriptor::registerFd(uint32_t events)
{
     epollInstance.registerFd(*this, events);
}

void EpollFileDescriptor::unregisterFd()
{
//    std:: cout << "Unregistering something!!!";
     epollInstance.unregisterFd(*this);
}
