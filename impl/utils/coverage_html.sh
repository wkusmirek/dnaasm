#!/bin/bash

# Build project with coverage flags
perl -i -pe 's/(COVERAGE=)False/\1True/g' build_custom.ini
perl -i -pe 's/(DEBUG=)False/\1True/g' build_custom.ini
set -e
scons
set +e

# Generate initial coverage information
lcov -b cpp/src -c -i -d ./cpp/src -o .coverage.wtest.base --no-external

# Run all tests:
scons t=c

# Generate coverage based on executed tests
lcov -b cpp/src -c -d ./cpp/src -o .coverage.wtest.run --no-external

# Merge coverage tracefiles
lcov -a .coverage.wtest.base -a .coverage.wtest.run -o .coverage.total

# Filtering, extracting project files
#lcov -e .coverage.total "`pwd`/cpp/src/*" -o .coverage.total.filtered

# Filtering, removing main file and boost_python file
lcov -r .coverage.total "`pwd`/cpp/src/dnaasm_main.cpp" -o .coverage.total
lcov -r .coverage.total "`pwd`/cpp/src/dnaasmpy.cpp" -o .coverage.total

# Extra: Clear up previous data, create html folder
if [[ -d ./html/ ]] ; then
    rm -rf ./html/*
else
    mkdir html
fi

mv .coverage.total .coverage.results

# Display coverage results in console
lcov --list .coverage.results

# Generate webpage
echo "To generate html with visual coverage report, type:"
echo "genhtml -o ./html/ .coverage.results"

# Cleanup
rm .coverage.wtest.*
