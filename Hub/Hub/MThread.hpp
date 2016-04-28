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

using namespace std; 

class MThread {
public:
    bool run(int nStackSize);
protected:
    static void* runThread(void* pMe);
    virtual void process();
    virtual void print_client_fd();

protected:
    pthread_t       _hThread;
    pthread_cond_t  _hEvent;
    pthread_mutex_t _hMutex;
};

#endif /* MThread_hpp */
