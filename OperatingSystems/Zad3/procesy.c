#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>

int main(int argc, char *argv[]){
    if(argc != 3){
        printf("Nie podano nr. sygnału i sposobu obsługi sygnału.\n");
        exit(EXIT_FAILURE);
    }
    int signal_action = atoi(argv[2]);

    if(signal_action != 1 && signal_action != 2 && signal_action != 3){
        printf("Podano nie prawidłowy sposób obsługi. Przewidywane sposoby to 1, 2 lub 3. \n");
        exit(EXIT_FAILURE);
    }
    
    int wait_id;
    int id, pid;
    for(int i = 0; i < 3; i++){
        id = fork();
        switch(id){
            case -1:
                perror("fork error");
                exit(1);
            case 0:
                execlp("./zad3_a", "zad3_a", argv[1], argv[2], (char *)NULL);
                break;
            default:
                pid = wait(&wait_id);
                printf("PID = %d \n", pid);
                if (WIFEXITED(wait_id)) {
                printf("Proces potomny zakończony normalnie. Status: %d\n", WEXITSTATUS(wait_id));
                } else if (WIFSIGNALED(wait_id)) {
                printf("Proces potomny zakończony sygnałem. Numer sygnału: %d, Nazwa: %s\n", WTERMSIG(wait_id), strsignal(WTERMSIG(wait_id)));
                }
                break;
        }
    }
    return 0;
}