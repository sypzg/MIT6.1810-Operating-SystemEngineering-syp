//
// Created by syp on 23-8-12.
//
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
    if(argc != 1){
        fprintf(2,"usage: pingpong\n");
        exit(1);
    }

    int p1[2];
    int p2[2];
    int ret;
    pipe(p1);
    pipe(p2);

    char buf;
    int pid;
    ret = fork();
    if(ret == 0){//child
        pid = getpid();
        ret = read(p1[0],&buf,1);
        fprintf(1,"%d: received ping\n",pid);
        write(p2[1]," ",1);
        exit(0);
    }else{
        pid = getpid();
        write(p1[1]," ",1);
        read(p2[0],&buf,1);
        fprintf(1,"%d: received pong\n",pid);
    }
    close(p1[0]);
    close(p1[1]);
    close(p2[0]);
    close(p2[1]);
    exit(0);
}