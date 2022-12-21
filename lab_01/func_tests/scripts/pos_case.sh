#!/bin/bash

### RETURN CODES:
 # 0 - SUCCESS
 # 1 - THE PROGRAM UNDER TEST RETURNED AN ERROR
 # 2 - VALGRIND MEMORY ERROR
 # 3 - COMPARATOR RETURNED FAILURE

file_stream_in="${1}"
file_stream_out_expect="${2}"
file_app_args=""

if [ $# -gt 2 ]; then
    file_app_args=$(cat "${2}")
fi

exit_code=1

if [ "$USE_VALGRIND" != "" ]; then 
    eval "valgrind --tool=memcheck -q --log-file=../../valgrind_%p_pos.log ../../app.exe $file_app_args < ${file_stream_in} > program_out.txt"
    exit_code=$?
    cd ../../
    log_file_name=$(find ./valgrind*.log | tail -1)
    cd ./func_tests/scripts || exit
    if ! bash mem_check.sh "../../${log_file_name}"; then
        exit 2
    fi
else 
    eval "../../app.exe $file_app_args < ${file_stream_in} > program_out.txt"
    exit_code=$?
fi

if [ $exit_code -ne 0 ]; then
    exit 1
fi

if bash ./comparator.sh "${file_stream_out_expect}" ./program_out.txt; then
    exit 0
else
    exit 3
fi
