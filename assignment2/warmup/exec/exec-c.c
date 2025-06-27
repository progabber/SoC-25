#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main(int argc, char *argv[]){
	printf("Going to list directories...\n");

	int error = execlp("ls", "ls", (char*) NULL); 
	// Comment the above line and uncomment the below
	// line to print statements after exec call
	// int error = execlp("s", "ls", (char*) NULL); 

	// The following lines are printed only when 
	// execlp returns with an error
	printf("Have listed directories\n");
	printf("execlp failed with exit code: %d\n", error);
	return 0;
}

