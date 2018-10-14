#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <stdint.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

#define SOCK_PATH "echo_socket"


typedef struct proto_t {
    uint32_t        len;
    uint8_t        *data;
} proto_t;

int main(void)
{
    int                 s;
    int                 t;
    int                 len;
    struct sockaddr_un  remote;
    char                buffer[1400];
    proto_t            *frame = (proto_t *)buffer;


    if ((s = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        exit(1);
    }

    printf("Trying to connect...\n");

    remote.sun_family = AF_UNIX;
    strcpy(remote.sun_path, SOCK_PATH);
    len = strlen(remote.sun_path) + sizeof(remote.sun_family);

    if (connect(s, (struct sockaddr *)&remote, len) == -1) {
        perror("connect");
        exit(1);
    }

    printf("Connected.\n");

    srand(time(NULL));
    for (;;) {
        len = (rand() % (sizeof(buffer) - sizeof(uint32_t))) + sizeof(uint32_t);

        frame->len = htobe32(len - sizeof(uint32_t));
        if (send(s, frame, len, 0) == -1) {
            perror("send");
            close(s);
            exit(1);
        }
    }

    close(s);

    return 0;
}