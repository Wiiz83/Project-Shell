#include "csapp.h"
#include <stdio.h>

int main(int argc ,char * argv[]){
	pid_t pid,pid2,pid3,ppid1,ppid2;
	pid = fork();
	while(1){
	//printf("le numéro du processus :%d , le numéro du père :%d\n ",getpid(),getppid());
	if(pid !=0 ){//pere
		printf("je suis le père, mon PID est %d et mon PPID est %d\n",getpid(),getppid());
		pid2 = fork();
			if(pid2 !=0 ){ //pere
				//printf("je suis le père, mon PID est %d et mon PPID est %d\n",getpid(),getppid());
				pid3 = fork();
				if(pid3 != 0){//pere
					//printf("je suis le père, mon PID est %d et mon PPID est %d\n",getpid(),getppid());
				}
				else{//fils3
					printf("je suis le troisième fils, mon PID est %d et mon PPID est %d\n",getpid(),getppid());
				}


			}
			else { // fils2
				printf("je suis le deuxième fils, mon PID est %d et mon PPID est %d\n",getpid(),getppid());

			}
	}
	else { //fils 1
		printf("je suis le premier fils, mon PID est %d et mon PPID est %d\n",getpid(),getppid());
		ppid1 = fork();
			if(ppid1!=0){ // je suis le fils1
				//printf("je suis le premier fils, mon PID est %d et mon PPID est %d\n",getpid(),getppid());
				ppid2 = fork();
				if(ppid2 != 0){//fils1
					//printf("je suis le premier fils, mon PID est %d et mon PPID est %d\n",getpid(),getppid());
				}
				else{//petit-fils2
					printf("je suis le petit fils2, mon PID est %d et mon PPID est %d\n",getpid(),getppid());
				}
				
				
			}else{//le petit fils 1
				printf("je suis le petit fils1, mon PID est %d et mon PPID est %d\n",getpid(),getppid());
			}
	}

		sleep(1);
	}
		return 0;
}
