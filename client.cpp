//
// Created by hlr on 2022/1/8.
//

#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include "src/utils.h"

#define BUFFER_SIZE 1024

int main() {
    int sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    errif(sock_fd == -1, "socket create error");

    struct sockaddr_in server_addr;
    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_addr.sin_port = htons(8888);
    server_addr.sin_family = AF_INET;

    errif(connect(sock_fd, (sockaddr*)&server_addr, sizeof(server_addr)) == -1, "socket connect error");

    while(true) {
        char buf[BUFFER_SIZE];
        bzero(&buf, sizeof(buf));
        scanf("%s", buf);
        ssize_t write_bytes = write(sock_fd, buf, sizeof(buf));
        printf("Log::sizeof(buf): %d\n", sizeof(buf));
        if(write_bytes == -1) {
            printf("socket already disconnected, can't write any more!\n");
            break;
        }
        bzero(&buf, sizeof(buf));
        ssize_t read_bytes = read(sock_fd, buf, sizeof(buf));
        if(read_bytes > 0) {
            printf("message from server: %s\n", buf);
        } else if(read_bytes == 0) {
            printf("server socket disconnected!\n");
            break;
        } else if(read_bytes == -1) {
            close(sock_fd);
            errif(true, "socket read error");
        }
    }

    close(sock_fd);
    return 0;
}