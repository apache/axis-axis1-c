#!/bin/sh
#
# Build the testcase
#
#   arg 1 : WSDL file
#   arg 2 : language (c/c++)

#Build the wsdl2ws tool from the source
ant -lib ${AXIS_JARS_HOME} -buildfile ${AXISCPP_HOME}/src/wsdl/build.xml
#Server sample build and install
TARGET_SERVER=$(echo $OUTPUT_DIR/$(basename $1 .wsdl).$2 | tr '+' 'p')_server
SERVICE_FILE_NAME=$(echo | grep portType $1|grep -o '".*"'|sed "s/\"//g").$2
echo ${SERVICE_FILE_NAME}
SERVER=$(echo testcases/server/$2/${SERVICE_FILE_NAME})
LIB_SERVICE_NAME=$(echo | grep portType $1|grep -o '".*"'|sed "s/\"//g")

java -cp ${WSDL2WS_HOME}/wsdl2ws.jar:${AXIS_JARS} org.apache.axis.wsdl.wsdl2ws.WSDL2Ws -sserver -l$2 -o$TARGET_SERVER $1

if [ $? -eq 0 ]
then
  cp $AXISCPP_TEST_BIN/configure.ac $AXISCPP_TEST_BIN/autogen.sh $TARGET_SERVER
  cp $SERVER $TARGET_SERVER
  cd $TARGET_SERVER
  ALLSOURCES=$(ls $(echo "*.$2" | tr '+' 'p') | tr -d "^M")
  printf "libservice_la_SOURCES = " > Makefile.am_temp
  echo "$ALLSOURCES" | awk '{printf" %s", $1}' >> Makefile.am_temp
  echo " " >> Makefile.am_temp
  cat $AXISCPP_TEST_BIN/Makefile.am_server >> Makefile.am_temp
  sed "s/service/${LIB_SERVICE_NAME}/g" Makefile.am_temp > Makefile.am
  ./autogen.sh
  ./configure --prefix=${AXISCPP_DEPLOY}
  make install
  ${APACHE2_HOME}/bin/apachectl restart
  ${APACHE_HOME}/bin/apachectl restart
else
  echo "WSDL2Ws.sh -sserver -l$2 -o$TARGET_SERVER $1 failed"
  exit 1
fi

#Client sample build
cd "${OUTPUT_DIR}/../.."
TARGET_CLIENT=$(echo $OUTPUT_DIR/$(basename $1 .wsdl).$2 | tr '+' 'p')_client
CLIENT=$(echo testcases/client/$2/$(basename $1 .wsdl)Client.$2 | tr '+' 'p')

java -cp ${WSDL2WS_HOME}/wsdl2ws.jar:${AXIS_JARS} org.apache.axis.wsdl.wsdl2ws.WSDL2Ws -sclient -l$2 -o$TARGET_CLIENT $1

if [ $? -eq 0 ]
then

  cp $AXISCPP_TEST_BIN/configure.ac $AXISCPP_TEST_BIN/autogen.sh $TARGET_CLIENT
  cp $CLIENT $TARGET_CLIENT
  cd $TARGET_CLIENT
  ALLSOURCES=$(ls $(echo "*.$2" | tr '+' 'p') | tr -d "
")
  printf "client_SOURCES = " > Makefile.am
  echo "$ALLSOURCES" | awk '{printf" %s", $1}' >> Makefile.am
  echo " " >> Makefile.am
  cat $AXISCPP_TEST_BIN/Makefile.am >> Makefile.am
  ./autogen.sh
  ./configure
  make
else
  echo "WSDL2Ws.sh -sclient -l$2 -o$TARGET_CLIENT $1 failed"
  exit 1
fi
exit 0

