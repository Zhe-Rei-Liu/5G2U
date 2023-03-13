#!/bin/bash
taskset -c 0,1,2,3 tshark -f 'tcp dst port 4840' -z io,phs -T fields -e frame.time_relative -e ip.src -e ip.dst -e tcp.srcport -e tcp.dstport -e frame.len -e tcp.seq -e tcp.ack -e opcua -E header=y -E separator=" " >wcccpacket.txt & 
taskset -c 2 tshark -f 'tcp dst port 4841' -z io,phs -T fields -e frame.time_relative -e ip.src -e ip.dst -e tcp.srcport -e tcp.dstport -e frame.len -e tcp.seq -e tcp.ack -e opcua -E header=y -E separator=" " >wcapacket.txt &
taskset -c 3 tshark -f 'ip dst 224.0.5.1 and ip src 192.168.0.102' -z io,phs -T fields -e frame.time_relative -e ip.src -e ip.dst -e frame.len -e udp.srcport -e udp.dstport -E header=y -E separator=" " >wcmpacket.txt 


