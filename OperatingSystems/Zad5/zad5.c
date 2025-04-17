#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<sys/wait.h>
#include<string.h>

#define myfifo "/tmp/myfifo"
void rmfifo(void){
    if(unlink(myfifo) == -1){
        perror("remove error");
        exit(EXIT_FAILURE);
    }
}
int main(int argc, char *argv[]){

    int id;
    atexit(rmfifo);
    mkfifo(myfifo, 0666);
    id = fork();
    if(id == -1){
        perror("fork error: ");
        exit(EXIT_FAILURE);
    }else if(id > 0){
        sleep(2);
        execlp("./output", "output", argv[2], myfifo, NULL);
        perror("execlp error: ");
        wait(NULL);
    }else{
        execlp("./input", "input", argv[1], myfifo, NULL);
        perror("execlp error: ");
    }
    
    if(close(*myfifo) == -1){
        perror("close error: ");
        exit(EXIT_FAILURE);
    }
    exit(0);


}