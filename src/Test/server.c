#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>

#define PORT 56300

void closeSocket(int Socket);

int main(int argc, char **argv)
{

    /* Vytvorenie socketu */
    int socketListen;
    if ((socketListen = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("Chyba pri vytvarani socktu.\n");
        exit(-1);
    }

    /* Vytvorenie adresy */
    struct sockaddr_in addressListen;
    addressListen.sin_family = AF_INET;         //Pripojenie zo siete
    addressListen.sin_port = htons(PORT);       // Port
    addressListen.sin_addr.s_addr = INADDR_ANY; // Prijimanie spojenie od kazdej IP

    /* Bind socket a adresy */
    if (bind(socketListen, (struct sockaddr *)&addressListen, sizeof(addressListen)) < 0)
    {
        perror("Chyba pri vystavovani socketu.\n");
        exit(-2);
    }

    /* Nastavenie pocuvania */
    if (listen(socketListen, 2) < 0)
    {
        perror("Chyba pri nastavovani pocuvania.\n");
        exit(-3);
    }

    printf("Socket bol uspesne vytoreny a nastavený.\n");

    /* Vytvorenie spojeni s clientami */
    int socketClient;
    struct sockaddr_in addressClient;
    socklen_t size;
    while (true)
    {

        if ((socketClient = accept(socketListen, (struct sockaddr *)&addressClient, &size)) < 0)
        {
            perror("Chyva pri vytvarani spojenia s klientom.\n");
            exit(-4);
        }

        switch (fork)
        {
        case -1:
            perror("Chyba pri vytvarani noveho procesu.");
            exit(-7);

        case 0:
            // Komunikacia s klientom
            closeSocket(socketListen);
            printf("Spojenie bolo uspesne nadviazane s clientom.\n");
            // ...
            break;
        default:
            closeSocket(socketClient);
        }

        printf("Server sa vypina.\n");

        return 0;
    }

    void closeSocket(int Socket)
    {
        if (close(socketClient) < 0)
        {
            perror("Chyba pri zatvarani socketu");
            exit(-8);
        }

        return;
    }