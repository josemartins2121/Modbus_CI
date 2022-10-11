#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include "modbusAP.h"
#include "modbusTCP.h"

void buff_code(char * buffer, char value);
void bufi16(char * buffer, uint16_t value);
void print_char_array(char * name, char * array, int len);


int write_multiple_regs(char* server_add, int port,uint16_t st_r,uint16_t n_r,uint16_t* val){
    
    if((server_add == NULL) | (port < 0) | (st_r <0)  | (n_r <0)| (val == NULL))return -1;
    if (n_r > MAX_WR_REGS)return -1;

    uint8_t APDU[MAX_APDU];
    uint16_t bytes = 2 * n_r;
    size_t APDU_len = 6 +  bytes;

    buff_code(APDU, FC_WRITE_MULTIPLE_REGISTERS);
    bufi16(&APDU[1],st_r);
    bufi16(&APDU[3],n_r);
    APDU[5] = (uint8_t) bytes;

    for(int i=0 ; i< n_r ;i++){
        APDU[6+i*2]=(uint8_t)(val[i]>> 8);
        APDU[6+1+i*2]=(uint8_t)(val[i] & 0xFF);
    } 
    
    //print_char_array("Write multiple register APDU: ",APDU,(int) APDU_len);
    
    int aux;
    aux = send_modbus_request(server_add,port,APDU,(uint16_t)APDU_len,APDU);
    // need to send APDU len , but no need to send APDU_R lenght because we are the ones that requested 
    if (aux < 0) return -1;

    if ( (uint8_t) APDU[0] & 0x80)return APDU[1];
    
    //printf("Foram escritos %d registos\n",(APDU[3]<<8)+APDU[4]);
    // return number of read register- ok or <0 - error 
    //return ((APDU[3]<<8)+APDU[4]); 
    return 0;
}

int read_h_regs(char* server_add, int port,uint16_t st_r,uint16_t n_r,uint16_t* val){
    
    if((server_add == NULL) | (port < 0) | (st_r <0)  | (n_r <0)| (val == NULL))return -1;
    if (n_r > MAX_RD_REGS)return -1;

    uint8_t APDU[MAX_APDU];
    size_t APDU_len = 5;

    buff_code(APDU, FC_READ_HOLDING_REGISTERS);
    bufi16(&APDU[1],st_r);
    bufi16(&APDU[3],n_r);

    //print_char_array("Read multiple register APDU: ",APDU,(int) APDU_len);
    
    int aux;
    aux = send_modbus_request(server_add,port,APDU,(uint16_t)APDU_len,APDU);
    // need to send APDU len , but no need to send APDU_R lenght because we are the ones that requested 
    if (aux < 0) return -1;

    if ( (uint8_t) APDU[0] & 0x80)return APDU[1];

    for( int i = 0; i < APDU[1]/2; i++) {
        val[i] = (uint16_t) (APDU[2+2*i]<<8) + (uint16_t)(APDU[3+2*i]);
    }
    //printf("Foram escritos %d registos\n",(APDU[1]/2));
    // return number of read register- ok or <0 - error 
    return 0;
    //return ((APDU[1]/2)); 
}



void buff_code(char * buffer, char value) {
    buffer[0] = value;
}

void bufi16(char * buffer, uint16_t value) {
    //value = htons(value);
    //memcpy(buffer, &value, sizeof(value)); 
    buffer[0] = (uint8_t)value >> 8;
    buffer[1] = (uint8_t)(value & 0xFF);

}

void print_char_array(char * name, char * array,int len) {
    printf(name);
    for (int i = 0; i < len; i++) {
        printf("%d ", array[i]);
    
    }
    printf("\n");
}


// modbusAP.C write multiple register 
// modbus AP.h mesmo define, e protótipo
// include modbus TCP 
