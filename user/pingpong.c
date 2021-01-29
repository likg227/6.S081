#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int 
main(){
    int P_1[2] = {3, 4};
    int P_2[2] = {5, 6};
    pipe(P_1);
    pipe(P_2);
    
    write(P_1[1], (void*)'P', 1);

    if(fork() == 0){

        printf("%d: received ping\n", getpid());
        
        char g_byte[1];
        read(P_1[0], g_byte, 1);
        write(P_2[1], g_byte, 1);
        exit(0);
    }
    else
    {
        wait(0);
        char get_byte[1];
        read(P_2[0], get_byte, 1);
        printf("%d: received pong\n", getpid());
        exit(0);
    }
}