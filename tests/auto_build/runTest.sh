#!/bin/sh
#
here=$PWD
script_location=$(dirname $0)
cd $script_location
TEST_HOME=$PWD
cd $here

WSDL=$1
LANG=${2:-c++}

# Strip any path and suffix stuff from WSDL
WSDL2=$(basename $WSDL wsdl)

if [[ ! -f $WSDL ]]
then
	# Try in the wsdls directory
	if [[ ! -f wsdls/${WSDL} ]]
	then
		if [[ ! -f wsdls/${WSDL2}.wsdl ]]
		then
			echo "Cannot find WSDL $WSDL"
			exit 0
		else
			WSDL=wsdls/${WSDL2}.wsdl
		fi
	else
		WSDL=wsdls/${WSDL}
	fi
fi

if [[ ! -f $TEST_HOME/testcases/platform/linux/setAxis.sh ]]
then
	echo "Cannot determine where the test framework is."
    echo "The $0 script is probably in the wrong directory"
	exit 1
fi

. $TEST_HOME/testcases/platform/linux/setAxis.sh 
[[ $? -ne 0 ]] && {
	exit 1
}

cd $AXISTEST_HOME

[[ -f $OUTPUT_DIR/buildTestCase.log ]] && >>$OUTPUT_DIR/buildTestCase.log
[[ -f $OUTPUT_DIR/runTestCase.log ]] && >>$OUTPUT_DIR/runTestCase.log
runTestCase.sh $WSDL c++

exit 0

