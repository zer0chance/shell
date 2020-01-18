#include <stdio.h>

#define SHELL_BUFSIZE 1024
#define SHELL_TOK_BUFSIZE 64
#define SHELL_TOK_DELIM " \n\t\a\r"


char* shell_read_line()
{
    int bufsize = SHELL_BUFSIZE;
    int position = 0;
    char* buffer = malloc(sizeof(char) * bufsize);
    if (!buffer) {
        fprintf(stderr, "alocation error\n");
        exit(EXIT_FAILURE);        
    }
    
    int c;
    
    while(1)
    {
        c = getchar();
        if (c == EOF || c == '\n') {
            buffer[position] = '\0';
            return buffer;
        }
        else {
            buffer[position] = c;
        }
        position++;

        if (position >= bufsize) {
            bufsize += SHELL_BUFSIZE;
            buffer = realloc(buffer, bufsize);
            if (!buffer) {
                fprintf(stderr, "alocation error\n");
                exit(EXIT_FAILURE);        
            }    
        }
    }
}   


char** shell_split_line(char* line)
{
	int bufsize = SHELL_TOKEN_BUFSIZE;
	int position = 0;
	char* token = NULL;
	char** tokens = malloc(sizeof(char *) * bufsize);
    
	if (!tokens) {
        fprintf(stderr, "alocation error\n");
        exit(EXIT_FAILURE);        
    } 

	token = strtok(line, SHELL_TOK_DELIM);

	while(token != NULL) {
		tokens[position] = token;
		position++;

		if (position >= bufsize) {
			bufsize += SHELL_TOK_BUFSIZE;	
			tokens = realloc(tokens, bufsize * sizeof(char *));
			 
			if (!tokens) {
        		fprintf(stderr, "alocation error\n");
        		exit(EXIT_FAILURE);        
    		}   
		}
		token = strtok(NULL, SHELL_TOK_DELIM);
	}
	
	tokens[position] = NULL;
	return tokens;	
}	


int* shell_launche(char** args)
{
    pid_t = pid, wpid;
    int status;

    pid = fork();
    if (pid == 0)
    {
        if (execvp(args[0], args) == -1)
        {
            perror("shell");
            exit(EXIT_FAILURE);
        }
    } 
    else if (pid < 0) 
    {
        perror("shell");
    }   
    else 
    {
        do {
            wpid = waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }

    return 1;
}


void shell_loop()
{
    char* line;
    char** args;
    int status;       

                    
    do{
        print("> ");
        line = shell_read_line();
        args = shell_split_line(line);
        status = shell_execute(args);

        free(line);
        free(args);
    } while(status);	
}



int main(int* argc, char **argv)
{
    shell_loop();
	
    return 0;
}
