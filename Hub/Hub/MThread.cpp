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
        sleep(3);
        print_client_fd();
    }
}

void MThread::print_client_fd() {
    cout<<"MThread"<<endl;
}