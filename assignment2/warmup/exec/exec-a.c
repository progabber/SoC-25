#include<stdlib.h>
#include<unistd.h>

int main(int argc, char *argv[]){
	execvp("ls", &argv[1]);
	return 0;
}
