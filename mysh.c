/*Programmer: Dalina Beckham
 * Purpose: Created a shell to work with stat, tail, python file, ls, and recursive commands.
 */

#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#define _GNU_SOURCE


void command (char* cmdline){
   char error_message[30] = "An error has occurred\n";
   char *args[100];
	int letgo =0;
//fprintf(stdout, "command : %s", cmdline);
//do python
	char *tempPy = (char * )malloc(strlen(cmdline));
//fprintf(stdout, "before strcpy %s", tempPy);

    	strcpy (tempPy, cmdline);
//	fprintf(stdout, "temppy %s", tempPy);

//fprintf(stdout, "temppy %s", tempPy);
    	char *pyToken = strtok(cmdline, " \n");
//fprintf(stdout, "before python: %s", pyToken);
	if(pyToken != NULL ){
//fprintf(stdout, "pytok not null %s",pyToken+strlen(pyToken)-4);
		if (strcmp(pyToken+strlen(pyToken)-3, ".py")==0){
//	fprintf(stdout, "pythong here:");
			cmdline = (char* )malloc(strlen(tempPy)+7);
//		fprintf(stdout, "before:%s", cmdline);
			strcpy(cmdline, "python ");
			strcpy((cmdline+7), tempPy);
//fprintf(stdout, "after:%s",cmdline );
//cmdline = strcat("python ", cmdline);
			letgo =1;	
		}
		else{
//fprintf(stdout, "bbefore cmdline copy");
//fprintf(stdout," before strcpy temppy %s\n", tempPy);

			strcpy(cmdline, tempPy);
//fprintf(stdout,"cmd line %s\n", cmdline);
//fprintf(stdout,"temppy %s\n", tempPy);

		}
		//*pyToken = '\0';
	}
	if( letgo==1){
		free(tempPy);//end of python check
	}
//fprintf(stdout, "before background: %s", cmdline);
//do background job
//fprintf(stdout, "this: %s", cmdline);
	
	int background =0;	
	char* ampy= strstr(cmdline, "&");
		if(ampy !=NULL){
			*ampy = '\0';
			background = 1;
		}//end of backgrounds
//fprintf(stdout, "before redirect: %s", cmdline);
//do redirectoion
	int redirect = 0;
	int redirArgs = 0;
	char* outfile;// = "/file/not/found";
	char* redirTok = strtok(cmdline, ">");
		while(redirTok !=NULL){
			redirArgs++;
			outfile = redirTok;
			redirTok = strtok(NULL, ">");
		}	
	if( redirArgs ==2){
//afprintf(stdout, "this is reidtok: %s",redirTok);
//fprintf(stdout, "redir is 2");
		int spacenum = 0;
		char *space = strtok(outfile, " \n\t\r");
			while(space!=NULL){
				spacenum++;
				space = strtok(NULL," \r\t\n");
			}
//	fprintf(stdout,"space num: %d\n",  spacenum);
			if(spacenum!=1){
	//			fprintf(stdout, "here 1\n");
				write(STDERR_FILENO, error_message, strlen(error_message));
					
				redirect = 0;
				return;
			}
			else{
	//			fprintf(stdout, "redir 1\n");
				redirect = 1;
			}
	}
	else if(redirArgs ==0){
	//			fprintf(stdout, "redirargs 0\n");
		write(STDERR_FILENO, error_message, strlen(error_message));

		redirect= 0;
	}
	else{
	//	fprintf(stdout, "redir is 0\n");

		redirect = 0;
	}//end if redirections



	//if (redirect == -1){
	//	return;
	//}
	
	int numArgs = 0;
	//splitting by spaces, tabs newlines
	char *word = strtok(cmdline, " \t\r\n");
//fprintf(stdout,"the word: %s", word);
	//if (word =='\0'){
	//	break;
	//}	
	args[0] = word;
	numArgs++;
	
	while (word!=NULL){
		word = strtok(NULL, " \t\n\r"); //resume where you left off passing null
		if (word =='\0'){
			continue;
		}
		else{
			args[numArgs] = word;
			numArgs++;
		}
	}
	args[numArgs] = '\0';//last is null to end

	if (strcmp(args[0],"exit")==0){		
		exit(0);
	}//end exit
	else if(numArgs == 0){
		return;
	}
	else if (strcmp(args[0], "cd") == 0){
	//	fprintf(stdout, "num arg: %s", args[1]);
		if(numArgs==1){
//			fprintf(stdout, "in here");
			char* homeDir = getenv("HOME");
			if(chdir(homeDir) != 0){
				write(STDERR_FILENO, error_message, strlen(error_message));
			}
		}	
		else if(numArgs ==2){
//					fprintf(stdout, "in here lab ");
			if(chdir(args[1]) != 0)	{
				write(STDERR_FILENO, error_message, strlen(error_message));
			}
		}
		else{
			write(STDERR_FILENO, error_message, strlen(error_message));
		}

	}//end cd
	else if (strcmp(args[0], "wait") == 0){
		if(numArgs != 1){
			write(STDERR_FILENO, error_message, strlen(error_message));
			return;	
		}
		else {
			pid_t pid;
			while (pid = waitpid(-1, NULL, 0)) {
   				if (errno == ECHILD) {
      					break;
   				}
			}
		}
	}//end wait
	else if(strlen(args[0]) >512){
//			fprintf(stdout, "very long");
			write(STDERR_FILENO, error_message, strlen(error_message));
			return;
		}
/*	else if(strcmp(args[0], "pwd") == 0 ){
		if(numArgs != 1){
			write(STDERR_FILENO, error_message, strlen(error_message));
			return;	
		}
		else {
			char* path=(char *)malloc(517);			
			path=getcwd(NULL,0);//get the path
			if (NULL == path){
         			write(STDERR_FILENO, error_message, strlen(error_message));
			    	return;
			} 

		}
	}//end pwd*/
	else {
//fprintf(stdout, "right here");
		
   		pid_t  pid;
     		//int    stat;
		pid = fork(); // fork a child process 
   			  if (pid  < 0) {  
//					fprintf(stdout, "error 0");

         			write(STDERR_FILENO, error_message, strlen(error_message));
			         exit(1);
			  }
			  else if (pid == 0) {
				   if (redirect == 1) {
					char* a = outfile;
					char* b = outfile;
	
					if (*b == ' '){
						while(*b !=0){
							*a = *b++;
							if(*a!=' '){
								a++;
							}	
				
							*a = 0;
						}
					}
 // fprintf(stdout,"%s",a);
		//			fprintf(stdout, "%s", a); 
					if (freopen(outfile, "w", stdout) == NULL ){
						//fprintf(stdout, "write to file");
						write(STDERR_FILENO, error_message, strlen(error_message));
						return;
					}
					outfile = '\0';
				    }
	
				    if (execvp(*args, args) < 0) {
				//			fprintf(stdout, "error 2");

						write(STDERR_FILENO, error_message, strlen(error_message));
				        	exit(0);
						//return;
				     }
				 //   else {
				//	execvp(*args, args);
				 //   }
		          }
			  else if (pid >0){
				if (background !=1){
					(void)waitpid(pid,NULL,0);
				}
			  }		  
			//parent process here
			  else {
				//	fprintf(stdout, "error 1");
             
         	 		write(STDERR_FILENO, error_message, strlen(error_message));

			  }
	}//end else for processing
return;
}
int main(int argc, char *argv[]){

   char line[515]={0};
   int batchmode = 0;
 
   char error_message[30] = "An error has occurred\n";
   FILE * in;

	if (argc >2){
		write(STDERR_FILENO, error_message, strlen(error_message));
		exit(1);
	}
	if(argc ==2){
	 	batchmode = 1;
		//close(fileno(stdin));
		in = fopen(argv[1], "r");
		if(in == NULL){
			write(STDERR_FILENO, error_message, strlen(error_message));
			exit(1);
		}
		//dup2(fileno(in), STDIN_FILENO);
		
	}
	
   while (1){
	char* reader;
	if (batchmode ==1){
		reader = fgets(line,514,in);
		if(strcmp(line, "\n")!=0){
			write(STDOUT_FILENO, line, strlen(line));
		}
		if(reader==NULL){
			exit(0);
		}
		if(strcmp(reader, "\n")==0 ||strcmp(reader, "\t\n")==0 ||(strcmp(reader, " \n")==0) ){
			continue;
		}
		//char*ignore;
	//	ignore = strtok(line, " \t\n\r");
//		if(ignore==NULL){
//			continue;
//		}

		else if(strlen(line) >512){
			//			fprintf(stdout, "very long 2");
			write(STDERR_FILENO, error_message, strlen(error_message));
			
		}
		else{
			command(reader);
		}
	}//end batch mode
	else{
	
		write(STDOUT_FILENO, "mysh> ", strlen("mysh> "));
		reader = fgets(line, 514, stdin);
		if(line ==NULL){
			exit(0);
		}
		if(strcmp(reader, "\n")==0 ||strcmp(reader, "\t\n")==0 ||(strcmp(reader, " \n")==0) ){
			continue;
		}

		//char*ignore;
	//	ignore = strtok(line, " \t\n\r");
//		if(ignore==NULL){
//			continue;
//		}
		else if(strlen(line) >512){
				//fprintf(stdout, "very long 3");
				//perror(NULL);
			write(STDERR_FILENO, error_message, strlen(error_message));
			//docommand = 0;
			//break;
		}
		else{
//			fprintf(stdout, "%s", reader);
			command(reader);
		}
	}//interactive mode
  }//end while loop
  if (batchmode == 1){
   	fclose(in);
  }
 
   return 0;
}
