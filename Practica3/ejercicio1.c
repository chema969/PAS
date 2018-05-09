#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>
#include <getopt.h>
#include <pwd.h>
#include <sys/types.h>

void help();
void usuarioNombre(char* nombre);
void usuarioId(char* nombre);

int main(int argc,char ** argv){
   int c;

   char *uvalue=NULL;
   char *ivalue=NULL;
   char *gvalue=NULL;
   char *dvalue=NULL;
   char *avalue=NULL;
   int option_index = 0;
   static struct option long_options[]=
      {
        {"username",	 required_argument,	   0, 'u'},  
        {"useruid",	 required_argument,	   0, 'i'}, 
        {"groupname",	 required_argument,	   0, 'g'}, 
        {"groupuid",	 required_argument,	   0, 'd'}, 
        {"allgroups",	 no_argument,	   0, 's'}, 
        {"allinfo",	 required_argument,	   0, 'a'}, 
        {"bactive",	 no_argument,	   0, 'b'}, 
        {"help",	 no_argument,	   0, 'h'}, 
  	{0, 0, 0, 0}
 };

    while((c=getopt_long(argc,argv,"u:i:g:d:sa:bh",long_options, &option_index))!=-1){
      if (c == -1)break;
      switch(c){
        case 'h':
          help();
         break;
        case 'u':
           uvalue=optarg;
           usuarioNombre(uvalue);
         break;
        case 'i':
           ivalue=optarg;
           usuarioId(ivalue);
          break;
      }
}
}

void usuarioNombre(char* nombre){
    struct passwd *pw;
    if ((pw = getpwnam(nombre)) == NULL)
        {
            fprintf(stderr, "Get of user information failed.\n");
            exit(1);
        }
        printf("Nombre: %s\n", pw->pw_gecos);
	
}


void usuarioId(char* nombre){
     struct passwd *pw;
     if ((pw = getpwnam(nombre)) == NULL)
        {
            fprintf(stderr, "Get of user information failed.\n");
            exit(1);
        }
     printf("UID:%d\n ", pw->pw_uid);
}
  
void help(){
    printf("\033[1m-u/--username\033[22m user Muestra la informacion del user\n");  
    printf("-i/--useruid id");   
   }
