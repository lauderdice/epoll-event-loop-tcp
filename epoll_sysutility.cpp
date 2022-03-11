

#include <unistd.h>
#include <sys/epoll.h>
#include <cstring>
#include <stdexcept>
#include <iostream>
#include "epoll_sysutility.h"
#include "epoll_filedescriptor.h"

EpollSysUtil::EpollSysUtil()
{
    epollFd = epoll_create1(0);
    if (epollFd == -1) {
        throw std::runtime_error(std::string("epoll_create1: ") + std::strerror(errno));
    }
}

EpollSysUtil::~EpollSysUtil()
{
    close(epollFd);
}

void EpollSysUtil::registerFd(EpollFileDescriptor &fd, uint32_t events)
{
    struct epoll_event ev;
    memset(&ev, 0, sizeof(ev));

    ev.events = events;
    ev.data.ptr = &fd;

    if (epoll_ctl(epollFd, EPOLL_CTL_ADD, fd.fd, &ev) == -1) {
        throw std::runtime_error(std::string("epoll_ctl: ") + std::strerror(errno));
    }
}

void EpollSysUtil::unregisterFd(EpollFileDescriptor &fd)
{
    struct epoll_event ev;
    memset(&ev, 0, sizeof(ev));

    ev.events = 0;
    ev.data.ptr = &fd;
//    std::cout << "Unregistering file descriptor " << fd;
    if (epoll_ctl(epollFd, EPOLL_CTL_DEL, fd.fd, &ev) == -1) {
        throw std::runtime_error(std::string("epoll_ctl: ") + std::strerror(errno));
    }
}

void EpollSysUtil::waitAndHandleEvents()
{
    struct epoll_event events[EPOLL_MAX_EVENTS];
    int i, n;
    n = epoll_wait(epollFd, events, EPOLL_MAX_EVENTS, -1);
    if (n == -1) {
        throw std::runtime_error(std::string("epoll_wait: ") + std::strerror(errno));
    }
    for (i = 0; i < n; i++) {
        EpollFileDescriptor *fd = (EpollFileDescriptor*)(events[i].data.ptr);
        fd->handleEvent(events[i].events);
    }
}
