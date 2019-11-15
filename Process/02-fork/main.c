#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    pid_t pid; 

    // 1. 终端是标准的输出设备,标准输出设备是行缓冲模式,当有 \n 的时候, 会刷新缓冲区
    // 2. 文件是全缓冲模式, 全缓冲模式下 \n 仅仅是一个换行的作用
    printf("[%d]: Begin!! \n", getpid());

    fflush(NULL);

    pid = fork();

    if (pid < 0) // error 
    {
        perror("fork() fail");
        exit(1);
    }

    if (pid == 0)  // child
    {
        printf("[%d]: Child \n", getpid());
    } 
    else    // Parent 
    {
        printf("[%d]: Parent \n", getpid());
    }

    printf("[%d]: end \n", getpid());

    return 0;
}
