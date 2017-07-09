//
//  manager.hpp
//  manager
//
//  Created by YOOGYOUNGYOON on 2016. 2. 12..
//  Copyright © 2016년 YOOGYOUNGYOON. All rights reserved.
//

#ifndef _MANAGER_H_
#define _MANAGER_H_

#include "../Common/Common.h"

#define MANAGE_MAX_NUM 1000

using namespace std;

typedef struct {
    int pid;
    vector<string> arg;
}Proc_manage_info;

class ManagerMain {
    
public:
    
    //ManagerMain();
    //~ManagerMain();
    
    int initialize();
    int process();
    int stop();
    
protected:
    string log_file_name;
    time_t last_p_check_time;
    int p_check_interval;
};


extern ManagerMain g_app;
extern comm_log c_log;

#endif /* _MANAGER_H_ */
