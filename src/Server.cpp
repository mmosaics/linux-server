//
// Created by hlr on 2022/1/9.
//

#include "Server.h"
#include "string.h"
#include <stdio.h>
#include <unistd.h>
#include <cerrno>

#define READ_BUFFER 1024

Server::Server(EventLoop * loop):loop_(loop) {
    acceptor = new Acceptor(loop_);
    //std::function<void(Socket*)> cb = std::bind(&Server::NewConnection, this, std::placeholders::_1);
    std::function<void(Socket*)> cb = [this](auto && PH1) { NewConnection(std::forward<decltype(PH1)>(PH1)); };
    acceptor->set_new_connection_callback(cb);
}

Server::~Server() {
    delete acceptor;
}

void Server::HandleReadEvent(int sockfd) {
    char buf[READ_BUFFER];
    while(true) {
        bzero(buf, sizeof(buf));
        ssize_t bytes_read = read(sockfd, buf, sizeof(buf));
        if(bytes_read > 0) {
            printf("message from client fd %d: %s\n", sockfd, buf);
            write(sockfd, buf, sizeof(buf));
        } else if(bytes_read == -1 && errno == EINTR) {
            printf("continue reading");
            continue;
        } else if(bytes_read == -1 && ((errno == EAGAIN) || (errno == EWOULDBLOCK))) {
            printf("finish reading once, errno: %d\n", errno);
            break;
        } else if(bytes_read == 0) {
            printf("EOF, client fd %d disconnected\n", sockfd);
            close(sockfd);
            break;
        }
    }
}

void Server::NewConnection(Socket *serv_socket) {
    auto *client_addr = new InetAddress(); //memory leak
    auto *client_socket = new Socket(serv_socket->Accept(client_addr)); //memory leak
    printf("new client fd %d! IP: %s Port: %d\n", client_socket->fd(), inet_ntoa(client_addr->addr_.sin_addr), ntohs(client_addr->addr_.sin_port));
    client_socket->NonBlocking();
    auto *client_chan = new Channel(loop_, client_socket->fd());
    //std::function<void()> cb = std::bind(&Server::HandleReadEvent, this, client_socket->fd());
    std::function<void()> cb = [this, capture0 = client_socket->fd()] { HandleReadEvent(capture0); };
    client_chan->set_callback(cb);
    client_chan->EnableReading();
}

