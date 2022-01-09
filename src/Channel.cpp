//
// Created by hlr on 2022/1/8.
//

#include "Channel.h"
#include "Epoll.h"
#include "EventLoop.h"

Channel::Channel(EventLoop *loop, int fd):event_loop_(loop), fd_(fd), events_(0), now_events_(0), in_epoll_(false) {
}

Channel::~Channel() {
}


void Channel::EnableReading() {
    events_ = EPOLLIN | EPOLLET;
    event_loop_->UpdateChannel(this);
}

int Channel::fd() {
    return fd_;
}

uint32_t Channel::events() {
    return events_;
}

uint32_t Channel::now_events() {
    return now_events_;
}


void Channel::set_in_epoll() {
    in_epoll_ = true;
}

void Channel::set_now_events(uint32_t event) {
    now_events_ = event;
}

bool Channel::in_epoll() {
    return in_epoll_;
}

void Channel::set_callback(std::function<void()> callback) {
    callback_ = callback;
}

void Channel::HandleEvent() {
    callback_();
}
