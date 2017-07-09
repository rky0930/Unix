#include "../Common/Common.h"
#include "Hub_Connecter.h"

int main(int argc, const char * argv[]) {

    comm_log c_log;
    string  p_name;
    int     p_num;
    int     p_num_sub;    
    const char*   h_ipaddr;
    int     h_port;
    
    if(argc == 6) {
        p_name    = string(argv[1]).c_str();
        p_num     = atoi(argv[2]);
        p_num_sub = atoi(argv[3]);
        h_ipaddr  = argv[4];
        h_port    = atoi(argv[5]);
        c_log.comm_log_init(p_name, c_log.getCurTime());
    }else{
        cerr<<"Usage: ./HubClinet <This Process name> <This Process number> <This Process sub-number> <Hub IP> <Hub Port>"<<endl;
        cerr<<"ex) ./HubClient HubClient1 1 1 0.0.0.0 20001"<<endl;

        return 1; 
    }
    
    
    Hub_Connecter g_hub(p_num, p_num_sub);  // 자신이 누구인지 선언 
    
    if(g_hub.open(h_ipaddr, h_port)){   //허브 주소 
        cerr<<"main: open error!"<<endl;
        exit(1);
    }
    while (1) {
        try {
            sleep(1);
            if(c_log.getCurTime()!=c_log.getLogTime()) {
                c_log.comm_log_init(p_name, c_log.getCurTime());
            }
            c_log.write_log(1,p_name);
            
            string data[3];
            for(int i=0; i<3; i++)
                cin>>data[i];
            
            int dest_p_num     = atoi(data[0].c_str());
            int dest_p_sub_num = atoi(data[1].c_str());
            string chat_msg = data[2]; 
            

            g_hub.write(DATA_MESSAGE, dest_p_num, dest_p_sub_num, chat_msg.c_str(), chat_msg.length());  // 메시지 보낼곳 
            
            char* msg = NULL;
            ssize_t msg_size = g_hub.read(msg);
            
            HUB_PACKET_HEADER hub_packet_header;
            memset(&hub_packet_header, 0, HUB_PACKET_HEADER_LEN);
            memcpy(&hub_packet_header, msg, HUB_PACKET_HEADER_LEN);
            if((msg_size>0                   &&
                msg_size<MAX_HUB_PACKET_LEN) ||
               (hub_packet_header.data_len>0 &&
                hub_packet_header.data_len<MAX_HUB_PACKET_DATA_LEN)
               )
            {
                char message[MAX_HUB_PACKET_DATA_LEN];
                memset(message, 0, MAX_HUB_PACKET_DATA_LEN);
                memcpy(message, msg+HUB_PACKET_HEADER_LEN, hub_packet_header.data_len);
                cout<<"message from hub(msg_size="<<msg_size<<"):"<<message<<endl;
            }
        }catch (int e) {
            cout<<"error:"<<e<<endl;
        }
     }
    
    return 0;
}
