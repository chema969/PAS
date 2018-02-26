#!/bin/bash
if [ $# -ne 1 ]; then
	echo "introduce un directorio"
	exit 1
fi
if [ -d $1 ]; then
  	cd $1
        i=0
        j=0
	for x in $(find -name "*.c"  )
		do
		let i=i+1
		done
	for x in $(find -name "*.h"  )
		do
		let j=j+1
		done
        echo "Hay $i ficheros .c y $j ficheros .h"
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

