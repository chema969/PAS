#!/bin/bash
if [ -f $1 ];then 
   for x in $(cat $1)
     do
       if [ $(ping -c 1 -w 2 $x|grep -Eo '[01] received'|sed -re's/received//') -eq 1 ];then
       echo "La ip $x comunico en $(ping -c 1 -w $2 $x|grep -Eo 'time=[0-9\.]*'|sed -re 's/time=//') ms" 
       else
       let a=$2*1000
       echo "La ip $x comunico en $a ms"
       fi
     done |sort -nk 6
fi
