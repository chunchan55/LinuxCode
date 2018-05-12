#!/bin/bash

#while read line
#do
#fun(){
#l="123wer456"
#part1=`echo $l | cut -b 1-3`
#part2=`echo $l | cut -b 4-6 | tr '[a-z]' '[A-Z]'`
#part3=`echo $l | cut -b 7-9`
#
#echo $part3$part2$part1
#}
#fun $1



#done<file

#
#function fib(){
#
#first=1
#second=1
#last=1
#i=3
#while [ $i -le $1 ]
#do
#let last=$first+$second
#let first=$second
#let second=$last
#let i++
#done
#echo $last
#}
#fib $@


#
#function fib2(){
#arr=(1 1)
#i=0
#while [ $i -lt $1 ]
#do 
#	let arr[i+2]=arr[i+1]+arr[i]
#	let i++
#done
#echo ${arr[i-1]}
#}
#fib2 $@  #$@意思就是可以传多个参数，$1就是一个，也是第一个参数

#function max_min(){
#max=$1
#min=$1
#total=0
#for i in $@
#do
#	[ $max -le $i ] && max=$i
#	[ $min -ge $i ] && min=$i 
#	let total+=$i
#	let i++
#
#done
#echo max=$max
#echo min=$min
#echo avg=`echo "ibase=10;scale=2;$total/$#" | bc`
#}
#max_min $@
#

#i=0
#str=''
#index=0
#labal=('|' '/' '-' '\\')
#while [ $i -le 100 ]
#do
#printf "[%-100s][%d%%][%c]\r" "$str" "$i" "${labal[$index]}"
#let index=i%4
#let i++
#str='#'$str
#
#sleep 0.1
#done


#printf "hello word!\n"
#sleep 3


