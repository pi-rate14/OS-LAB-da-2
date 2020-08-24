#include <stdio.h>
#include <stdlib.h>
int main()
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
}
