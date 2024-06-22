#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"


int main(int argc, char *argv[]){
    int cd = channel_create();
    printf("cahnnel des=%d", cd);
    if (cd < 0)
    {
        printf("Failed to create channel\n");
        exit(1);
    }
    else{
        printf("cd=%d\n", cd);
    }
    if (fork() == 0) 
    {
        if (channel_put(cd, 42) < 0) 
        {
            printf("Failed to put data in channel\n");
            exit(1);
        }
        else{
            printf("succses put\n");
        }
        channel_put(cd, 43); // Sleeps until cleared

        channel_destroy(cd);
        // Handle error
    } else 
    {
        int data;
        if (channel_take(cd, &data) < 0) 
        { // 42
            printf("Failed to take data from channel\n");
            exit(1);
        }
        else{
            printf("succses take\n");
        }
        data = channel_take(cd, &data); // 43
        // Handle error
        data = channel_take(cd, &data); // Sleep until child destroys channel
        // Handle error
    }
    printf("exit");
    exit(0);
}
