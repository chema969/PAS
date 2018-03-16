#!/bin/bash
cat $1 | sed '/^\ /d' |sed -re '/=/d'|sed -re 's/\-.*\-//g'|sed -re '/^$/d'>tmp
cat tmp | sed 's/)//g'| sed 's/(/\|\-\> Fecha de estreno:/g' | sed 's/Dirigida por/\|\-\>Director:/g'|sed 's/Reparto/\|\-\>Reparto/g'|sed -r -e 's/(^[A-Za-z¿¡])/Pelicula:\1/'|sed -re 's/(.*hr.*min)/Duracion:\1/'
rm tmp
