//
//  main.cpp
//  Dummy_HubConnect
//
//  Created by YOOGYOUNGYOON on 2016. 5. 4..
//  Copyright © 2016년 YOOGYOUNGYOON. All rights reserved.
//

#include <iostream>
#include "comm_log.hpp"
#include "Hub_Connecter.hpp"

int main(int argc, const char * argv[]) {
    comm_log c_log;
    string p_name;
    if(argc == 2) {
        p_name= string(argv[1]);
        c_log.comm_log_init(p_name, c_log.getCurTime());
    }
    
    
    Hub_Connecter g_hub(PROCID_TF, 3);
    
    if(g_hub.open("0.0.0.0", 20001)){
        cerr<<"main: open error!"<<endl;
        exit(1);
    }
    while (1) {
        try {
            sleep(1);
            if(c_log.getCurTime()!=c_log.getLogTime()) {
                c_log.comm_log_init(p_name, c_log.getCurTime());
            }
            c_log.write_log(1,p_name);
            
            char test[101];
            strcpy(test, "HEY JK3 im TF3 ! :D");
            g_hub.write(DATA_MESSAGE, PROCID_JK, 3, test, 101);
            
            char* msg = NULL;
            ssize_t msg_size = g_hub.read(msg);
            
            HUB_PACKET_HEADER hub_packet_header;
            memset(&hub_packet_header, 0, HUB_PACKET_HEADER_LEN);
            memcpy(&hub_packet_header, msg, HUB_PACKET_HEADER_LEN);
            if((msg_size>0                   &&
                msg_size<MAX_HUB_PACKET_LEN) ||
               (hub_packet_header.data_len>0 &&
                hub_packet_header.data_len<MAX_HUB_PACKET_DATA_LEN)
               )
            {
                char message[MAX_HUB_PACKET_DATA_LEN];
                memset(message, 0, MAX_HUB_PACKET_DATA_LEN);
                memcpy(message, msg+HUB_PACKET_HEADER_LEN, hub_packet_header.data_len);
                cout<<"message from hub(msg_size="<<msg_size<<"):"<<message<<endl;
            }
        }catch (int e) {
            cout<<"error:"<<e<<endl;
        }
     }
    
    return 0;
}
