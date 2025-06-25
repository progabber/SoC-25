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
		printf("I am a child\n");
		exit(0);
	}
	else { // parent process
		wait(NULL);
		printf("I am a parent\n");
	}
}
