1. Generate stub.
Execute:
java -classpath $AXISCPP_HOME/build/lib/wsdl2ws.jar:$CLASSPATH org.apache.axis.wsdl.wsdl2ws.WSDL2Ws -o./gen_src -lc++ -sclient [wsdlFileName]

This will generate C++ client stub class and other utility classes and place in a sub folser named gen_src.

2. Write the client logic.
Write the client logic. See Client.cpp for an example.
You need to use the client stub class. 
How to locate the stub class from the generetd source? 
    The WSDL2Ws tool uses the name of the 'wsdl:binding' for its generated stub class name.
    You can look in the WSDL file to get to know the binding name.
    Alternatively, you can look for the class that is derived from the 'Stub' class in the generated source.
    
For more information on the operations supported by the stub please have a look at the API documentation of the 'Stub' class.

3. Build the source