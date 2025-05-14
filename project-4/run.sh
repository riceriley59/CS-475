#!/bin/bash

executable=project-4
output_file="project-4.csv"

array_sizes=(1000 10000 50000 100000 500000 1000000 2000000 4000000 6000000 8000000)

> "$output_file"

make clean
echo "Array Size (#), Non SIMD Mult (MegaMults/sec), SIMD Mult (MegaMults/sec), Speedup, Non SIMD Mult Sum (MegaMultSums/sec), SIMD Mult Sum (MegaMultSums/sec), Speedup" >> "$output_file"

for arraysize in "${array_sizes[@]}";
do
    echo "Running with array size of $arraysize..."

    make clean-no-csv
    make arraysize=$arraysize

    ./$executable &>> "$output_file"
done

make clean-no-csv
