#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]){
	struct sockaddr_un addr,address;
	char buf[100];
	int fd,cl,rc;
	printf( "The process identifier (pid) of the parent process is %d\n", (int)getpid());
	
	int pid = fork();
    
	if(pid==0){
		fd = socket(AF_UNIX, SOCK_STREAM, 0);
		address.sun_family = AF_UNIX;
		strncpy(address.sun_path, "socket", sizeof(address.sun_path)-1);
		bind(fd, (struct sockaddr*)&address, sizeof(address));
		listen(fd, 5);
		while (1) {
			if ( (cl = accept(fd, NULL, NULL)) == -1) {
			  perror("accept error");
			  continue;
			}
		
			while ( (rc=read(cl,buf,sizeof(buf))) > 0) {
			  printf("read %u bytes: %.*s\n", rc, rc, buf);
			}
			if (rc == -1) {
			  perror("read");
			  return -1;
			}
			else if (rc == 0) {
			  printf("EOF\n");
			  close(cl);
			}
	  }

	}
	else{  
	  if ( (fd = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
		perror("socket error");
		exit(-1);
	  }
	  
	  memset(&addr, 0, sizeof(addr));
	  addr.sun_family = AF_UNIX;
	  
	  strncpy(addr.sun_path, "socket", sizeof(addr.sun_path)-1);

	  {
	  	  unsigned int i = 0;
	  	  for(i = 0; i < 0xFFFFFFFC;i++) 
	  	  	 if(i%100000==0) printf("Waiting for parent thread to finish socket init %d\n",i);
	  }
	  connect(fd, (struct sockaddr*)&addr, sizeof(addr));
	
	  while( (rc=read(STDIN_FILENO, buf, sizeof(buf))) > 0) {
		if (write(fd, buf, rc) != rc) {
		  fprintf(stderr,"\n%s\n",buf);
		  if (rc > 0) fprintf(stderr,"partial write");
		  else {
			perror("write error");
			exit(-1);
		  }
		}
	  }
	}
	
	
	return 0;
}
