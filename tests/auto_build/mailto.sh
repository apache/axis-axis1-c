#!/bin/bash
HOME_DIR="/home/damitha/projects/cvshead/tests/auto_build"
PATH="/usr/bin:/usr/sbin:/usr/local/bin:$PATH"
export HOME_DIR PATH
if test -f $HOME_DIR/mailto; then
    cat  $HOME_DIR/testcases/build/runTestCase.log | mutt -s "[test-results]Axis C++ Autobuild and regression test" -a "$HOME_DIR/testcases/build/buildTestCase.log" -x axis-c-dev@ws.apache.org
fi
