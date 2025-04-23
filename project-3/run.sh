#!/bin/bash

output_file="results.csv" > "$output_file"

for t in 1 2 4 6 8
do
    for cap in 2 3 4 5 10 15 20 30 40 50
    do
        echo "Running with $t threads and $cap capitals..."

        make clean
        make threads=$t capitals=$cap

        ./main 2>&1 | tee -a "$output_file"
    done
done

make clean
