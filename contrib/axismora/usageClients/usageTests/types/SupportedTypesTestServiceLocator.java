/**
 * SupportedTypesTestServiceLocator.java
 *
 * This file was auto-generated from WSDL
 * by the Apache Axis WSDL2Java emitter.
 */

package usageTests.types;

public class SupportedTypesTestServiceLocator extends org.apache.axis.client.Service implements usageTests.types.SupportedTypesTestService {

    // Use to get a proxy class for Heavy
    private final java.lang.String Heavy_address = "http://localhost:8080/axis/services/Heavy";

    public java.lang.String getHeavyAddress() {
        return Heavy_address;
    }

    // The WSDD service name defaults to the port name.
    private java.lang.String HeavyWSDDServiceName = "Heavy";

    public java.lang.String getHeavyWSDDServiceName() {
        return HeavyWSDDServiceName;
    }

    public void setHeavyWSDDServiceName(java.lang.String name) {
        HeavyWSDDServiceName = name;
    }

    public usageTests.types.SupportedTypesTest getHeavy() throws javax.xml.rpc.ServiceException {
       java.net.URL endpoint;
        try {
            endpoint = new java.net.URL(Heavy_address);
        }
        catch (java.net.MalformedURLException e) {
            throw new javax.xml.rpc.ServiceException(e);
        }
        return getHeavy(endpoint);
    }

    public usageTests.types.SupportedTypesTest getHeavy(java.net.URL portAddress) throws javax.xml.rpc.ServiceException {
        try {
            usageTests.types.HeavySoapBindingStub _stub = new usageTests.types.HeavySoapBindingStub(portAddress, this);
            _stub.setPortName(getHeavyWSDDServiceName());
            return _stub;
        }
        catch (org.apache.axis.AxisFault e) {
            return null;
        }
    }

    /**
     * For the given interface, get the stub implementation.
     * If this service has no port for the given interface,
     * then ServiceException is thrown.
     */
    public java.rmi.Remote getPort(Class serviceEndpointInterface) throws javax.xml.rpc.ServiceException {
        try {
            if (usageTests.types.SupportedTypesTest.class.isAssignableFrom(serviceEndpointInterface)) {
                usageTests.types.HeavySoapBindingStub _stub = new usageTests.types.HeavySoapBindingStub(new java.net.URL(Heavy_address), this);
                _stub.setPortName(getHeavyWSDDServiceName());
                return _stub;
            }
        }
        catch (java.lang.Throwable t) {
            throw new javax.xml.rpc.ServiceException(t);
        }
        throw new javax.xml.rpc.ServiceException("There is no stub implementation for the interface:  " + (serviceEndpointInterface == null ? "null" : serviceEndpointInterface.getName()));
    }

    /**
     * For the given interface, get the stub implementation.
     * If this service has no port for the given interface,
     * then ServiceException is thrown.
     */
    public java.rmi.Remote getPort(javax.xml.namespace.QName portName, Class serviceEndpointInterface) throws javax.xml.rpc.ServiceException {
        if (portName == null) {
            return getPort(serviceEndpointInterface);
        }
        String inputPortName = portName.getLocalPart();
        if ("Heavy".equals(inputPortName)) {
            return getHeavy();
        }
        else  {
            java.rmi.Remote _stub = getPort(serviceEndpointInterface);
            ((org.apache.axis.client.Stub) _stub).setPortName(portName);
            return _stub;
        }
    }

    public javax.xml.namespace.QName getServiceName() {
        return new javax.xml.namespace.QName("http://usageTests/types", "SupportedTypesTestService");
    }

    private java.util.HashSet ports = null;

    public java.util.Iterator getPorts() {
        if (ports == null) {
            ports = new java.util.HashSet();
            ports.add(new javax.xml.namespace.QName("Heavy"));
        }
        return ports.iterator();
    }

}
