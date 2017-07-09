//
//  main.cpp
//  Dummy
//
//  Created by YOOGYOUNGYOON on 2016. 5. 4..
//  Copyright © 2016년 YOOGYOUNGYOON. All rights reserved.
//

#include "../Common/Common.h"

int main(int argc, const char * argv[]) {
    comm_log c_log;
    string p_name;
    string log_message; 
    if(argc != 3) {
        cerr<<"argc != 2"<<endl;
        cerr<<"<<Usage>> ./Dummy process_name log_message"<<endl;        
        exit(1);     
    }

    p_name= string(argv[1]);
    log_message= string(argv[2]);
    c_log.comm_log_init(p_name, c_log.getCurTime());

    while (1) {
        sleep(5);
        if(c_log.getCurTime()!=c_log.getLogTime()) {
            c_log.comm_log_init(p_name, c_log.getCurTime());
        }
        c_log.write_log(1,log_message);
    }
    
    return 0;
}
