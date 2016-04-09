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
#include "comm_log.hpp"
#include "map.hpp"
#include <vector>
#include <list>

class HubMain {
public:
    void init();
    void process();
    
protected:
    string log_file_name;
    time_t last_p_check_time;
    int p_check_interval;
};

extern mymaps map;
extern HubMain g_app;
extern comm_log c_log;


#endif /* HubMain_hpp */
