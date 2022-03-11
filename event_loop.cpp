//
// Created by lauderdice on 06.03.22.
//

#include <iostream>
#include <csignal>
#include "event_loop.h"
#include "helper_func.h"
void signal_callback_handler(int signum) {
    throw InterruptException(signum);
}
int EventLoop::run_forever(int iterations) {
    signal(SIGINT, signal_callback_handler);
    signal(SIGTERM, signal_callback_handler);
    try
    {
        if (iterations > 0){
            while   (iterations > 0){
                epoll.waitAndHandleEvents();
                iterations--;
            }
            return 0;
        } else {
            while (true){
                epoll.waitAndHandleEvents();
            }
        }
    }catch(InterruptException& e)
    {
        std::cout << "Terminating the event loop, received signal " << e.S << std::endl;
        return 0;
    }
}

EventLoop::EventLoop(EpollSysUtil &epollInstance) : epoll(epollInstance){
}

EventLoop::~EventLoop() = default;
