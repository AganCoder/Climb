#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
#include <arpa/inet.h>


int main(int argc, char const *argv[])
{
    // ipv4
    int sockfd;
    struct sockaddr_in addr_in;
    char buffer[1000];
    
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("init socket fail");
        exit(1);
    }

    bzero(&addr_in, sizeof(addr_in));    
    addr_in.sin_family = AF_INET;
    addr_in.sin_port = htons(9898);
    addr_in.sin_addr.s_addr = inet_addr("103.101.153.8");

    if ((connect(sockfd, (struct sockaddr *)&addr_in, sizeof(addr_in)))<0)
    {
        perror("connect fail");
        exit(1);
    }

    while (fgets(buffer, sizeof(buffer), stdin))
    {
        write(sockfd, buffer, strlen(buffer));
    }

    close(sockfd);

    return 0;
}
