#!/bin/bash
set +e
cd "$WORKSPACE/impl"
perl -i -pe 's/(COVERAGE=)False/\1True/g' build_custom.ini
perl -i -pe 's/(DEBUG=)False/\1True/g' build_custom.ini
set -e
scons
scons syncdb=1
set +e
export LD_LIBRARY_PATH="$PWD/cpp/lib"${LD_LIBRARY_PATH:+:$LD_LIBRARY_PATH}
python3 build_web/manage.py jenkins --settings=config.settings.dev version production current dnaasmpy assembly align olc bst scaffold user file logs mail --enable-coverage --noinput
mv reports/coverage.xml reports/python_coverage.xml
mv reports/junit.xml reports/python_results.xml
# fix relative path issues for pyflakes and coverage
perl -i -pe 's#build_web#impl/build_web#g' reports/pyflakes.report
perl -i -pe 's#build_web#impl/build_web#g' reports/python_coverage.xml
