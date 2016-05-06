//
//  MQueue.cpp
//  Hub
//
//  Created by YOOGYOUNGYOON on 2016. 4. 25..
//  Copyright © 2016년 YOOGYOUNGYOON. All rights reserved.
//

#include "MQueue.hpp"
#include <iostream>
using namespace std;



MQueue::MQueue(int p_q_size) {
    q_size    = p_q_size;
    q_count   = 0;
    q_head    = 0;
    q_tail    = 0;
    msg_queue = new MESSAGE[q_size];
    memset(msg_queue, 0, sizeof(MESSAGE)*q_size);
    cout<<"q_size: "<<p_q_size<<endl;
}

int MQueue::getMessage(MESSAGE &msg) {
    if(q_count <= 0) {
        return 1;
    }
    if(q_head >= q_size) {
        q_head = 0;
    }
    memcpy(&msg, &(msg_queue[q_head]), sizeof(MESSAGE));

    q_count--;
    q_head++;

    return 0;
}

void MQueue::putRawMessage(ssize_t msg_size, char* &msg){
    MESSAGE tmp_msg;
    cout<<&tmp_msg<<endl;  //계속 변해야함
    tmp_msg.msg_pointer = (unsigned long)msg;
    tmp_msg.msg_size = msg_size;
    putMessage(tmp_msg);
}

ssize_t MQueue::getRawMessage(char* &msg){
    MESSAGE tmp_msg;
    getMessage(tmp_msg);
    memcpy(&msg, &(tmp_msg.msg_pointer), tmp_msg.msg_size);
    return tmp_msg.msg_size;
    
}

int MQueue::putMessage(MESSAGE &msg) {
    //mutex
    if(q_count == q_size) {
        //queue full!
        return 1;
    }
    if(q_tail >= q_size) {
        //queue cycle done. go back to start again.
        q_tail = 0;
    }
    memcpy(&(msg_queue[q_tail]), &msg, sizeof(MESSAGE));
    q_count++;
    q_tail++;
    return 0;
}