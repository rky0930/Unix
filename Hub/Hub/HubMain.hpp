//
//  HubMain.hpp
//  Hub
//
//  Created by YOOGYOUNGYOON on 2016. 4. 9..
//  Copyright © 2016년 YOOGYOUNGYOON. All rights reserved.
//

#ifndef HubMain_hpp
#define HubMain_hpp

#include <stdio.h>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <vector>
#include <list>

#include "comm_log.hpp"
#include "map.hpp"
#include "pClient.hpp"

class HubMain {
public:
    int initialize();
    int process();
    string getProcessName(){
        return process_name;
    };
    int stop();
    
protected:
    string log_file_name;
    time_t last_p_check_time;
    int p_check_interval;
    string process_name = "hub";
    
};

extern mymaps map;
extern HubMain g_app;
extern comm_log c_log;


#endif /* HubMain_hpp */
