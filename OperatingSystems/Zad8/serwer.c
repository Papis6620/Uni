#include <stdio.h>
#include <stdlib.h>
#include <mqueue.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "kolejka.h"
#include <unistd.h>
#include <signal.h>

mqd_t desk_server;

void exit_q(){
    printf("Zamykanie i usuwanie kolejki serwera\n");
    q_del(SERVER_Q);
    q_close(desk_server);
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

    struct mq_attr attr, newattr;
    mqd_t desk_client;
    char msg_r[MSG_LENGTH];
    char msg_s[MSG_LENGTH];
    int a, b, result, pid;
    char op;
    char client[20];
    newattr.mq_maxmsg = 10;
    newattr.mq_msgsize = MSG_LENGTH;
    newattr.mq_flags = 0;
    newattr.mq_curmsgs = 0;

    desk_server = q_create(SERVER_Q, &newattr);
    desk_server = q_open(SERVER_Q, O_RDONLY);

    q_atr_get(desk_server, &attr);
    printf("Utworzono kolejke %s, deskryptor: %d, atrybuty: \n", SERVER_Q, desk_server);
    printf("mq_flags: %ld\n", attr.mq_flags);
    printf("mq.maxmsg: %ld\n", attr.mq_maxmsg);
    printf("mq_msgsize: %ld\n", attr.mq_maxmsg);
    printf("mq_curmsgs: %ld\n", attr.mq_curmsgs);

    while(1){
        printf("Oczekiwanie na wiadomość \n");
        q_receive(desk_server, msg_r, MSG_LENGTH);
        printf("Odebrana wiadomość: /%s\n", msg_r);
        sscanf(msg_r, "%d %d %c %d", &pid, &a, &op, &b);
        printf("Wysyłanie odpowiedzi\n");
        sleep(rand() % 4);
        sprintf(client, "/%d", pid);
        desk_client = q_open(client, O_WRONLY);

        if(op == '+'){
            result = a + b;
            sprintf(msg_s, "%d", result);
        }else if(op == '-'){
            result = a - b;
            sprintf(msg_s, "%d", result);
        }else if(op == '*'){
            result = a * b;
            sprintf(msg_s, "%d", result);
        }else if(op == '/'){
            if(b != 0){
                result = a / b;
                sprintf(msg_s, "%d", result);
            }else{
                sprintf(msg_s, "%s", "Nie można podzielić przez 0");
            }
            
        }else{
            sprintf(msg_s, "Podano nieporawany operator");
        }
        
        printf("Wysłano wiadomości do klienta\n");
        q_send(desk_client, msg_s, MSG_LENGTH, 1);
        q_close(desk_client);
    }
    exit(EXIT_SUCCESS);
}