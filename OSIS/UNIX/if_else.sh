#!/bin/bash

if (cat $0 1>/dev/null )
then
    echo "Successful cat"
fi

if (rmdir "not exist" 2> /dev/null)
then
    echo "Not possible"
else
    echo "Cannot remove if not exist"
fi
