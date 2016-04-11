//
//  pClient.hpp
//  Hub
//
//  Created by YOOGYOUNGYOON on 2016. 4. 10..
//  Copyright © 2016년 YOOGYOUNGYOON. All rights reserved.
//

#ifndef pClient_hpp
#define pClient_hpp

#include <iostream>
#include "stdio.h"
#include "stdlib.h"
#include <string>
#include "time.h"
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define BUF_LEN 128

using namespace std;
class pClient {
public:
    int write(char* msg);//추후에 queue에서 데이터 가져와서 출력하도록 만듬.
    int open(int port);
    int read();
    int close();
    int dispatch();
    int onMessage();
    int initialize(int p_client_fd);
private:
    struct sockaddr_in server_addr, client_addr;
    char temp[20];
    int server_fd, client_fd;
    //server_fd, client_fd : 각 소켓 번호
    socklen_t len;

};

#endif /* pClient_hpp */
