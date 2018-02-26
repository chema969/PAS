#!/bin/bash
if [ $# -lt 1 ] || [ $# -gt 2 ] ; then
	echo "introduce como minimo un directorio"
	exit 1
fi
if [ -d $1 ]; then      
        if [ $# -eq 2 ] ; then
		echo "Nombre,LongitudUsuario,FechaModificacion,FechaAcceso,Tamano,Bloques,Permisos,Ejecutable"
		for x in $(find $1 -size +$2)
	 		do
 			echo "$(basename $x), $(stat -c %w $x) $(stat -c %x $x)"
			done 
	fi
fi
