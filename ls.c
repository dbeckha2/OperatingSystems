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
#include <time.h>
#define _GNU_SOURCE
//dalina 

void status(char *file){
	struct stat theStat;
	
	stat(file, &theStat);

	 printf("\n\nFile: %s\n",file);
    printf("ID of device file contained in: %zu\n", theStat.st_dev);
    printf("Inode number: %zu\n",theStat.st_ino);
    printf("Protection: %c\n",theStat.st_mode);
    printf("Number of links: %zu\n",theStat.st_nlink);
    printf("Owner's user id: %d\n",theStat.st_uid);
    printf("Owner's group id: %d \n",theStat.st_gid);
    printf("device if (if the file is special): %zu\n",theStat.st_rdev);
    printf("Size in bytes: %zu\n",theStat.st_size);
    printf("Blocksize for file system I/O: %zu\n",theStat.st_blksize);
    printf("Number of 512B blocks allocated: %zu\n",theStat.st_blocks);
    printf("time last accessed: %s",ctime(&theStat.st_atime));
    printf("time last modified: %s",ctime(&theStat.st_mtime));
    printf("time last status change: %s",ctime(&theStat.st_ctime));


     printf("Permissions:");

         if(S_ISDIR(theStat.st_mode) ){
                 printf( "d");
         }
         else{
                printf("-");
         }


         if(theStat.st_mode & S_IRUSR){
                printf( "r");
         }
         else{
                printf( "-");
         }


         if (theStat.st_mode & S_IWUSR){
                printf( "w");
         }
         else{
                printf( "-");
         }


         if(theStat.st_mode & S_IXUSR) {
                printf( "x");
         }
         else{
                printf( "-");
         }

         if(theStat.st_mode & S_IRGRP){
                printf( "r");
         }
         else {
                printf( "-");
         }


         if (theStat.st_mode & S_IWGRP){
                printf( "w");
         }
         else{
                printf( "-");
         }

	 if(theStat.st_mode & S_IXGRP){
                printf( "x");
         }
         else{
                printf( "-");
         }


         if(theStat.st_mode & S_IROTH){
                printf( "r");
         }
         else{
                printf("-");
         }


         if(theStat.st_mode & S_IWOTH){
                printf("w" );
         }
         else {
                printf( "-");
          }

         if (theStat.st_mode & S_IXOTH){
                printf( "x");
         }
         else{
                printf( "-");
        }




	return;

}

  
 int main(int argc, char**argv){
    char error_message[30] = "An error has occurred";
  

    struct dirent *dirPointer = NULL; 
    int counter = 0; 
  
    char *directory = getenv("PWD"); 
    if(NULL == directory){ 
       		 write(STDERR_FILENO, error_message, strlen(error_message)); 
        return -1; 
    } 
  
    DIR *file = opendir((const char*)directory); 

      if(NULL == file) { 
 	 write(STDERR_FILENO, error_message, strlen(error_message)); 
        return -1; 
     } 


	 if(argc ==1){
 
	       for(counter = 0; NULL != (dirPointer = readdir(file)); counter++){ 
		     if(dirPointer->d_name[0] != '.') {
			    printf("%s\t",dirPointer->d_name); 
			}
     		} 

	 }
	else if (argc ==2 & strcmp(argv[1], "-l")==0){
	 	for(counter = 0; NULL != (dirPointer = readdir(file)); counter++){ 
		      if(dirPointer->d_name[0] != '.') {
   
				status(dirPointer->d_name); 
			}
     		} 

		
	}
	else if (argc =3){ 
		for(counter = 0; NULL != (dirPointer = readdir(file)); counter++){ 
		      if(strcmp(dirPointer->d_name,argv[2]) == 0){
				 DIR *file2 = opendir((const char*)argv[2]); 

				for(counter = 0; NULL != (dirPointer = readdir(file2)); counter++){ 
					if(dirPointer->d_name[0] != '.'){
				
							status(dirPointer->d_name); 
			//			}
			//			else{
			//				printf("heeeee");
			//				 write(STDERR_FILENO, error_message, strlen(error_message)); 
			//				exit(1);
			//			}
					}
				}
		      }

		}
	}
     printf("\n");   
    return 0; 
 }

