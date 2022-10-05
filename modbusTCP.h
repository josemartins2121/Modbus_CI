#ifndef TCP_DEFINE 

#define TCP_DEFINE 1
#define TCP_MODBUS_PROTOCOL 0
#define BUF_LEN 256
#define TCP_HEADER_LENGTH 7

extern int send_modbus_request(char* server_add, int port,char* APDU,uint16_t APDUlen,char* APDU_R);
extern int assert_connection(char* server_add, int port);
extern void buff_code_TCP(char * buffer, char value);
extern void bufi16_TCP(char * buffer, uint16_t value);
extern void print_char_array_TCP(char * name, char * array,int len); 


#endif


