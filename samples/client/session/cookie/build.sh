#!/bin/sh

java org.apache.axis.wsdl.WSDL2Java -S true -d Session -Nurn:Total axisj Total.wsdl

cp -f axisj/TotalSoapBindingImpl.java.bak axisj/TotalSoapBindingImpl.java

javac axisj/*.java

#Cannot test with Simple server as it uses href/multiref
#Configure tomcat based Axis server not to use href/multiref
#java org.apache.axis.transport.http.SimpleAxisServer -p 9090 &


java -classpath $AXISCPP_HOME/lib/axis/wsdl2ws.jar:$CLASSPATH org.apache.axis.wsdl.wsdl2ws.WSDL2Ws -ogen_src -lc++ -sclient Total.wsdl

g++ Client.cpp gen_src/*.cpp -Igen_src -I$AXISCPP_HOME/include -L$AXISCPP_DEPLOY/lib -ldl -laxiscpp_client -oclient

