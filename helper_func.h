//
// Created by lauderdice on 06.03.22.
//

#ifndef EPOLL_SERVER_HELPER_FUNC_H
#define EPOLL_SERVER_HELPER_FUNC_H


#include <exception>

class InterruptException : public std::exception{
public:
    InterruptException(int s);
    int S;
};

#endif //EPOLL_SERVER_HELPER_FUNC_H
