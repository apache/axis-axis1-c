This sample shows how you can use HTTP Cookie based sessions with Axis C++ clients.
As of now, Cookie based session handling is a 'client side only' feature in Axis C++. 
Hence, you will have to use Axis Java server side to run this sample.
It is expected that Axis C++ would support Cookey based sessions on server side in future releases.

1. Generate the Axis Java code for the WSDL file:
java org.apache.axis.wsdl.WSDL2Java -S true -d Session -Nurn:Total axisj Total.wsdl

2. The implementation logic for Java server side is already written for you. 
Copy that to Impl file
cp axisj/TotalSoapBindingImpl.java.bak axisj/TotalSoapBindingImpl.java

Also if you need to compare C++ client's behavior to that if Java client, a Java client
implementation is also provided in axisj/Client.java

3. Compile the generated Java code
javac axisj/*.java

4. It is a known fact that Axis C++ cannot handle href/multiref. By default, Axis Java 
uses href/multiref. So before you run this sample, you have to disable the use of
href/multiref by Axis Java server by editing server-config.wsdd file in 
$TOMCAT_HOME/webapps/axis/WEB-INF. In that file set the sendMultiRefs setting to false.
<parameter name="sendMultiRefs" value="false"/>

Alternatively you can run Axis Java's SimpleAxisServer with href/multiref disabled.
There is a server-config.wsdd file with href/multiref disabled in this sample's folder,
so when you run SimpleAxisServer from this folder href/multiref would be disabled.
java org.apache.axis.transport.http.SimpleAxisServer -p 9090 &

5. Now deploy the Axis Java service.
java org.apache.axis.client.AdminClient -hlocalhost -p9090 axisj/deploy.wsdd

6. We are done with Java stuff now. Let's generate C++ client side code for the WSDL and
place the generated code in gen_src sub folder.
java -classpath $AXISCPP_HOME/lib/axis/wsdl2ws.jar:$CLASSPATH org.apache.axis.wsdl.wsdl2ws.WSDL2Ws -ogen_src -lc++ -sclient Test.wsdl

7. You need to write the client code. It is already done for you and the code is in Client.cpp.
The only difference when maintaining session with the service from a C++ client, compared to 
clients that does not maintain session, is to call setMaintainSession() on top of the stub object.
If you say:
    stubObject.setMaintainSession(true);
session maintenance would be enabled. To disable session maintanace use:
    stubObject.setMaintainSession(false);

8. Compile the generated code and client code.
g++ Client.cpp gen_src/*.cpp -Igen_src -I$AXISCPP_HOME/include -L$AXISCPP_DEPLOY/lib -ldl -laxiscpp_client -oclient

9. Run the client.
./client

10. If you want to verify that the Java client does the same, run:
java axisj.Client

There are couple of Linux shell scripts to help you run this sample on Linux.
Just run:
./test.sh

- Samisa...