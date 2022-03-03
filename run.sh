#!/bin/bash

runtime=1
sum_iops=0
# testapp=''
for i in `seq $runtime`; do 
    iops=$(./a.out 8 256 seq 00,01,02,03,04,05,06,07)
    sum_iops=`expr $sum_iops + $iops`
done
echo `expr $sum_iops / $runtime`