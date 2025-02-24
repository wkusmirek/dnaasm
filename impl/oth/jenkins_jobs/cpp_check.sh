#!/bin/bash

# set up config and build project
set +e
cd "$WORKSPACE/impl"
perl -i -pe 's/(COVERAGE=)False/\1True/g' build_custom.ini
perl -i -pe 's/(DEBUG=)False/\1True/g' build_custom.ini
set -e
scons
set +e
mkdir reports

# run C++ unit tests and save reports
LD_LIBRARY_PATH=$PWD/cpp${LD_LIBRARY_PATH:+:$LD_LIBRARY_PATH} ./cpp/dnaasm_dbj_test --log_format=XML --log_sink=reports/cpp_dbj_results.xml --log_level=all --report_level=no --result_code=no
LD_LIBRARY_PATH=$PWD/cpp${LD_LIBRARY_PATH:+:$LD_LIBRARY_PATH} ./cpp/dnaasm_olc_test --log_format=XML --log_sink=reports/cpp_olc_results.xml --log_level=all --report_level=no --result_code=no
LD_LIBRARY_PATH=$PWD/cpp${LD_LIBRARY_PATH:+:$LD_LIBRARY_PATH} ./cpp/dnaasm_scfr_test --log_format=XML --log_sink=reports/cpp_scfr_results.xml --log_level=all --report_level=no --result_code=no

# remove file and line attributes from TestCase and TestSuite xml tags
perl -i -pe 's/(Test(?:Case|Suite).+?) file="[^"]+" line="[^"]+">/\1>/g' ./reports/cpp_dbj_results.xml
perl -i -pe 's/(Test(?:Case|Suite).+?) file="[^"]+" line="[^"]+">/\1>/g' ./reports/cpp_olc_results.xml
perl -i -pe 's/(Test(?:Case|Suite).+?) file="[^"]+" line="[^"]+">/\1>/g' ./reports/cpp_scfr_results.xml

# run static code analysis and code coverage
cppcheck --enable=all --inconclusive --inline-suppr --xml --xml-version=2 ./cpp 2> ./reports/cppcheck.xml
perl -i -pe 's#file="#file="impl/#g' ./reports/cpp*
gcovr --exclude-unreachable-branches -x -r ../ -o reports/cpp_coverage.xml
perl -i -pe 's/(trivial::)info\);/\1trace\);/g' cpp/src/log.cpp
