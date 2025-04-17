#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(){
    int UID = getuid();
    int GID = getgid();
    int PID = getpid();
    int PPID = getppid();
    int PGID = getpgid(PID);
    printf("Identyfikatory procesu:\n");
    printf("UID = %d, ",UID);
    printf("GID = %d, ",GID);
    printf("PID = %d, ",PID);
    printf("PPID = %d, ",PPID);
    printf("PGID = %d\n",PGID);
    return 0;
}
