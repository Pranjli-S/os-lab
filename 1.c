#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();
    if (pid < 0) { perror("fork"); return 1; }
    if (pid == 0) {
        printf("Child PID=%d, Parent PID=%d\n", getpid(), getppid());
        execlp("ls", "ls", "-l", NULL);
        perror("exec");
        _exit(1);
    }
    int status;
    wait(&status);
    printf("Parent PID=%d finished, child exit=%d\n", getpid(), WEXITSTATUS(status));
    return 0;
}
