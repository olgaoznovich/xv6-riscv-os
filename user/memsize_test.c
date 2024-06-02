#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
    printf("memsize before allocation: %d\n", memsize());
    void* allocation = malloc(20000);
    printf("memsize after allocation: %d\n", memsize());
    free(allocation);
    printf("memsize after freeing: %d\n", memsize());

    exit(0,"");
}