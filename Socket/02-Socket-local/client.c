#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <string.h>
#include <stddef.h>
#include <unistd.h>


static const char *SERVERNAME = "@servername";

int main(int argc, char const *argv[])
{
    int sockfd;
    struct sockaddr_un serverAddr;
    socklen_t len;
    char buffer[1024];

    sockfd = socket(AF_UNIX, SOCK_STREAM, 0);

    if (sockfd < 0)
    {
        perror("init fail");
        exit(1);
    }

    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sun_family = AF_UNIX;
    strncpy(serverAddr.sun_path, SERVERNAME, sizeof(serverAddr.sun_path));  

    serverAddr.sun_path[0] = '\0';
    len = offsetof(struct sockaddr_un, sun_path) + sizeof(SERVERNAME);

    if (connect(sockfd, (struct sockaddr *)&serverAddr, len) < 0)
    {
        perror("connect fail");
        exit(1);
    }

    while (fgets(buffer, sizeof(buffer), stdin) != NULL)
    {
        write(sockfd, buffer, strlen(buffer));
    }

    close(sockfd);

    return 0;
}
