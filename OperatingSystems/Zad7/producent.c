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

typedef struct
{
    char bufor[NBUF][NELE];
    int wstaw, wyjmij;
}SegmentPD;

int main(int argc, char *argv[]){

    const char *sem_prod = argv[1];
    const char *sem_kons = argv[2];
    const char *pd_nazwa = argv[3];
    const char *plik_nazwa = argv[4];

    if(argc != 5){
        printf("Niepoprawna ilość argumentów");
        exit(EXIT_FAILURE);
    }
    sem_t *prod_adres = otworz(sem_prod);
    printf("Adres semaforu producenta: %p\n", (void *)prod_adres);
    sem_t *kons_adres = otworz(sem_kons);
    printf("Adres semaforu konsumenta: %p\n", (void *)kons_adres);

    int deskryptor_pd = pd_otworz(pd_nazwa);

    SegmentPD *wpd = (SegmentPD *) pd_mmap(sizeof(SegmentPD), deskryptor_pd);
    printf("Pamieć dzielona - rozmiar: %ld\n",sizeof(wpd));
    printf("Adres pamięci: %d\n", deskryptor_pd);

    wpd->wstaw = 0;

    int plik = open(plik_nazwa, O_RDONLY, 0644);
    if(plik == -1){
        perror("open error");
        exit(EXIT_FAILURE);
    }
    int odczyt, prod_val, kons_val;
    do{
        opusc(prod_adres);
        prod_val = wartosc(prod_adres);
        kons_val = wartosc(kons_adres);
        printf("Wartosc semefora producenta: %d\n", prod_val);
        printf("Wartość semafora konsumanta: %d\n", kons_val);

        odczyt = read(plik, wpd->bufor[wpd->wstaw], NELE);
        if(odczyt == -1){
            perror("read error: ");
            exit(EXIT_FAILURE);
        }
        if(odczyt < NELE){
            wpd->bufor[wpd->wstaw][odczyt] = '\0';
        }
    
        printf("Indeks elementu buforu: %d\n", wpd->wstaw);
        printf("Odczytane bajty: %d\n", odczyt);
        printf(" - Przesłany tekst");

        if(write(STDOUT_FILENO, wpd->bufor[wpd->wstaw], odczyt) == -1){
            perror("write error: ");
            exit(EXIT_FAILURE);
        }
        printf("\n");
        wpd->wstaw = (wpd->wstaw + 1) % NBUF;

        podnies(kons_adres);
    }while(odczyt > 0);

    if(close(plik) == -1){
        perror("close error");
        exit(EXIT_FAILURE);
    }
    zamknij(prod_adres);
    zamknij(kons_adres);
    pd_zamknij(deskryptor_pd);

    return 0;

}