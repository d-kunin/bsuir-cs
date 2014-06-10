#/bin/bash

DIR="."
echo "$DIR"
for FILE in "$DIR/*" 
do
	file $FILE
done


