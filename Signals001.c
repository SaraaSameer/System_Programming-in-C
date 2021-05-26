//Signal Handling through Sigaction
#include<stdio.h>
#include<signal.h>
#include<unistd.h>


void signal_handler(int signo)
{
if (signo == SIGUSR1)
printf("received SIGUSR1\n");
else if (signo == SIGKILL)
printf("received SIGKILL\n");
else if (signo == SIGSTOP)
printf("received SIGSTOP\n");
}



int main(void)
{
    struct sigaction sa;
    sa.sa_handler = &signal_handler;
    if (sigaction(SIGUSR1, &sa, NULL) == SIG_ERR)
    {
       printf("\nCan't catch SIGUSR1\n");
    }
     if (sigaction(SIGKILL, &sa, NULL) == SIG_ERR)
    {
       printf("\nCan't catch SIGKILL\n");
    }
     if (sigaction(SIGSTOP, &sa, NULL) == SIG_ERR)
    {
       printf("\nCan't catch SIGSTOP\n");
    }

    while(1)
    sleep(1);
    return 0;    
}
    
