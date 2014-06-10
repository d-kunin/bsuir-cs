#!/bin/bash
echo $0
FILE=`pwd`/$0
echo $FILE

if test -s $FILE
then
    echo "This file is not empty"
fi

if test -r $FILE
then
    echo "This file is readable"
fi

if test -f $FILE
then
    echo "This is simple existing file"
fi

if test -d $FILE
then
    echo "This is directory"
fi
