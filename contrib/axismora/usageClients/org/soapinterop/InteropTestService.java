/**
 * InteropTestService.java
 *
 * This file was auto-generated from WSDL
 * by the Apache Axis WSDL2Java emitter.
 */

package org.soapinterop;

public interface InteropTestService extends javax.xml.rpc.Service {
    public java.lang.String getechoAddress();

    public org.soapinterop.InteropTestPortType getecho() throws javax.xml.rpc.ServiceException;

    public org.soapinterop.InteropTestPortType getecho(java.net.URL portAddress) throws javax.xml.rpc.ServiceException;
}
