#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_INPUT_SIZE 1024
#define MAX_TOKEN_SIZE 64
#define MAX_NUM_TOKENS 64
#define MAX_CWD_LENGTH 256
#define MAX_BG_LENGTH 64


// Splits the string by space and returns the array of tokens
char **tokenize(char *line)
{
  char **tokens = (char **)malloc(MAX_NUM_TOKENS * sizeof(char *));
  char *token = (char *)malloc(MAX_TOKEN_SIZE * sizeof(char));
  int i, tokenIndex = 0, tokenNo = 0;

  for(i =0; i < strlen(line); i++){

    char readChar = line[i];

    if (readChar == ' ' || readChar == '\n' || readChar == '\t'){
      token[tokenIndex] = '\0';
      if (tokenIndex != 0){
	tokens[tokenNo] = (char*)malloc(MAX_TOKEN_SIZE*sizeof(char));
	strcpy(tokens[tokenNo++], token);
	tokenIndex = 0; 
      }
    } else {
      token[tokenIndex++] = readChar;
    }
  }
 
  free(token);
  tokens[tokenNo] = NULL ;
  return tokens;
}


int main(int argc, char* argv[]) {
	char  line[MAX_INPUT_SIZE];            
	char  **tokens;              
	int i;
	int background_pids[MAX_BG_LENGTH], pgids[MAX_BG_LENGTH]; // end is signified by a 0
	background_pids[0] = 0;
	pgids[0] = 0;


	while(1) {			
		/* BEGIN: TAKING INPUT */
		bzero(line, sizeof(line));
		char cwd[MAX_CWD_LENGTH];
		if (getcwd(cwd, MAX_CWD_LENGTH) == NULL){
			strcpy(cwd, "...");
		}
		printf("%s $ ", cwd);
		scanf("%[^\n]", line);
		getchar();

		line[strlen(line)] = '\n'; //terminate with new line
		tokens = tokenize(line);

		// check for dead background processes
		for (int i = 0; background_pids[i] != 0; i++) {
			if (waitpid(background_pids[i], NULL, WNOHANG) == background_pids[i]) {
				printf("Background process with PID: %d and PGID: %d is now dead :)\n", background_pids[i], pgids[i]);
				background_pids[i] = -1; // space to be recovered after the for loop
				pgids[i] = -1; // space to be recovered after the for loop
			}
		}

		// cleaning up spaces occupied by reaped background processes
		for (int i = 0, offset = 0; i < MAX_BG_LENGTH; i++) {
			if (background_pids[i] == -1) offset++;
			background_pids[i] = background_pids[i+offset];
			pgids[i] = pgids[i+offset];
			if (background_pids[i] == 0) {
				break;
			}
		}

		// check if command empty
		if (tokens[0] == NULL) continue;

		// check if background command
		int background_comm = 0;
		int token_no = 0;
		while (tokens[token_no] != NULL) token_no++;
		if (strcmp(tokens[token_no-1], "&") == 0) {
			background_comm = 1;
			tokens[token_no-1] = NULL;
			free(tokens[token_no]); // free the memory!
		}
       
		// if fork is required
		if (strcmp(tokens[0], "cd") && strcmp(tokens[0], "exit")){
			// forking child process to run command
			int cpid = fork();

			// error handling
			if (cpid < 0){
				perror("Fork failed\n");
				exit(EXIT_FAILURE);
			}
			else if (cpid == 0){
				if (!background_comm){
					int pgid = getpgid(cpid);
					printf("PARENT GROUP ID: %d\nPID: %d\n", pgid, cpid);
				}
				// execute the command using execvp
				if (execvp(tokens[0], tokens) < 0){
					printf("Command invalid, please try again\n");
					exit(EXIT_FAILURE);
				}
			}
			else {
				if (!background_comm){
					// reap the child
					int status;
					waitpid(cpid, &status, 0);
					if (WIFEXITED(status)) {
						printf("EXITSTATUS: %d\n", WEXITSTATUS(status));
					}
					else {
						printf("Did not terminate normally");
					}
				}
				else {
					int i = 0;
					setpgid(cpid, 0);
					while (background_pids[i] != 0) i++;
					background_pids[i] = cpid; background_pids[i+1] = 0;
					pgids[i] = getpgid(cpid); pgids[i+1] = 0;
				}
			}
		}
		else if (strcmp(tokens[0], "cd") == 0) {
			// cd command
			if (tokens[1] == NULL) {
				printf("No path provided\n");
			}
			else if (chdir(tokens[1])){
				printf("Error in changing directory\n");
			}
		}
		else if (strcmp(tokens[0], "exit") == 0) {
			// exit command

			// terminate all background processes
			for (int i=0; background_pids[i] != 0; i++) {
				kill(background_pids[i], SIGKILL);
			}

			// Freeing the allocated memory	
			for(i=0;tokens[i]!=NULL;i++){
				free(tokens[i]);
			}
			free(tokens);
			return 0;
		}
		else {
			printf("asdfasdfasdf\n");
		}
		// Freeing the allocated memory	
		for(i=0;tokens[i]!=NULL;i++){
			free(tokens[i]);
		}
		free(tokens);

	}
	return 0;
}
