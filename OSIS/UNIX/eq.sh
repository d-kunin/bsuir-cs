#!/bin/bash

if [ $# -eq 1 ]
then
    echo "Has one arguments"
    if [ $1 = foo ]
    then
	echo "Argument if foo"
    elif [ ! \( $1 = bar \) ]
    then
	echo "Argument is not bar"
    else
	echo "Argument is wrong =("
    fi
else
    echo "I want exactly two arguments"
fi
