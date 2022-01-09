//
// Created by hlr on 2022/1/9.
//

#ifndef WEB_SERVER_SERVER_H
#define WEB_SERVER_SERVER_H

#include "EventLoop.h"
#include "Socket.h"
#include "Acceptor.h"

class Server {
private:
    EventLoop *loop_;
    Acceptor *acceptor;

public:
    explicit Server(EventLoop*);
    ~Server();

    static void HandleReadEvent(int);
    void NewConnection(Socket *serv_socket);


};


#endif //WEB_SERVER_SERVER_H
