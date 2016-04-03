//
//  manager.hpp
//  manager
//
//  Created by YOOGYOUNGYOON on 2016. 2. 12..
//  Copyright © 2016년 YOOGYOUNGYOON. All rights reserved.
//

#ifndef manager_hpp
#define manager_hpp

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include "map.hpp"
#include "comm_log.hpp"
#include <vector>
#include <list>

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



extern mymaps map;
extern ManagerMain g_app;
extern comm_log c_log;

#endif /* manager_hpp */
