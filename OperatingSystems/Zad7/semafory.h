#ifndef SEMAFORY_H
#define SEMAFORY_H

sem_t *stworz (const char *name, int value);
sem_t *otworz (const char *name);
void zamknij (sem_t *sem_t);
int wartosc (sem_t *sem);
void podnies (sem_t *sem);
void opusc (sem_t *sem);
void usun (const char *name);

#endif