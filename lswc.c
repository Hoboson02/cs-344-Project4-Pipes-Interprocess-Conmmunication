#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
	int fds[2];
	pipe(fds);
	if (fork() == 0) {
		dup2(fds[0], 0);
		close(fds[1]);
		execlp("wc", "wc", "-l",NULL);
		exit(1);
	}
	dup2(fds[1], 1);
	close(fds[0]);
	execlp("ls", "ls", "-1", "-a", argv[1] ,NULL);
}