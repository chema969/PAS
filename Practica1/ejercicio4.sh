#!/bin/bash
echo "El numero de archivos de esta carpeta es $(find -maxdepth 1 -type f|wc -l)"
who -u | sort| uniq -u
read -p "¿Qué carácter quieres contar? " -t5 caracter
if [ -z $caracter ];then 
	caracter="a"
fi
a=$(find -name "*" -printf %f | wc -m)
b=$(find -name "*" -printf %f| tr -d $caracter| wc -m)
echo "El caracter $caracter aparece $[a-b] veces"
