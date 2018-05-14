#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <mqueue.h>
#include <time.h>
#include <errno.h>
#include "common.h"


int main(){
   mqd_t queue1,queue2;
   printf("Intento abrir cola 1");
   queue1=mq_open("/micolados",O_WRONLY);
   if(queue1==-1){
       perror("Opening queue error");
       exit(-1);
     }
   queue2=mq_open( COLA_SERVIDOR_ENVIA ,O_RDONLY);
   if(queue2==-1){
       perror("Opening queue error");
       exit(-1);
     }
   char buffer[MAX_SIZE + 1];
   char respuesta[MAX_SIZE+1];
   printf("Se pedirá hasta que se escriba la palabra de salida \"%s\" \n",MSG_STOP);
   do{
       printf(">");
       int i;
       ssize_t j;
       fflush(stdout);
	memset(buffer, 0, MAX_SIZE); 
	memset(respuesta, 0, 20);   
       fgets(buffer, MAX_SIZE, stdin);
       buffer[strlen(buffer)-1] = '\0';
       i=mq_send(queue1,buffer,MAX_SIZE,0);
       if(i==-1){
          perror("Queue send error");
          exit(-1);
          }
       j=mq_receive(queue2,respuesta,MAX_SIZE,NULL);
       printf("<%s\n",respuesta);
       }while(strncmp(buffer, MSG_STOP, strlen(MSG_STOP)));
   }
