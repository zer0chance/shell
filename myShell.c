#include <stdio.h>

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
