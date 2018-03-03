#!/bin/bash
if [ $# -lt 1 ] || [ $# -gt 3 ] ; then
	echo "introduce como minimo un directorio"
	exit 1
fi
if [ -d $1 ]; then
	cd $1
	if [ $# -eq 1 ]; then 
		a=10000
		b=100000
	elif [ $# -eq 2 ]; then 
		a=$2
		b=100000
	else
		a=$2
		b=$3
	fi
	if [ -e "pequeño" ]; then
		rm -rf ./pequeño
	fi
        if [ -e "mediano" ]; then
		rm -rf ./mediano
	fi
	if [ -e "grande" ]; then
		rm -rf ./grande
	fi
		mkdir "mediano"
		mkdir "grande"
		mkdir "pequeño"
	for x in $(find -type f)
		do
		if [ $(wc -c <$x) -gt $b ]; then 
			mv $x "./grande"
		elif [ $(wc -c <$x) -lt $a ]; then
			mv $x "./pequeño"
		else 
			mv $x "./mediano"
		fi
		done	
fi

