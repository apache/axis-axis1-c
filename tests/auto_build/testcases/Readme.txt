##############################################################################

This folder contains basic regression test cases for the C/C++
Client Web Services Stack (CWSS).

##############################################################################

DIRECTORY STRUCTURE
-------------------

platform/
 Contains the scripts for test framework.

wsdls/
 Contains the WSDL for the test cases.

client/
 Contains the C and C++ invocation clients.
 NOTES: Each client must have the same basename as the WSDL file
        plus Client.
        Example: SimpleTypeArray.wsdl -> SimpleTypeArrayClient.c[pp] 

output/
 Contains the output of the client invocation expected result.

server/
 Contains the server implementation of the binding (WAS 5.0.2). And
 the ear file. 

##############################################################################

ENVIRONMENT VARIABLES
---------------------

The easiest way of configuring the test framework is to set some environment
variables.

------------------------------------------------------------------------------
Variable          | Description
------------------------------------------------------------------------------
AXISCPP_HOME      | Axis C++ build directory
------------------------------------------------------------------------------
AXISTEST_HOME     | This specifies the location of the testcase framework with
                  | the directory structure specified above.
------------------------------------------------------------------------------
JAVA_HOME         | Path to the java installation
------------------------------------------------------------------------------
ANT_HOME          | Path to the ant installation
##############################################################################

SCRIPTS
-------

runAllTests.[sh|bat] [lang]

  Run all the test cases present in the client folders for the specified
  language, default c++. The test will only be run if there is a matching
  client source file and wsdl

runTest.[sh|bat] wsdls\<wsdl> [lang]

  Run the client test for the specified WSDL file and the specified language,
  default c++. If there is not a matching client source file for the WSDL file
  then nothing is done.


##############################################################################

Example of using the test framework
-----------------------------------

Linux
-----

Snippet from a script
-----------------------
  runTest.sh wsdls/MathOps.wsdl c++
-----------------------

  Should result in:
   "Regression test on wsdls/MathOps.wsdl for c++ success"


When you want to add a new test please be aware of the following simple steps.

1. Write the cpp file containing your main method of access and put
   it in $AXISCPP_HOME/tests/auto-build/testcases/client/cpp
    NOTES: Each client cpp file must have the same basename as the 
    WSDL  file plus Client.
    Example: SimpleTypeArray.wsdl -> SimpleTypeArrayClient.c[pp]

2. Put the wsdl you hope to test in
   testcases/wsdls

3. Give the server and port running the webservice in 
   testcases/platform/linux/test.config file

4. Add the following entry into the testcases/runAllTests.sh

   runTestCase.sh wsdls/<your-wsdl-name.wsdl c++
   [[ $? -eq 0 ]] && passed=$(($passed + 1))

5. cd to testcases and run runAllTests.sh
   You will have a new folder creaed in testcases/build folder with the 
   same name as the client cpp file name.
   First time you should get run FAIL message. That's because you still
   does not have a .out file indicating your expected result. We will
   create this in the next step

7. in testcases/build/<automaticall creaed your client folder> you will
   see a file named <Your client file name>.cpp.out
   Copy this file into testcases/output

8. run runAllTests.sh again. This time you should get your test passed
   with SUCCESS.
   This time the build/<Your client file name>.cpp.out matchs correctly
   with the pre created output in testcases/output
