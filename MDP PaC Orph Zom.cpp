#include<iostream>
#include<stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include<cstdlib>
using namespace ::std;
int PaC()
{
   int forkresult, parent_ID;

   forkresult=fork();
   if(forkresult !=0 )
   {
        printf(" I am the parent my ID is = %d" , getpid());
        printf(" and my child ID is = %d\n" , forkresult);
   }
   parent_ID = getpid();

   if(forkresult ==0)
      printf(" I am the  child ID is = %d",getpid());
   else
      printf(" and my parent ID is = %d", parent_ID);
   return 0;
}
int zom()
{
    pid_t child_pid = fork();
    if (child_pid > 0)
        sleep(50);
    else
        exit(0);
    return 0;
}
int orph()
{
    int pid = fork();

    if (pid > 0)
        printf("in parent process");
    else if (pid == 0)
    {
        sleep(30);
        printf("in child process");
    }
    return 0;
}

int main()
{
    float result;
    int choice, num;
    printf("Press 1 to create parent and child process and find their process id\n");
    printf("Press 2 to create zombie process\n");
    printf("Press 3 to create orphan process\n");
    printf("Enter your choice:\n");
    cin >> choice;
    switch (choice) {
    case 1: {
        PaC();
        break;
    }
    case 2: {
        zom();
        break;
    }
    case 3: {
        orph();
        break;
    }
    default:
        printf("wrong Input\n");
    }
    return 0;
}

