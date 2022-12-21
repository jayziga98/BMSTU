#!/bin/bash

flags="-std=c99 -Wall -Werror -Wpedantic -Wextra -Wfloat-equal -Wvla"
extra="--coverage"
filenames="main big_real int_utils big_int beauty_print big_nums_operations char_utils"
objects=""
out="app.exe"

for name in $filenames; do
    program="${name}.c"
    eval "gcc -c ${program} ${flags} ${extra}"
    objects+=" ${name}.o"
done

eval "gcc --coverage -o ${out} ${objects}"
