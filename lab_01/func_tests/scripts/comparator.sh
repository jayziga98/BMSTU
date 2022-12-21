#!/bin/bash

file1="$1"
file2="$2"

regex="[+-]0.?[0-9]*[eE][+-][0-9]*"
file1_numbers=$(grep -Eo "$regex" "$file1" | tail -1)
file2_numbers=$(grep -Eo "$regex" "$file2" | tail -1)

if [ "$file1_numbers" == "$file2_numbers" ]; then
    exit 0
else
    exit 1
fi
