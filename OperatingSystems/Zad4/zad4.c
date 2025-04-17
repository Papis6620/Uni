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
    if(argc < 2){
        printf("Nie podano nazw plików\n");
        exit(EXIT_FAILURE);
    }
    int filedes[2];
    unsigned char buffer[BUFFER_SIZE];
    int id, random_time;

    if(pipe(filedes) == -1){    //tworzenie potoku
        perror("pipe error: ");
        exit(EXIT_FAILURE);
    }
    
    id = fork();
    if(id == -1){
        perror("fork error: ");
        exit(EXIT_FAILURE);
    }

    if(id > 0){ // producent
        close(filedes[0]);
        int plik = open(argv[1], O_RDONLY, 0666);
        int odczyt;
        if(plik == -1){
            perror("open error: ");
            exit(EXIT_FAILURE);
        }
        do{
        random_time = rand() % 4;
        printf("Oczekiwano przez: %d \n", random_time + 1);
        sleep(random_time + 1);
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
        if(write(filedes[1], &buffer, odczyt) == -1){
            perror("write error: ");
            exit(EXIT_FAILURE);
        }
    }while(odczyt == BUFFER_SIZE);
        close(plik);
        close(filedes[1]);

    }else{ // konsument
        random_time = rand() % 4;
        sleep(random_time + 1);
        close(filedes[1]);
        int plik2 = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0666);
        int odczyt;
        if(plik2 == -1){
            perror("open error: ");
            exit(EXIT_FAILURE);
        }
        do{
        
        odczyt = read(filedes[0], &buffer, BUFFER_SIZE);
        if(odczyt == -1){
            perror("read error: ");
            exit(EXIT_FAILURE);
        }
        
        if(write(STDOUT_FILENO, &buffer, odczyt) == -1){
            perror("write error: ");
            exit(EXIT_FAILURE);
        }else{
            printf(" - pobrano \n");
        }
        
        if(write(plik2, &buffer, odczyt) == -1){
            perror("write error: ");
            exit(EXIT_FAILURE);
        }
    }while(odczyt == BUFFER_SIZE);
        close(plik2);
        close(filedes[0]);
    }
    wait(NULL);
    return 0;


}