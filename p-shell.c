#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/types.h>
#include <wait.h>
#include <sys/resource.h>

/**
 * 
 * shell runs this program when exec cmd is called
 * 
*/

int main (char* argc[], char* argv[])
{
	int i;
	int num;
	int sltime;
	
	num = atoi(argv[1]);
	sltime = 1000 * atoi(argv[2]);
	
	printf("This is program %s and it prints %d times...\n\n", argv[0], num);
	
	if (*argv[3] != 1)
	{
		// forground process
		for (i=1; i<=num; i++)
		{
			printf("This is program %s and it prints for the %d time of %d...\n",argv[0],i,num);
			usleep(sltime);
		}
	}
	else
	{
		// background process
		for (i=1; i<=num; i++)
		{
			usleep(sltime);
		}
	}
	
	return 0;		
}
