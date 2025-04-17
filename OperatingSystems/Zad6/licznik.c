#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <semaphore.h>
#include "semafory.h"
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int main (int argc, char *argv[]) {
	
	int odczyt;
	char bufor[100];
	int liczba;
	int sk;
	sem_t *semafor;
	int wartosc_semafora;
	int plik;
	
	if (argc != 3) {
		printf ("Błąd: niepoprawna liczba argumentów!\n");
		printf ("Wywołaj podprogram wpisując: %s liczba sekcji krytycznycg nazwa semafora\n", argv[0]);
		_exit (EXIT_FAILURE);
	}
	
	sk = atoi(argv[1]);
	semafor = otworz(argv[2]);
	
	for (int i = 0; i < sk; i++) {
		
		sleep(rand() % 4);
		
		wartosc(semafor, &wartosc_semafora);
		printf("PID: %d \t", getpid());
		printf ("Wartość semafora przed SK: %d\n", wartosc_semafora);
		opusc(semafor);
		
		if ((plik = open ("numer.txt", O_RDONLY, 0644)) == -1) {
			printf ("Błąd otwarcia pliku do odczytu");
			perror ("Błąd pliku");
			_exit (EXIT_FAILURE);
		}
		
		odczyt = read(plik, &bufor, 10);
		if (odczyt == -1) {
			printf("Błąd odczytu z pliku\n");
			_exit(EXIT_FAILURE);
		} else if (odczyt == 0) {
			break;
		} else {
			bufor [odczyt] = '\0';
			wartosc(semafor, &wartosc_semafora);
			printf("\tPID: %d \t", getpid());
			printf("Semafor %d odczytany numer: %s nr. SK: %d\n", wartosc_semafora, bufor, i);
		}
		
		if (close (plik) == -1) {
			perror ("Błąd zamknięcia pliku");
			exit (EXIT_FAILURE);
		}
		
		liczba = atoi (bufor);
		liczba++;
		sprintf (bufor, "%d", liczba);
		
		sleep (rand() % 4);
		
		if ((plik = open ("numer.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644)) == -1) {
			printf ("Błąd otwarcia pliku do zapisu");
			perror ("Błąd pliku");
			_exit (EXIT_FAILURE);
		}
		
		if (write (plik, &bufor, strlen(bufor)) == -1){
			perror("Błąd write do pliku");
			_exit(EXIT_FAILURE);
		}
		
		if (close (plik) == -1) {
			perror ("Błąd zamknięcia pliku");
			exit (EXIT_FAILURE);
		}
		
		podnies(semafor);
		wartosc(semafor, &wartosc_semafora);
			printf("PID: %d \t", getpid());
			printf ("Wartość semafora po SK: %d\n", wartosc_semafora);
	}
	

	zamknij(semafor);
	
	return 0;
}