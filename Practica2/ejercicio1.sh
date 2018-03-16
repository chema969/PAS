#!/bin/bash
echo "1)Duracion de la pelicula"
cat peliculas.txt | grep -E 'min$'  
echo "***************************"
echo "2)Pais de origen"
#cat peliculas.txt | grep '(*).-'
cat peliculas.txt | grep -E -o '\-.*-$'
echo "***************************"
echo "3)Solo el pais de origen"
cat peliculas.txt | grep -E -o '\-.*-$' | tr -d -
echo "***************************"
echo "4)Peliculas segun su año"
echo "Hay $(cat peliculas.txt | grep -E -o '^\(.*\)' | grep 2017| wc -l) peliculas de 2017 y $(cat peliculas.txt | grep -E -o '^\(.*\)' | grep 2016| wc -l) peliculas de 2016"
echo "***************************"
echo "5)Documento sin espacios"
cat peliculas.txt |grep -E '[0-9a-zA-Z]|='
echo "***************************"
echo "6)Lineas que empiezan en E"
cat peliculas.txt |grep -E '^\ .E|^E'
echo "***************************"
echo "7)Mostrar aquellas lı́neas que contengan una letra ’d’, ’l’ o ’t’, una vocal, y la misma letra"
cat peliculas.txt |grep -E 'd[aeiou]d|t[aeiou]t|l[aeiou]l'
echo "***************************"
echo "8)Lineas con ocho o mas aes"
cat peliculas.txt |grep -E 'a.*a.*a.*a.*a.*a.*a.*a'
echo "***************************"
echo "9)Lineas que no empiezen por espacio y que acaben con tres puntos"
cat peliculas.txt |grep -E '^[^\ ].*\.\.\.'
echo "***************************"
echo "10) Mostrar entre comillas las vocales con tilde"
cat peliculas.txt |sed 's/á/\"á\"/g'

