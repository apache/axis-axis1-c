/**
 * HeavyTestService.java
 *
 * This file was auto-generated from WSDL
 * by the Apache Axis WSDL2Java emitter.
 */

package heavytest.performence;

public interface HeavyTestService extends javax.xml.rpc.Service {
    public java.lang.String getHeavyAddress();

    public heavytest.performence.HeavyTest getHeavy() throws javax.xml.rpc.ServiceException;

    public heavytest.performence.HeavyTest getHeavy(java.net.URL portAddress) throws javax.xml.rpc.ServiceException;
}
