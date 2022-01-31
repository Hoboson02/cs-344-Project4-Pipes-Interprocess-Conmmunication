#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char **argv){
	if(argc < 3) { // 1. Parse the command line to make sure the user has entered the minimum amount of information.
		printf("Error: Amount of input below minimum amount of 3 \n");
		exit(1);
	}

	int fd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0644); // 2. open() the output file.

    int fds[2];
	pipe(fds); // 3. Create a pipe().

	if (fork() == 0) { // 4. fork() a child process to run the command.
		dup2(fds[1], 1); // dup2() the output end of the pipe into stdout.
		close(fds[0]); // close() the input end of the pipe.
		char * const *args = argv + 2;
		execvp(argv[2], args); // execvp() the command.
		exit(1);
	}
// 6. In the parent:
	close(fds[1]); // close() the output end of the pipe.
	char buf[2048];
	int count;

	while ((count = read(fds[0], buf, sizeof buf)) > 0) { // read() will return zero bytes read on end-of-file (EOF). Repeatedly read() from the input end into a buffer.
		write(fd, buf, count); // write() the buffer into the output file you opened earlier.
  }
  	close(fds[0]); // close() the input end of the pipe.
	close(fd); // close() the output file.
}
