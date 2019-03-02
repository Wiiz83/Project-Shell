/** TIBA - UZAN **/

/* eval : interprete une ligne de commande passee en parametre*/
#include "myshell.h"

void eval(char *cmdline)
{
    char *argv[MAXARGS]; // argv pour execve()
    char buf[MAXLINE];   // contient ligne commande modifiee
    int bg;              // arriere-plan ou premier plan ?
    pid_t pid;           // process id

    strcpy(buf, cmdline);
    bg = parseline(buf, argv);
    
    //initialiser un ensemble de signaux qui ne contient que SIGCHLD
	sigset_t signalSet;  
	sigemptyset(&signalSet);
	sigaddset(&signalSet, SIGCHLD);

    if (argv[0] == NULL)
        return;                      // ignorer lignes vides

    if (!builtin_command(argv)) {    // commande integree ?
        
        /* block SIGCHLD signal */	
		sigprocmask(SIG_BLOCK, &signalSet, NULL);
        
        // si oui, executee directement
        if ((pid = Fork()) == 0) {   // si non, executee par un fils

		    // Créer un nouveau groupe de processus avec les fils
		    //setpgid(0, 0);

		    //unblock SIGCHLD signal
		    sigprocmask(SIG_UNBLOCK, &signalSet, NULL);        
	    
            if (execvp(argv[0],argv) < 0) {
                printf("%s: Command not found.\n", argv[0]);
                exit(0);
            }
            exit(0);
        }

        /*parent*/	
        if (!bg) { // le pere attend fin du travail de premier plan
            //int status;
		    ajouterjob(TabJob, pid, FG, cmdline); //add fg job
		    sigprocmask(SIG_UNBLOCK, &signalSet, NULL);
            /*if (waitpid(pid, &status, 0) < 0){
                unix_error("waitfg: waitpid error");
            }*/
            waitfg(pid);    
        }else {

        	// travail d'arriere-plan, on imprime le pid
	    	ajouterjob(TabJob, pid, BG, cmdline); //add fg job
			printf("[%d] (%d) %s",jobbypid(TabJob, pid)->job_number,pid,cmdline); 	            
            sigprocmask(SIG_UNBLOCK, &signalSet, NULL);   //unblock signal
        }
    }
}


void waitfg(pid_t pid)
{
	while(pid == premierplan(TabJob)) { 
		sleep(0);
	}
}


// si le premier parametre est une commande integree,
// l'executer et renvoyer "vrai"
int builtin_command(char **argv)
{

    if (!strcmp(argv[0], "quit")) // commande "quitter"
        exit(0);
    if (!strcmp(argv[0], "&"))    // ignorer & tout seul
        return 1;

    if (!strcmp(argv[0],"fg") || !strcmp(argv[0],"bg")) {
        bg_fg(argv);
        return 1;
    }

    if (!strcmp(argv[0], "jobs")){ // commande "jobs"
        afficher(TabJob);
        return 1;
    }

    return 0;                 // ce n'est pas une commande integree
}
