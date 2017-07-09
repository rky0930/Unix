#ifndef Hub_Interface_h
#define Hub_Interface_h

// PROCESS ID
#define PROCID_HUB  0x00
#define PROCID_TF   0x01
#define PROCID_ML   0x02
#define PROCID_JK   0x03
#define PROCID_JV   0x04

// MESSAGE TYPE
#define     DATA_MESSAGE 0x00
#define REGISTER_MESSAGE 0x01

#define TO_DISTRIBUTER 0x01
#define TO_CLIENT      0x02

typedef struct {
    unsigned char proc_id;
    unsigned char proc_no;
}HUB_REGISTER;

typedef struct {
    unsigned char msg_type    ;
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

#endif /* Hub_Interface_h */
