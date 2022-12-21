#!/bin/bash

reset="\033[0m"
bold="\033[1m"
red="\033[38;5;160m"
green="\033[38;5;76m"
blue="\033[38;5;81m"
yellow="\033[38;5;228m"
gray="\033[38;5;246m"
green="\033[38;5;76m"
pink="\033[38;5;225m"
green_bg="\033[48;5;028m"
red_bg="\033[48;5;052m"
width=33

function waitUntilKey {
	printBig "Press any KEY to continue" "${pink}" 66
	read -n 1
}

function printBig {
	if [ $# -gt 2 ]; then
		width=$3
	fi

	echo -ne "${2}${bold}┌"
	for (( i = 0; i < width; i++ ))
	do
		echo -ne "─"
	done
	echo -e "┐${reset}"

	echo -ne "${2}${bold}│${reset}"
	len=${#1}
	spacesL=$(( width - len ))
	spacesL=$(( spacesL / 2 ))
	spacesR=$(( width - len + 1 ))
	spacesR=$(( spacesR / 2 ))
	for (( i = 0; i < spacesL; i++ ))
	do
		echo -ne "${2}${bold} ${reset}"
	done
	echo -ne "${2}${bold}${1}${reset}"
	for (( i = 0; i < spacesR; i++))
	do
		echo -ne "${2}${bold} ${reset}"
	done
	echo -e "${2}${bold}│${reset}"


	echo -ne "${2}${bold}└"
	for (( i = 0; i < width; i++ ))
	do
		echo -ne "─"
	done
	echo -e "┘${reset}"

	width=33
}