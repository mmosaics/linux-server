//
// Created by hlr on 2022/1/8.
//

#ifndef WEB_SERVER_SOCKET_H
#define WEB_SERVER_SOCKET_H

#include "InetAddress.h"

class Socket {
private:
    int fd_;

public:
    Socket();
    explicit Socket(int);
    ~Socket();

    void Bind(InetAddress*);
    void Listen();
    void NonBlocking();

    int Accept(InetAddress*);

    int fd();
};


#endif //WEB_SERVER_SOCKET_H
