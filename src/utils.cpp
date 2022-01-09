//
// Created by hlr on 2022/1/8.
//


#include "utils.h"

void errif(bool condition, const char *errmsg) {
    if(condition) {
        perror(errmsg);
        exit(EXIT_FAILURE);
    }
}