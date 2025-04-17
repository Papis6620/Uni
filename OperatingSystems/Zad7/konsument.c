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

int czy_koniec(SegmentPD PD, int bufor_nr, int* koniec){
    int i;
    for(i = 0; i < NELE; i++){
        if(PD.bufor[bufor_nr][i] == '\0'){
            *koniec = i;
            return 0;
        }
    }
    return 1;
}


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
    printf("\tAdres semaforu producenta: %p\n", (void *)prod_adres);
    sem_t *kons_adres = otworz(sem_kons);
    printf("\tAdres semaforu konsumenta: %p\n", (void *)kons_adres);

    int deskryptor_pd = pd_otworz(pd_nazwa);

    SegmentPD *wpd = (SegmentPD *) pd_mmap(sizeof(SegmentPD), deskryptor_pd);
    printf("\tPamieć dzielona - rozmiar: %ld\n",sizeof(wpd));
    printf("\tAdres pamięci: %d\n", deskryptor_pd);

    wpd->wyjmij = 0;

    int plik = open(plik_nazwa, O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if(plik == -1){
        perror("open error");
        exit(EXIT_FAILURE);
    }
    int zapis, prod_val, kons_val, koniec;
    do{
        opusc(kons_adres);
        prod_val = wartosc(prod_adres);
        kons_val = wartosc(kons_adres);
        printf("\tWartosc semefora producenta: %d\n", prod_val);
        printf("\tWartość semafora konsumanta: %d\n", kons_val);

        if(!czy_koniec(*wpd, wpd->wyjmij, &koniec)){
            zapis = write(plik, wpd->bufor[wpd->wyjmij], koniec);
            if(zapis == -1){
            perror("read error: ");
            exit(EXIT_FAILURE);
        }
        }else{
            zapis = write(plik, wpd->bufor[wpd->wyjmij], NELE);
            if(zapis == -1){
            perror("read error: ");
            exit(EXIT_FAILURE);
        }
        }
        printf("\tIndeks elementu buforu: %d\n", wpd->wyjmij);
        printf("\tOdczytane bajty: %d\n", zapis);
        printf(" - Odczytany tekst");

        if(write(STDOUT_FILENO, wpd->bufor[wpd->wyjmij], zapis) == -1){
            perror("write error: ");
            exit(EXIT_FAILURE);
        }
        printf("\n");
        wpd->wyjmij = (wpd->wyjmij + 1) % NBUF;

        podnies(prod_adres);
    
    }while(zapis > 0);

    if(close(plik) == -1){
        perror("close error");
        exit(EXIT_FAILURE);
    }
    zamknij(prod_adres);
    zamknij(kons_adres);
    pd_zamknij(deskryptor_pd);

    return 0;

}