#!/bin/bash
set +e
cd "$WORKSPACE/impl"
perl -i -pe 's/(COVERAGE=)True/\1False/g' build_custom.ini
perl -i -pe 's/(DEBUG=)True/\1False/g' build_custom.ini
set -e
scons
set +e
scons t=p
