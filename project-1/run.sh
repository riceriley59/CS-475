#!/bin/bash

output_file="results.txt" > "$output_file"  # Clear the file before running

for t in 1 2 4 8
do
    for tr in 50000 100000 150000
    do
        echo "Running with $t threads and $tr trials..." | tee -a "$output_file"

        make clean
        make threads=$t trials=$tr

        ./main 2>&1 | tee -a "$output_file"
        echo "" | tee -a "$output_file"  # Add spacing
    done
done

make clean # Get rid of remaining executable
