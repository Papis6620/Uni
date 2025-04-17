#include "pd.h"
#include <unistd.h>
#include <stdlib.h>
#include <stddef.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int pd_stworz(const char *name){
    int deskryptor = shm_open(name, O_EXCL | O_RDWR | O_CREAT, 0644);
    if(deskryptor == -1){
        perror("shm_open error");
        exit(EXIT_FAILURE);
    }else{
        return deskryptor;
    }
}
int pd_otworz(const char *name){
    int deskryptor = shm_open(name, O_RDWR, 0644);
    if(deskryptor == -1){
        perror("shm_open error");
        exit(EXIT_FAILURE);
    }else{
        return deskryptor;
    }
}
void pd_zamknij(int fd){
    if(close(fd) == -1){
        perror("close error");
        exit(EXIT_FAILURE);
    }
}
void pd_usun(const char *name){
    if(shm_unlink(name) == -1){
        perror("shm_unlink error");
        exit(EXIT_FAILURE);
    }
}
void *pd_mmap(size_t length, int fd){
    void *adres = mmap(NULL, length, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if(adres == MAP_FAILED){
        perror("mmap error");
        exit(EXIT_FAILURE);
    }else{
        return adres;
    }
}
void pd_munmap(void *adres, size_t length){
    if(munmap(adres, length) == -1){
        perror("munmap error");
        exit(EXIT_FAILURE);
    }
}
void pd_ftrunacte(int fd, size_t length){
    if(ftruncate(fd, length) == -1){
        perror("ftruncate error");
        exit(EXIT_FAILURE);
    }
}