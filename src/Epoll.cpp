//
// Created by hlr on 2022/1/8.
//

#include "Epoll.h"
#include <string.h>
#include <unistd.h>
#include "utils.h"

#define MAX_EVENTS 1000

Epoll::Epoll(): epfd_(-1), events_(nullptr) {
    epfd_ = epoll_create1(0);
    errif(epfd_ == -1, "epoll create error");
    events_ = new epoll_event[MAX_EVENTS];
    bzero(events_, sizeof(*events_) * MAX_EVENTS);
}

Epoll::~Epoll() {
    if(epfd_ != -1) {
        close(epfd_);
        epfd_ = -1;
    }
    delete [] events_;
}

void Epoll::Register(int fd, uint32_t op) {
    struct epoll_event ev;
    bzero(&ev, sizeof(ev));
    ev.data.fd = fd;
    ev.events = op;
    int ret = epoll_ctl(epfd_, EPOLL_CTL_ADD, fd, &ev);
    errif(ret == -1, "epoll register event error");
}

/*
std::vector<epoll_event> Epoll::Poll(int timeout) {
    std::vector<epoll_event> active_events;
    int nfds = epoll_wait(epfd_, events_, MAX_EVENTS, timeout);
    errif(nfds == -1, "epoll wait error");
    for(int i = 0; i < nfds; ++i) {
        active_events.push_back(events_[i]);
    }
    return active_events;
}
 */

std::vector<Channel *> Epoll::Poll(int timeout) {
    std::vector<Channel*> active_channels;
    int nfds = epoll_wait(epfd_, events_, MAX_EVENTS, timeout);
    errif(nfds == -1, "epoll wait error");
    for(int i = 0; i < nfds; ++i) {
        Channel *channel = static_cast<Channel*>(events_[i].data.ptr);
        channel->set_now_events(events_[i].events);
        active_channels.push_back(channel);
    }
    return active_channels;
}

void Epoll::UpdateChannel(Channel *channel) {
    int fd = channel->fd();
    struct epoll_event event{};
    event.events = channel->events();
    event.data.ptr = channel;
    if(!channel->in_epoll()) {
        //channel不在epoll中，那么需要添加
        int ret = epoll_ctl(epfd_, EPOLL_CTL_ADD, fd, &event);
        errif(ret == -1, "epoll add error");
        channel->set_in_epoll();
    } else {
        int ret = epoll_ctl(epfd_, EPOLL_CTL_MOD, fd, &event);
        errif(ret == -1, "epoll modify error");
    }

}
