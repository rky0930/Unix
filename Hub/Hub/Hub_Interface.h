//
//  Hub_Interface.h
//  Hub
//
//  Created by YOOGYOUNGYOON on 2016. 5. 4..
//  Copyright © 2016년 YOOGYOUNGYOON. All rights reserved.
//

#ifndef Hub_Interface_h
#define Hub_Interface_h

#define PROCID_HUB  0x00
#define PROCID_TF   0x01
#define PROCID_ML   0x02
#define PROCID_JK   0x03
#define PROCID_JV   0x04

#define TO_DISTRIBUTER 0
#define TO_CLIENT      1

typedef struct {
    unsigned char proc_id;
    unsigned char proc_no;
}HUB_REGISTER;

typedef struct {
    unsigned char src_proc_id;
    unsigned char src_proc_no;
    unsigned char dst_proc_id;
    unsigned char dst_proc_no;
    unsigned int  data_len   ;
} HUB_PACKET_HEADER;

typedef struct {
    HUB_PACKET_HEADER header;
    char* data;
} HUB_PACKET;

#define HUB_REGISTER_LEN       sizeof(HUB_REGISTER)
#define HUB_PACKET_HEADER_LEN  sizeof(HUB_PACKET_HEADER)
#define HUB_PAKCET_LEN         sizeof(HUB_PACKET)
#define MAX_HUB_PACKET_LEN     0x1000



#endif /* Hub_Interface_h */
