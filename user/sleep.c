#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int 
main(int argc, char* argv[]){
    if(argc < 2){
        fprintf(2, "sleep has no argument\n");
        exit(1);
    }
    int time_len = atoi(argv[1]);
    if(sleep(time_len) < 0){
        fprintf(2, "sleep failed\n");
        exit(1);
    }
    exit(0);
}