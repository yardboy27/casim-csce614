#!/bin/sh

# List of all SPEC benchmarks
spec_benchmarks=("bzip2" "gcc" "mcf" "hmmer" "sjeng" "libquantum" "xalancbmk" "milc" "cactusADM" "leslie3d" "namd" "soplex" "calculix" "lbm")

# List of all PARSEC benchmarks
parsec_benchmarks=("blackscholes" "bodytrack" "canneal" "dedup" "fluidanimate" "freqmine" "streamcluster" "swaptions" "x264")

# Run SPEC benchmarks
for bench in "${spec_benchmarks[@]}"; do
    echo "Running SPEC benchmark: $bench with LRU replacement policy..."
    ./hw4runscript SPEC "$bench" LRU
done

# Run PARSEC benchmarks
for bench in "${parsec_benchmarks[@]}"; do
    echo "Running PARSEC benchmark: $bench with LRU replacement policy..."
    ./hw4runscript PARSEC "$bench" LRU
done

