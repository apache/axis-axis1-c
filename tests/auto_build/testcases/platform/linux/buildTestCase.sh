#!/bin/sh
#
# Build the testcase
#
#   arg 1 : WSDL file
#   arg 2 : language (c/c++)

#Build the wsdl2ws tool from the source
ant -buildfile ${AXISCPP_HOME}/src/wsdl/build.xml
#javac -classpath $AXIS_JARS -d temp ./org/apache/axis/wsdl/wsdl2ws/*.java
#jar cmf mainClass $WSDL2WS_HOME/wsdl2ws.jar ./org
#javac -d temp -sourcepath /home/damitha/projects/cvshead/src/wsdl/org/apache/axis/wsdl/wsdl2ws/*.java
TARGET=$(echo $OUTPUT_DIR/$(basename $1 .wsdl).$2 | tr '+' 'p')
CLIENT=$(echo testcases/client/$2/$(basename $1 .wsdl)Client.$2 | tr '+' 'p')
#WSDL2Ws.sh -sclient -l$2 -o$TARGET $1

java -cp ${WSDL2WS_HOME}/wsdl2ws.jar:${AXIS_JARS} org.apache.axis.wsdl.wsdl2ws.WSDL2Ws -sclient -l$2 -o$TARGET $1

if [ $? -eq 0 ]
then
  # Added by Andrew Perry
  cp testcases/client/cpp/MySignal.* $TARGET
  # End Add

  cp $AXISCPP_TEST_BIN/configure.ac $AXISCPP_TEST_BIN/autogen.sh $TARGET
  cp $CLIENT $TARGET
  cd $TARGET
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
  echo "WSDL2Ws.sh -sclient -l$2 -o$TARGET $1 failed"
  exit 1
fi

exit 0

