#!/bin/bash

# Build the project
cmake --build build

# Run the inOneWeekend command with arguments passed to the script
./build/inOneWeekend "$@" > image.ppm

# Run the a.out program
./a.out

# Open the generated image
open image.png

