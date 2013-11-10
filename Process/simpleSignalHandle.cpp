#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

void mySigHandler(int signalId)
{
	printf("Handler for SIGTERM called\n");
}

void  INThandler(int sig)
{
     char  c;

     signal(sig, SIG_IGN);
     printf("OUCH, did you hit Ctrl-C?\n"
            "Do you really want to quit? [y/n] ");
     c = getchar();
     if (c == 'y' || c == 'Y')
          exit(0);
     else
          signal(SIGINT, INThandler);
     getchar(); // Get new line character
}


int main()
{
	signal(SIGINT, INThandler);
	signal(SIGTERM, mySigHandler);
     while (1);
     return 0;

	return 1;
}
