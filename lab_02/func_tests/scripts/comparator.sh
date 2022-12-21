#!/bin/bash

file1="$1"
file2="$2"

if cmp "$file1" "$file2"; then
    exit 0
else
    exit 1
fi
