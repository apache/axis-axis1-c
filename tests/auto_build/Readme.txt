##############################################################################

This folder contains auto build script for Axis C++ and basic regression test 
cases for the C/C++ Service/Client Web Services Stack. For each wsdl service is 
created and built and installed into the server.  Remeber to put your correct 
port type implementation class in the appropriate place described in the 
documentation.

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

  Run all the test cases present in the service/client folders for the specified
  language, default c++. The test will only be successfull if there is a matching
  service/client source files and wsdl. 
  Note that in this case only the services and clients are built. Axis C++ is not 
  built in this case. It is assumed that $AXISCPP_HOME/tests/auto_build/cvsautobuild 
  is downloaded and built and installed by a previous run of autoBuildCVS.sh script.

runTest.[sh|bat] wsdls\<wsdl> [lang]

  Run the client test for the specified WSDL file and the specified language,
  default c++. If there is not a matching service/client source file for the WSDL file
  then build may fail.
  Note that in this case only the service and client are built. Axis C++ is not
  built in this case. It is assumed that $AXISCPP_HOME/tests/auto_build/cvsautobuild
  is downloaded and built and installed by a previous run of autoBuildCVS.sh script.


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

4. Give your APACHE2_HOST, APACHE_HOST, APACHE2_PORT and APACHE_PORT  in
   testcases/platform/linux/apache_ports.config file. 

   If you run autoBuildCVS.sh script then all test services are assumed 
   to be run on the server/port specified on apache_ports.config file.

   If you just run tests by giving runAllTests.sh or runTest.sh
   you can give the server name and port of a remote machine
   which run your service in generated test.config.

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
