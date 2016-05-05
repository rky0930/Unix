//
//  comm_log.hpp
//  manager
//
//  Created by YOOGYOUNGYOON on 2016. 2. 13..
//  Copyright © 2016년 YOOGYOUNGYOON. All rights reserved.
//

#ifndef comm_log_hpp
#define comm_log_hpp

#include <iostream>
#include <string>
#include <fstream>


using namespace std;

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


#endif /* comm_log_hpp */
