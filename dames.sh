#!/bin/bash
if [ $# == 0 ]
then
	echo "Usage : [-ah] nombre de dames"
	exit 0
fi

if [ $1 == "-a" ]
then
	./gen/dame $2 > src/input.txt
	./src/FC -a ./src/input.txt
elif [ $1 == "-ah" ]
then
	./gen/dame $2 > src/input.txt
	./src/FC_heuristique -a ./src/input.txt
elif [ $1 == "-h" ]
then
	./gen/dame $2 > src/input.txt
	./src/FC_heuristique ./src/input.txt
else
	./gen/dame $1 > src/input.txt
	./src/FC ./src/input.txt
fi

