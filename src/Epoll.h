//
// Created by hlr on 2022/1/8.
//

#ifndef WEB_SERVER_EPOLL_H
#define WEB_SERVER_EPOLL_H

#include <sys/epoll.h>
#include <vector>
#include "Channel.h"

class Epoll {
private:
    int epfd_;
    struct epoll_event *events_;

public:
    Epoll();
    ~Epoll();

    void Register(int fd, uint32_t op);
    //std::vector<epoll_event> Poll(int timeout = -1);
    std::vector<Channel*> Poll(int timeout = -1);
    void UpdateChannel(Channel *channel);


};


#endif //WEB_SERVER_EPOLL_H
