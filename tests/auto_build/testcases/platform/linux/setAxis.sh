#!/bin/sh
#
if [[ -z "$AXISCPP_HOME" ]]
then
	echo "Environment variable AXISCPP_HOME is not set."
	echo "Please set and re-try."
	return 1
fi

# Work out where the script is called from and use that as the TEST_HOME
here=$PWD
script_location=$(dirname $0)
cd $script_location
TEST_HOME=$PWD
#
# These variables can be overridden by setting the variables in the
# calling shell. It'll use the variable if set otherwise it'll use
# the default value
set -x
AXISTEST_HOME=${AXISTEST_HOME:-$TEST_HOME}
AXISCPP_HOME=${AXISCPP_HOME:-/home/damitha/projects/cvshead/tests/auto_build/cvsautobuild}
AXISCPP_DEPLOY=${AXISCPP_DEPLOY:-/usr/local/axicpp_deploy}
WSDLSRC_HOME="${AXISCPP_HOME}/src/wsdl"
WSDL2WS_HOME=${WSDL2WS_HOME:-/home/damitha/projects/cvshead/tests/auto_build/cvsautobuild/lib/axis}   # location of WSDL2Ws.jar
AXIS_JARS_HOME=${AXIS_JARS_HOME:-/home/damitha/axisjava}  # location of axis.jar and others
APACHE2_HOME=${APACHE2_HOME:-/usr/local/apache2}
APACHE_HOME=${APACHE_HOME:-/usr/local/apache}
set +x
#
# These variables are based upon the variables above, but rely on a standard
# directory structure
AXISCPP_HOME_BIN=$AXISCPP_HOME/lib      # location of the axiscpp libraries
AXISCPP_HOME_INCL=$AXISCPP_HOME/include # location of the include files


# where the test framework scripts for this platform live. Linux means UNIX
AXISCPP_TEST_BIN=$AXISTEST_HOME/testcases/platform/linux
OUTPUT_DIR=$AXISTEST_HOME/testcases/build         # where the tests are built

# if this is set and the file exists allows for the endpoint host and port
# of the web service in the WSDL to be altered to use the values in the file
# This is useful for tcpmon and WS-I
SERVICE_CONFIG=$AXISCPP_TEST_BIN/test.config

# List of all the pre-req jar files needed for WSDL2Ws. Used to set CLASSPATH
AXIS_JARS="$AXIS_JARS_HOME/axis.jar:$AXIS_JARS_HOME/commons-discovery.jar:$AXIS_JARS_HOME/commons-logging.jar:$AXIS_JARS_HOME/jaxrpc.jar:$AXIS_JARS_HOME/saaj.jar:$AXIS_JARS_HOME/wsdl4j.jar:$AXIS_JARS_HOME/xml-apis.jar"

JAVA_HOME=${JAVA_HOME:-/usr/local/java}        # Where java is installed
ANT_HOME=${ANT_HOME:-/usr/local/ant}
CLASSPATH="$WSDL2WS_HOME/wsdl2ws.jar:$AXIS_JARS"   # set the classpath for WSDL2Ws

# set the PATH to include the test framework scripts and guraentee java
# is in the PATH too
PATH="$ANT_HOME/bin:$JAVA_HOME/bin:$AXISCPP_TEST_BIN:$PATH"

LD_LIBRARY_PATH=$AXISCPP_DEPLOY/lib:$XERCESC_HOME/lib:$EXPAT_HOME/lib:$LD_LIBRARY_PATH

# export variables that will be used by other programs
#export PATH JAVA_HOME CLASSPATH LD_LIBRARY_PATH

# export variables that will be used by other scripts
export TEST_HOME APACHE2_HOME APACHE_HOME AXISCPP_HOME AXISCPP_DEPLOY AXISCPP_HOME_BIN AXISCPP_HOME_INCL AXISCPP_TEST_BIN OUTPUT_DIR SERVICE_CONFIG WSDL2WS_HOME AXIS_JARS_HOME AXIS_JARS PATH JAVA_HOME CLASSPATH LD_LIBRARY_PATH WSDLSRC_HOME


# The End
##########

