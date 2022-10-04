#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdio.h>
#include "modbusTCP.h"




int send_modbus_request(char* server_add, int port,char* APDU,int APDUlen,char* APDU_R){
    int sock, len;

    struct sockaddr_in serv;
    socklen_t addlen = sizeof(serv);
 
    sock = socket(PF_INET, SOCK_STREAM, 0);
    
    serv.sin_family = AF_INET; 
    serv.sin_port = htons(port);
    inet_aton(server_add,&serv.sin_addr);

    if (connect(sock, (struct sockaddr *) &serv, addlen) < 0) {
        printf("Connect-error\n");
        close(sock);
        return -1;
    }
    printf("Socket conectado\n");

  /*   len = send(sock,APDU,APDUlen,0);
    len = recv(sock,APDU_R,BUF_LEN,0);
 */
    close(sock);


    return 0;
}



//send modbus request
