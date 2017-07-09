#ifndef _HUB_INTERFACE_H_
#define _HUB_INTERFACE_H_

// PROCESS ID
#define PROCID_HUB  0x0
#define PROCID_TF   0x1
#define PROCID_ML   0x2
#define PROCID_JK   0x3
#define PROCID_JV   0x4

// MESSAGE TYPE
#define     DATA_MESSAGE 0x0
#define REGISTER_MESSAGE 0x1

#define TO_DISTRIBUTER 0x1
#define TO_CLIENT      0x2

typedef struct {
    unsigned char proc_id;
    unsigned char proc_no;
}HUB_REGISTER;

typedef struct {
    unsigned char msg_type    ;  //
    unsigned char src_proc_id ;
    unsigned char src_proc_no ;
    unsigned char dst_proc_id ;
    unsigned char dst_proc_no ;
    unsigned int  data_len    ;
} HUB_PACKET_HEADER;

typedef struct {
    HUB_PACKET_HEADER header;
    char* data;
} HUB_PACKET;

#define HUB_PACKET_HEADER_LEN    sizeof(HUB_PACKET_HEADER)
#define MAX_HUB_PACKET_DATA_LEN  0x1000
#define MAX_HUB_PACKET_LEN       HUB_PACKET_HEADER_LEN+MAX_HUB_PACKET_DATA_LEN


#endif // _HUB_INTERFACE_H_ 
