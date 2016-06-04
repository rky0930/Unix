//
//  MThread.cpp
//  Hub
//
//  Created by YOOGYOUNGYOON on 2016. 4. 27..
//  Copyright © 2016년 YOOGYOUNGYOON. All rights reserved.
//

#include "MThread.hpp"
#include "HubMain.hpp"


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

        if(mqueue.getMessage(msg)){
            cout<<"no message"<<endl;
            continue;
        }
        cout<<"----"<<endl;
        
        char* pData = (char*)msg.msg_pointer;
        cout<<"process(): "<<pData<<endl;
        
        //패킷 해더 검출
        HUB_PACKET_HEADER hub_packet_header;
        memset(&hub_packet_header, 0, HUB_PACKET_HEADER_LEN);
        memcpy(&hub_packet_header, pData, HUB_PACKET_HEADER_LEN);
        cout<<(int)hub_packet_header.dst_proc_id<<", "<<(int)hub_packet_header.dst_proc_no<<endl;
        
        //데이터 메시지
        if(hub_packet_header.msg_type == DATA_MESSAGE)
        {
            // 자기 패킷인지 확인
            if(getProcId() == hub_packet_header.dst_proc_id &&
               getProcNo() == hub_packet_header.dst_proc_no    )
            {
                ssize_t nWrite;
                cout<<"1111"<<endl;
                nWrite = write(pData, msg.msg_size);
                if(nWrite <0)
                {
                    cerr<<"MThread: write error!"<<endl;
                }
                cout<<"2222"<<endl;
            }
            else
            {
                // 클라이언트 리스트 루프
                list<pClient*> & tmp_client_list = g_app.getClientList();
                list<pClient*>::iterator itr, itrPrev;
                for(itr = tmp_client_list.begin(); (itrPrev = itr) != tmp_client_list.end();itr++)
                {
                    pClient* tmp_client = *itr;
                    //목적 클라이언트 찾으면 포스트 해줌
                    if(tmp_client->getProcId() == hub_packet_header.dst_proc_id &&
                       tmp_client->getProcNo() == hub_packet_header.dst_proc_no    )
                    {
                        tmp_client->postMessage(msg.msg_size, (unsigned long)msg.msg_pointer);
                        break;
                    }
                }
            }
        // 등록 패킷
        }else if(hub_packet_header.msg_type == REGISTER_MESSAGE)
        {
            setProcInfo(hub_packet_header.src_proc_id, hub_packet_header.src_proc_no);
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

void MThread::postMessage(ssize_t msg_size, unsigned long msg_pointer) {
    cout<<"postMessage msg_size: "<<msg_size<<endl;
    char* tmp_msg = (char*)msg_pointer;
    mqueue.putRawMessage(msg_size, tmp_msg);
}

int   MThread::close() {
    cout<<"MThread close"<<endl;
    return 0;
}

ssize_t MThread::write(const char *msg, ssize_t msg_size) {
    cout<<"MThread write"<<endl;
    return 0;
}
void MThread::setProcInfo(unsigned char proc_id, unsigned char proc_no) {
    cout<<"MThread::setProcInfo()"<<endl;
}

unsigned char MThread::getProcId(){
    cout<<"MThread::getProcId()"<<endl;
    return -1;
}
unsigned char MThread::getProcNo(){
    cout<<"MThread::getProcNo()"<<endl;
    return -1;
}



