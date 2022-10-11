#include <string.h>
#include <stdio.h>
#include "modbusAP.h"

int main(int argc, char const *argv[])
{   
  /*   int num_regs = 0;
    uint16_t data2[] = { 1, 5, 3, 4, 5, 6, 7, 8, 10 ,12 }; 

    num_regs = write_multiple_regs("127.0.0.1",502,0, 0, data2);
    printf("[MB client] Foram escritos %d registos\n",num_regs);


    num_regs = read_h_regs("127.0.0.1",502,0, 2, data2);
    printf("[MB client] Foram lidos %d registos\n",num_regs);
    for (int i = 0; i < 2; i++) {
        printf("%d ", data2[i]);
    
    }
    printf("\n");
    return 0; */

    int i ;
    uint16_t data[5];


    i=read_h_regs("127.0.0.1",502,3, 1, &data[0]);
    if(i!= 0)return i;
    i=read_h_regs("127.0.0.1",502,5, 1, &data[0]);
    if(i!= 0)return i;
    i = write_multiple_regs("127.0.0.1",502,6, 1, &data[0]);
    if(i!=0)return i;


    i = read_h_regs("127.0.0.1",502,4, 1, &data[1]);
    if(i!= 0)return i;

    i = read_h_regs("127.0.0.1",502,9, 1, &data[2]);
    if(i!= 0)return i;


    data[3] = 55;
    i = write_multiple_regs("127.0.0.1",502,0, 1, &data[3]);
    if(i!=0)return i;
    //printf("%d",data[2]);

    if ( data[2] == 0){
        data[4] = (uint16_t)5555;
    }
    else data[4] = data[0] + data[1];
    //printf("%d",data[4]);

    i = write_multiple_regs("127.0.0.1",502,1, 1, &data[4]);
    if(i!= 0)return i;
    /* i = write_multiple_regs("10.227.113.1",502,2, 1, &data[4]);
    if(i!= 0)return i; */


    return 0;
 
}
