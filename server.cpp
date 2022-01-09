#include "src/EventLoop.h"
#include "src/Server.h"

int main() {
    EventLoop *loop = new EventLoop();
    Server *server = new Server(loop);
    loop->Loop();
    return 0;
}
