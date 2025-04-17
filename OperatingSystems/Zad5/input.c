#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<sys/wait.h>
#include<string.h>

#define BUFFER_SIZE 10

int main(int argc, char *argv[]){

    unsigned char buffer[BUFFER_SIZE];
    
    int plik = open(argv[1], O_RDONLY, 0666);
    int fifo = open(argv[2], O_WRONLY);
    int odczyt;

    if(plik == -1){
        perror("open error: ");
        exit(EXIT_FAILURE);
    }
    do{
        odczyt = read(plik, &buffer, BUFFER_SIZE);
        if(odczyt == -1){
            perror("read error: ");
            exit(EXIT_FAILURE);
        }
        if(write(STDOUT_FILENO, &buffer, odczyt) == -1){
            perror("write error: ");
            exit(EXIT_FAILURE);
        }
         printf(" - przesłano\n");
        if(write(fifo, &buffer, odczyt) == -1){
            perror("write error: ");
            exit(EXIT_FAILURE);
        }
    }while(odczyt == BUFFER_SIZE);

    close(plik);
    exit(0);

}