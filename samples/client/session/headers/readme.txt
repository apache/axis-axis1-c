This folder contains;
1. The source to the client side SOAP header based handler
2. The source to the client application that uses a "session scoped" service, "Counter" hosted in Axis java.
3. The WSDL to the Counter service that can be used to generate both the java server side and the C++ client side.
4. The client.wsdd needed to configure the client for the session handler



WIN 32

-Use the vc workspace \c\vc\samples\client\session\Headers\Headers.dsw to compile the client side handler for this 
sample

-Use WSDL2Ws to generated the client side stubs from c\samples\client\session\headers\Counter.wsdl in 
c\samples\client\session\headers\gen_src. Compile the client application using the vc workspace at
\c\vc\samples\client\session\Headers\Headers.dsw




Linux

-........



COMMON


-Host the service in Axis java (Check c/samples/server/session/headers/readme.txt on how to do this).

-Configure the client to use the provided client.wsdd from axiscpp.conf (make appropriate changes if necessary 
to the client.wsdd to make it load the handler )

-Run the tcpMonitor and configure it to check the conversation between the client and server

-Run the client; inspect the SOAP messages in tcpMonitor to see the values returned by the server incremented by 1 each 
time (as done throught the client). Counting starts at the value 97, which is set at the server side web service.