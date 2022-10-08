#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "modbusTCP.h"
#include "modbusAP.h"


int send_modbus_request(char* server_add, int port,char* APDU,uint16_t APDUlen,char* APDU_R){
  int sock = assert_connection(server_add, port);
  if(sock < 0) return -1;
  
  int static transaction_id = 0;
  transaction_id++;

  //uint16_t total_length = APDUlen + TCP_HEADER_LENGTH;
  uint8_t MBAP[TCP_HEADER_LENGTH];
  //printf("Apdu-len: %d \n",(APDUlen>>8));  

  bufi16_TCP(MBAP, transaction_id);
  bufi16_TCP(&MBAP[2], TCP_MODBUS_PROTOCOL);
  bufi16_TCP(&MBAP[4],APDUlen + 1);
  MBAP[6] = (uint8_t) 0x01; // 0xFF don´t care for server !!!!!! 0x01 may work 
  
  if(send(sock, MBAP, TCP_HEADER_LENGTH, 0)<0){
    return -1;
  }
  if(send(sock, APDU, APDUlen, 0) < 0){
    return -1;
  }

  //print_char_array_TCP("Header-TCP: ",MBAP,TCP_HEADER_LENGTH); // send MBAP header
  //print_char_array_TCP("APDU: ",APDU,APDUlen); // send APDU 

  if(recv(sock, MBAP,TCP_HEADER_LENGTH,0)<0){
    return -1;
  }

  //print_char_array_TCP("Received header: ",MBAP,TCP_HEADER_LENGTH);

  int len;
  len = (MBAP[4]<<8)+MBAP[5];
  
  if(recv(sock, APDU_R,len-1,0)<0 ){
    return -1;
  }

  //print_char_array_TCP("Received data: ",APDU_R,len-1);
  close(sock);
  return 0;
}


int assert_connection(char* server_add, int port){
  int sock, len,error;
  struct sockaddr_in serv;
  socklen_t addlen = sizeof(serv);
 
  sock = socket(PF_INET, SOCK_STREAM, 0);
  if(sock <0)return -1;
    
  serv.sin_family = AF_INET; 
  serv.sin_port = htons(port);
  inet_aton(server_add,&serv.sin_addr);
  error = connect(sock, (struct sockaddr *) &serv, addlen);
  if (error  < 0) {
    //printf("Connect-error  , %d\n",error);
    return -1;
  }
  //printf("Socket conectado\n");
  
  return sock; 
}

void buff_code_TCP(char * buffer, char value) {
    buffer[0] = value;
}

void bufi16_TCP(char * buffer, uint16_t value) {
    //value = htons(value);
    //memcpy(buffer, &value, sizeof(value)); 
    buffer[0] = (uint8_t)value >> 8;
    buffer[1] = (uint8_t)(value & 0xFF);

}

void print_char_array_TCP(char * name, char * array,int len) {
    printf(name);
    for (int i = 0; i < len; i++) {
        printf("%d ", array[i]);
    
    }
    printf("\n");
}

