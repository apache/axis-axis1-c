#!/bin/sh
#
set +u # Don't complain about unset variables
unset=0
if [[ -z "$AXISCPP_HOME" ]]
then
	echo -e "Environment variable AXISCPP_HOME is not set. A default will be used"
    unset=1
fi
if [[ -z "$AXISCPP_HOME" ]]
then
	echo -e "Environment variable AXISCPP_HOME is not set. A default will be used"
    unset=1
fi

if [[ -z "$HOME_DIR" ]]
then
HOME_DIR=$PWD
export HOME_DIR
fi
#if [[ -z "$AXISTEST_HOME" ]]
#then
#	echo -e "Environment variable AXISTEST_HOME is not set. A default will be used"
#    unset=1
#fi

if [[ $unset -ne 0 ]]
then
	echo -n "Some required environment variables have not been set. "
	echo -n "Continue? [Y/N] "; read x
    case $x in
		Y|y) ;;
          *) echo -e "Exiting." ; exit 1 ;;
	esac
fi

. ${HOME_DIR}/testcases/platform/linux/setAxis.sh 

#rm -rf $OUTPUT_DIR
passed=0
num_tests=0
for X in ${TEST_HOME}/testcases/wsdls/*.wsdl
do
runTestCase.sh "$X" c++
[[ $? -eq 0 ]] && passed=$(($passed + 1))
num_tests=`expr $num_tests + 1`
echo " "
done

echo -n "${passed}/${num_tests} tests passed."
[[ $passed -eq $num_tests ]] && echo " PASSED" || echo " FAILED"

#exit 0

#for file in $(find client -name "*.c" -o -name "*.cpp")
#do
# runTestCase.sh $(echo testcases/wsdls/$(basename $file) | sed "s/Client\./.wsdl /" | sed "s/pp/++/")
#done
