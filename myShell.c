#include <stdio.h>

#define SHELL_BUFSIZE 1024
#define SHELL_TOK_BUFSIZE 64
#define SHELL_TOK_DELIM " \n\t\a\r"


int shell_cd(char **args);
int shell_help(char **args);
int shell_exit(char **args);


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


char *builtin_str[] = {
  "cd",
  "help",
  "exit"
};

int (*builtin_func[]) (char **) = {
  &shell_cd,
  &shell_help,
  &shell_exit
};

int shell_num_builtins() {
  return sizeof(builtin_str) / sizeof(char *);
}

int shell_cd(char **args)
{
  if (args[1] == NULL) {
    fprintf(stderr, "shell: expected argument to \"cd\"\n");
  } else {
    if (chdir(args[1]) != 0) {
      perror("shell");
    }
  }
  return 1;
}

int shell_help(char **args)
{
  printf("Type program names and arguments, and hit enter.\n");
  printf("The following are built in:\n");

  for (int i = 0; i < shell_num_builtins(); i++) {
    printf("  %s\n", builtin_str[i]);
  }

  printf("Use the man command for information on other programs.\n");
  return 1;
}

int shell_exit(char **args)
{
  return 0;
}


int shell_execute(char **args)
{
  if (args[0] == NULL) {
    // An empty command was entered.
    return 1;
  }

  for (int i = 0; i < shell_num_builtins(); i++) {
    if (strcmp(args[0], builtin_str[i]) == 0) {
      return (*builtin_func[i])(args);
    }
  }

  return shell_launch(args);
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
