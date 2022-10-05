#include <string.h>
#include <stdio.h>
#include "modbusAP.h"

int main(int argc, char const *argv[])
{
    uint16_t data2[] = { 1, 2, 3, 4, 5, 6, 7, 8 }; 
    write_multiple_regs("127.0.0.1",502,0, 8, data2);
    return 0;
}


//invoca Mod BUS AP.h
//-c compila sem gerar executável 