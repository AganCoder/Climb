#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// 求解 30000000 - 30000200 之间的质数
// 查看孤儿进程

#ifndef true
#define true 1
#define false 0
#endif

#define LEFT 30000000
#define RIGHT 30000200

int isPrimer(unsigned int number)
{
    if (number <= 0)
    {
        return false;
    }

    for (size_t i = 2; i < number / 2; i += 1)
    {
        if (number % i == 0)
        {
            return false;
        }
    }

    return true;
}

int main(int argc, char const *argv[])
{
    pid_t pid;
    int index;

    for (index = LEFT; index < RIGHT; index += 1)
    {
        if ((pid = fork()) < 0)
        {
            perror("fork fail");
            exit(0);
        }

        if (pid > 0) // parent 
        {

        }
        
        if (pid == 0) // child 
        {
            if (isPrimer(index) == true)
            {
                printf("number = %d is Primer \n", index);
            }  
            
            // sleep(1000); // 孤儿进程，由 init 进程接管
            // must exit
            exit(0);
        }
    }

    // sleep(1000); // 子进程僵尸态
    return 0;
}
