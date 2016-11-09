#!/bin/sh

path=(pwd)

for testfile in $path/tests/
do
	if ./stsh $testfile > $testfile.out
	then
		echo "$testfile success"
	else
		echo "$testfile failure"
	fi
done

