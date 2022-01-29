#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {

// 0. Parse the command line
// 1. Make a pipe() in the parent
// 2. fork().
// 3. The child will run wc:
//     - dup2() the read end of the pipe into stdin
//     - close() the write end of the pipe
//     - execlp() the wc command
// 4. The parent will run ls:
//     - dup2() the write end of the pipe into stdout
//     - close() the read end of the pipe
//     - execlp() the ls command 
}