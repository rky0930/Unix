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

void pClient::setProcInfo(unsigned char p_proc_id, unsigned char p_proc_no) {
    proc_id = p_proc_id;
    proc_no = p_proc_no;
}

unsigned char pClient::getProcId(){
    return proc_id;
}

unsigned char pClient::getProcNo(){
    return proc_no;
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

ssize_t pClient::write(const char* msg, ssize_t msg_size){
    return ::write(client_fd, msg, msg_size);
};

//int pClient::SendToOtherClient(char* &buffer) {
//    queue.putMessage(msg); 
//}

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

