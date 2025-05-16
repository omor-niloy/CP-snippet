#!/bin/bash

# Check if correct number of arguments is provided
if [ "$#" -ne 4 ]; then
    echo "Usage: $0 <test_generator> <slow_code> <fast_code> <iterations>"
    exit 1
fi

# Assign arguments to variables
TEST_GEN="$1"
SLOW_CODE="$2"
FAST_CODE="$3"
ITERATIONS="$4"

# Compile the C++ programs
g++ "$TEST_GEN.cpp" -o "$TEST_GEN"
g++ "$SLOW_CODE.cpp" -o "$SLOW_CODE"
g++ "$FAST_CODE.cpp" -o "$FAST_CODE"

for ((i = 1; i <= ITERATIONS; i++)); do
    echo "Running test $i..."
    
    # Generate test cases
    ./"$TEST_GEN" > input.txt
    
    # Run both programs
    ./"$SLOW_CODE" < input.txt > slowo.txt
    ./"$FAST_CODE" < input.txt > fasto.txt
    
    # Compare the outputs
    if ! diff -q slowo.txt fasto.txt > /dev/null; then
        echo "Test $i failed! Outputs do not match."
        diff slow_output.txt fast_output.txt  # Show differences
        exit 1  # Stop execution
    fi
done

echo "All tests passed successfully!"

# ./slow.sh t ex2 ex1 100
# chmod +x slow.sh
