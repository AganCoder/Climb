#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h> 


int main(int argc, char const *argv[])
{
    int serfd, clifd;
    struct sockaddr_in seraddr_in, cliaddr_in;
    socklen_t clilen;
    char buffer[1000];

    if ((serfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("init socket fail");
        exit(1);
    }

    bzero(&seraddr_in, sizeof(seraddr_in));
    seraddr_in.sin_family = AF_INET;
    seraddr_in.sin_port = htons(9898);
    seraddr_in.sin_addr.s_addr = inet_addr("103.101.153.8");

    if (bind(serfd, (struct sockaddr *)&seraddr_in, sizeof(seraddr_in)) < 0)
    {
        perror("bind fail");
        exit(1);
    }

    if (listen(serfd, 20) < 0)
    {
        perror("listen fail");
        exit(1);
    }

    while (1)
    {
        if ((clifd = accept(serfd, (struct sockaddr *)&cliaddr_in, &clilen)) < 0)
        {
            perror("accept fail");
            continue;
        }

        while (1)
        {
            memset(buffer, 0, sizeof(buffer));
            int len = read(clifd, buffer, sizeof(buffer));

            if (len < 0 )
            {
                perror("read fail");
                break;
            }

            if (len == 0)
            {
                perror("EOF");
                break;
            }

            printf("receive: %s", buffer);
        }

        close(clifd);
    }

    close(serfd);

    return 0;
}
