/** TIBA - UZAN **/

#include "myshell.h"

/* clearjob - Clear the entries in a job struct */
void jobvide(job *job)
{
    job->job_pid = 0;
    job->job_number = 0;
    job->sig = UNDEF;
    job->cmdline[0] = '\0';
}

/* initjobs - Initialilsation de la liste des jobs */
void initialisation(job *TabJob) 
{
	prochainjob = 1;
    int i;
    for (i = 0; i < MAXJOBS; i++)
		jobvide(&TabJob[i]);
}

int premierecase(job *TabJob)
{
	int i;
		for(i=0;i< MAXJOBS;i++){
			if(TabJob[i].sig==10){
				return i;
			}
		}
	return -1;
}

/* addjob - Ajouter un job */
int ajouterjob(job *TabJob, pid_t job_pid, int sig, char *cmdline)
{
    int i;
    
    if (job_pid < 1)
	return 0;

    for (i = 0; i < MAXJOBS; i++) {
	if (TabJob[i].job_pid == 0) {
	    TabJob[i].job_pid = job_pid;
	    TabJob[i].sig = sig;
	    TabJob[i].job_number = prochainjob++;
	    if (prochainjob > MAXJOBS)
		prochainjob = 1;
	    strcpy(TabJob[i].cmdline, cmdline);
	    printf("Job Ajouté [%d] %d %s\n", TabJob[i].job_number, TabJob[i].job_pid, TabJob[i].cmdline);
        return 1;
	}
    }
    printf("Essayé de créer trop de Jobs\n");
    return 0;
}

/* maxjid - Rretourner le maximum des jobs */
int maxjid(job *TabJob) 
{
    int i, max=0;

    for (i = 0; i < MAXJOBS; i++)
	if (TabJob[i].job_number > max)
	    max = TabJob[i].job_number;
    return max;
}

/* deletejob - Suprimer un job de la liste */
int deletejob(job *TabJob, pid_t job_pid)
{
    int i;

    if (job_pid < 1)
	return 0;

    for (i = 0; i < MAXJOBS; i++) {
		if (TabJob[i].job_pid == job_pid) {
		    jobvide(&TabJob[i]);
		    prochainjob = maxjid(TabJob)+1;
		    return 1;
		}
    }
    return 0;
}

/* premierplan - 
Retour PID du travail de premier plan en cours, 0 si aucun job */
pid_t premierplan(job *TabJob)
{
    int i;

    for (i = 0; i < MAXJOBS; i++)
	if (TabJob[i].sig == FG)
	    return TabJob[i].job_pid;
    return 0;
}

/* jobbypid  - trouver un job (by PID) dans la liste des jobs*/
job* jobbypid(job *TabJob, pid_t job_pid)
{
    int i;

    if (job_pid < 1)
	return NULL;

    for (i = 0; i < MAXJOBS; i++)
	if (TabJob[i].job_pid == job_pid)
	    return &TabJob[i];
    return NULL;
}

/* jobbyid  - trouver un job (by ID) dans la liste des jobs */
job* jobbyid(job *TabJob, int job_number)
{
    int i;

    if (job_number < 1)
	return NULL;
    for (i = 0; i < MAXJOBS; i++)
	if (TabJob[i].job_number == job_number)
	    return &TabJob[i];
    return NULL;
}

/* afficher - afficher la liste des jobs */
void afficher(job *TabJob)
{
	    int i;
	    
	    for (i = 0; i < MAXJOBS; i++) {
		if (TabJob[i].job_pid != 0) {
		    printf("[%d] (%d) ", TabJob[i].job_number, TabJob[i].job_pid);
		    switch (TabJob[i].sig) {
			case BG: 
			    printf("En cours d'exécution ");
			    break;
			case FG: 
			    printf("Premier plan ");
			    break;
			case ST: 
			    printf("Arrêté ");
			    break;
		    default:
			    printf("listjobs: Erreur interne: job[%d].Sig=%d ", 
				   i, TabJob[i].sig);
		    }
		    printf("%s \n", TabJob[i].cmdline);
		}
	}
}

/* pid2jid - PID to job ID */
int pid2jid(pid_t pid) 
{
    int i;

    if (pid < 1)
	return 0;
    for (i = 0; i < MAXJOBS; i++)
	if (TabJob[i].job_pid == pid) {
            return TabJob[i].job_number;
        }
    return 0;
}


