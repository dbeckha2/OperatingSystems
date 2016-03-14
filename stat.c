#include <sys/types.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
//dalina

int main(int argc, char **argv){
 struct stat theStat;
  
 if(argc != 2){   
	printf("No file passed\n");
        return 1;
    }
   
      

    if(0> stat(argv[1],&theStat) ){
  //	printf("heyyyyyyyy");
	      return 1;
    }


    printf("\n\nFile: %s\n",argv[1]);
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
    printf("\n\n");
 

    return 0;
}
