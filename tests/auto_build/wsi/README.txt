#
# WS-I test tool automation (See http://ws-i.org)
#
# The purpose of the scripts in this directory is to run the standard Axis C++
# tests through the WS-I test monitor and WS-I conformance analyzer to check that
# the SOAP messages being created by the Axis C++ product adhere to the WS-I
# standards.
#
# This is designed to work with the WS-I 1.1 Basic Profile only and will only
# check the request and response messages on the wire.
#
# The analyzer config file is BasicProfile_1.1_TAD.xml
#
##################################################################################

To run the test type the following

ant -Dwsi.home=xxx -Ddir.xmlParser=xxx -Dtest.host=xxx -Dtest.port=xxx
[-Ddir.release=xxx -Dtest.list=xxx]

Options:
--------

-Dwsi.home=/opt/wsi-test-tools
	This is the location of the WS-I test tools package.
	This is a mandatory property.

-Ddir.xmlParser=$XERCES_HOME/lib
	This is the location of the XML parser external package libraries
	This is a mandatory property.

-Dtest.host=lion
	This is the name of the server that the services are running on
	This is a mandatory property.

-Dtest.port=9080
	This is the port that the services are listening on
	This is a mandatory property.

-Ddir.release
	This will need to be specified if the packaging step has been performed.
	If only the Ant build phase has been done then this need not be specified.
	Default: as specified in Axis C++ default platform properties file.

-Dtest.list=/home/andyp/cwssBuild/src/ws-axis/c/tests/auto_build/wsi/test.list
	This is the list of the tests to run through the WS-I test tool.
	Default: all tests.

Output:
-------

The test output will be in the standard location ${dir.obj}/test/generated.
The WS-I output for the tests will be written to ${dir.obj}/test/wsi/reports

To view the WS-I reports please refer to the WS-I documentation.


