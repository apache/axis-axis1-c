#!/bin/sh

java -classpath $AXISCPP_HOME/lib/axis/wsdl2ws.jar:$CLASSPATH org.apache.axis.wsdl.wsdl2ws.WSDL2Ws -ogen_src -lc++ -sclient inquire_v2.wsdl

g++ Client.cpp gen_src/*.cpp -Igen_src -I$AXISCPP_HOME/include -L$AXISCPP_DEPLOY/lib -ldl -laxiscpp_client -oclient

