#!/bin/bash

# Check if the input and output files are provided
if [ "$#" -ne 2 ]; then
  echo "Usage: $0 <input_csv_file> <output_file>"
  exit 1
fi

input_file=$1
output_dir=$2
output_file="$output_dir/t1.csv"

# Ensure the input file exists
if [ ! -f "$input_file" ]; then
  echo "Error: File '$input_file' not found."
  exit 1
fi

# Read the file and process it
{
  # Read the header line and extract the last word of each item
  IFS=',' read -r -a header <<< "$(head -n 1 "$input_file")"
  for (( i=0; i<${#header[@]}; i++ )); do
    header[$i]="${header[$i]##* }"  # Extract the last word after the last space
  done

  # Process the remaining lines
  tail -n +2 "$input_file" | while IFS=',' read -r -a values; do
    for (( i=0; i<${#header[@]}; i++ )); do
      echo "${header[$i]} = ${values[$i]}"
    done
    echo ".."
  done
} > "$output_file"

