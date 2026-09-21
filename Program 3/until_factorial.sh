#!/usr/bin/env bash
num=5
fact=1
i=1

until [ $i -gt $num ]
do
  fact=$((fact * i))
  i=$((i + 1))
done

echo "Factorial of $num = $fact"