#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>

#include "modbusTCP.h"
#include "modbusAP.h"


int send_modbus_request(char* server_add, int port,char* APDU,int APDUlen,char* APDU_R){
  int sock = assert_connection(server_add, port);
  if(sock < 0) return -1;
  
  int static transaction_id = 0;
  transaction_id++;

  //uint16_t total_length = APDUlen + TCP_HEADER_LENGTH;
  char * header_buffer = (char * ) malloc(sizeof(char) * TCP_HEADER_LENGTH);
    
  bufi16_TCP(header_buffer, transaction_id);
  bufi16_TCP(&header_buffer[2], TCP_MODBUS_PROTOCOL);
  bufi16_TCP(&header_buffer[4], APDUlen + 1);
  buff_code_TCP(&header_buffer[6], 0x01); // 0xFF don´t care for server !!!!!! 0x01 may work 
  
  send(sock, header_buffer, TCP_HEADER_LENGTH, 0);
  send(sock, APDU, APDUlen, 0);


  print_char_array_TCP("Header-TCP",header_buffer,TCP_HEADER_LENGTH);
  print_char_array_TCP("APDU",APDU,APDUlen);

  free(header_buffer);
  shutdown(sock,SHUT_RDWR);
  return 0;
}


int assert_connection(char* server_add, int port){
  int sock, len,error;
  struct sockaddr_in serv;
  socklen_t addlen = sizeof(serv);
 
  sock = socket(PF_INET, SOCK_STREAM, 0);
    
  serv.sin_family = AF_INET; 
  serv.sin_port = htons(port);
  inet_aton(server_add,&serv.sin_addr);
  error = connect(sock, (struct sockaddr *) &serv, addlen);
  if (error  < 0) {
    printf("Connect-error  , %d\n",error);
    return -1;
  }
  printf("Socket conectado\n");
  
  return sock; 
}

void buff_code_TCP(char * buffer, char value) {
    buffer[0] = value;
}

void bufi16_TCP(char * buffer, uint16_t value) {
    //value = htons(value);
    //memcpy(buffer, &value, sizeof(value)); 
    buffer[0] = (uint8_t)value >> 8;
    buffer[1] = (uint8_t)(value & 0xF);

}

void print_char_array_TCP(char * name, char * array,int len) {
    printf(name);
    for (int i = 0; i < len; i++) {
        printf("%02x ", array[i]);
    
    }
    printf("\n");
}

