//
//  HubConnect.hpp
//  Dummy_HubConnect
//
//  Created by YOOGYOUNGYOON on 2016. 5. 4..
//  Copyright © 2016년 YOOGYOUNGYOON. All rights reserved.
//

#ifndef HubConnect_hpp
#define HubConnect_hpp

#include "Hub_Interface.h"
#include <iostream>
#include <arpa/inet.h>
#include <string.h>
#include <sys/ioctl.h>

using namespace std;

class Hub_Connecter {
    
public:
    int open(const char* hub_ip, const int port);
    int write(int msg_type, int dst_proc_id, int dst_proc_no, const char* pData=NULL, unsigned int data_len=0);
    ssize_t read(char* &buffer);
    Hub_Connecter(int dst_proc_id, int dst_proc_no);
protected:
    //packet
    unsigned char src_proc_id;
    unsigned char src_proc_no;
    
    //socket
    struct sockaddr_in hub_sock;
    int hub_fd;
    
};




#endif /* HubConnect_hpp */
