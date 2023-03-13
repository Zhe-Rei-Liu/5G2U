#!/bin/bash

cpufreq-set -g performance

#stress-ng --zlib 8
#stress-ng --cpu 5 -l 95  &
#stress-ng --taskset 5 --vm 1 --vm-bytes 5% &
#stress-ng --taskset 6 --vm 1 --vm-bytes 5% &
#stress-ng --taskset 7 --vm 1 --vm-bytes 5%

#stress-ng --vm 5 --vm-bytes 1G --vm-keep &
stress-ng --matrix-3d 4 &
#stress-ng --sock 3 &
#stress-ng --taskset 0 --cpu 1 -l 50 &
#stress-ng --taskset 1 --cpu 1 -l 50 &
#stress-ng --taskset 2 --cpu 1 -l 50 &
#stress-ng --taskset 3 --cpu 1 -l 50 &
stress-ng --taskset 4 --cpu 1 -l 90 &
stress-ng --taskset 5 --cpu 1 -l 90 &
stress-ng --taskset 6 --cpu 1 -l 90 &
stress-ng --taskset 7 --cpu 1 -l 90

#stress-ng --taskset 7 --vm 1 --vm-bytes 5%
#stress-ng --matrix-3d 12  

#stress-ng --cpu 4 -l 95  &
#taskset -c 0-3 stress-ng --sock 80
#taskset -c 0 stress-ng --cpu 1 -l 95 &
#taskset -c 1 stress-ng --cpu 1 -l 95 &
#taskset -c 2 stress-ng --cpu 1 -l 95  &
#taskset -c 3 stress-ng --cpu 1 -l 95 
#taskset -c 3 stress-ng --vm 1 --vm-bytes 10% 




