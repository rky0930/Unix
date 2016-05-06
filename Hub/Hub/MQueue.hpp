//
//  MQueue.hpp
//  Hub
//
//  Created by YOOGYOUNGYOON on 2016. 4. 25..
//  Copyright © 2016년 YOOGYOUNGYOON. All rights reserved.
//

#ifndef MQueue_hpp
#define MQueue_hpp

#include <stdio.h>
#include <string.h>

typedef struct {
    int msg_tpye;
    ssize_t msg_size;
    unsigned long msg_pointer;
} MESSAGE;

class MQueue {
public:
    MQueue(int q_size=1000);
    int getMessage(MESSAGE &msg);
    int putMessage(MESSAGE &msg);
    void putRawMessage(ssize_t msg_size, char* &msg);
    ssize_t getRawMessage(char* &msg);

protected:
    MESSAGE* msg_queue;
    int q_size;
    int q_count;
    int q_head;
    int q_tail;
};

#endif /* MQueue_hpp */
