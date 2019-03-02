/** TIBA - UZAN **/

#include "myshell.h"

void bg_fg(char **argv) 
{
	job* jobp=NULL;
	char *numeros;
	int i;
	if(argv[1] == NULL) {  //no argument
        printf("%s commande demande PID ou %%jobid argument\n", argv[0]);  
        return;  
    }  	
	
	if(argv[1][0]=='%') //numero argument
	{
		numeros=argv[1]+sizeof(char); //ignore initial '%' 
		
		//check formatting
		for(i=0;i<strlen(numeros);i++){
			if(!isdigit(numeros[i])) {
				printf("%s: argument devra etre un PID ou %%ID\n",argv[0]);	
				return;
			}
		}	
		int job_number=atoi(numeros);
		
		// check job is in list
		if((jobp = jobbyid(TabJob, job_number)) == NULL) {  
            printf("%%%s: Aucun tel job\n", numeros);  
            return;  
        }  		
		jobp=jobbyid(TabJob,job_number);	// retourner job by num
	}

	else if(atoi(argv[1])!=0){ //pid argument
		numeros=argv[1];
		
		//check formatting
		for(i=0;i<strlen(numeros);i++){
			if(!isdigit(numeros[i])) {
				printf("%s: argument devra etre un PID ou %%ID\n",argv[0]);
				return;
			}
		}			
		pid_t job_pid=atoi(numeros);
		
		//check if process is in list
		if((jobp=jobbypid(TabJob,job_pid)) == NULL) {  
            printf("(%s): Aucun tel job\n", numeros);  
            return;  
        }  			
	}

	else { 
		printf("%s: argument devra etre un PID ou %%ID\n",argv[0]);
		return;
	}
	
	if(!strcmp(argv[0],"bg")) //bg
	{
    	TabJob->sig=BG; //affecte BG au Signale
		kill(-(TabJob->job_pid), SIGCONT); //on envoie le signal
		printf("[%d] (%d) %s\n", TabJob->job_number,TabJob->job_pid, TabJob->cmdline);	
	}

	else
	{
        TabJob->sig=FG; //affecte FG au Signale
        kill(-(TabJob->job_pid), SIGCONT); 
		//waitfg(TabJob->job_pid); //wait for process to terminate

	}
}
