#!/bin/bash

### RETURN CODES:
 # 0 - SUCCESS
 # 1 - THE PROGRAM UNDER TEST RETURNED AN ERROR
 # 2 - VALGRIND MEMORY ERROR
 # 3 - COMPARATOR RETURNED FAILURE

red="\033[38;5;160m"
reset="\033[0m"

file_stream_in="${1}"
file_app_args=""

if [ $# -gt 1 ]; then
    file_app_args=$(cat "${2}")
fi

exit_code=0

if [ "$USE_VALGRIND" != "" ]; then 
    eval "valgrind --tool=memcheck -q --log-file=../../valgrind_%p_neg.log ../../app.exe $file_app_args < ${file_stream_in} > program_out.txt"
    exit_code=$?
    cd ../../
    log_file_name=$(find ./valgrind*.log | tail -1)
    cd ./func_tests/scripts || exit
    if ! bash mem_check.sh "../../${log_file_name}"; then
        exit 2
    fi
else 
    eval "../../app.exe $file_app_args < ${file_stream_in} > 'program_out.txt'"
    exit_code=$? 
    err=$(grep -Eo "Ошибка: .*!" "program_out.txt")
    >&2 echo -e "${red}${err}${reset}"
fi

if [ $exit_code -ne 0 ]; then
    exit 0
else
    exit 1
fi
