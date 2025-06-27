#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>

int main(int argc, char *argv[]){
	if (argc != 3){
		fprintf(stderr, "Incorrect number of arguments\nUsage: ./exec-b <command> <arg>\n");
		exit(1);
	}

	int cpid = fork();
	if (cpid < 0){
		fprintf(stderr, "Error in forking\n");
	}
	else if (cpid == 0){
		execvp(argv[1], &argv[1]);
	}
	else {
		wait(NULL);
		printf("Command sucessfully completed\n");
	}
	return 0;
}

