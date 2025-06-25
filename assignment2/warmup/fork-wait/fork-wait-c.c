#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>

int main(int argc, char *argv[]){
	int cpid = fork();
	if (cpid < 0){
		printf("Error in creating process\n");
		exit(1);
	}
	else if (cpid == 0){ // child process
		printf("PID of child: %d\n", (int) getpid());
		exit(0);
	}
	else{ // parent process
		wait(NULL);
		printf("Reaped process with PID: %d\n", cpid);
	}
}
