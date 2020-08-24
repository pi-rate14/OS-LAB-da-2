#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

void *primeNumbers(void *vargp){
    int n, i, m = 0,flag = 0;

    printf("Enter the number to check whether it's PRIME or not : \n");
    scanf("%d",&n);

    m = n/2;

    for(i = 2 ; i <= m ; i++){
        if(n%i == 0){
            printf("The number %d is not PRIME.\n",n);
            flag = 1;
            break;
        }
    }
    if(flag == 0){
        printf("The number %d is PRIME.\n",n);
    }

    return 0;
}

int main(){
    pthread_t thread_id;

    pthread_create(&thread_id, NULL, primeNumbers, NULL);
    pthread_join(thread_id, NULL);

    return 0;
}
