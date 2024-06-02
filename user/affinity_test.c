#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
    set_affinity_mask(0b00101);
    while(1) {
        printf("process pid: %d\n", getpid());
    }
}