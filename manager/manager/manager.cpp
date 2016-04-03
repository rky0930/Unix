//
//  manager.cpp
//  manager
//
//  Created by YOOGYOUNGYOON on 2016. 2. 12..
//  Copyright © 2016년 YOOGYOUNGYOON. All rights reserved.
//

#include "manager.hpp"

ManagerMain g_app;
mymaps map;
comm_log c_log;


int ManagerMain::initialize()
{
    cout<<"initialize"<<endl;
    
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
    

    //fork and setid()
    int nPid = fork();
    if(nPid<0) {
        exit(EXIT_FAILURE);
    }else if (nPid){
        exit(EXIT_SUCCESS);
    }else {
        if(setsid() < 0) {
            exit(EXIT_FAILURE);
        }
    }
    nPid = fork();  //두번째 포크는 왜하는거지...??
    if(nPid<0) {
        exit(EXIT_FAILURE);
    }else if (nPid){
        exit(EXIT_SUCCESS);
    }
 
    return 0;
    
}
int ManagerMain::process()
{
    list<Proc_manage_info> p_list;
    cout<<"process"<<endl;
    
    
    //Made manger process list
    string config_name = "";
    string config_value = "";
    for (int i=0;i<map.getMaxCnt(); i+=2) {
        
        config_name   = map.getByIndex(i).key;
        config_value  = map.getByIndex(i).value;
        cout<<config_name<<": "<<config_value<<endl;
        
        for (int j=1;j<atoi(map.get(config_name+"_COUNT").c_str())+1; j++) {
            Proc_manage_info p_info;
            p_info.pid = 0;
            p_info.arg.push_back("./"+config_value);
            p_info.arg.push_back( config_value+to_string(j));
            p_list.push_back(p_info);
        }
    }

    
    while (1) {
    
        sleep(1);
        time_t c_time = time(NULL);
        if(c_time > last_p_check_time + p_check_interval) {
            last_p_check_time=c_time;
            if(c_log.getCurTime()!=c_log.getLogTime()) {
                c_log.comm_log_init("manager", c_log.getCurTime());
            }
            
            // make child process
            
            c_log.write_log(1, "manager_wait");
            list<Proc_manage_info>::iterator itr;
            cout<<"-----"<<endl;
            for (itr = p_list.begin(); itr!=p_list.end(); itr++) {
                Proc_manage_info &info  = (Proc_manage_info&) *itr;
                cout<<info.pid<<" "<<info.arg.at(0)<<" "<<info.arg.at(1)<<endl;
                
                if (info.pid==0) {
                    int nPid_c = fork();
                    if(nPid_c<0) {
                        exit(EXIT_FAILURE);
                    }else if (nPid_c){
                        info.pid = nPid_c;
                        
                    }else {
                        char* arg[3];
                        arg[0] = strdup(info.arg.at(0).c_str());
                        arg[1] = strdup(info.arg.at(1).c_str());
                        arg[2] = NULL;
                        execvp(info.arg.at(0).c_str(),arg);
                        exit(0);
                    }
                }else{
                    if(waitpid(info.pid, NULL, WNOHANG)) {
                        info.pid = 0;
                    }
                }
            }
//            break;
        }
    }
    return 0 ;
}

//정리해보기
//1. .cfg 환경변수로 위치파악
//2. 설정파일에서 관리해야할 프로세스확인
//3. manager 부모pid 1로만듬.
//4. fork로프로세스생성
//  4-1. 부모 프로세스는 관리를 위해 죽지않음. 포크할때얻은자식프로세스pid를 info.pid에 저장
//  4-2. 자식프로세스는 execvp로 관리해야할프로세스실행시킴 자식프로세스는다이
//5.리스트에저장된pid를waitpid로 주기적으로 확인하며 죽은프로세스면 info.pid를 0으로만듬
//6.info.pid가 0인 프로세스는 4번으로넘어가서 기동  모드


int ManagerMain::stop()
{
    exit(EXIT_SUCCESS);
    return 0;
}


int main(int argc, const char * argv[]) {
    cout<<"main"<<endl;
    
    if(g_app.initialize()) {
        cerr<<"Initialize Error!"<<endl;
        exit(EXIT_SUCCESS);
    };
    g_app.process();
    g_app.stop();
    
    return 0;
}