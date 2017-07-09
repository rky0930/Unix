//
//  comm_log.hpp
//  manager
//
//  Created by YOOGYOUNGYOON on 2016. 2. 13..
//  Copyright © 2016년 YOOGYOUNGYOON. All rights reserved.
//

#ifndef _COMM_LOG_H_
#define _COMM_LOG_H_

#include "Common.h"


class comm_log {
public:
    int comm_log_init(string log_file_name, string c_date);
    int write_log(int level, string msg);
    string getCurTime();
    string getLogTime();
protected:
    int log_level;
    char* log_file;
    string log_location;
    string c_log_date;
    ofstream fd;
};


#endif // _COMM_LOG_H_
