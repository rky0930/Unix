//
//  pClient.cpp
//  Hub
//
//  Created by YOOGYOUNGYOON on 2016. 4. 10..
//  Copyright © 2016년 YOOGYOUNGYOON. All rights reserved.
//

#include "pClient.hpp"

int pClient::initialize(int p_client_fd) {
    client_fd = p_client_fd;

    return 0;
    
}
int pClient::getSocket() {
    return client_fd;
}

int pClient::write(char* msg){
    char buffer[BUF_LEN];
    memset(buffer, 0x00, sizeof(buffer));
    strcpy(buffer, msg);
    ::write(client_fd, buffer, sizeof(buffer));
    return 0;
};

int pClient::close() {
    
    ::close(server_fd);
    return 0;
}

void pClient::print_client_fd() {
    cout<<"pClient: "<<client_fd<<endl;
}


