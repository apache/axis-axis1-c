1. Generate stub.
java -classpath $AXISCPP_HOME/build/lib/wsdl2ws.jar:$CLASSPATH org.apache.axis.wsdl.wsdl2ws.WSDL2Ws -o./gen_src -lc++ -sclient wsdlFile