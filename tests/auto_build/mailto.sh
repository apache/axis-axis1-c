#!/bin/bash
HOME_DIR="/home/damitha/projects/cvshead/tests/auto_build"
PATH="/usr/bin:/usr/sbin:/usr/local/bin:$PATH"
export HOME_DIR PATH
if test -f $HOME_DIR/mailto; then
#echo "$HOME_DIR"
#cat  $HOME_DIR/testcases/build/runTestCase.log | mutt -s "[test-results]Axis C++ Autobuild and regression test" -a "$HOME_DIR/testcases/build/buildTestCase.log" -x axis-c-dev@ws.apache.org
cat  log $HOME_DIR/testcases/build/runTestCase.log | mutt -s "[test-results]Axis C++ Autobuild and regression test" -x axis-c-dev@ws.apache.org
touch ${HOME_DIR}/DAMITHA3
fi
