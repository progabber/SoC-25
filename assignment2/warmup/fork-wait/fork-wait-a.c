#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>

int main(int argc, char *argv[]){
	printf("Enter the value of N: ");
	int N;
	scanf("%d", &N);
	for (int i=0; i<N; i++){
		int cpid = fork();
		if (cpid < 0){
			printf("Error in creating process\n");
			exit(1);
		}
		else if (cpid == 0){ // child process
			printf("PID: %d\tPPID: %d\n", (int) getpid(), (int) getppid());
		}
		else{ // parent process
			wait(NULL);
			printf("Reaped process with PID: %d\n", cpid);
		}
	}
}
