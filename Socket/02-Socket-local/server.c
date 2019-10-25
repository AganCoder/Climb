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
    struct sockaddr_un clientAddr;
    socklen_t clientLen;
    socklen_t serverLen;

    char buffer[1024];
    int connfd;

    if ((sockfd = socket(AF_UNIX, SOCK_STREAM, 0)) < 0)
    {
        perror("init fail");
        exit(1);
    }
    
    // 2. 设置对应地址,然后进行 connect
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sun_family = AF_UNIX;
    strncpy(serverAddr.sun_path, SERVERNAME, sizeof(serverAddr.sun_path));  

    // abstract & calculate length
    serverAddr.sun_path[0] = '\0';
    serverLen = offsetof(struct sockaddr_un, sun_path) + sizeof(SERVERNAME);

    if (bind(sockfd, (struct sockaddr *)&serverAddr, serverLen) < 0)
    {
        perror("bind fail");
        exit(1);
    }

    if (listen(sockfd, 20) < 0)
    {
        perror("listen fail");
        exit(1);
    }

    while (1)
    {
        // 阻塞到有客户端链接
        if ((connfd = accept(sockfd, (struct sockaddr *)&clientAddr, &clientLen))  < 0) 
        {
            printf("accept fail \r\n");
            continue;
        }
        printf("accept success \r\n");

        while(1) 
        {  
            memset(buffer, 0, sizeof(buffer));
            
            int n = read(connfd, buffer, sizeof(buffer));  
            if (n < 0) {  
                perror("read error");  
                break;  
            } else if(n == 0) {  
                printf("EOF\n");  
                break;  
            }  
            
            printf("received: %s", buffer);  
        }  
        close(connfd);
    }

    close(sockfd);

    return 0;
}
