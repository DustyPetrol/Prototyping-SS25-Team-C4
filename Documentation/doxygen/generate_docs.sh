#!/bin/bash
set -e

doxygen Doxyfile

# Go to the latex build directory
cd ./tmp/latex/

# Run make
make

# Copy the generated PDF back to the original directory
cp refman.pdf ../../CodeDocumentation.pdf

echo "refman.pdf copied to $(pwd)/../../"
