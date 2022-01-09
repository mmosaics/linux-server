//
// Created by hlr on 2022/1/8.
//

#include "Socket.h"
#include <sys/socket.h>
#include <unistd.h>
#include <fcntl.h>
#include "utils.h"

Socket::Socket() {
    fd_ = socket(AF_INET, SOCK_STREAM, 0);
    errif(fd_ == -1, "socket create error");
}

Socket::Socket(int fd): fd_(fd) {
    errif(fd == -1, "socket create error");
}

Socket::~Socket() {
    if(fd_ != -1) {
        close(fd_);
        fd_ = -1;
    }
}

void Socket::Bind(InetAddress *addr) {
    int ret = bind(fd_, (sockaddr*)&addr->addr_, addr->addr_len_);
    errif(ret == -1, "socket bind error");
}

void Socket::Listen() {
    int ret = listen(fd_, SOMAXCONN);
    errif(ret == -1, "socket listen error");
}

int Socket::Accept(InetAddress *addr) {
    int client_fd = accept(fd_, (sockaddr*)&addr->addr_, &addr->addr_len_);
    errif(client_fd == -1, "socket accept error");
    return client_fd;
}

void Socket::NonBlocking() {
    fcntl(fd_, F_SETFL, fcntl(fd_, F_GETFL) | O_NONBLOCK);
}

int Socket::fd() {
    return fd_;
}