cmake_minimum_required(VERSION 3.21)
project(web_server)

set(CMAKE_CXX_STANDARD 20)

add_executable(web_server server.cpp src/Epoll.cpp src/Epoll.h src/Socket.cpp src/Socket.h src/InetAddress.cpp src/InetAddress.h src/utils.h src/utils.cpp src/Channel.cpp src/Channel.h src/EventLoop.cpp src/EventLoop.h src/Server.cpp src/Server.h src/Acceptor.cpp src/Acceptor.h)

add_executable(client_test client.cpp src/utils.h src/utils.cpp)
