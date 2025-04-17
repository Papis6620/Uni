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

#define SCIEZKA "./"

char nazwa_semafora[20];

void wyjscie(void){
	usun(nazwa_semafora);
}

void sygnal_wyjscie(int signal){
	printf("Sygnał przerwania, usuwanie semafora\n");
	usun (nazwa_semafora);
	_exit(EXIT_SUCCESS);
}

int main (int argc, char *argv[]){
	
	if (argc != 5) {
		printf ("Błąd: niepoprawna liczba argumentów!\n");
		printf ("Wywołaj program wpisując: %s nazwe podprogramu ilosc procesow ilosc sekcji krytycznych nazwa semafora\n", argv[0]);
		exit (EXIT_FAILURE);
	}
	
	if (atexit (wyjscie) != 0) {
		perror("atexit error");
		exit(EXIT_FAILURE);
	}
	
	if (signal (SIGINT, sygnal_wyjscie) == SIG_ERR) {
		perror("Błąd signal");
		exit(EXIT_FAILURE);
	}
	
	int wait_id;
	int n;
	int plik;
	
	char temp[strlen(argv[1]) + 3];
	n = atoi (argv[2]);
	strcpy (nazwa_semafora, argv[4]);
	
	
	if ((plik = open ("numer.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644)) == -1) {
		printf ("Błąd otwarcia pliku do zapisu");
		perror ("Błąd pliku");
		exit (EXIT_FAILURE);
	}
	
	if (write (plik, "0", 2) == -1){
		perror("Błąd write do pliku");
		exit(EXIT_FAILURE);
	}
	
	if (close (plik) == -1) {
		perror ("Błąd zamknięcia pliku");
		exit (EXIT_FAILURE);
	}
	
	
	sem_t *semafor = stworz(nazwa_semafora);
	int wartosc_semafora;
	wartosc (semafor, &wartosc_semafora);
	printf ("Utworzono semafor %s (%p) o wartości %d\n", nazwa_semafora, (void *)semafor, wartosc_semafora);

	
	for (int i = 0; i < n; i++) {
		
		switch (fork ()) {
			case -1:
				perror("fork error");
				exit(EXIT_FAILURE);
			case 0:				
				sprintf (temp, "%s%s", SCIEZKA, argv[1]);
				execl (temp, argv[1], argv[3], argv[4], NULL); 
				perror ("execl error");
				exit(EXIT_FAILURE);
				
				break;
				
			default:
				
				break;
				
		}
	}
	
	for (int i = 0; i < n; i++) {
		if (wait (&wait_id) == -1) {
			perror ("Błąd wait");
			exit (EXIT_FAILURE);
		}
	}
	
	if ((plik = open ("numer.txt", O_RDONLY, 0644)) == -1) {
		printf ("Błąd otwarcia pliku do odczytu");
		perror ("Błąd pliku");
		exit (EXIT_FAILURE);
	}
	
	int odczyt;
	char bufor[10];
	
	odczyt = read(plik, &bufor, 10);
	if (odczyt == -1) {
		printf("Błąd odczytu z pliku\n");
		exit(EXIT_FAILURE);
	} else if (odczyt == 0) {
		printf("Plik jest pusty!\n");
		exit(EXIT_FAILURE);
	} else {
		if (atoi(bufor) == (atoi (argv[2]) * atoi (argv[3]))) {
			printf ("\nProgram zakończony pomyślnie! Liczba w pliku: %s\n", bufor);
		} else {
			printf ("\nProgram nie zadziałał poprawnie! Liczba w pliku: %s, oczekiwano: %d\n", bufor, (atoi (argv[2]) * atoi (argv[3])));
		}
	}
	
	if (close (plik) == -1) {
		perror ("Błąd zamknięcia pliku");
		exit (EXIT_FAILURE);
	}
	
	return 0;
}