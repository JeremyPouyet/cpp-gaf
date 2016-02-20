#!/bin/bash
cmd="time ./open-gaf problems/iis/Iis.so problems/iis/problem.ini && gnuplot -p conf.gnp"
if [ "$#" -ne 0 ]; then
    make re && make -C problems/iis/ && eval $cmd
else
    time ./open-gaf problems/iis/ && gnuplot -p conf.gnp
fi
