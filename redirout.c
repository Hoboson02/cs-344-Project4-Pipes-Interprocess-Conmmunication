#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char **argv){
// 1. Parse the command line to make sure the user has entered the minimum amount of information.
	if(argc < 3) {

		exit(1);
	}
// 2. open() the output file.
	int fd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);

    int fds[2];
// 3. Create a pipe().
	pipe(fds);
// 4. fork() a child process to run the command.
	if (fork() == 0) {
// 5. In the child:
// 		dup2() the output end of the pipe into stdout.
		dup2(fds[1], 1);
// 		close() the input end of the pipe.
		close(fds[0]);
// 		execvp() the command.
		execvp(argv[2], );
		exit(1);
	}

    close(fds[0]);
	close(fd)
}
// 6. In the parent:
// 		close() the output end of the pipe.
// 		Repeatedly read() from the input end into a buffer.
// 			write() the buffer into the output file you opened earlier.
// 			read() will return zero bytes read on end-of-file (EOF).
// 		close() the input end of the pipe.
// 		close() the output file.