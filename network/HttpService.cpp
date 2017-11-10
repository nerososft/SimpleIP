//
// Created by neroyang on 2017/11/8.
//

#include <iostream>
#include <pthread.h>
#include <string.h>
#include <zconf.h>
#include <netinet/in.h>
#include "HttpService.h"
#include "../Go.h"

namespace OpenIP{
    void HttpService::init() {

    }
    char* appendCharToCharArray(char* array, char a)
    {
        size_t len = strlen(array);

        char* ret = new char[len+2];

        strcpy(ret, array);
        ret[len] = a;
        ret[len+1] = '\0';

        return ret;
    }
    char* appendCharsToCharArray(char* array, char* a)
    {

        for(int i = 0;i<strlen(a);i++) {
            array = appendCharToCharArray(array,a[i]);
        }
        return array;
    }
    bool isRunning  = false;
    void *thread_run(void *arg) {
        struct sockaddr_in addr;
        memset(&addr, 0, sizeof(addr));
        int fd;
        addr.sin_family = AF_INET;
        addr.sin_port = htons(8081);
        addr.sin_addr.s_addr = INADDR_ANY;
        if((fd = socket(AF_INET, SOCK_STREAM, 0))==-1)
        {
            std::cerr<<"Unable to Open the Socket"<<std::endl;
            isRunning = false;
            return NULL;
        }
        if (bind(fd, (struct sockaddr*)(&addr), sizeof(addr)) != 0)
        {
            std::cerr<<"Unable to bind the Socket"<<std::endl;
            isRunning = false;
            return NULL;
        }
        if (listen(fd, 50) == -1)
        {
            std::cerr<<"Unable to listen the Socket"<<std::endl;
            isRunning = false;
            return NULL;
        }
        while(true){
            sockaddr client_addr;
            unsigned int nLength;
            int fdc = accept(fd, &client_addr, &nLength);
            if (fdc == -1){
                std::cerr<<"Unable to Connect with the client"<<std::endl;
                return NULL;
            } else{
                char *request = new char[1000];
                memset(request, 0, 1000);
                read(fdc, request, 1000);
                //std::cout<<request<<std::endl;


                char* buf = "HTTP/1.1 200 OK\r\nServer: OpenIP GO HTTP Service BY NeroYang"
                        "\r\nContent-Type: text/json;charset=utf-8\r\n\r\n"
                        "{map:[";
                for(int i = 0;i<19;i++){
                    buf = appendCharToCharArray(buf,'[');
                    for(int j = 0;j<19;j++){
                        if(map[i][j]==0){
                            buf = appendCharToCharArray(buf,'0');
                        }else if(map[i][j]==1){
                            buf = appendCharToCharArray(buf,'1');
                        }else if(map[i][j]==-1){
                            buf = appendCharToCharArray(buf,'-');
                            buf = appendCharToCharArray(buf,'1');
                        }

                        if(j!=18){
                            buf = appendCharToCharArray(buf,',');
                        }
                    }
                    buf = appendCharToCharArray(buf,']');
                    if(i!=18){
                        buf = appendCharToCharArray(buf,',');
                    }
                }
                buf = appendCharToCharArray(buf,']');

                buf = appendCharsToCharArray(buf,",qi:[],yingxiang:[]}");

                write(fdc, buf, strlen(buf));
                close(fdc);
                delete[] request;
            }
        }
    }

    void HttpService::child_thread() {
        pthread_t t;
        pthread_attr_t attr;
        if (pthread_attr_init(&attr) != 0)
            std::cerr << "Unable to launch a thread\n";
        if(pthread_create(&t, &attr, thread_run, NULL) != 0)
            std::cerr << "Unable to launch a thread\n";
        if(pthread_attr_destroy(&attr) != 0)
            std::cerr << "Unable to launch a thread\n";
        if(pthread_detach(t) != 0)
            std::cerr << "Unable to launch a thread\n";
    }

    void HttpService::start() {

    }


    void HttpService::stop() {

    }
}