//
//  MThread.hpp
//  Hub
//
//  Created by YOOGYOUNGYOON on 2016. 4. 27..
//  Copyright © 2016년 YOOGYOUNGYOON. All rights reserved.
//

#ifndef MThread_hpp
#define MThread_hpp

#include <iostream>
#include <string.h>
#include <pthread.h>
#include "MQueue.hpp"

using namespace std; 

class MThread {
public:
    bool run(int nStackSize);
    void stop();
    void postMessage(int msg_tpye, ssize_t msg_size=0, unsigned long msg_pointer=0);
protected:
    static void* runThread(void* pMe);
    virtual void process();
    virtual void print_client_fd();
    virtual int close();

protected:
    pthread_t       _hThread;
    pthread_cond_t  _hEvent;
    pthread_mutex_t _hMutex;
    int thread_stop_flag  = false;  // 임시 Thread 정지 처리(추후 메시지 기반으로 정지되도록 수정 요망.
    
    MQueue mqueue;
    
};

#endif /* MThread_hpp */
