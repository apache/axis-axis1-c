/**
 * TimeBean.java
 *
 * This file was auto-generated from WSDL
 * by the Apache Axis 1.2alpha Feb 10, 2004 (12:04:50 GMT+06:00) WSDL2Java emitter.
 */

package org.objectweb.jonas.jtests.beans.time;

public interface TimeBean extends java.rmi.Remote {
    public java.util.Calendar getDate() throws java.rmi.RemoteException;
    public long getDateAsLong() throws java.rmi.RemoteException;
}
