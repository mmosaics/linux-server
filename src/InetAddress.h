//
// Created by hlr on 2022/1/8.
//

#ifndef WEB_SERVER_INETADDRESS_H
#define WEB_SERVER_INETADDRESS_H

#include <arpa/inet.h>

class InetAddress {
public:
    struct sockaddr_in addr_;
    socklen_t addr_len_;
    InetAddress();
    InetAddress(const char* ip, uint16_t port);
    ~InetAddress();

};


#endif //WEB_SERVER_INETADDRESS_H
