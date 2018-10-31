#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <arpa/inet.h>

#define PORT 56300

int main(int argc, char ** argv) {

    /* Vytvorenie socketu */
    int socketClient;
    if((socketClient = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        perror("Chyba pri vytvarani socktu.\n");
        exit(-1);
    }

    /* Vytvorenie adresy */
    struct sockaddr_in addressServer;
    addressServer.sin_family = AF_INET; //Pripojenie zo siete
    addressServer.sin_port = htons(PORT); // Port
    addressServer.sin_addr.s_addr = inet_addr("127.0.0.1");

    /* Pripojenie na server */
    if(connect(socketClient, (struct sockaddr *) &addressServer, sizeof(addressServer)) < 0){
        perror("Chyba pri pripajani.\n");
        exit(-2);
    }

    printf("Pripojene.\n");

    close(socketClient);

    printf("Socket bol uzatvoreny.\n");

    return 0;
}