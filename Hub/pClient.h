//
//  pClient.hpp
//  Hub
//
//  Created by YOOGYOUNGYOON on 2016. 4. 10..
//  Copyright © 2016년 YOOGYOUNGYOON. All rights reserved.
//

#ifndef pClient_hpp
#define pClient_hpp

#include "../Common/Common.h"
#include "../Common/Common_network.h"

#include "MQueue.h"
#include "MThread.h"

#define BUF_LEN 128

class pClient : public MThread {
public:
    ssize_t write(const char* msg, ssize_t msg_size);
    int open(int port);
    ssize_t read(char* &buffer);
    int close();
    int dispatch();
    int onMessage();
    int initialize(int p_client_fd);
    
    // 프로세스 등록
    void setProcInfo(unsigned char proc_id, unsigned char proc_no);
    unsigned char getProcId();
    unsigned char getProcNo();
    
    int getSocket();
private:
    struct sockaddr_in server_addr, client_addr;
    int server_fd, client_fd;
    //server_fd, client_fd : 각 소켓 번호
    socklen_t len;
    bool client_close_flag;
    unsigned char proc_id;
    unsigned char proc_no;
};

#endif /* pClient_hpp */
