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
SERVER=$(echo testcases/server/$2/${SERVICE_FILE_NAME})
LIB_SERVICE_NAME=$(echo | grep portType $1|grep -o '".*"'|sed "s/\"//g")
STYLE=$(echo | grep style $1 | grep -o 'style=".*"' | grep -o '".*"' | sed "s/\"//g")
#sed -e "s/service_name/${LIB_SERVICE_NAME}/g" -e "s/service_lib_name/${LIB_SERVICE_NAME}/g" -e "s/STYLE/${STYLE}/g" service_temp.wsdd > service.wsdd
java -cp ${WSDL2WS_HOME}/wsdl2ws.jar:${AXIS_JARS} org.apache.axis.wsdl.wsdl2ws.WSDL2Ws -sserver -l$2 -o$TARGET_SERVER $1
sed -e "s/<?xml.*>//g" -e "s/<\/deployment>//g" -e "s/<deployment.*>//g" $TARGET_SERVER/deploy.wsdd > deploy.wsdd
if ! test -f server.wsdd_temp2; then
cat server.wsdd_temp > server.wsdd_temp2
fi
grep "${LIB_SERVICE_NAME}" server.wsdd_temp2
if [ $? -eq 0 ]
then
echo "Service already listed in the server.wsdd"
else
cat deploy.wsdd >> server.wsdd_temp2
fi
sed -e "s/<\/deployment>//g" server.wsdd_temp2 > server.wsdd
echo "</deployment>" >> server.wsdd

if [ $? -eq 0 ]
then
  cp $SERVER $TARGET_SERVER
  cd $TARGET_SERVER
  g++ -shared -I$AXISCPP_HOME/include -olibservice.so *.cpp
  cp -f libservice.so $AXISCPP_DEPLOY/lib/lib${LIB_SERVICE_NAME}.so
  cp -f server.wsdd $AXISCPP_DEPLOY/etc/
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

  cp $CLIENT $TARGET_CLIENT
  cd $TARGET_CLIENT
  g++ -I$AXISCPP_HOME/include -L$AXISCPP_DEPLOY/lib -laxiscpp_client -ldl -oclient *.cpp
else
  echo "WSDL2Ws.sh -sclient -l$2 -o$TARGET_CLIENT $1 failed"
  exit 1
fi
exit 0

