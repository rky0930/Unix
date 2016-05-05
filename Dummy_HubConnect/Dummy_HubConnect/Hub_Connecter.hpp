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

using namespace std;

class Hub_Connecter {
    
public:
    int open(unsigned char proc_id, unsigned char proc_no, const char* hub_ip="0.0.0.0", const int port=20001);
    int write(const char* pData, unsigned int data_len, unsigned char dst_proc_id, unsigned char dst_proc_no);
    int read();
    Hub_Connecter(unsigned char dst_proc_id, unsigned char dst_proc_no);
protected:
    //packet
    unsigned char src_proc_id;
    unsigned char src_proc_no;
    
    //socket
    struct sockaddr_in hub_sock;
    int hub_fd;
    
};




#endif /* HubConnect_hpp */
