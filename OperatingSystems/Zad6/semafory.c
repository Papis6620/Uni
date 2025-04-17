#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

sem_t *stworz(const char *name) {
	sem_t *adres_semafora;
	if ((adres_semafora = sem_open(name, O_CREAT | O_EXCL, 0644, 1)) == SEM_FAILED) {
		perror ("błąd tworzenia semafora");
		exit (EXIT_FAILURE);
	} else {
		return adres_semafora;
	}
}

sem_t *otworz(const char *name) {
	sem_t *adres_semafora;
	if ((adres_semafora = sem_open(name, 0)) == SEM_FAILED) {
		perror ("błąd otworzenia semafora");
		exit (EXIT_FAILURE);
	} else {
		return adres_semafora;
	}
}

void zamknij(sem_t *sem_t) {
	if (sem_close (sem_t) == -1) {
		perror ("błąd zamykania semafora");
		exit (EXIT_FAILURE);
	}
}

void wartosc(sem_t *sem, int *sval) {
	if (sem_getvalue(sem, sval) == -1) {
		perror ("błąd odczytywania wartości semafora");
		exit (EXIT_FAILURE);
	}
}

void podnies(sem_t *sem) {
	if (sem_post(sem) == -1) {
		perror ("błąd podnoszenia semafora");
		exit (EXIT_FAILURE);
	}
}

void opusc(sem_t *sem) {
	if (sem_wait(sem) == -1) {
		perror ("błąd opuszczania semafora");
		exit (EXIT_FAILURE);
	}
}

void usun(const char *name) {
	if (sem_unlink(name) == -1) {
		perror ("błąd usuwania semafora");
		exit (EXIT_FAILURE);
	}
}