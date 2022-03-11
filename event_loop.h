//
// Created by lauderdice on 06.03.22.
//

#ifndef EPOLL_SERVER_EVENT_LOOP_H
#define EPOLL_SERVER_EVENT_LOOP_H


#include "epoll_sysutility.h"

class EventLoop {
public:
    EventLoop(EpollSysUtil &instance);
    ~EventLoop();
    int run_forever(int iterations);
private:
    EpollSysUtil& epoll;

};


#endif //EPOLL_SERVER_EVENT_LOOP_H
