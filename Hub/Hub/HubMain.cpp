//
//  HubMain.cpp
//  Hub
//
//  Created by YOOGYOUNGYOON on 2016. 4. 9..
//  Copyright © 2016년 YOOGYOUNGYOON. All rights reserved.
//
#include <iostream>
#include "HubMain.hpp"

void HubMain::init() {
    //log file location
    c_log.comm_log_init("manager", c_log.getCurTime());
    
    //process check interval
    p_check_interval = 10;
    
    //config file reading
    char* env_file;
    string cfg_location;
    ifstream fd;
    
    env_file = getenv("TEST_CFG");
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

    
    
}

void HubMain::process() {
    
    std::cout << "Hello, World!\n";

    
}



int main(int argc, const char * argv[]) {
    // insert code here...
    
    std::cout << "Hello, World!\n";
    return 0;
}
