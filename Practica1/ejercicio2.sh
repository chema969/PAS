#!/bin/bash
if [ $# -lt 1 ] || [ $# -gt 2 ] ; then
	echo "introduce como minimo un directorio"
	exit 1
fi
if [ -d $1 ]; then      
        if [ $# -eq 2 ] ; then
		tam=$2
	else
		tam=0
	fi
	echo "Nombre,LongitudUsuario,FechaModificacion,FechaAcceso,Tamano,Bloques,Permisos,Ejecutable"
	for x in $(find $1 -size +$tam)
	 	do
		if [ -x $x ]; then
 			r=1
		else
			r=0
		fi
 		echo "$(basename $x); $(stat -c %U $x | wc -m);$(stat -c %y $x);$(stat -c %X $x);$(stat -c %s $x);$(stat -c %b $x);$(stat -c %A $x);$r "
		done | sort -t ";" -nk 5
	
fi
