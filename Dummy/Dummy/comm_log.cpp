//
//  comm_log.cpp
//  manager
//
//  Created by YOOGYOUNGYOON on 2016. 2. 13..
//  Copyright © 2016년 YOOGYOUNGYOON. All rights reserved.
//

#include "comm_log.hpp"


int comm_log::comm_log_init(string log_file_name, string c_date)
{
    
    c_log_date = c_date;
    log_file_name=log_file_name+".out."+c_log_date+".log";
    
    log_file = getenv("LOG_PATH");
    if (log_file == NULL) {
        cerr<<"Not found log variable. "<<endl;
    }else{
        log_location = string(log_file);
        log_location = log_location+log_file_name;
        cout<<log_location<<endl;
    }
    if (fd.is_open()) {
        fd.close();
    }
    fd.open(log_location);
    
    return 0;
}

int comm_log::write_log(int level, string msg)
{
    
    fd<<msg<<endl;

    return 0;
}

string comm_log::getCurTime() {
    
    time_t c_time = time(NULL);
    struct tm *today;
    today = localtime(&c_time);
    string year, month, day, hour;
    string c_date = "";

    year = to_string(today->tm_year + 1900);
    if(today->tm_mon<10) {
        month = "0"+to_string(today->tm_mon+1);
    }else{
        month = to_string(today->tm_mon+1);
    }
    if(today->tm_mday<10) {
        day = "0"+to_string(today->tm_mday);
    }else{
        day = to_string(today->tm_mday);
    }
    if(today->tm_hour<10) {
        hour = "0"+to_string(today->tm_hour);
    }else{
        hour = to_string(today->tm_hour);
    }
    
    c_date = year+month+day+hour;
    
    return c_date;
}

string comm_log::getLogTime() {
    return c_log_date;
}

