#!/usr/bin/env bash
rows=5
for (( i=1; i<=rows; i++ ))
do
for (( j=i; j<rows; j++ ))
do
echo -n " "
done
for (( k=1; k<=i; k++ ))
do
echo -n "* "
done
echo ""
done