##############################################################################

This folder contains auto build script for Axis C++ and basic regression test 
cases for the C/C++ Service/Client Web Services Stack. For each wsdl service is 
created and built and installed into the server.  Remeber to put your correct 
port type implementation class in the appropriate place described in the 
documentation. Normally you don't put this implementation file if your service 
is running in a remote server.

##############################################################################

DIRECTORY STRUCTURE
-------------------

testcases/platform/
 Contains the scripts for test framework.

testcases/wsdls/
 Contains the WSDL for the test cases.

testcases/server/
 Contains the C and C++ service classes.
 NOTES:
        Implementation class name of the wsdl PortType is taken
        from the port name of the wsdl file suffixing with .cpp/.c

testcases/client/
 Contains the C and C++ invocation clients.
 NOTES: Each client must have the same basename as the WSDL file
        plus Client.
        Example: SimpleTypeArray.wsdl -> SimpleTypeArrayClient.c[pp] 

testcases/output/
 Contains the output of the client invocation expected result.

##############################################################################

ENVIRONMENT VARIABLES
---------------------

The easiest way of configuring the test framework is to set some environment
variables.

------------------------------------------------------------------------------
Variable          | Description
------------------------------------------------------------------------------
AXISCPP_HOME      | Axis C++ build directory
-----------------------------------------------------------------------------
AXISCPP_DEPLOY    | Axis C++ deployed here. Server and Client libraries
                  | are taken from here
------------------------------------------------------------------------------
AXISTEST_HOME     | This specifies the location of the testcase framework with
                  | the directory structure specified above. Path is
                  | upto(including) testcases folder
------------------------------------------------------------------------------
JAVA_HOME         | Path to the java installation
------------------------------------------------------------------------------
ANT_HOME          | Path to the ant installation
------------------------------------------------------------------------------
AXIS_JARS_HOME    | Path to the axis jars
##############################################################################

SCRIPTS
-------
autoBuildCVS.sh

 Checkout Axis C++ from cvs and build it and run all the test cases.

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

When you want to add a new test please be aware of the following simple steps.

1. Put the wsdl you hope to test in
   testcases/wsdls

2. Create the c/cpp file which has the name of the port type name of the wsdl
   and implement your service

3. Write the c/cpp file containing your main method of access and put
   it in $AXISCPP_HOME/tests/auto-build/testcases/client/cpp
    NOTES: Each client cpp file must have the same basename as the 
    WSDL  file plus Client.
    Example: SimpleTypeArray.wsdl -> SimpleTypeArrayClient.c[pp]

4. Add the server and port running the webservice in 
   testcases/platform/linux/test.config file. The format is
   <wsdl file name (without .wsdl part)>:host=<your host>
   <wsdl file name (without .wsdl part)>:port=<your port>
   Also give your APACHE2_PORT and APACHE_PORT in
   testcases/platform/linux/apache_ports.config file. Giving
   these information is very important as tests are first run
   using apache2 and then using apache. port in test.config
   is replaced with whatever on apache_ports.config file whenever
   the tests are run. Anyway you must initially give the port
   in test.config file as a initialization kind of value.

5. cd to auto_build and edit the build.sh file
   according to your configure requirments.
   Run autoBuildCVS.sh
   This will first checkout from cvs and then build the source.
   Then generate samples from each wsdl.
   You will have two folders created in testcases/build folder for service
   and client. Each have the wsdl filename suffixed with .cpp_server and 
   .cpp_client respectively.
   First time you should get run FAIL message. That's because you still
   does not have a .out file indicating your expected result. We will
   create this in the next step

6. in testcases/build/<automaticall creaed your client folder> you will
   see a file named <Your client file name>.cpp.out
   Copy this file into testcases/output

7. Next time you should get your test passed
   with SUCCESS.
   This time the build/<Your client file name>.cpp.out matchs correctly
   with the pre created output in testcases/output
