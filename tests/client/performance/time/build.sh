#!/bin/sh
java -classpath $AXISCPP_HOME/lib/axis/wsdl2ws.jar:$CLASSPATH org.apache.axis.wsdl.wsdl2ws.WSDL2Ws -sclient -lc++ -ogen_src $AXISCPP_DEPLOY/wsdls/base.wsdl
g++ -I$AXISCPP_HOME/include -L$AXISCPP_DEPLOY/lib -laxiscpp_client -ldl -otimeTest Client.cpp gen_src/*.cpp

