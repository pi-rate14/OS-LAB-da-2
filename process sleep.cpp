#include<stdio.h>
#include <sys/types.h>
#include <unistd.h>
int main()
{
    int pid = fork();
    sleep(3000);
    printf("3 seconds have passed");
    return 0;
}
