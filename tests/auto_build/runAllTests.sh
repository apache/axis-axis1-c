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

. testcases/platform/linux/setAxis.sh 

#rm -rf $OUTPUT_DIR

passed=0
num_tests=21

#test1 
runTestCase.sh testcases/wsdls/RpcHttpHeaderTest1.wsdl c++
[[ $? -eq 0 ]] && passed=$(($passed + 1))
#test2
runTestCase.sh testcases/wsdls/RpcHttpHeaderTest2.wsdl c++
[[ $? -eq 0 ]] && passed=$(($passed + 1))
#test3 
runTestCase.sh testcases/wsdls/RpcHttpHeaderTest3.wsdl c++
[[ $? -eq 0 ]] && passed=$(($passed + 1))
#test4 
runTestCase.sh testcases/wsdls/RpcHttpHeaderTest4.wsdl c++
[[ $? -eq 0 ]] && passed=$(($passed + 1))
#test5 
runTestCase.sh testcases/wsdls/RpcHttpHeaderTest5.wsdl c++
[[ $? -eq 0 ]] && passed=$(($passed + 1))
#test6 
runTestCase.sh testcases/wsdls/RpcHttpHeaderTest7.wsdl c++
[[ $? -eq 0 ]] && passed=$(($passed + 1))
#test7 
runTestCase.sh testcases/wsdls/RpcHttpHeaderTest8.wsdl c++
[[ $? -eq 0 ]] && passed=$(($passed + 1))
#test8 
runTestCase.sh testcases/wsdls/RpcSoapHeaderTest1.wsdl c++
[[ $? -eq 0 ]] && passed=$(($passed + 1))
#test9 
runTestCase.sh testcases/wsdls/RpcSoapHeaderTest2.wsdl c++
[[ $? -eq 0 ]] && passed=$(($passed + 1))
#test10 
runTestCase.sh testcases/wsdls/RpcSoapHeaderTest3.wsdl c++
[[ $? -eq 0 ]] && passed=$(($passed + 1))
#test11
runTestCase.sh testcases/wsdls/RpcSoapHeaderTest4.wsdl c++
[[ $? -eq 0 ]] && passed=$(($passed + 1))
#test12
runTestCase.sh testcases/wsdls/RpcSoapHeaderTest6.wsdl c++
[[ $? -eq 0 ]] && passed=$(($passed + 1))
#test13 
runTestCase.sh testcases/wsdls/RpcSoapHeaderTest8.wsdl c++
[[ $? -eq 0 ]] && passed=$(($passed + 1))
#test14 
runTestCase.sh testcases/wsdls/RpcSoapHeaderTest9.wsdl c++
[[ $? -eq 0 ]] && passed=$(($passed + 1))
#test15 
runTestCase.sh testcases/wsdls/RpcSoapHeaderTest10.wsdl c++
[[ $? -eq 0 ]] && passed=$(($passed + 1))
#test16 
runTestCase.sh testcases/wsdls/MathOps.wsdl c++
[[ $? -eq 0 ]] && passed=$(($passed + 1))
#test17 
runTestCase.sh testcases/wsdls/ExceptionTest.wsdl c++
[[ $? -eq 0 ]] && passed=$(($passed + 1))
#test18 
runTestCase.sh testcases/wsdls/FaultMapping.wsdl c++
[[ $? -eq 0 ]] && passed=$(($passed + 1))
#test19 
runTestCase.sh testcases/wsdls/InteropTestRound1.wsdl c++
[[ $? -eq 0 ]] && passed=$(($passed + 1))
#test20
runTestCase.sh testcases/wsdls/ExtensibilityQuery.wsdl c++
[[ $? -eq 0 ]] && passed=$(($passed + 1))
#test21
runTestCase.sh testcases/wsdls/Calculator.wsdl c++
[[ $? -eq 0 ]] && passed=$(($passed + 1))

# inserted Adrian Dick by
#runTestCase.sh testcases/wsdls/SimpleTypeArray.wsdl c++
#[[ $? -eq 0 ]] && passed=$(($passed + 1))
#runTestCase.sh testcases/wsdls/SimpleTypeInnerUnbounded.wsdl c++
#[[ $? -eq 0 ]] && passed=$(($passed + 1))
#runTestCase.sh testcases/wsdls/SimpleTypeInnerUnboundedInOutput.wsdl c++
#[[ $? -eq 0 ]] && passed=$(($passed + 1))
# runTestCase.sh testcases/wsdls/SOAPHeaderStockService.wsdl c++
#[[ $? -eq 0 ]] && passed=$(($passed + 1))
# runTestCase.sh testcases/wsdls/TradeServices.wsdl c++
#[[ $? -eq 0 ]] && passed=$(($passed + 1))

echo -n "${passed}/${num_tests} tests passed."
[[ $passed -eq $num_tests ]] && echo " PASSED" || echo " FAILED"

exit 0

for file in $(find client -name "*.c" -o -name "*.cpp")
do
 runTestCase.sh $(echo testcases/wsdls/$(basename $file) | sed "s/Client\./.wsdl /" | sed "s/pp/++/")
done
