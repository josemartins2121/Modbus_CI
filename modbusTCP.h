#ifndef TCP_DEFINE 1
#define TCP_DEFINE 1

#define BUF_LEN 256
extern int send_modbus_request(char* server_add, int port,char* APDU,int APDUlen,char* APDU_R);

#endif


