#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]){
	printf( "The process identifier (pid) of the parent process is %d\n", (int)getpid());
	
	int pid = fork();
    printf("PID %d pid %d\n\n",(int)getpid(), pid );
	
	return 0;
}
