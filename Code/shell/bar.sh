#!/bin/bash

i=0
str=''
index=0
labal=('|' '/' '-' '\\')
colour=42
while [ $i -le 100 ]
do
printf "\e[31m[%-100s][%d%%][%c]\r" "$str" "$i" "${labal[$index]}"
let index=i%4
let i++
str='#'$str

sleep 0.1
done
printf "\e[0m \n"
