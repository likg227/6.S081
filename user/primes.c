#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
void E_prime(int P_1[], int P_2[]){


    int get_num[1];
    
    read(P_1[0], get_num, sizeof(get_num));
    int p = get_num[0];
    printf("prime %d\n", p);

    pipe(P_2);

    while (read(P_1[0], get_num, sizeof(get_num)) > 0)
    {
        if(get_num[0] % p != 0){
            //printf("get %d\n", get_num[0]);
            write(P_2[1], get_num, sizeof(get_num));
        }
    }
    //printf("while loop succeed finishing!\n");
    close(P_2[1]);
    return;
}

int main(){
    int Pipe[12][2];

    pipe(Pipe[0]);

    int send_num[1];
    for(int i = 2; i <= 35; ++i){
        send_num[0] = i;
        write(Pipe[0][1], send_num, sizeof(send_num));
    }
    close(Pipe[0][1]);
    for (int i = 0; i < 11; ++i)
    {   //printf("this is the %dth turn\n", i);
        if(fork() == 0){
            //printf("this is process %d", i);
            E_prime(Pipe[i], Pipe[i+1]);
            //printf("E_prime has succeed exitting\n");
        }
        else
        {
            wait(0);
            exit(0);
        }   
    }
    exit(0);
}