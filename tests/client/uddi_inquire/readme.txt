To get this sample working, follow the following steps.

1. Generate the source code for WSDL file
java -classpath $AXISCPP_HOME/lib/axis/wsdl2ws.jar:$CLASSPATH org.apache.axis.wsdl.wsdl2ws.WSDL2Ws -sclient -lc++ -ogen_src inquire_v2.wsdl

2. Compile the code
g++ -ouddi_client -I$AXISCPP_HOME/include/ -I./ -L$AXISCPP_DEPLOY/lib/ Client.cpp gen_src/*.cpp -laxiscpp_client -ldl

3. Run the progrem
./uddi_client <service url>

I could get this sample working with
http://www-3.ibm.com/services/uddi/testregistry/inquiryapi URL.

Samisa...
