#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include <pthread.h>

int mutex; 
void program(int numChekers);
int
main(int argc, char *argv[])
{
  char buf[10];
  int numChekers = 3;
  if(argc > 1){
    numChekers = atoi(argv[1]);
  }
   int run = 1;
   while (run)
   {
     program(numChekers);
     wait(0);
     int answer = 0;
     while (answer == 0)
     {
        while (wait(0) > 0);
        printf("An 100 primes were printed start agaim?[Y/N]\n");
        // pthread_mutex_unlock(&mutex);
        gets(buf, sizeof(buf));
        if (buf[0] == 'Y' || buf[0] == 'N')
        {
            answer = 1;
        }
     }
     if (buf[0] == 'N')
     {
        run = 0;
     }
   }
  printf("pid=%d\n", getpid());
  printf("Shudown procces finish\n");
  exit(0);
}


void program(int numChekers){
  int pid = -1;
  int printerid;
  int *checkers = (int *)malloc(sizeof(int) * numChekers); 
  int channel1 = channel_create();
  int channel2 = channel_create();
  
  printerid = fork();
  if(printerid > 0){
    for(int i=0; i < numChekers; i++){
        pid = fork();
        if(pid == 0){
            break;
        }
        else{
            checkers[i] = pid;
        }
    }
  }
  if(pid > 0)
  {
    // main proces
    int num = 2;
    int channelExist1 = 0;
    while (channelExist1 != -1)
    {
        channelExist1 = channel_put(channel1, num);
        num++;
    }
    
  }
  else if(printerid == 0)
  {
    //printer
    int counter = 1;
    int channelExist2 = 0;
    int * data = (int *)malloc(sizeof(int));
    while (counter < 101)
    {
       channelExist2 = channel_take(channel2, data);
       if(channelExist2 == 0){
         printf("count=%d num=%d\n",counter,  *data);
         counter ++;
       }
    }
    channel_destroy(channel2);
    printf("pid=%d\n", getpid());
    printf("Shudown printer procces\n");
    exit(0);
  }
  else
  {
    // cheker proces
    int channelExist2 = 0;
    while (channelExist2 != -1)
    {
        int * data = (int *)malloc(sizeof(int));
        *data = 0;
        channel_take(channel1, data);
        int found = 0;
        for(int i =2; i * i<= *data && found != 1; i++){
            if(*data % i == 0){
                found = 1;
            }
        }
        if(found ==0){
            // prime 
            channelExist2 = channel_put(channel2, *data);
        }
    }
    channel_destroy(channel1);
    printf("pid=%d\n", getpid());
    printf("Shudown cheker procces\n");
    exit(0);
  }
  wait(0);
}
