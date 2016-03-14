#include<stdio.h>
#include<stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#define _GNU_SOURCE
#define MAX 100

int main(int argc, char **argv){
       
       FILE * fp;
      char * line = NULL;
     size_t len = 0;
     ssize_t read;
	ssize_t backread;

    struct dirent *dirPointer = NULL;
    int counter = 0;

    char *directory = getenv("PWD");
char *words[10]; 

//printf("this word: %s", words[0]); 
			int pos =0;



	  DIR *file = opendir((const char*)directory);

//	int num = 0;
//printf("%s", argv[1]);
	if (argc ==3){
			
		char *theNum = strtok(argv[1], "-");
			
		int num = atoi(theNum);
//	printf(" number: %d\n", num);


//int out = 0;
		 for(counter = 0; NULL != (dirPointer = readdir(file)); counter++){
                      if(strcmp(dirPointer->d_name,argv[2]) == 0){
				 fp = fopen(argv[2], "rb");
	
	
				while ((read = getline(&line, &len, fp)) != -1) {
        			//	   printf("Retrieved line of length %zu :\n", read);
				 //          printf("%s", line);
					words[pos] = (char*)malloc(MAX);
					  strcpy(words[pos], line);
					    //num++;
						++pos;
			        }
				words[pos] = '\0';
				//printf("%s", words[0]);
				
				if (num > pos){
					int q;
					for (q = 0; q<pos; q++){
						printf("%s", words[q]); 
					}	


					//printf("number out of bounds\n");
				
				}
				else{
					int p;
					for (p = pos-num; p<pos; p++){
						printf("%s", words[p]); 
					}
				}
				//out = 1; 			
				break;
			}

			//if ( out == 1){
		//		break;
	//		}
		 }


			fclose(fp);
		       if (line){
		          free(line);
			}
			exit(EXIT_SUCCESS);

	}







	return 0;
}
