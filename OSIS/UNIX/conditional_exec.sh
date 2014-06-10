#!/bin/bash

rmdir not_ex && will_not_start
rmdir not_ex && echo "Will be called"
echo "Second command will not start" || foo
echo "background execution with &" &

(ps; who) | more
