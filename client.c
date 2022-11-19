#include "includes/minitalk.h"

void charToBits(int server_id, char caracter)
{
    int bitForm;

    bitForm = 8;
    while (bitForm > 0)
    {
        if ((caracter % 2) == 1)
        {
            //write(1, "1", 1);
            kill(server_id, SIGUSR1);
        }
        if ((caracter % 2) == 0)
        {
            //write(1, "0", 1);
            kill(server_id, SIGUSR2);
        }
        usleep(50);
		caracter /= 2; 
        bitForm--;
    }
}

void sendMessage(int server_id, char *message)
{
    int i;
	char caracter;
    // message should be sent as a number of bits 8 bits is a character no matter how many bits signals 
    i = 0;
    while (message[i])
    {
		caracter = message[i];
        charToBits(server_id, caracter);
        i++;
    }
    caracter = message[i];
    charToBits(server_id, caracter);
}

//lets simulate a client by trigerring a signal on the process pid that is on pause waiting for us to talk to 

int main(int argc, char** argv)
{
    if (argc > 3 || argc < 2)
    {
        write(1, "error usage ALBATALE : ./a.out server_ID string_MSG\n", 47);
        exit(1);
    }
    else
    {
        int server_id = atoi(argv[1]);
        if (argv[2] == NULL)
        {
            write(1, "received PID Listenning : ", 26);
            write(1, argv[1], strlen(argv[1]));
            write(1, "\n", 1);
            write(1, "send a message a batale to the listenning pid\n", 46);
        }
        else
        {
            sendMessage(server_id, argv[2]);
        }
    }
    return (0);
}