#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#define _GNU_SOURCE
//dalina

int main(int argc, char **argv){
 void dirInfor(const char *, int);

   if(argc !=1){

   	dirInfor(argv[1], 0);

   }
   else{

	dirInfor(".",0);

   }
    return 0;
}

void dirInfor(const char *dirName, int place){
    DIR *directory;
    struct dirent *dirPointer;
int  mark =0;
    if (!(directory = opendir(dirName))){
        return;
     }
    if (!(dirPointer = readdir(directory))){
        return;
     }
	do{
   	     if (dirPointer->d_type == DT_DIR) {
       		     char path[1024];
       		    	 int size = snprintf(path, sizeof(path)-1, "%s/%s", dirName, dirPointer->d_name);
          		  path[size] = 0;
			printf("-------------------------\n");

                     printf("%*s[%s]\n", place*2, "", dirPointer->d_name);
			mark = 1;
            dirInfor(path, place + 1);
             }
             else{
		if(mark ==1){
			printf("-------------------------\n");
			mark =0;
		}
	//printf("hey bitch");
			
		if (strcmp( dirPointer->d_name, "..")!=0 && strcmp( dirPointer->d_name, ".")!=0){
          		  printf("%*s\t* %s\n", place*2, "", dirPointer->d_name);
		}
		     }
		
    }     while (dirPointer = readdir(directory));
    closedir(directory);
}
