#!/bin/bash

executable=project-4
output_file="project-4.csv"

> "$output_file"

make clean
echo "Threads (#), Cities (#), Capitals (#), Performance (MegaCityCapitals/sec)" >> "$output_file"

for arraysize in 1 2 4 6 8
do
    echo "Running with array size of $arraysize..."

    make clean-no-csv
    make arraysize=$arraysize

    ./$executable >> "$output_file"
done

make clean-no-csv
