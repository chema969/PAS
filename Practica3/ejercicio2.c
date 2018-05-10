#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h> //wait
#include <errno.h> //Control de errores


int main(){
  int childpid,status,pipestatus1,pipestatus2;
  pid_t pid;  
  int fildes1[2],fildes2[2];
  const int BSIZE = 100;
  char buf[BSIZE];
  ssize_t nbytes,nbytes2;
  
  pipestatus1=pipe(fildes1);
  pipestatus2=pipe(fildes2);
  

  if(pipestatus1==-1){
       perror("Pipe error");
        exit(EXIT_FAILURE);
      }
  if(pipestatus2==-1){
       perror("Pipe error");
        exit(EXIT_FAILURE);
      }
  


  pid=fork();
   switch(pid){

       case -1:
        perror("fork error");
        exit(EXIT_FAILURE);


       case 0:{
         if(close(fildes1[1])==-1){//cierro la tuberia de escribir de foldes1
                perror("Close error");
                exit(EXIT_FAILURE);
                 }
      
        if(close(fildes2[0])==-1){//cierro la tuberia de leer de foldes2
                perror("Close error");
                exit(EXIT_FAILURE);
                 } 
         
        nbytes=read(fildes1[0],buf,BSIZE);
        if(nbytes==-1){
             perror("Read error");
             exit(EXIT_FAILURE);
          }
         printf("[HIJO]Recibido %s de la tuberia fildes1\n",buf);
         if((atoi(buf)%2)==0){
         printf("[HIJO]Enviando PAR a mi padre\n");
           if((write(fildes2[1],"PAR",5))==-1){
                 perror("Write error");
                 exit(EXIT_FAILURE);
              }
         }
         else{
           printf("[HIJO]Enviando IMPAR a mi padre\n");
           if((write(fildes2[1],"IMPAR",5))==-1){
                 perror("Write error");
                 exit(EXIT_FAILURE);
              }
         }
        close(fildes1[0]);
        close(fildes2[1]);
        exit(EXIT_SUCCESS);
       }
       default:{
        if(close(fildes2[1])==-1){//cierro la tuberia de escribir de foldes2
                perror("Close error");
                exit(EXIT_FAILURE);
                 }
      
        if(close(fildes1[0])==-1){//cierro la tuberia de leer de foldes1
                perror("Close error");
                exit(EXIT_FAILURE);
                 } 
        char n[10];
        printf("[PADRE]Introduce un numero:");
        scanf("%s",n);
        printf("[PADRE]Voy a pasar el número %s por la tuberia fildes1\n",n);
          if((write(fildes1[1],n,10))==-1){
                 perror("Write error");
                 exit(EXIT_FAILURE);
              }
        char eq[6];
        nbytes2=read(fildes2[0],eq,5);
          if(nbytes2==-1){
               perror("Read error");
               exit(EXIT_FAILURE);
               }
        printf("[PADRE]He recibido %s de mi hijo \n",eq);
        close(fildes1[1]);
        close(fildes2[0]);
        childpid=wait(&status);
         if(childpid>0){
                if (WIFEXITED(status)) {
					printf("child %d exited, status=%d\n",childpid, WEXITSTATUS(status));
				} else if (WIFSIGNALED(status)) {
					printf("child %d killed (signal %d)\n", childpid, WTERMSIG(status));
				} else if (WIFSTOPPED(status)) {
					printf("child %d stopped (signal %d)\n", childpid, WSTOPSIG(status));
				}
                   }

            

        }
}
}
