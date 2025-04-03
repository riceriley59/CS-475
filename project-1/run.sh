#!/bin/bash

output_file="results.csv" > "$output_file"  # Clear the file before running

for t in 1 2 4 8
do
    for tr in 1 10 100 1000 100000 500000
    do
        echo "Running with $t threads and $tr trials..."

        make clean
        make threads=$t trials=$tr

        ./main 2>&1 | tee -a "$output_file"
    done
done

make clean # Get rid of remaining executable
