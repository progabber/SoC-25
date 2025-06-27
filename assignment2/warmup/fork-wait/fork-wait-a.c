#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>

/* 
   (2^N - 1) child processes are created. This can be seen
   using an induction argument:

   1.	Let the first child be 'x'. Now 'x' creates children 
   	(N - 1) times. So 'x' has (2^(N - 1) - 1) children.
	Along with 'x', these are 2^(N - 1) processes.

   2.	Now we come back to the parent process which has to 
   	create children (N - 1) times now. So we get 
	(2^(N - 1) - 1) processes more.

   In total, we get (2^N - 1) child processes.

*/

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
