#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>   /* pour avoir wait & co. */
#include <ctype.h>      /* pour avoir isspace & co. */
#include <string.h>
#include <errno.h>      /* pour avoir errno */
#include <signal.h>

int main(){
	
	int i;
	printf("Un test pour le Ctr+C et Ctr+Z\n");
	for (i=0;i<10;i++){
		printf("%d\n",i);
		sleep(6);
	}

	return 0;
}
