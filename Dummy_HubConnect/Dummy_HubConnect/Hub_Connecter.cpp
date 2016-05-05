//
//  HubConnect.cpp
//  Dummy_HubConnect
//
//  Created by YOOGYOUNGYOON on 2016. 5. 4..
//  Copyright © 2016년 YOOGYOUNGYOON. All rights reserved.
//

#include "Hub_Connecter.hpp"


Hub_Connecter::Hub_Connecter(unsigned char p_src_proc_id, unsigned char p_src_proc_no){
    src_proc_id = p_src_proc_id;
    src_proc_no = p_src_proc_no;
}

int Hub_Connecter::open(unsigned char proc_id, unsigned char proc_no, const char* hub_ip, const int hub_port) {
    
    cout<<hub_ip<<endl;
    cout<<hub_port<<endl;
    
    memset(&hub_sock, 0, sizeof(hub_sock));
    
    HUB_REGISTER reg;
    reg.proc_id = proc_id;
    reg.proc_no = proc_no;
    

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
    
    return 0;
}

int Hub_Connecter::write(const char* pData, unsigned int data_len, unsigned char dst_proc_id, unsigned char dst_proc_no) {
    
    if(hub_fd <= 0) {
        cerr<<"write::Hub Connect Error!"<<endl;
        return 1;
    }
    
    HUB_PACKET_HEADER hub_packet_header;
    
    hub_packet_header.src_proc_id = '1';
    hub_packet_header.src_proc_no = '1';
    hub_packet_header.dst_proc_id = '1';
    hub_packet_header.dst_proc_no = '1';
    hub_packet_header.data_len    = data_len   ;
    
    char packet[MAX_HUB_PACKET_LEN];
    ssize_t  packet_len = 0;

    memcpy(packet, &hub_packet_header, HUB_PACKET_HEADER_LEN);
    packet_len += HUB_PACKET_HEADER_LEN;
    
    memcpy(packet+HUB_PACKET_HEADER_LEN, pData, data_len);
    packet_len += data_len;
    cout<<pData<<endl;
    ssize_t nWrite = ::write(hub_fd, packet, packet_len);
    if(nWrite < 0) {
        cerr<<"Hub_Connecter: write error!"<<endl;
        return 1;
    }
    return 0;
}

