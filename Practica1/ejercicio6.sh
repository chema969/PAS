#!/bin/bash
function recursivo() {
     cd $1
     echo "cambiando a $1, 2=$2"
     echo "<ul>">>"$2"
     for x in $(ls)
	do
	if [ -d $x ];then
	    echo "<li><strong>$(realpath $x)</strong></li>">>"$2"
	    recursivo $x $2
	else
	    echo "<li>$(realpath $x)</li>">>"$2"
         fi
         done
   echo "</ul>">>"$2"
   cd ..
return 0
}

echo "<html>">"$2.html"
echo "<head>">>"$2.html"
echo "<title>Listado del directorio $1</title>">>"$2.html"
echo "</head>">>"$2.html"
echo "<body>">>"$2.html"
echo "<style type="text/css">">>"$2.html"
echo "body { font-family: sans-serif;}">>"$2.html"
echo "</style>">>"$2.html"
echo "<h1>Listado del directorio $1</h1>">>"$2.html"
a=$(realpath "$2.html")
echo $a
recursivo $1 $a 
