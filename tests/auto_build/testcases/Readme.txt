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


