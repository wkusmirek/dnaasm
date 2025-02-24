#!/bin/sh
set +e
cd "$WORKSPACE/impl"
perl -i -pe 's/(COVERAGE=)True/\1False/g' build_custom.ini
perl -i -pe 's/(DEBUG=)True/\1False/g' build_custom.ini
rm -f install/web_server/dnaasm*.deb
set -e
scons
scons install=1
scp install/web_server/dnaasm*amd64.deb braster@francja:dnaasm_server_amd64.deb
scp oth/jenkins_jobs/dnaasm_server_deb_install.sh braster@francja:dnaasm_server_deb_install.sh
ssh -t braster@francja 'chmod +x dnaasm_server_deb_install.sh; sudo ~/dnaasm_server_deb_install.sh'
