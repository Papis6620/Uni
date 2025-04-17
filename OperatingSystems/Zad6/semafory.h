#ifndef SEMAFORY_H
#define SEMAFORY_H

sem_t *stworz (const char *name);
sem_t *otworz (const char *name);
void zamknij (sem_t *sem_t);
void wartosc (sem_t *sem, int *sval);
void podnies (sem_t *sem);
void opusc (sem_t *sem);
void usun (const char *name);

#endif