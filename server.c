#include "./includes/minitalk.h"

void signalStateHandler(int signum, siginfo_t *info, void *ucontext)
{
	static int              caracter = 0;
	static int	            bitForm = 0;
    int                     arr[8] = {128, 64, 32, 16, 8, 4, 2, 1};

    if (bitForm < 8)
    {
        if (signum == SIGUSR1)
            caracter = caracter + arr[7 - bitForm];
        bitForm++;
    }
	if (bitForm == 8)
	{
		write(1, &caracter, 1);
		if (caracter == 0) // after the null caracter we print a newline to stdout to make thing clear
            write(1, "\n", 1);
        caracter = 0;
		bitForm = 0;
	}
}

int main ()
{
    struct sigaction    saFamily;
    int                 serverPid;
    
    serverPid = getpid();
    saFamily.sa_sigaction = signalStateHandler;
    saFamily.sa_flags = SA_SIGINFO;
    write(1, "ServerPid  :", 12);
    printf("[%d]\n", serverPid);
    sigaction(SIGUSR1, &saFamily, NULL);
    sigaction(SIGUSR2, &saFamily, NULL);
    while (1)
        pause();
    return (0);
}