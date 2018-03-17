#!/bin/bash
for x in $(cat  /etc/passwd|grep $1$)
do
b=$(echo $x|grep -Eo '^[a-zA-Z0-9\-]*')
echo $x|grep -Eo '^[a-zA-Z0-9\-]*'|sed -re's/(^[a-zA-Z0-9\-])/Logname:\1/'
echo $x|grep -Eo '^[a-zA-Z0-9\-]*:.:[0-9]*'|sed -re 's/^[a-zA-Z0-9\-]*:.//'|sed -re 's/(.*)/\|\-\>UID:\1/'
a=$(echo $x|grep -Eo '^[a-zA-Z0-9\-]*:.:[0-9]*:[0-9]*'|sed -re 's/^[a-zA-Z0-9\-]*:.:[0-9]*://')
cat /etc/group|grep :$a:|grep -o '^[a-zA-Z0-9\-]*' |sed -re 's/(.*)/\|\-\>Grupo:\1/'
echo "|->IdGrupo:$a"
echo $x|grep -Eo '^[a-zA-Z0-9\-]*:.:[0-9]*:[0-9]*:[A-Za-z0-9\,\-]*'|sed -re 's/^[a-zA-Z0-9\-]*:.:[0-9]*:[0-9]*//'|sed -re 's/(.*)/\|\-\>gecos\1/'
echo $x|grep -Eo '^[a-zA-Z0-9\-]*:.:[0-9]*:[0-9]*:[A-Za-z0-9\,\-]*:[A-Za-z0-9\/\-]*:'|sed -re 's/^[a-zA-Z0-9\-]*:.:[0-9]*:[0-9]*:[A-Za-z0-9\,\-]*//'|sed -re 's/(.*)/\|\-\>Home\1/'
echo "|->Shell por defecto:$1"
if [ $(who|grep $b|wc -l) -ge 1 ];then
   echo "|->Logueado=1"
else
   echo "|->Logueado=0"
fi
done

