#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <mqueue.h>
#include <time.h>
#include <errno.h>
#include <unistd.h>
#include "common.h"
#include <getopt.h>
#include <regex.h>

void colas(char* ,mqd_t *queue1,mqd_t *queue2);

int main(int argc, char ** argv){
  int c;
  int* long_index;
  mqd_t myqueuestart1,myqueuestart2;
  struct mq_attr attr,attr2;
  attr.mq_maxmsg = 10;        // Maximo número de mensajes
  attr.mq_msgsize = MAX_SIZE;
  attr.mq_flags=0;
  attr2.mq_maxmsg = 10;        // Maximo número de mensajes
  attr2.mq_msgsize = MAX_SIZE;
  attr2.mq_flags=0;
  printf("Servidor encendido\n");

  myqueuestart1=mq_open(COLA_CLIENTE_ENVIA, O_RDONLY |O_CREAT ,0644 ,&attr);

  myqueuestart2=mq_open( COLA_SERVIDOR_ENVIA  ,O_WRONLY |O_CREAT  ,0644 ,&attr2);

  if((myqueuestart1==-((mqd_t)-1))||(myqueuestart2==-((mqd_t)-1))){
      perror("opening queue error");
      exit(-1);
      }

   struct option long_options[]=
          {
          {"regex", required_argument , 0,'r'},
          {0,0,0,0}
         };

  while(c=getopt_long(argc,argv,"r:", long_options, long_index)){
       if(c==-1) break;
       if(c=='r'){
         int stop=0;
         char recibido[MAX_SIZE+1];
            do{
               ssize_t size;
               size=mq_receive(myqueuestart1,recibido,MAX_SIZE,NULL);
               if(size<0){
                        perror("Error al recibir el mensaje");
			exit(-1);
		}
               printf(">%s\n",recibido);
               if(!strncmp(recibido,MSG_STOP,strlen(MSG_STOP))) stop=1;
               else{
                  regex_t regex;
                  int reg_error=regcomp(&regex,optarg,0);
               if(reg_error){
                  perror("regex error");
                  exit(-1);
                 } 
               int match = regexec(&regex, recibido, 0, NULL, 0);   
               if(match==0){
                  printf("<PASO COINCIDE\n");
                  mq_send(myqueuestart2,"COINCIDE",MAX_SIZE,0);}
              
               else
                  mq_send(myqueuestart2,"NO COINCIDE",MAX_SIZE,0);
             
               regfree(&regex);
           }
      }while(stop==0);
          }
        if(c=='?')break;
      }
    if (optind < argc)
	{
		printf("Argumentos ARGV que no son opciones: ");
		while (optind < argc)
			printf("%s ", argv[optind++]);
		putchar ('\n');
	}
       if(mq_close(myqueuestart1) == (mqd_t)-1){
            perror("Close error");
            exit(-1);
            }
        if(mq_close(myqueuestart2) == (mqd_t)-1){
            perror("Close error");
            exit(-1);
            }
        if(mq_unlink(COLA_SERVIDOR_ENVIA) == (mqd_t)-1)
	{
		perror("Error al eliminar la cola del servidor");
		exit(-1);
	}
        if(mq_unlink(COLA_CLIENTE_ENVIA) == (mqd_t)-1)
	{
		perror("Error al eliminar la cola del servidor");
		exit(-1);
	}
}





