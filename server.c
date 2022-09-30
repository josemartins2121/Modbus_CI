#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdio.h>


#define MYPORT 22222
#define BUF_LEN 256


int main(void) {
    int so, sd, len;
    //so->socket 
    struct sockaddr_in loc, rem;
    socklen_t addlen = sizeof(loc);
    char buf[BUF_LEN];

    so = socket(PF_INET, SOCK_STREAM, 0);
    loc.sin_family = AF_INET;
    loc.sin_port = htons(MYPORT);

    inet_aton("127.0.0.1",&loc.sin_addr);
    bind(so, (struct sockaddr *) &loc, addlen); 
    //obrigatório usar bind() , fazer com que o socket esteja associado obrigatoriamente à porta definida 
    listen(so, 2);//prepara o socket para receção e atribui fila de espera 

    sd=accept(so, (struct sockaddr *) &rem, &addlen);
    inet_ntoa(buf,rem.sin_addr);
    //imprimir porta que o cliente utilizou !! não o 22222
    printf("%s - %d\n",buf,ntohs(rem.sin_port));
    // função bloqueante, fica à espera até receber um pedido
    //rem -> endereço do cliente que se ligou 

    // socket de ligação e dos dados 
    // sccept retorna socket de dados 
    while(buf[0] != 'X') {
        len=recv(sd, buf, BUF_LEN, 0);
        printf("String recebida:(lend-%d) %s\n",len,buf);
        for (int i = 0; buf[i]!='\0'; i++) {
            if(buf[i] >= 'a' && buf[i] <= 'z') {
            buf[i] = buf[i] -32;
            }
        }

        len = send(sd,buf,strlen(buf)+1,0);
    }

    close(so);
}

