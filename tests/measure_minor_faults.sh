#!/bin/bash

# Initialize variables
total_minor_faults=0
iterations=100

# Run the command 10 times
for ((i=1; i<=iterations; i++))
do
    # Run the command and capture the output
    output=$(/usr/bin/time -v ./allocator 0.00 2>&1)
    
    # Debugging: Print the output
    #echo "Output of iteration $i:"
    #echo "$output"
    
    # Extract the number of minor page faults
    minor_faults=$(echo "$output" | grep "Minor (reclaiming a frame) page faults" | awk -F': ' '{print $2}' | tr -d ' ')
    
    # Debugging: Print the extracted minor faults
    echo "Minor faults in iteration $i: $minor_faults"
    
    # Add to the total, ensure minor_faults is a number
    if [[ "$minor_faults" =~ ^[0-9]+$ ]]; then
        total_minor_faults=$((total_minor_faults + minor_faults))
    else
        echo "Warning: Failed to extract minor faults in iteration $i"
    fi
done

# Calculate the average
average_minor_faults=$(echo "scale=0; $total_minor_faults / $iterations" | bc)

# Print the average
echo "Average Minor Page Faults: $average_minor_faults"