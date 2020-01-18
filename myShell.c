#include <stdio.h>
#define SHELL_BUFSIZE 1024


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
            realoc(buffer, bufsize);
            if (!buffer) {
                fprintf(stderr, "alocation error\n");
                exit(EXIT_FAILURE);        
            }    
        }
    }
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
