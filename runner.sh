#!/bin/bash

# Run the ray tracer 5 times with values 1 through 5 as input params
# Define an array with the desired input parameters
params=(9 7 5 3 1)

# Run the ray tracer with each parameter and save the outputs
for i in "${params[@]}"; do
    ./build/inOneWeekend $i > "image_$i.ppm"
done

