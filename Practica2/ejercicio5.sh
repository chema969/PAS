#!/bin/bash
cat /proc/cpuinfo|grep -E 'model name'| sed -re 's/model name/Modelo del procesador/'
cat /proc/cpuinfo|grep -E 'cpu MHz'| sed -re 's/cpu MHz/Numero de megahercios/'
cat /proc/cpuinfo|grep -E 'cache size'| sed -re 's/cache size/Tamaño de la caché/'
cat /proc/cpuinfo|grep -E 'vendor_id'| sed -re 's/vendor_id/Id del vendedor/'
cat /proc/mounts |sort -r|sed -re 's/^[a-z]/\-\>Punto de montaje:/'|sed -re 's/ rw,.*$//'|sed -re 's/(\/[a-z/]*)/Dispositivo:\1/'|sed -re 's/([a-z]*$)/Tipo:\1/'
cat /proc/partitions |grep -Eo '[0-9]* [a-z0-9]*$'|sed -re '/name/d'|sed -re 's/(^[0-9])/Bloques:\1/'|sed -re 's/([a-z0-9]*$)/Particion:\1/'


