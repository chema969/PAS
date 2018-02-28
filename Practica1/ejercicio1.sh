#!/bin/bash
if [ $# -ne 1 ]; then
	echo "introduce un directorio"
	exit 1
fi
if [ -d $1 ]; then
  	cd $1
        echo "Hay $(find -name "*.c"|wc -l  ) ficheros .c y $(find -name "*.h"|wc -l  ) ficheros .h"
	for x in $(find -name "*.c"  ) 
		do
		echo -e "El fichero $x tiene $(wc -l < $x) lineas y $(wc -m < $x) caracteres" 
		done 
	for x in $(find -name "*.h"  ) 
		do
		echo -e "El fichero $x tiene $(wc -l < $x) lineas y $(wc -m < $x) caracteres" 
		done 
else
	echo "eso no es un directorio"
fi | sort -nrk 8

