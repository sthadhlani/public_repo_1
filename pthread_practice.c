#include <stdio.h>
#include <pthread.h>
#define TOTAL_THREADS 3

void *thread_func(void *arg){
   int i=0,j=0;
   int x;
   int *t_num = (int *)arg;
   while(i<100){
	printf("This is parrellel thread %d iteration %d\n",*t_num,i);
	for(j=0;j<10000000;j++) {x = j;}
	i++;
   }
   return 0;
} 

int main(int argc, char* argv[]){
    printf("Hello World!\n");
    pthread_t thread_t[TOTAL_THREADS];
    int x[TOTAL_THREADS];
    int i = 0;
    for(i = 0; i < TOTAL_THREADS; i++){
    	x[i] = i;
        if(pthread_create(&thread_t[i],NULL,thread_func,&x[i])){
	     printf("Error creating thread\n");
	     return 1;
        }
    }

    for(i = 0; i < TOTAL_THREADS; i++){
    	if(pthread_join(thread_t[i],NULL)){
    		printf("Error Joinin Pthread %d",i);
    	}
    }
    
    return 0;
}
