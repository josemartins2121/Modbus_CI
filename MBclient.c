#include <string.h>
#include <stdio.h>
#include "modbusAP.h"

int main(int argc, char const *argv[])
{   
    int num_regs = 0;
    uint16_t data2[8] = { 1, 5, 3, 4, 5, 6, 7, 8 }; 

    num_regs = write_multiple_regs("127.0.0.1",502,0, 8, data2);
    printf("[MB client] Foram escritos %d registos\n",num_regs);
    return 0;
}


//invoca Mod BUS AP.h
//-c compila sem gerar executável 