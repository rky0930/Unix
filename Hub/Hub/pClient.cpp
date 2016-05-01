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
    client_close_flag = false;
    return 0;
    
}
int pClient::getSocket() {
    return client_close_flag ? 0:client_fd;
}

ssize_t pClient::read(char* &buffer) {
    ssize_t msg_size;
    unsigned int nData;
    if(ioctl(client_fd, FIONREAD, &nData)<0) {
        cerr<<"pClient Read: ioctl error"<<endl;
    }
    buffer = new char[nData];

    msg_size = ::read(client_fd, buffer, nData);
    if(msg_size<=0){
        close();
        return -1;
    }
    return msg_size;
}

int pClient::write(char* msg){
    char buffer[BUF_LEN];
    memset(buffer, 0x00, sizeof(buffer));
    strcpy(buffer, msg);
    ::write(client_fd, buffer, sizeof(buffer));
    return 0;
};

int pClient::close() {
    cout<<"pClient Close!"<<endl;
    if(!client_close_flag) {
        cout<<"client_close_flag:"<<client_close_flag<<endl;
        client_close_flag = true;
        shutdown(client_fd, SHUT_RDWR);
        ::close(client_fd);
    }
    return 0;
}

void pClient::print_client_fd() {
    cout<<"pClient: "<<client_fd<<endl;
}


