#!/bin/bash
cmd="time ./open-gaf problems/iis/ && gnuplot -p conf.gnp"
if [ "$#" -ne 0 ]; then
    make re && make -C problems/iis/ && eval $cmd
else
    eval $cmd
fi
