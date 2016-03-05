#!/bin/bash

cmd=""
green='\e[32m'
red='\e[91m'
default='\e[0m'

#check make option
if [ "$#" -eq 1 ]; then
    cmd=$1
fi

function check_failure {
    if [ $? -ne 0 ]; then
	echo -e "${red}Failure...${default}"
	exit -1
    fi
}

#execute make on all problems
for dir in ./problems/*; do
    echo -e "${green}Executing make $cmd on $dir${default}"
    make -C $dir $cmd
    check_failure
    echo -e "${green}Success!${default}"
done

#execute make on the framework
echo -e "${green}Executing make $cmd on open-gaf${default}"
make $cmd
check_failure
echo -e "${green}Success!${default}"

#execute make on the project generator
echo -e "${green}Executing make $cmd on project generator${default}"
make -C ./template/ $cmd
echo -e "${green}Success!${default}"

exit 0
