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

. platform/linux/setAxis.sh 

rm -rf $OUTPUT_DIR

passed=0
num_tests=21

# inserted Adrian Dick by
#test1 
runTestCase.sh wsdls/RpcHttpHeaderTest1.wsdl c++
[[ $? -eq 0 ]] && passed=$(($passed + 1))
#test2
runTestCase.sh wsdls/RpcHttpHeaderTest2.wsdl c++
[[ $? -eq 0 ]] && passed=$(($passed + 1))
#test3 
runTestCase.sh wsdls/RpcHttpHeaderTest3.wsdl c++
[[ $? -eq 0 ]] && passed=$(($passed + 1))
#test4 
runTestCase.sh wsdls/RpcHttpHeaderTest4.wsdl c++
[[ $? -eq 0 ]] && passed=$(($passed + 1))
#test5 
runTestCase.sh wsdls/RpcHttpHeaderTest5.wsdl c++
[[ $? -eq 0 ]] && passed=$(($passed + 1))
#test6 
runTestCase.sh wsdls/RpcHttpHeaderTest7.wsdl c++
[[ $? -eq 0 ]] && passed=$(($passed + 1))
#test7 
runTestCase.sh wsdls/RpcHttpHeaderTest8.wsdl c++
[[ $? -eq 0 ]] && passed=$(($passed + 1))
#test8 
runTestCase.sh wsdls/RpcSoapHeaderTest1.wsdl c++
[[ $? -eq 0 ]] && passed=$(($passed + 1))
#test9 
runTestCase.sh wsdls/RpcSoapHeaderTest2.wsdl c++
[[ $? -eq 0 ]] && passed=$(($passed + 1))
#test10 
runTestCase.sh wsdls/RpcSoapHeaderTest3.wsdl c++
[[ $? -eq 0 ]] && passed=$(($passed + 1))
#test11
runTestCase.sh wsdls/RpcSoapHeaderTest4.wsdl c++
[[ $? -eq 0 ]] && passed=$(($passed + 1))
#test12
runTestCase.sh wsdls/RpcSoapHeaderTest6.wsdl c++
[[ $? -eq 0 ]] && passed=$(($passed + 1))
#test13 
runTestCase.sh wsdls/RpcSoapHeaderTest8.wsdl c++
[[ $? -eq 0 ]] && passed=$(($passed + 1))
#test14 
runTestCase.sh wsdls/RpcSoapHeaderTest9.wsdl c++
[[ $? -eq 0 ]] && passed=$(($passed + 1))
#test15 
runTestCase.sh wsdls/RpcSoapHeaderTest10.wsdl c++
[[ $? -eq 0 ]] && passed=$(($passed + 1))
#test16 
runTestCase.sh wsdls/MathOps.wsdl c++
[[ $? -eq 0 ]] && passed=$(($passed + 1))
#test17 
runTestCase.sh wsdls/ExceptionTest.wsdl c++
[[ $? -eq 0 ]] && passed=$(($passed + 1))
#test18 
runTestCase.sh wsdls/FaultMapping.wsdl c++
[[ $? -eq 0 ]] && passed=$(($passed + 1))
#test19 
runTestCase.sh wsdls/InteropTestRound1.wsdl c++
[[ $? -eq 0 ]] && passed=$(($passed + 1))
#test20
runTestCase.sh wsdls/ExtensibilityQuery.wsdl c++
[[ $? -eq 0 ]] && passed=$(($passed + 1))
#test21
runTestCase.sh wsdls/Calculator.wsdl c++
[[ $? -eq 0 ]] && passed=$(($passed + 1))

#runTestCase.sh wsdls/SimpleTypeArray.wsdl c++
#[[ $? -eq 0 ]] && passed=$(($passed + 1))
#runTestCase.sh wsdls/SimpleTypeInnerUnbounded.wsdl c++
#[[ $? -eq 0 ]] && passed=$(($passed + 1))
#runTestCase.sh wsdls/SimpleTypeInnerUnboundedInOutput.wsdl c++
#[[ $? -eq 0 ]] && passed=$(($passed + 1))
# runTestCase.sh wsdls/SOAPHeaderStockService.wsdl c++
#[[ $? -eq 0 ]] && passed=$(($passed + 1))
# runTestCase.sh wsdls/TradeServices.wsdl c++
#[[ $? -eq 0 ]] && passed=$(($passed + 1))

echo -n "${passed}/${num_tests} tests passed."
[[ $passed -eq $num_tests ]] && echo " PASSED" || echo " FAILED"

exit 0

for file in $(find client -name "*.c" -o -name "*.cpp")
do
 runTestCase.sh $(echo wsdls/$(basename $file) | sed "s/Client\./.wsdl /" | sed "s/pp/++/")
done
