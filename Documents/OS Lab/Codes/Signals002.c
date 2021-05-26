#include<unistd.h>
#include<stdio.h>
#include<signal.h>

void handle_stop( int sig)
{
  // Process will not terminate
  sleep(1);
  printf("Process doesnot stop\n");
}

int main()
{
    //Method01 to ignore signal
    if (SIG_ERR != signal (SIGKILL, SIG_IGN))    //Since ignoring the sigkill will generate an error, printf should not be executed
    {
      printf("\n SIGKILL can't be ignored");
    }  
    
    //Method02 to ignore signal
    struct sigaction sa;
    sa.sa_handler = &handle_stop;
    sa.sa_flags = SA_RESTART;
    sigaction(SIGTSTP, &sa ,NULL);
    
    //Testing Code
    int num;

    printf("Enter Number");
    scanf("%d", &num);       //CTRL+Z to stop process
    return 0;
}
