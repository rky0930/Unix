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
    client.run(3);
    struct sockaddr_in server_addr, client_addr;
    
    int server_fd;
    //server_fd, client_fd : 각 소켓 번호
    int msg_size;
    char server_ip[20];
    socklen_t len;
    int port_num =20002;  // chage to get from config file.
    
    
    
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
    fd_set fds;
    int max_fd=0;
    int fds_arr[1000];
    fds_arr[max_fd] = server_fd;
    max_fd++;
    while(1)
    {
        FD_ZERO(&fds);
        for (int i=0;i<max_fd; i++) {
            FD_SET(fds_arr[i], &fds);
        }
        int state = ::select(fds_arr[max_fd-1]+1, &fds, NULL, NULL, NULL);
//        cout<<"state:"<<state<<endl;
        if (state<=0) {
            cout<<"select error occur!"<<endl;
        }else{
            if(FD_ISSET(server_fd, &fds)) {
                int client_fd=0;
                client_fd = accept(fds_arr[0], (struct sockaddr *)&client_addr, &len);
                if(client_fd < 0)
                {
                    printf("Server: accept failed.\n");
                    exit(0);
                }
                client.initialize(client_fd);
                fds_arr[max_fd]= client_fd;
                max_fd++;
            }
            for(int i=1;i<max_fd;i++){
                if(FD_ISSET(fds_arr[i],&fds)){
                    char buffer[BUF_LEN];
                    memset(buffer, 0x00, sizeof(buffer));
                    msg_size = ::read(fds_arr[i], buffer, 1024);
                    if(msg_size<=0) {
                        client.close();
                        break;
                    }
                    cout<<"R["<<fds_arr[i]<<"]: "<<buffer;
                }
            }
            
        }
//        cout<<server_fd<<" "<<fds_arr[max_fd-1]<<endl;
//        inet_ntop(AF_INET, &client_addr.sin_addr.s_addr, server_ip, sizeof(server_ip)); // IP 어드래스
//        printf("Server : %s client connected.\n", server_ip);
        
        
//        char buffer[BUF_LEN];
//        while(1){
//            memset(buffer, 0x00, sizeof(buffer));
//            len = sizeof(client_addr);
//            msg_size = ::read(client_fd, buffer, 1024);
//            if(msg_size<=0) {
//                client.close();
//                break;
//            }
//            cout<<"buffer_read: "<<buffer<<endl;
//            client.write(buffer);
//        }
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
