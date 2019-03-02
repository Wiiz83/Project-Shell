/** TIBA - UZAN **/

#include "csapp.h"
#define MAXARGS 128
#define MAXJOBS 10

/* Job states */
#define UNDEF 0 /* undefined */
#define FG 1    /* running in foreground */
#define BG 2    /* running in background */
#define ST 3    /* stopped */

typedef struct {
	int job_number;	// numéro du job(entier>0)
	pid_t job_pid;	// pid du processus qui l'execute
	int sig; 	// état du job
	char cmdline[MAXARGS]; //ligne de commande executée par le job
} job;

job TabJob[MAXJOBS];
int prochainjob;    /* next job ID to allocate */


// PRIMITIVES
int parseline(char *buf, char **argv);
int builtin_command(char **argv);
void eval(char*cmdline);
void bg_fg(char **argv);

void sigchld_handler(int sig);
void sigint_handler(int sig);
void sigtstp_handler(int sig);
void sigquit_handler(int sig);

void waitfg(pid_t pid);
int maxjid(job *TabJob);
void jobvide(job *job);
void initialisation(job *TabJob);
int premierecase(job *TabJob);
int ajouterjob(job *TabJob, pid_t job_pid, int sig, char *cmdline);
int deletejob(job *TabJob, pid_t job_pid);
pid_t premierplan(job *TabJob);
job *jobbypid(job *TabJob, pid_t job_pid);
job *jobbyid(job *TabJob, int job_number);
void afficher(job *TabJob);
int pid2jid(pid_t pid);






