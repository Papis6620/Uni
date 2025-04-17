#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int pd_stworz(const char *name);
int pd_otworz(const char *name);
void pd_zamknij(int fd);
void pd_usun(const char *name);
void *pd_mmap(size_t length, int fd);
void pd_munmap(void *adres, size_t length);
void pd_ftrunacte(int fd, size_t length);
