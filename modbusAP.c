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
    if (n_r > MAX_REG)return -1;

    uint16_t bytes = 2 * n_r;
    size_t buff_len = 6 +  bytes;
    char * buff = (char*) malloc(sizeof(char)*buff_len);

    buff_code(buff, FC_WRITE_MULTIPLE_REGISTERS);
    bufi16(&buff[1],st_r);
    bufi16(&buff[3],n_r);
    buff[5] = (uint8_t) bytes;

    for(int i=0 ; i< n_r ;i++){
        bufi16(&buff[6+i*2],val[i]);
    } 
    
    print_char_array("Write multiple register APDU: ",buff,(int) buff_len);
    
    
    char * APDU_R = (char*) malloc(sizeof(char)*bytes);

    int aux;
    aux = send_modbus_request(server_add,port,buff,(uint16_t)buff_len,APDU_R);
    // need to send APDU len , but no need to send APDU_R lenght because we are the ones that requested 
    if (aux < 0) return -1;
    else {
        if ( (char) APDU_R[0] & 0x80){
            return -APDU_R[1];
        }
    }

    free(buff);
    printf("Foram escritos %d registos\n",(APDU_R[3]<<8)+APDU_R[4]);
    // return number of read register- ok or <0 - error 
    return ((APDU_R[3]<<8)+APDU_R[4]); 
}

// se tiver em baixo dá erro 
// se dá erro de 

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
        printf("%02x ", array[i]);
    
    }
    printf("\n");
}


// modbusAP.C write multiple register 
// modbus AP.h mesmo define, e protótipo
// include modbus TCP 
