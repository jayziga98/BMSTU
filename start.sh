#!/bin/bash
source ./lib.sh

reset="\033[0m"
red="\033[38;5;160m"
green="\033[38;5;76m"
blue="\033[38;5;81m"
yellow="\033[38;5;228m"
gray="\033[38;5;246m"
green="\033[38;5;76m"
green_bg="\033[48;5;028m"
red_bg="\033[48;5;052m"

USE_VALGRIND=""
export USE_VALGRIND

COVERAGE=""

total=0
exp_total=0

incorrect="labs │"
correct="labs │"

pref="lab"

clear

lab=$(find . -maxdepth 1 -type d | grep -E "${pref}_${1}.*")
lab=$(echo "$lab" | sed 's/_/ /g' | sort -k3 | sed 's/ /_/g' | tr '\n' ' ')
for i in $lab
do
	check=0
	exp_check=0

	num=$(echo -n "$i" | grep -Eo "${1}(_[0-9]*)*" | sed 's/${pref}_//g')

	printBig "$i" "${reset}" "66"
	sleep 3

	printBig "CODECHECKER" "${yellow}"
	cd ../СИ/"Программирование на С"/CodeChecker/Codechecker/ || exit
	path="/Users/toupist/Desktop/ТиСД/${pref}_${num}"
	files=$(find "../../../../ТиСД/${pref}_${num}" -name "*.c" -exec basename {} \;)
	for file in $files; do
		out=$(eval "./Codechecker.exe $path/$file" | sed -e '/register/d')
		if [ -n "$out" ]; then
			printBig "BAD ➜ $file" "${red}"
			echo "$out"
			printBig "BAD ➜ $file" "${red}"
		else
			printBig "GOOD ➜ $file" "${green}"
			check=$(( check + 1 ))
		fi
		exp_check=$(( exp_check + 1 ))
	done
	printBig "CODECHECKER" "${yellow}"
	cd ../../../../ТиСД || exit
	cd "${pref}_${num}" || exit


	printBig "CLANG" "${blue}"
	for file in ./*.c; do
		out=$(eval "clang -Weverything -Wno-conversion -Wno-sign-conversion -c $file 2>&1 | grep -E 'prototypes|poison-system-directories|padded' | wc -l | grep -Eo '[0-9]*'")
		exp_out=$(eval "clang -Weverything -Wno-conversion -Wno-sign-conversion -c $file 2>&1 | grep -E '[0-9]* warning(s)? generated.$' | grep -Eo '[0-9]*'")
		if [ "$out" != "$exp_out" ]; then
			printBig "BAD ➜ $file" "${red}"
			eval "clang -Weverything  -Wno-conversion -Wno-sign-conversion -c $file"
			printBig "BAD ➜ $file" "${red}"
			
		else
			printBig "GOOD ➜ $file" "${green}"
			check=$(( check + 1 ))
		fi
		exp_check=$(( exp_check + 1 ))
	done
	printBig "CLANG" "${blue}"


	if [ -n "$COVERAGE" ]; then
		bash build_gcov.sh
	elif [ "$USE_VALGRIND" == "" ]; then
		bash build_release.sh
	else
		bash build_debug.sh
	fi

	printBig "SHELLCHECK" "${gray}"
	out=$(eval "bash check_scripts.sh" | grep -vE "./*.sh")
	if [ -n "$out" ]; then
		printBig "BAD" "${red}"
		echo "$out"
		printBig "BAD" "${red}"
		
	else
		printBig "GOOD" "${green}"
		check=$(( check + 1 ))
	fi
	exp_check=$(( exp_check + 1 ))
	printBig "SHELLCHECK" "${gray}"


	cd func_tests/scripts/ || exit
	bash func_tests.sh
	exit_code=$?
	check=$(( check + exit_code ))

	cd ../../
	if [ -n "$COVERAGE" ]; then
		bash ./collect_coverage.sh
	fi

	if [ "${2}" != "-s" ]; then
		if [ "$USE_VALGRIND" == "" ] || [ "${2}" == "-c" ]; 
		then
			bash clean.sh
		fi
	fi
	find . -name .dSYM -print -delete
	find . -name .DS_Store -print -delete
	cd ../../

	if [ "$exp_check" == "$check" ]; then
		correct+=" ${num} │"
		printBig "EXCELLENT!" "${green}" 66
		total=$(( total + 1 ))
		sleep 3
		clear
	else
		incorrect+=" ${num} │"
		printBig "DISGUSTING!" "${red}" 66
		waitUntilKey
		clear
	fi

	exp_total=$(( exp_total + 1 ))
done

if [ "$exp_total" == "$total" ]; then
	printBig "$correct" "${green_bg}" 66
	sleep 1
	clear
	exit 0
else
	printBig "$incorrect" "${red_bg}" 66
	waitUntilKey
	clear
	exit "$(( exp_total - total ))"
fi

# regex="(.*= \"\")|(.*\+= 1;)"
# find ./iu7-cprog-labs-2022-kozlitinmaxim/*/main.c -exec cat {} + | grep -E "$regex"
