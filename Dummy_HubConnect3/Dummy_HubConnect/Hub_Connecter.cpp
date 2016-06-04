//
//  HubConnect.cpp
//  Dummy_HubConnect
//
//  Created by YOOGYOUNGYOON on 2016. 5. 4..
//  Copyright © 2016년 YOOGYOUNGYOON. All rights reserved.
//

#include "Hub_Connecter.hpp"


Hub_Connecter::Hub_Connecter(int p_src_proc_id, int p_src_proc_no){
    src_proc_id = p_src_proc_id;
    src_proc_no = p_src_proc_no;
}

int Hub_Connecter::open(const char* hub_ip, const int hub_port) {
    

    memset(&hub_sock, 0, sizeof(hub_sock));
    
    hub_sock.sin_family = AF_INET;
    hub_sock.sin_addr.s_addr = inet_addr(hub_ip); //IP ADDR
    hub_sock.sin_port = htons(hub_port); // PORT
    hub_fd = socket(AF_INET, SOCK_STREAM, 0);

    
    if(::connect(hub_fd, (struct sockaddr *)&hub_sock, sizeof(hub_sock))<0) {
        cerr<<"open::Hub Connect Error!"<<endl;
        return 1;
    }
    
    // register
    // data write..
    write(REGISTER_MESSAGE, PROCID_HUB, 0);

    
    
    return 0;
}

int Hub_Connecter::write(int msg_type, int dst_proc_id, int dst_proc_no, const char* pData,unsigned int data_len) {
    
    if(hub_fd <= 0) {
        cerr<<"write::Hub Connect Error!"<<endl;
        return 1;
    }
    
    HUB_PACKET_HEADER hub_packet_header;
    
    hub_packet_header.msg_type    = msg_type ;
    hub_packet_header.src_proc_id = src_proc_id  ;
    hub_packet_header.src_proc_no = src_proc_no  ;
    hub_packet_header.dst_proc_id = dst_proc_id  ;
    hub_packet_header.dst_proc_no = dst_proc_no  ;
    hub_packet_header.data_len    = data_len     ;
    
    cout<<"msg_type   : "<<(int)hub_packet_header.msg_type<<endl;
    cout<<"src_proc_id: "<<(int)hub_packet_header.src_proc_id<<endl;
    cout<<"src_proc_no: "<<(int)hub_packet_header.src_proc_no<<endl;
    cout<<"dst_proc_id: "<<(int)hub_packet_header.dst_proc_id<<endl;
    cout<<"dst_proc_no: "<<(int)hub_packet_header.dst_proc_no<<endl;
    cout<<"data_len   : "<<(int)hub_packet_header.data_len<<endl;
    
    char packet[MAX_HUB_PACKET_DATA_LEN];
    ssize_t  packet_len = 0;

    memcpy(packet, &hub_packet_header, HUB_PACKET_HEADER_LEN);
    packet_len += HUB_PACKET_HEADER_LEN;
    
    if(msg_type == DATA_MESSAGE) {
        memcpy(packet+HUB_PACKET_HEADER_LEN, pData, data_len);
        packet_len += data_len;
        cout<<pData<<endl;
    }
    ssize_t nWrite = ::write(hub_fd, packet, packet_len);
    if(nWrite < 0) {
        cerr<<"Hub_Connecter: write error!"<<endl;
        return 1;
    }
    
    return 0;
}
ssize_t Hub_Connecter::read(char* &buffer) {
    ssize_t msg_size;
    unsigned int nData;
    if(ioctl(hub_fd, FIONREAD, &nData)<0) {
        cerr<<"pClient Read: ioctl error"<<endl;
    }
    buffer = new char[nData];
    
    msg_size = ::read(hub_fd, buffer, nData);
    if(msg_size<=0){
        return -1;
    }
    return msg_size;

}


