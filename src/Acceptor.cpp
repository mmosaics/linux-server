//
// Created by hlr on 2022/1/9.
//

#include "Acceptor.h"
#include "Socket.h"
#include "Channel.h"

Acceptor::Acceptor(EventLoop *loop): loop_(loop) {
    sock_ = new Socket();
    addr = new InetAddress("127.0.0.1", 8888);
    sock_->Bind(addr);
    sock_->Listen();
    sock_->NonBlocking();
    accept_channel_ = new Channel(loop_, sock_->fd());
    std::function<void()> cb = [this] { AcceptConnection(); };
    accept_channel_->set_callback(cb);
    accept_channel_->EnableReading();
}

Acceptor::~Acceptor() {
    delete sock_;
    delete addr;
    delete accept_channel_;
}

void Acceptor::AcceptConnection() {
    new_connection_callback_(sock_);
}

void Acceptor::set_new_connection_callback(std::function<void(Socket *)> cb) {
    new_connection_callback_ = cb;
}

std::function<void(Socket *)> Acceptor::new_connection_callback() {
    return new_connection_callback_;
}

