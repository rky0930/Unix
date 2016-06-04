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
#include "Hub_Interface.h"
#include "MQueue.hpp"



using namespace std; 

class MThread {
public:
    bool run(int nStackSize);
    void stop();
    void postMessage(ssize_t msg_size, unsigned long msg_pointer);
protected:
    static void* runThread(void* pMe);
    virtual void process();
    virtual int close();
    virtual ssize_t write(const char* msg, ssize_t msg_size);
    
    virtual void setProcInfo(unsigned char proc_id, unsigned char proc_no);
    virtual unsigned char getProcId();
    virtual unsigned char getProcNo();
    
protected:
    pthread_t       _hThread;
    pthread_cond_t  _hEvent;
    pthread_mutex_t _hMutex;
    int thread_stop_flag  = false;  // 임시 Thread 정지 처리(추후 메시지 기반으로 정지되도록 수정 요망.
    
    MQueue mqueue;
    
};

#endif /* MThread_hpp */
