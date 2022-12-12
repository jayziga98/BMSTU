#!/bin/bash

reset="\033[0m"
bold="\033[1m"
red="\033[38;5;160m"
green="\033[38;5;76m"
yellow="\033[38;5;228m"
purple="\033[38;5;140m"
blue="\033[38;5;81m"
gray="\033[38;5;246m"

failed_tests=0

echo -e "${bold}START TESTING${reset}"

echo -e "${purple}Positive tests${reset}"
counter=1
correct_tests=0
file="../data/pos_0${counter}"
while [ -f "${file}_in.txt" ]; do

    exit_code=1

    if [ -f "${file}_args.txt" ]; then
        bash pos_case.sh "${file}_in.txt" "${file}_out.txt" "${file}_args.txt"
        exit_code=$?
    else
        bash pos_case.sh "${file}_in.txt" "${file}_out.txt"
        exit_code=$?
    fi

    check=0

    if [ $exit_code -eq 0 ] || [ $exit_code -eq 2 ]; then
        echo -ne "${green}Positive test №${counter}: \tPASSED${reset}"
        check=$(( check + 1 ))
    else
        check=$(( check - 1 ))
        echo -ne "${red}Positive test №${counter}: \tFAILURE${reset}"  
    fi

    if [ "$USE_VALGRIND" != "" ]; then 
        if [ $exit_code -ne 2 ]; then
            check=$(( check + 1 ))
            echo -ne "\t${blue}[${green}Memory OK${blue}]${reset}"
        else
            check=$(( check - 1 ))
            echo -ne "\t${blue}[${red}Memory BAD${blue}]${reset}"
        fi
        rm -f ./temp.log
    else
        echo -ne "\t${blue}[${gray}Memory NOT CHECKED${blue}]${reset}"
    fi

    echo

    if [ $check -gt 0 ]; then
        correct_tests=$(( correct_tests + 1 ))
    else
        failed_tests=$(( failed_tests + 1 ))
    fi

    counter=$(( counter + 1 ))
    file="../data/pos_0${counter}"
    if [ $counter -gt 9 ]; then
        file="../data/pos_${counter}"
    fi

done

counter=$(( counter - 1 ))
if [ $counter -eq 0 ]; then
    echo -e "${yellow}There are no ${bold}positive${reset} ${yellow}'in' files${reset}"
else
    echo -e "Positive tests: correct ${correct_tests} of ${counter}"
fi


echo -e "${purple}Negative tests${reset}"
counter=1
correct_tests=0
file="../data/neg_0${counter}"
while [ -f "${file}_in.txt" ]; do

    exit_code=1

    if [ -f "${file}_args.txt" ]; then
        bash neg_case.sh "${file}_in.txt" "${file}_args.txt"
        exit_code=$?
    else
        bash neg_case.sh "${file}_in.txt"
        exit_code=$?
    fi

    check=0

    if [ $exit_code -eq 0 ] || [ $exit_code -eq 2 ]; then
        echo -ne "${green}Negative test №${counter}: \tPASSED${reset}"
        check=$(( check + 1 ))
    else
        check=$(( check - 1 ))
        echo -ne "${red}Negative test №${counter}: \tFAILURE${reset}"  
    fi

    if [ "$USE_VALGRIND" != "" ]; then 
        if [ $exit_code -ne 2 ]; then
            check=$(( check + 1 ))
            echo -ne "\t${blue}[${green}Memory OK${blue}]${reset}"
        else
            check=$(( check - 1 ))
            echo -ne "\t${blue}[${red}Memory BAD${blue}]${reset}"
        fi
        rm -f ./temp.log
    else
        echo -ne "\t${blue}[${gray}Memory NOT CHECKED${blue}]${reset}"
    fi

    echo

    if [ $check -gt 0 ]; then
        correct_tests=$(( correct_tests + 1 ))
    else
        failed_tests=$(( failed_tests + 1 ))
    fi

    counter=$(( counter + 1 ))
    file="../data/neg_0${counter}"
    if [ $counter -gt 9 ]; then
        file="../data/neg_${counter}"
    fi

done

counter=$(( counter - 1 ))
if [ $counter -eq 0 ]; then
    echo -e "${yellow}There are no ${bold}negative${reset} ${yellow}'in' files${reset}"
else
    echo -e "Negative tests: correct ${correct_tests} of ${counter}"
fi

exit $failed_tests
