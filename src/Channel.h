//
// Created by hlr on 2022/1/8.
//

#ifndef WEB_SERVER_CHANNEL_H
#define WEB_SERVER_CHANNEL_H

#include <sys/epoll.h>
#include <functional>

class EventLoop;
class Epoll;
class Channel {
private:
    EventLoop *event_loop_;
    int fd_;
    uint32_t events_;
    uint32_t now_events_;
    bool in_epoll_;
    std::function<void()> callback_;

public:
    Channel(EventLoop *loop, int fd);
    ~Channel();

    void HandleEvent();
    void EnableReading();

    int fd();
    uint32_t events();
    uint32_t now_events();
    bool in_epoll();
    void set_in_epoll();

    void set_now_events(uint32_t);
    void set_callback(std::function<void()>);


};


#endif //WEB_SERVER_CHANNEL_H
