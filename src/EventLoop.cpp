//
// Created by hlr on 2022/1/9.
//

#include "EventLoop.h"

EventLoop::EventLoop(): epoll_(nullptr), quit_(false) {
    epoll_ = new Epoll();
}

EventLoop::~EventLoop() {
    delete epoll_;
}

void EventLoop::Loop() {
    while(!quit_) {
        std::vector<Channel*> channel;
        channel = epoll_->Poll();
        for(auto it = channel.begin(); it != channel.end(); ++it) {
            (*it)->HandleEvent();
        }
    }
}

void EventLoop::UpdateChannel(Channel *ch) {
    epoll_->UpdateChannel(ch);
}