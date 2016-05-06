//
//  MThread.cpp
//  Hub
//
//  Created by YOOGYOUNGYOON on 2016. 4. 27..
//  Copyright © 2016년 YOOGYOUNGYOON. All rights reserved.
//

#include "MThread.hpp"

void* MThread::runThread(void* pMe) {
    ((MThread*)pMe)->process();
    pthread_exit(NULL);
    return NULL;
}


bool MThread::run(int nStackSize) {
    pthread_mutex_init(&_hMutex, NULL);
    pthread_cond_init(&_hEvent, NULL);
    pthread_attr_t *pAttr = NULL;
    pthread_attr_t threadAttr;
    if (nStackSize > 0) {
        pAttr = &(threadAttr);
        pthread_attr_init(pAttr);
        pthread_attr_setstacksize(pAttr, (size_t) nStackSize);
    }
    int nError = pthread_create(&_hThread, pAttr, runThread, this);
    if(nError) {
        strerror(nError);
        _hThread = 0;
        pthread_cond_destroy(&_hEvent);
        pthread_mutex_destroy(&_hMutex);
        if(pAttr) {
            pthread_attr_destroy(&threadAttr);
        }
        return false;
    }
    if(pAttr) pthread_attr_destroy(&threadAttr);
    
    return true;
}

void MThread::process(){
    while (true) {
        if(thread_stop_flag) {
            cout<<"MThread stop"<<endl;
            break;
        }
        MESSAGE msg;
        sleep(1);

        if(mqueue.getMessage(msg))
            continue;
        
        char* pData = (char*)msg.msg_pointer;
        if(msg.msg_tpye==TO_DISTRIBUTER) {
           // to distriuter
            cout<<endl;
        }else if(msg.msg_tpye==TO_CLIENT){
            ssize_t nWrite;
            nWrite = write(pData, msg.msg_size);
            if(nWrite <0){
                cerr<<"MThread: write error!"<<endl;
            }
        }

    }
}

void MThread::stop() {
    close();
    thread_stop_flag = true;
    if(_hThread){
        pthread_join(_hThread, 0);
        pthread_cond_destroy(&_hEvent);
        pthread_mutex_destroy(&_hMutex);
    }
    _hThread = 0;
}

void MThread::postMessage(int msg_tpye, ssize_t msg_size, unsigned long msg_pointer) {
    
    MESSAGE msg;
    msg.msg_tpye = msg_tpye;
    msg.msg_size = msg_size;
    msg.msg_pointer = msg_pointer;
    
    mqueue.putMessage(msg);
}

int   MThread::close() {
    cout<<"MThread close"<<endl;
    return 0;
}

ssize_t MThread::write(const char *msg, ssize_t msg_size) {
    cout<<"MThread write"<<endl;
    return 0;
}
