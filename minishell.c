#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>     // Used for fork()
#include <sys/types.h>  // Used for pid_t
#include <sys/wait.h>   // Used for wait()

#define MAXLINE 4096

int main(void){
			
	char buffer[MAXLINE];
	
	char *commands[5];
			
	do{	
		printf("$ ");
		//reset the command with empty string
		for(int i = 0; i < 5; i++)
			commands[i] = NULL; //COULD BE ALSO ""
						
		//read line
		if(fgets(buffer,MAXLINE,stdin) != NULL){
							  			    
		    // replace \n with \0 
		    if (buffer[strlen(buffer)-1] == '\n')
		      	buffer[strlen(buffer)-1] = '\0';
		      			      						  			    		   	
			//get first command	    		    
			commands[0] = strtok(buffer, " \t");
						
			//keep getting commands until we get four or until the commands end, and store them in the correct format. Ej: "command1","command2"...
			for(int i = 1; i < 4; i++){
				
				commands[i] = strtok(NULL, " \t");
			}
						
			if(!strcmp(commands[0],"help")){
			
				printf("\nThis minishell is very basic and you have to be very careful\n\n");
				printf("--Implemented commands--\n");
				printf("-help: displays useful information\n");
				printf("-exit: used to exit the minishell\n\n");
				printf("This minishell can do basic unix commands such as ls, ls -a, ls- la, rm, more, cp, echo.\n\n");
				printf("As specified in the task, it only takes the first four arguments into account and\n");
				printf("it ignores the rest of the arguments so be careful.\n\n");
			}
			
			else if(!strcmp(commands[0],"exit")){}
			
			else{
				
				pid_t pid = fork();
			
				if (pid == 0) {   // The child process 
			
				    execlp(commands[0],commands[0] ,commands[1] , commands[2] , commands[3], NULL);
				    exit(127);     // Only if execv() fails
				    
				} else {          // pid != 1 the parent process
				
				    waitpid(pid, NULL, 0); // Wait for child to exit
				}		
			}
		}
		
	}while(strcmp(commands[0], "exit")); //run until exit command is typed
	
	return EXIT_SUCCESS;
}
