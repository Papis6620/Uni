#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(){
    int id;
    int i = 0;
    printf("Pokolnie nr. %d ", i);
    printf("Proces macierzysty: UID = %d, GID= %d, PID= %d, PGID = %d, PPID = %d \n", getuid(), getgid(), getpid(), getpgid(getpid()), getppid());
    for(i = 0; i < 3; i++){
        id = fork();
        switch(id){
            case -1:
                perror("fork error");
                exit(1);
            case 0:
                sleep(i);
                printf("Pokolenie nr. %d ", i+1);
                printf("Proces potomny: UID = %d, GID= %d, PID= %d, PGID = %d, PPID = %d \n", getuid(), getgid(), getpid(), getpgid(getpid()), getppid());
                break;
            default:
                sleep(i+1);
                break;
        }
    }
    return 0;
}
