#!/bin/sh
#
# Build the testcase
#
#   arg 1 : WSDL file
#   arg 2 : language (c/c++)

mkdir -p $OUTPUT_DIR
SERVICE_HOST=$(echo $(basename $1 .wsdl):host=)
SERVICE_PORT=$(echo $(basename $1 .wsdl):port=)
echo $SERVICE_HOST > service_host
echo $SERVICE_PORT > service_port
URI=
# If a config file exists then alter the endpoint to use the config data
if [ -f "$SERVICE_CONFIG" ]
then
  # Extract the soap address from the WSDL so we can alter the endpoint for the tests, i.e.
  # point to a different server and/or port
  URI=$(grep -F soap:address $1 | cut -d\" -f2)
  CONTEXT=$(echo $URI | cut -d\" -f2 | cut -d/ -f4-)
  URI_HOST=$(grep -f "service_host" $SERVICE_CONFIG | cut -d= -f2)
  URI_PORT=$(grep -f "service_port" $SERVICE_CONFIG | cut -d= -f2)
  #URI_HOST=$(grep -E "^host=" $SERVICE_CONFIG | cut -d= -f2)
  #URI_PORT=$(grep -E "^port=" $SERVICE_CONFIG | cut -d= -f2)
  if [ -n "$URI_HOST" -a -n "$URI_PORT" ]
  then
    #echo "WSDL URI = $URI"
    NEW_URI="http://$URI_HOST:$URI_PORT/$CONTEXT"
    URI=$NEW_URI
    #echo "modified = $URI"
  else
    URI=
  fi
fi
TARGET=$(echo $(basename $1 .wsdl).$2 | tr '+' 'p')_client
OUTPUT=$(echo $(basename $1 .wsdl).out)

TIME=$(date "+%d/%m/%Y %H:%M:%S")
echo "${TIME}: Running tests in $TARGET"
echo "                     Endpoint <${URI:-default}>"

if [ ! -f output/$OUTPUT ]
then
  OUTPUT=$(echo $(basename $1 .wsdl).$2.out | tr '+' 'p')
fi

rm -rf $OUTPUT_DIR/$TARGET

# Set the exist status. Assume the worst
status=1
# Build the test client, including the generation of the stubs
buildTestCase.sh $* >>$OUTPUT_DIR/buildTestCase.log 2>&1
if [ ! -f $OUTPUT_DIR/$TARGET/client ]
then

  TIME=$(date "+%d/%m/%Y %H:%M:%S")
  echo "${TIME}: Regression test on $TARGET: BUILD FAILED" |tee -a $OUTPUT_DIR/runTestCase.log

else
  TIME=$(date "+%d/%m/%Y %H:%M:%S")
  echo "${TIME}: Regression test on $TARGET: BUILD SUCCESS" |tee -a $OUTPUT_DIR/buildTestCase.log
  export LD_LIBRARY_PATH=$AXISCPP_HOME_BIN:$LIB_XERCES_BIN:$LD_LIBRARY_PATH

  # Pass in the URI if it has been set.
  $OUTPUT_DIR/$TARGET/client $URI > $OUTPUT_DIR/$TARGET/$OUTPUT
  if [ -f $OUTPUT_DIR/$TARGET/$OUTPUT ]
  then
    diff -q testcases/output/$OUTPUT $OUTPUT_DIR/$TARGET 2>/dev/null
    if [ $? -eq 0 ]
    then
      TIME=$(date "+%d/%m/%Y %H:%M:%S")
      echo "${TIME}: Regression test on $TARGET: RUN SUCCESS" |tee -a $OUTPUT_DIR/runTestCase.log
      status=0
    else
      TIME=$(date "+%d/%m/%Y %H:%M:%S")
      echo "${TIME}: Regression test on $TARGET: RUN FAILED" |tee -a $OUTPUT_DIR/runTestCase.log
    fi
  else
    TIME=$(date "+%d/%m/%Y %H:%M:%S")
    echo "${TIME}: Regression test on $TARGET: RUN FAILED" |tee -a $OUTPUT_DIR/runTestCase.log
  fi

fi

exit $status

# The End
##########

