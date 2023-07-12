#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/param.h"

#define MAXLINES 32

int main(int argc, char* argv[]){
    char *order = "echo";
    char buf[MAXARG * MAXLINES], *param[MAXARG], *p;
    int paramI = 0;
    if (argc > 1) {
        if (argc + 1 > MAXARG) {
            fprintf(2, "xargs: too many ars\n");
            exit(1);
        }
        order = argv[1];
        for (int i = 1; i < argc; i++) {
            param[paramI++] = argv[i];
        }
    } 
    else {
        param[paramI++] = order;
    }
    p = buf;
    while(1){
        int ret;
        while(1){
            ret = read(0, p, 1);
            if(ret == 0 || *p == '\n'){
                break;
            }
            ++p;
        }
        *p = 0;
        param[paramI] = buf;
        if(fork() == 0){
            exec(order, param);
            exit(0);
        }
        else{
            p = buf;
            wait((int*)0);
        }
        if(ret == 0){
            break;
        }
    }
    exit(0);
}