#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <semaphore.h>
#include "semafory.h"
#include <signal.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "pd.h"

#define NELE 20
#define NBUF 5
#define INPUT "input"
#define OUTPUT "output"
const char *sem_prod = "sem_prod";
const char *sem_kons = "sem_kons";
const char *pd = "pd";

void wyjscie(void){
	usun(sem_prod);
    usun(sem_kons);
    pd_usun(pd);
}

void sygnal_wyjscie(int signal){
	printf("Sygnał przerwania\n");
	exit(EXIT_SUCCESS);
}

typedef struct
{
    char bufor[NBUF][NELE];
    int wstaw, wyjmij;
}SegmentPD;

int main(int argc, char *argv[]){

    sem_t *prod_adres, *kons_adres;
    int wait_id, deskryptor_PD;
    
    prod_adres = stworz(sem_prod, NBUF);
    printf("Utworzono semafor %s (%p) o wartości %d\n", sem_prod, (void *)prod_adres, wartosc(prod_adres));
    kons_adres = stworz(sem_kons, 0);
    printf("Utworzono semafor %s (%p) o wartości %d\n", sem_kons, (void *)kons_adres, wartosc(kons_adres));

    deskryptor_PD = pd_stworz(pd);
    pd_ftrunacte(deskryptor_PD, sizeof(SegmentPD));
    printf("Adres pamięci dzielonej: %d, rozmiar: %ld", deskryptor_PD, sizeof(SegmentPD));
    if(atexit(wyjscie) != 0){
        perror("atexit error");
        exit(EXIT_FAILURE);
    }
    if(signal(SIGINT, sygnal_wyjscie) == SIG_ERR){
        perror("sig error");
        exit(EXIT_FAILURE);
    }

    int id = fork();
    int id2;

    if(id > 0){
        id2 = fork();
        if(id2 == 0){
            execlp("./konsument.x", "konsument", sem_prod, sem_kons, pd, OUTPUT, NULL);
            perror("execlp error");
            exit(EXIT_FAILURE);
        }else if(id2 > 0){
                if(wait(&wait_id) == -1){
                perror("wait error");
                exit(EXIT_FAILURE);
                }        
        }else{  
            perror("fork error");
            exit(EXIT_FAILURE);
        }
    if(wait(&wait_id) == -1){
                perror("wait error");
                exit(EXIT_FAILURE);
                }  
    }else if(id == 0){
        execlp("./producent.x", "producent", sem_prod, sem_kons, pd, INPUT, NULL);
            perror("execlp error");
            exit(EXIT_FAILURE);
    }else{
            perror("fork error");
            exit(EXIT_FAILURE);
        }

    pd_zamknij(deskryptor_PD);
    return 0;
    
}
