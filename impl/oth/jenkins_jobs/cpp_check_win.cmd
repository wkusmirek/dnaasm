@ECHO OFF
cd "%WORKSPACE%\impl"

REM set coverage and debug options to true in config file
perl -i.bak -pe "s/(COVERAGE=)False/\1True/g" build_custom.ini
perl -i.bak -pe "s/(DEBUG=)False/\1True/g" build_custom.ini

REM enable 64-bit VS Compiler
call "C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\vcvarsall.bat" amd64
call scons

mkdir reports

REM run boost unit tests
call cpp\dnaasm_dbj_test --output_format=XML --log_sink=reports\cpp_dbj_results.xml --log_level=all --report_level=no --result_code=no
call cpp\dnaasm_olc_test --output_format=XML --log_sink=reports\cpp_olc_results.xml --log_level=all --report_level=no --result_code=no
call cpp\dnaasm_scfr_test --output_format=XML --log_sink=reports\cpp_scfr_results.xml --log_level=all --report_level=no --result_code=no

REM remove file and line attributes from TestCase and TestSuite tags in the report
perl -i.bak -pe "s/(Test(?:Case|Suite).+?) file=\"[^^\"]+\" line=\"[^^\"]+\">/\1>/g" reports\cpp_dbj_results.xml
perl -i.bak -pe "s/(Test(?:Case|Suite).+?) file=\"[^^\"]+\" line=\"[^^\"]+\">/\1>/g" reports\cpp_olc_results.xml
perl -i.bak -pe "s/(Test(?:Case|Suite).+?) file=\"[^^\"]+\" line=\"[^^\"]+\">/\1>/g" reports\cpp_scfr_results.xml

REM run static code check and coverage counter
cppcheck --enable=all --inconclusive --inline-suppr --xml --xml-version=2 ./cpp 2> reports\cppcheck.xml
python3 C:\Python35\Scripts\gcovr --exclude-unreachable-branches -x -r ../ -o reports/cpp_coverage.xml

REM wait for report files to be saved successfully
REM this ping command is Windows version of 'sleep 2', nevermind
PING -n 3 127.0.0.1>nul

REM perl -i.bak -pe "s#file=\"#file=\"impl/#g" reports\cpp_results.xml
perl -i.bak -pe "s#file=\"#file=\"impl\#g" reports\cppcheck.xml

REM cleanup
perl -i.bak -pe "s/(COVERAGE=)True/\1False/g" build_custom.ini
perl -i.bak -pe "s/(DEBUG=)True/\1False/g" build_custom.ini

exit /B 0
