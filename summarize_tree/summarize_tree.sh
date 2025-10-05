#!/usr/bin/env bash

# Given directory to work in
DIR="$1"
cd "$DIR" || exit 1

# Total counts of dirs and files
num_dir=$(find . -type d | wc -l)
num_file=$(find . -type f | wc -l)

echo "There were $num_dir directories."
echo "There were $num_file regular files."