
#ifndef _MQUEUE_H_
#define _MQUEUE_H_

#include "../Common/Common.h"

#define TO_OTHER_CLIENT 0x01
#define TO_MY_CLIENT    0x02

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

#endif // _MQUEUE_H_
