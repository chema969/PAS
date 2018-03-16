#!/bin/bash
echo "Listado de directorios secretos"
for x in $(ls -a "/home/$USER" | grep -E '^\.')
do 
   echo "$x $(echo $x|wc -m)"
done |sort -nk 2| sed 's/[0-9]*$//'
if [ -f $1 ];then
   echo "Se va a copiar $(echo $1|grep -oE '[A-Za-z\.0-9]*$')"
   cat $1 |sed -re '/^$/d'>"$(echo $1|grep -oE '[A-Za-z\.0-9]*$').sinLineasBlancas"
   echo "Creado $(echo $1|grep -oE '[A-Za-z\.0-9]*$').sinLineasBlancas"
fi
ps |grep -v '^.*PID'| sed -re 's/(^[0-9]*)/PID=\1/' | sed -re 's/pts\/[0-9]*//' | sed -re 's/([0-9]*:[0-9]*)/HORA \1/' | sed -re 's/([a-zA-Z0-9]*$)/PROCESO=\1/'
