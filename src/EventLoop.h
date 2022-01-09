//
// Created by hlr on 2022/1/9.
//

#ifndef WEB_SERVER_EVENTLOOP_H
#define WEB_SERVER_EVENTLOOP_H

#include "Epoll.h"

class EventLoop {
private:
    Epoll *epoll_;
    bool quit_;

public:
    EventLoop();
    ~EventLoop();
    void Loop();
    void UpdateChannel(Channel*);

};


#endif //WEB_SERVER_EVENTLOOP_H
