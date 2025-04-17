#include <stdio.h>
#include <stdlib.h>
#include <mqueue.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "kolejka.h"
#include <unistd.h>
#include <signal.h>

mqd_t server, desk_client;
char client[10];

void exit_q(){
    printf("Zamykanie kolejki serwera i usuwanie kolejki klienta\n");
    q_close(server);
    q_close(desk_client);
    q_del(client);
}
void exit_sig(int signal){
    printf("SIGINT - wyłączanie programu\n");
    exit(EXIT_SUCCESS);
}

int main(){

    if(signal(SIGINT, exit_sig) == SIG_ERR){
        perror("signal error");
        exit(EXIT_FAILURE);
    }

    if(atexit(exit_q) != 0){
        perror("atexit error");
        exit(EXIT_FAILURE);
    }

    int pid = getpid();
    struct mq_attr attr, newattr;
    char msg[MSG_LENGTH];
    char string[40];
    
    sprintf(client, "/%d", pid);

    newattr.mq_maxmsg = 10;
    newattr.mq_msgsize = MSG_LENGTH;
    newattr.mq_flags = 0;
    newattr.mq_curmsgs = 0;

    desk_client = q_create(client, &newattr);
    desk_client = q_open(client, O_RDONLY);
    sleep(1);
    server = q_open(SERVER_Q, O_WRONLY);

    q_atr_get(desk_client, &attr);
    printf("Utworzono kolejke %s, deskryptor: %d, atrybuty: \n", client, desk_client);
    printf("mq_flags: %ld\n", attr.mq_flags);
    printf("mq.maxmsg: %ld\n", attr.mq_maxmsg);
    printf("mq_msgsize: %ld\n", attr.mq_maxmsg);
    printf("mq_curmsgs: %ld\n", attr.mq_curmsgs);

    printf("Wprowadź wiadomość\n");

    while(fgets(string, sizeof(string), stdin) != NULL){
        sprintf(msg, "%d %s", pid, string);
        printf("Wysłano: /%s\n", msg);
        q_send(server, msg, MSG_LENGTH, 1);
        printf("Wysłano wiadomość\n");
        printf("Oczekiwanie na odpowiedź\n");
        sleep(rand() % 4);

        q_receive(desk_client, msg, MSG_LENGTH);
        printf("Odpwiedź: %s\n", msg);
        printf("Wprowadź wiadomość\n");
    }
    exit(EXIT_SUCCESS);
}