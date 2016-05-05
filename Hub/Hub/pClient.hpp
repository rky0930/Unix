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
#include "MQueue.hpp"
#include "MThread.hpp"
#include <sys/ioctl.h>


#define BUF_LEN 128

using namespace std;
class pClient : public MThread {
public:
    ssize_t write(const char* msg, ssize_t msg_size);
    int open(int port);
    ssize_t read(char* &buffer);
    int close();
    int dispatch();
    int onMessage();
    int initialize(int p_client_fd);
    int getSocket();
    void print_client_fd();
private:
    struct sockaddr_in server_addr, client_addr;
    int server_fd, client_fd;
    //server_fd, client_fd : 각 소켓 번호
    socklen_t len;
    bool client_close_flag;

};

#endif /* pClient_hpp */
