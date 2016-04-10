//
//  pClient.cpp
//  Hub
//
//  Created by YOOGYOUNGYOON on 2016. 4. 10..
//  Copyright © 2016년 YOOGYOUNGYOON. All rights reserved.
//

#include "pClient.hpp"
int pClient::open(int port){
    if((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {// 소켓 생성
        printf("Server : Can't open stream socket\n");
        exit(0);
    }
    memset(&server_addr, 0x00, sizeof(server_addr));
    //server_Addr 을 NULL로 초기화
    
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(port);
    //server_addr 셋팅
    
    if(::bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) <0)
    {//bind() 호출
        printf("Server : Can't bind local address.\n");
        exit(0);
    }
    
    if(listen(server_fd, 5) < 0)
    {//소켓을 수동 대기모드로 설정
        printf("Server : Can't listening connect.\n");
        exit(0);
    }
    
    return 0;
}

int pClient::write(string msg){

    while(1)
    {
        client_fd = ::accept(server_fd, (struct sockaddr *)&client_addr, &len);
        if(client_fd < 0)
        {
            printf("Server: accept failed.\n");
            exit(0);
        }
        inet_ntop(AF_INET, &client_addr.sin_addr.s_addr, temp, sizeof(temp));
        printf("Server : %s client connected.\n", temp);
        char buffer[BUF_LEN];
        memset(buffer, 0x00, sizeof(buffer));
        printf("Server : wating connection request.\n");
        len = sizeof(client_addr);
        
        msg_size = ::read(client_fd, buffer, 1024); //echo server
        cout<<"b::"<<buffer<<endl;
        ::write(client_fd, buffer, msg_size);
        printf("Server : %s client closed.\n", temp);
    }
    
    return 0;

};

int pClient::read() {
    return 0;
};
int pClient::close() {
    
    ::close(server_fd);
    return 0;
}

