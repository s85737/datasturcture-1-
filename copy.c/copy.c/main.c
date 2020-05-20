#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>


int main(int argc, char* argv[]){

   int fd = open(argv[1], O_RDONLY, S_IRWXU);
   int fdc = open(argv[2], O_CREAT, S_IRWXU| O_RDWR);
   int fileSize= lseek(fd,0,SEEK_END);
   char buf[fileSize];

   if (argc != 3) {
   printf("uasage) ./copy.out source_file target_file\n");
    exit(-1);
   }

   if (fd < 0){
     fprintf(stderr, "Cannot open file %s\n",argv[1]);
     exit(-1);
   }

    int read_size = read(fd, buf, fileSize);
     if (read_size <0){
       printf("read file ERROR\n");
     }
     printf("%d\n",fileSize);
     printf("%d\n",read_size);
     printf("%c\n",buf[5]);
    int written_size = write(fdc, buf, fileSize);
    if (written_size< 0){
     printf("Write file ERROR \n");
     }

   close(fd);
   close(fdc);
   return 0;
 }
