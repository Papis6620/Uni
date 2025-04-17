#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
                sleep(2);
                printf("Proces potomny: UID = %d, GID= %d, PID= %d, PGID = %d, PPID = %d \n", getuid(), getgid(), getpid(), getpgid(getpid()), getppid());
                break;
            default:
                break;
        }
    }
    return 0;
}