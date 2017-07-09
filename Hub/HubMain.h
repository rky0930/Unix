//
//  HubMain.h
//  Hub
//
//  Created by YOOGYOUNGYOON on 2016. 4. 9..
//  Copyright © 2016년 YOOGYOUNGYOON. All rights reserved.
//

#ifndef _HUBMAIN_H_
#define _HUBMAIN_H_

#include "../Common/Common.h"
#include "pClient.h"
#include "MQueue.h"
#include "Hub_Interface.h"

class HubMain {
public:
    int initialize();
    int process();
    int stop();
    int ServerListen();
    int ClientAccept();
    string getProcessName(){
        return process_name;
    };
    list<pClient*> & getClientList();
protected:
    string log_file_name;
    time_t last_p_check_time;
    int p_check_interval;
    string process_name = "hub";
    
    
    // Network programming related Variables. 
    int max_fd;
    int server_fd;  // server socket file descripter
    int port_num;  // 컨피그 파일에서 받도록 처리할 것.

    
    list<pClient*> client_list;
};

extern HubMain g_app;
extern comm_log c_log;


#endif /* _HUBMAIN_H_ */
