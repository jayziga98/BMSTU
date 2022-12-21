#!/bin/bash
source ./lib.sh

pref="lab"

cd ./"${pref}_${1}"/func_tests/data

for (( i = $2; i <= $3; i++ )); do
	num="${i}"
	if [ $i -lt 10 ]; then
		num="0${i}"
	fi

	touch "pos_${num}_in.txt"
	touch "pos_${num}_out.txt"
done

if [ $# -gt 3 ]; then
	for (( i = $4; i <= $5; i++ )); do
		num="${i}"
		if [ $i -lt 10 ]; then
			num="0${i}"
		fi

		touch "neg_${num}_in.txt"
		touch "neg_${num}_args.txt"
	done
fi

cd ../../../..