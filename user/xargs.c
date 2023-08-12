//
// Created by syp on 23-8-12.
//
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
    if(argc < 2){
        fprintf(2,"usage: xargs command [arguments ...]\n");
        exit(1);
    }
    int ret;



    int ptr = 0;

    char *m_argv[argc];
    for(int i = 1; i < argc; ++i){
        m_argv[i-1]=argv[i];
    }

    char str[100];
    while(read(0,str+ptr,1)){
        ptr++;
        if(ptr==100){
            fprintf(2,"receive_buf is full");
            exit(1);
        }
    }

    int len = ptr;
    ptr = 0;
    while(ptr < len){
        int i;
        for(i = ptr;i<len&&str[i]!='\n'; i++);
        str[i] = '\0';
        m_argv[argc - 1] = str + ptr;
        ptr = i+1;
        ret = fork();
        if(!ret){
            exec(m_argv[0], m_argv);
        }
        while(wait(0)!=-1);
    }

    exit(0);
}

