//
//  HubMain.cpp
//  Hub
//
//  Created by YOOGYOUNGYOON on 2016. 4. 9..
//  Copyright © 2016년 YOOGYOUNGYOON. All rights reserved.
//
#include <iostream>
#include "HubMain.hpp"


mymaps map;
HubMain g_app;
comm_log c_log;

int HubMain::initialize() {
    //log file location
    c_log.comm_log_init(g_app.getProcessName(), c_log.getCurTime());
    
    //process check interval
    p_check_interval = 10;
    
    //config file reading
    char* env_file;
    string cfg_location;
    ifstream fd;
    
    env_file = getenv("PROCESS_CFG");
    if (env_file == NULL) {
        cerr<<"Not found env variable. "<<endl;
    }else{
        cfg_location = string(env_file);
        cout<<"env: "<<env_file<<endl;
    }
    
    
    fd.open (cfg_location);
    
    string line;
    string word;
    string a, key, value;
    if(fd.is_open()){
        while (getline(fd, line)) {
            for (int i =0; i<line.size(); i++) {
                a=line.at(i);
                if (a=="#") break;
                if (a==":") {
                    key=line.substr(0,i-1);
                    value = line.substr(i+2, line.size());
                    break;
                }
            }
            map.insert(key, value);
        }
    }else{
        cerr<<"file is not exist!"<<endl;
    }
    fd.close();

    
    return 0;
}

int HubMain::process() {
    
    std::cout << "HubMain::process\n";

    
    // Client Class
    pClient client;
    
    struct sockaddr_in server_addr, client_addr;
    
    int server_fd, client_fd;
    //server_fd, client_fd : 각 소켓 번호
    int msg_size;
    char temp[20];
    socklen_t len;
    int port_num =20002;
    


    if((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {// 소켓 생성
        printf("Server : Can't open stream socket\n");
        exit(0);
    }
    memset(&server_addr, 0x00, sizeof(server_addr));
    //server_Addr 을 NULL로 초기화
    
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(port_num);
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
    while(1)
    {
        client_fd = ::accept(server_fd, (struct sockaddr *)&client_addr, &len);
        if(client_fd < 0)
        {
            printf("Server: accept failed.\n");
            exit(0);
        }
        inet_ntop(AF_INET, &client_addr.sin_addr.s_addr, temp, sizeof(temp));

        client.initialize(client_fd);

        printf("Server : %s client connected.\n", temp);

        char buffer[BUF_LEN];
        memset(buffer, 0x00, sizeof(buffer));
        len = sizeof(client_addr);
        msg_size = ::read(client_fd, buffer, 1024);
        cout<<"buffer_read: "<<buffer<<endl;
        client.write(buffer);
    }
    
   return 0;
    
}

int HubMain::stop() {
    c_log.write_log(10,"Hub Main Stop");
    return 0;
}




int main(int argc, const char * argv[]) {

    if(g_app.initialize()) {
        cerr<<"Initialize Error!"<<endl;
        exit(EXIT_SUCCESS);
    };
    g_app.process();
    g_app.stop();
    

    
    return 0;
}
