#/bin/bash

EXT=$1
TG_DIR="output_$EXT"
mkdir "$TG_DIR" || cp *.$EXT $TG_DIR & echo "copied $EXT file"
