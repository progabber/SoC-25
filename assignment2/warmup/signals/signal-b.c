#include<stdlib.h>
#include<unistd.h>
#include<stdio.h>
#include<sys/wait.h>
#include<signal.h>

void handler(int sig){
	printf("\nI WILL KEEP RUNNING FOREVER!\n");
}

int main(int argc, char *argv[]){
	if (signal(SIGINT, handler) == SIG_ERR){
		fprintf(stderr, "Error while receiving signal\n");
		exit(EXIT_FAILURE);
	}
	while (1){
		printf("I (process %d) am peacefully running, don't try to stop me\n", (int) getpid());
		sleep(1);
	}
}
