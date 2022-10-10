#include <string.h>
#include <stdio.h>
#include "modbusAP.h"

int main(int argc, char const *argv[])
{   
    int num_regs = 0;
    uint16_t data2[] = { 1, 5, 3, 4, 5, 6, 7, 8, 10 ,12 }; 

    num_regs = write_multiple_regs("127.0.0.1",502,0, 0, data2);
    printf("[MB client] Foram escritos %d registos\n",num_regs);


    num_regs = read_h_regs("127.0.0.1",502,0, 2, data2);
    printf("[MB client] Foram lidos %d registos\n",num_regs);
    for (int i = 0; i < 2; i++) {
        printf("%d ", data2[i]);
    
    }
    printf("\n");
    return 0;
}


//invoca Mod BUS AP.h
//-c compila sem gerar executável 