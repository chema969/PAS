#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>
#include <getopt.h>
#include <pwd.h>
#include <grp.h>
#include <sys/types.h>

void help();
void usuarioNombre(char* nombre);
void usuarioId(int id);
void allgroups();
void todo(char *nombre);
void grupoUsuarioAct();

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
           usuarioId(atoi(ivalue));
          break;
        case 'a':
           avalue=optarg;
           todo(avalue);
           break;
        case 's':
          allgroups();
         break;
        case 'b':
          grupoUsuarioAct();
         break;
        case '?':
				/* getopt_long ya imprime su mensaje de error, no es necesario hacer nada */
				/* Si queremos imprimir nuestros propios errores, debemos poner opterr=0,
				 y hacer algo como lo que se expone a continuacion. Pruebe a hacer sus propios errores.
				if (optopt == 'c')
					fprintf (stderr, "La opción %c requiere un argumento.\n", optopt);*/
				break;
       default:
				abort ();
      }
if (optind < argc)
	{
		printf("Argumentos ARGV que no son opciones: ");
		while (optind < argc)
			printf("%s ", argv[optind++]);
		putchar ('\n');
	}
}
}



void grupoUsuarioAct(){
  struct group *gr;
  if((gr = getgrgid (getegid()))==NULL){
        fprintf(stderr, "Get of group information failed.\n");
            exit(1);
        }
      	printf("ID:%d Nombre del grupo: %s\n",gr->gr_gid, gr->gr_name);   
}



void allgroups(){
      struct group *gr;
      while(gr=getgrent())
      	printf("ID:%d Nombre del grupo: %s\n",gr->gr_gid, gr->gr_name);    
}




void todo(char *nombre){
struct passwd *pw;
struct group *gr;
    if ((pw = getpwnam(nombre)) == NULL)
        {
            fprintf(stderr, "Get of user information failed.\n");
            exit(1);
        }
        printf("Nombre: %s\n", pw->pw_gecos);
	printf("Login: %s\n", pw->pw_name);
	printf("Password: %s\n", pw->pw_passwd);
	printf("UID: %d\n", pw->pw_uid);
	printf("Home: %s\n", pw->pw_dir);
	printf("Número de grupo principal: %d\n", pw->pw_gid);
   if((gr=getgrgid( pw->pw_gid))==NULL)        {
            fprintf(stderr, "Get of group information failed.\n");
            exit(1);
        }
          	printf("ID del grupo:%d Nombre del grupo: %s\n",gr->gr_gid, gr->gr_name);
}

void usuarioNombre(char* nombre){
    struct passwd *pw;
    if ((pw = getpwnam(nombre)) == NULL)
        {
            fprintf(stderr, "Get of user information failed.\n");
            exit(1);
        }
        printf("Nombre: %s\n", pw->pw_gecos);
	printf("Login: %s\n", pw->pw_name);
	printf("Password: %s\n", pw->pw_passwd);
	printf("UID: %d\n", pw->pw_uid);
	printf("Home: %s\n", pw->pw_dir);
	printf("Número de grupo principal: %d\n", pw->pw_gid);

	
}


void usuarioId(int id){
     struct passwd *pw;
     if ((pw = getpwuid(id)) == NULL)
        {
            fprintf(stderr, "Get of user information failed.\n");
            exit(1);
        }
     printf("Nombre: %s\n", pw->pw_gecos);
	printf("Login: %s\n", pw->pw_name);
	printf("Password: %s\n", pw->pw_passwd);
	printf("UID: %d\n", pw->pw_uid);
	printf("Home: %s\n", pw->pw_dir);
	printf("Número de grupo principal: %d\n", pw->pw_gid);

}
  
void help(){
    printf("\033[1m-u/--username\033[22m user Muestra la informacion del user\n");  
    printf("-i/--useruid id");   
   }
