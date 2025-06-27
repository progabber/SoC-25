#include<stdlib.h>
#include<unistd.h>
#include<stdio.h>
#include<sys/wait.h>
#include<signal.h>

int main(int argc, char *argv[]){
	int cpid = fork();
	if (cpid < 0){
		fprintf(stderr, "Error while forking\n");
	}
	else if (cpid == 0){
		printf("Going to sleep for 60 seconds...\n");
		sleep(60);
	}
	else {
		sleep(1);
		for (int i=3; i>0; i--){
			printf("Killing process %d in %d second(s)\n", cpid, i);
			sleep(1);
		}
		kill(cpid, SIGTERM);
		wait(NULL);
		printf("Child terminated and successfully reaped\n");
		exit(EXIT_SUCCESS);
	}

}
