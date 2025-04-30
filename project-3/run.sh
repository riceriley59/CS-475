#!/bin/bash

executable=project-3
output_file="project-3.csv"

> "$output_file"

make clean
echo "Threads (#), Cities (#), Capitals (#), Performance (MegaCityCapitals/sec)" >> "$output_file"

for t in 1 2 4 6 8
do
    for cap in 2 3 4 5 10 15 20 30 40 50
    do
        echo "Running with $t threads and $cap capitals..."

        make clean-no-csv
        make threads=$t capitals=$cap csv=true

        ./$executable >> "$output_file"
    done
done

make clean-no-csv
