This folder contains;
1. The source to the client side SOAP header based handler
2. The source to the client application that uses a "session scoped" service, "Counter" to be hosted in Axis java.
3. The WSDL to the Counter service that can be used to generate both the java server side and the C++ client side.
4. The client.wsdd needed to configure the client for the session handler



WIN 32

-Use the vc workspace \c\vc\samples\client\session\Headers\Headers.dsw to compile the client side handler for this 
sample

-Run the command java org.apache.axis.wsdl.wsdl2ws.WSDL2Ws ../Counter.wsdl -o./gen_src -lc++ -sclient 
from within c\samples\client\session\headers\sessionclient to generate the client stubs

-Compile the client application using the vc workspace at
\c\vc\samples\client\session\Headers\Headers.dsw




Linux

-compile the sessionhandler using the sources in c\samples\client\session\headers\sessionhandler.
 To do that you can use the build.sh file in there.

-Run the command java org.apache.axis.wsdl.wsdl2ws.WSDL2Ws ../Counter.wsdl -o./gen_src -lc++ -sclient 
from within c\samples\client\session\headers\sessionclient to generate the client stubs

-Compile the client application using  the following command from within c\samples\client\session\headers\sessionclient

g++ CounterClient.cpp gen_src/*.cpp -Igen_src
 -I$AXISCPP_HOME/include -L$AXISCPP_DEPLOY/lib -ldl
 -laxiscpp_client -oclient



COMMON


-Host the service in Axis java (Check c/samples/server/session/headers/readme.txt on how to do this).

-Configure the client to use the provided client.wsdd from axiscpp.conf (make appropriate changes if necessary 
in the client.wsdd to the absolute path of the hanlder )

-Run the tcpMonitor and configure it to check the conversation between the client and server

-Run the client in the following fashion
CounterClient count 1 http://localhost:8080/axis/services/CounterService

inspect the SOAP messages in tcpMonitor to see the values returned by the server incremented by 1 each 
time (as done throught the client). Counting starts at the value 97, which is set at the server side web service.
