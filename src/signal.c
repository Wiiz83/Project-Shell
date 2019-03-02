/** TIBA - UZAN **/

#include "myshell.h"

/*****************
 * Signal handlers
 *****************/

/* Sigchld_handler - Le noyau envoie un SIGCHLD au shell à chaque fois que se termine un travail 
d enfant (devient un zombie), ou arrête parce qu'il a reçu un SIGSTOP ou SIGTSTP. 
Le Handler recueille tous les enfants de zombies disponibles, 
mais ne pas attendre pour tous les autres enfants qui courent 
actuellement de mettre fin.*/ 

void sigchld_handler(int sig) 
{
    int status;
    int pid=1;
    while(pid>0){
        pid=waitpid(-1,&status,WNOHANG|WUNTRACED);  // Retourne pid d'un enfant dont l'état a changé
        
        if(pid>0) // si l'état est changé 
        {
            if(WIFEXITED(status)) // Enfant est sorti normalement (exit)
                deletejob(TabJob,pid);
            else {
				if(WIFSIGNALED(status)){  /* enfant est sorti parce qu'un signal ne soit pas pris */
					if(WTERMSIG(status)==2) //si le signal qui a causé l'enfant de mettre fin est 2, il a été mis fin par un processus différent 			
						printf("Job [%d] (%d) Terminé par le signal %d\n", pid2jid(pid), pid, WTERMSIG(status));
					deletejob(TabJob,pid);
				}
				else if(WIFSTOPPED(status)){    /* child stopped by receipt of a signal */
					jobbypid(TabJob,pid)->sig=ST;
					printf("Job [%d] (%d) Arrêté par le signal %d\n", pid2jid(pid), pid, WSTOPSIG(status));
				}
			}
        }        
    }	
}

/* 
Sigint_handler - Le noyau envoie un SIGINT au shell à chaque fois que les
types d'utilisateurs ctrl-c au clavier. 
Attrapez et l'envoyer * au poste de premier plan.
 */
void sigint_handler(int sig) 
{
    	int fg_pid;
	
	// assurer qu'il est un fg travail
	if((fg_pid=premierplan(TabJob))==0)
		return;
    
	// evoyer le signal à fg job
	kill(-(fg_pid), SIGINT);
}

/* 
sigtstp_handler - Le noyau envoie un SIGINT au shell à chaque fois que les
types d'utilisateurs ctrl-z au clavier. 
Attrapez et l'envoyer * au poste de premier plan.
 */
void sigtstp_handler(int sig) 
{
    	int fg_pid;
	
	// assurer qu'il est un fg travail
	if((fg_pid=premierplan(TabJob))==0)
		return;
    
	// evoyer le signal à fg job
	kill(-(fg_pid), SIGSTOP);
	kill(-(fg_pid), SIGTSTP);

}




