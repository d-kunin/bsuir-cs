#/bin/bash

LOCAL_VAR="Only local"
GLOBAL_VAR="Global for this shell"
export GLOBAL_VAR
echo "List of all VARS"
set
echo "Remove global with unset"
unset GLOBAL_VAR
set
