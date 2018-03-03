#!/bin/bash
mkdir temp
for x 
    do
	cp -R $x "temp"
    done
cd temp
tiempo=$(date +%s)
copia="copia-$(whoami)-$tiempo.tar.gz"
tar -zcf $copia *
cd ..
if [ ! -e "./copia" ];then
    mkdir "copia"
fi
mv "./temp/$copia" "./copia"
rm -rf "temp"
let tiempo=$tiempo-200
cd ./copia
for x in $(ls)
    do
        if [ $tiempo -gt "$(stat -c %Y $x)" ];then
		echo "$x tiene $[$tiempo+200-$(stat -c %Y $x)] tiempo de vida por lo que se eliminará"
		rm $x
	fi
    done
