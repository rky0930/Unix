//
//  main.cpp
//  Dummy_HubConnect
//
//  Created by YOOGYOUNGYOON on 2016. 5. 4..
//  Copyright © 2016년 YOOGYOUNGYOON. All rights reserved.
//

#include <iostream>
#include "comm_log.hpp"
#include "Hub_Connecter.hpp"

int main(int argc, const char * argv[]) {
    comm_log c_log;
    string p_name;
    if(argc == 2) {
        p_name= string(argv[1]);
        c_log.comm_log_init(p_name, c_log.getCurTime());
    }
    
    
    Hub_Connecter g_hub(PROCID_TF, 3);
    
    if(g_hub.open("0.0.0.0", 20001)){
        cerr<<"main: open error!"<<endl;
        exit(1);
    }
    while (1) {
        sleep(1);
        if(c_log.getCurTime()!=c_log.getLogTime()) {
            c_log.comm_log_init(p_name, c_log.getCurTime());
        }
        c_log.write_log(1,p_name);
        
        char test[101];
        strcpy(test, "Correct message from Dummy! :D");
        g_hub.write(DATA_MESSAGE, PROCID_JV, 1, test, 101);

    }
    
    return 0;
}
