#!/bin/bash

cmd=""
green='\e[32m'
default='\e[0m'

#check make option
if [ "$#" -eq 1 ]; then
    cmd=$1
fi

#execute make on all problems
for dir in ./problems/*; do
    echo -e "${green}Executing make $cmd on $dir${default}"
    make -C $dir $cmd
done

#execute make on the framework
echo -e "${green}Executing make $cmd on open-gaf${default}"
make $cmd
