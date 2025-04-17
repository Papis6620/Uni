#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(){
    int id;
    printf("Proces macierzysty: UID = %d, GID= %d, PID= %d, PGID = %d, PPID = %d \n", getuid(), getgid(), getpid(), getpgid(getpid()), getppid());
    for(int i = 0; i < 3; i++){
        id = fork();
        switch(id){
            case -1:
                perror("fork error");
                exit(1);
            case 0:
                execlp("./start", "start", (char *) NULL);
                perror("execlp error");
                break;
            default:
                wait(NULL);
                break;
        }
    }    
    return 0;
    
}