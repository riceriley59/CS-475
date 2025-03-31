#!/bin/bash

output_file="results.txt"
> "$output_file"  # Clear the file before running

for t in 1 4
do
    echo "Running with $t threads..." | tee -a "$output_file"
    make clean
    make threads=$t
    ./main 2>&1 | tee -a "$output_file"
    echo "" | tee -a "$output_file"  # Add spacing
done

make clean
