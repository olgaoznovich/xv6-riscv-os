#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
    
    // char* msg = malloc(18);
    char* msg = "Goodbye World xv6";
    printf("goodbye.c 11 hehe: %s\n", msg);
    printf("goodbye.c 11 hehe: %p\n", msg);
    exit(1507, msg);
}

