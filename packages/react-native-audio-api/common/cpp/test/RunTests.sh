#!/bin/bash

set -e

cleanup() {
    echo "Cleaning up..."
    rm -rf build/
}

trap cleanup EXIT
# Step 1: Move to the script's directory
cd "$(dirname "$0")"
# Step 2: Configure CMake project
# mkdir build
cmake -S . -B build

# Step 3: Build the project
cmake --build build

# Step 4: Run the test binary
cd build
./tests
cd ..

# Step 5: Clean up build directory
rm -rf build/
