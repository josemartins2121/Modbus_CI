#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdio.h>
#include <arpa/inet.h>




#define MYPORT 22222
#define BUF_LEN 256


int main (void) {
    int sock, len;
    // sock -> file descriptor 
    struct sockaddr_in serv;// endereço da internt 
    socklen_t addlen = sizeof(serv);
    char buf[BUF_LEN];


    // para modbus definir dois APDU vetores com o máximo de 256 bytes 
    // uint 8 ou uint 16

    sock = socket(PF_INET, SOCK_STREAM, 0);
    
    serv.sin_family = AF_INET; //família protocolar
    serv.sin_port = htons(MYPORT);// htons número inteiro da arquitetura global para o formato da internet, mesmo alinhamento de bits
    inet_aton("127.0.0.1",&serv.sin_addr); //converter decimal para binário 4 bytes ASCII to network 


    connect(sock, (struct sockaddr *) &serv, addlen); // retorna com erro 
    // são feitos para todos os tipos de sockets, não só para a internet 
    // razão do cast 
    while( buf[0] != 'X')
    {
        printf("String a enviar: ");
        scanf("%s", buf);
        len = send(sock, buf, strlen(buf)+1, 0);
        len = recv(sock,buf,BUF_LEN,0);
        printf("String recebida: %s\n",buf);
    }

    shutdown(sock,SHUT_RDWR);
}
