
#ifndef _HUBCONNECT_H_
#define _HUBCONNECT_H_

#include "../Common/Common.h"
#include "../Common/Common_network.h"
#include "Hub_Interface.h"

using namespace std;

class Hub_Connecter {
    
public:
    int open(const char* hub_ip, const int port);
    int write(int msg_type, int dst_proc_id, int dst_proc_no, const char* pData=NULL, unsigned int data_len=0);
    ssize_t read(char* &buffer);
    Hub_Connecter(int dst_proc_id, int dst_proc_no);
protected:
    //packet
    unsigned char src_proc_id;
    unsigned char src_proc_no;
    
    //socket
    struct sockaddr_in hub_sock;
    int hub_fd;
    
};

#endif // _HUBCONNECT_H_
