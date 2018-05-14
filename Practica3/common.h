#ifndef COMMON_H_
#define COMMON_H_
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>

#define COLA_SERVIDOR_ENVIA  "/colilla"_getpwuid(geteuid())->pw_name
#define COLA_CLIENTE_ENVIA  "/micolados"_getpwuid(geteuid())->pw_name
#define MAX_SIZE     1024
#define MSG_STOP     "exit"


#endif /* #ifndef COMMON_H_ */
