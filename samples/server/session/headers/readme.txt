-This folder contains the source needed to build the Axis java service needed to run the soap header based session client

-compile this java source file and deploy it in Axis java (visit http://ws.apache.org/axis/java/index.html for further 
details)

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