//
// Created by hlr on 2022/1/9.
//

#ifndef WEB_SERVER_ACCEPTOR_H
#define WEB_SERVER_ACCEPTOR_H

#include <functional>

class EventLoop;
class Socket;
class InetAddress;
class Channel;
class Acceptor {
private:
    EventLoop *loop_;
    Socket *sock_;
    InetAddress *addr;
    Channel *accept_channel_;

    std::function<void(Socket*)> new_connection_callback_;
public:
    explicit Acceptor(EventLoop *loop);
    ~Acceptor();
    void AcceptConnection();

    void set_new_connection_callback(std::function<void(Socket*)>);
    std::function<void(Socket*)> new_connection_callback();
};


#endif //WEB_SERVER_ACCEPTOR_H
