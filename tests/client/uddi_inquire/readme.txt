To get this sample working, follow the following steps.

1. Generate the source code for WSDL file
java -classpath $AXISCPP_HOME/lib/axis/wsdl2ws.jar:$CLASSPATH org.apache.axis.wsdl.wsdl2ws.WSDL2Ws -sclient -lc++ -ogen_src inquire_v2.wsdl

2. Edit the gen_src/Makefile.am and add ../Client.cpp sources and @LINKCLIENTLIB@ macro

3. configure; make; make install

4. Run the progrem
./gen_src/InquireService <service url>

I could get this sample working with
http://www-3.ibm.com/services/uddi/testregistry/inquiryapi URL.

Samisa...
