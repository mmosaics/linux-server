//
// Created by hlr on 2022/1/8.
//

#include "InetAddress.h"
#include <string.h>

InetAddress::InetAddress(): addr_len_(sizeof(addr_))  {
    bzero(&addr_, sizeof(addr_));
}

InetAddress::InetAddress(const char *ip, uint16_t port) {
    bzero(&addr_, sizeof(addr_));
    addr_.sin_family = AF_INET;
    addr_.sin_addr.s_addr = inet_addr(ip);
    addr_.sin_port = htons(port);
    addr_len_ = sizeof(addr_);
}

InetAddress::~InetAddress() {}