-This folder contains the sources needed to build the Axis java service needed to run the soap header based session client

-compile these java source files and deploy them in Axis java (visit http://ws.apache.org/axis/java/index.html on how to 
achieve this)

-The following should be put in the server-config.wsdd of Axis java for this service to behave as having session scope.

<service name="CounterService" provider="java:RPC">
<parameter name="scope" value="session"/>
<requestFlow> 
<handler type="session"/> 
</requestFlow> 
<responseFlow> 
<handler type="session"/> 
</responseFlow> 
  <parameter name="allowedMethods" value="*"/>
  <parameter name="className" value="counters.CounterSoapBindingImpl"/>
  <namespace>http://xml.apache.org/axis/wsdd/</namespace>
</service>

- since Axis c++ doesn't support multiref yet, Axis java multiref should be disabled by putting the element 
<parameter name="sendMultiRefs" value="false"/> 
under <globalConfiguration>