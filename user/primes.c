//
// Created by syp on 23-8-12.
//
#include "../kernel/types.h"
#include "../kernel/stat.h"
#include "../user/user.h"

void pipeline(int* pi){
    //fprintf(1,"begin<%d>\n",getpid());
    close(pi[1]);
    int a;
    int ret = read(pi[0],&a,4);
    if(ret == 0){
        exit(0);
    }
    fprintf(1,"prime %d\n",a);

    int p[2];
    pipe(p);

    ret = fork();
    if(!ret){
        pipeline(p);
    }
    close(p[0]);

    int n;
    while(read(pi[0],&n,4)){
        if(n%a){
            write(p[1],&n,4);
        }
    }
    close(p[1]);
    close(pi[0]);
    while(wait(0)!=-1);
    //fprintf(1,"end<%d>\n",getpid());
    exit(0);
}

int main(int argc, char *argv[])
{
    if(argc != 1){
        fprintf(2,"usage: primes\n");
        exit(1);
    }

    int p[2];
    int ret;
    pipe(p);

    ret = fork();
    if(ret != 0){
        pipeline(p);
    }
    close(p[0]);

    int a = 2;
    fprintf(1,"prime %d\n",a);
    for(int i = 3; i <= 35; ++i){
        if(i%a){
            ret = write(p[1],&i, 4);
        }
    }
    close(p[0]);
    close(p[1]);
    while(wait(0)!=-1);//if not inside wait to while, syscall wait did not work correctly.
    exit(0);
}