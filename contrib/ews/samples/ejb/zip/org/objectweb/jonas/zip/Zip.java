/**
 * Zip.java
 *
 * This file was auto-generated from WSDL
 * by the Apache Axis 1.2alpha Feb 10, 2004 (12:04:50 GMT+06:00) WSDL2Java emitter.
 */

package org.objectweb.jonas.zip;

public interface Zip extends java.rmi.Remote {
    public java.lang.String getDepartmentForCode(java.lang.String depCode) throws java.rmi.RemoteException;
    public java.lang.String getDepartmentAdminCenterForCode(java.lang.String depCode) throws java.rmi.RemoteException;
    public java.lang.String getDepartmentList(java.lang.String separator) throws java.rmi.RemoteException;
    public java.lang.String getTownForZip(java.lang.String zipCode, java.lang.String separator) throws java.rmi.RemoteException;
    public java.lang.String getZipForTown(java.lang.String town, java.lang.String separator, boolean exactMatch) throws java.rmi.RemoteException;
    public java.lang.String getTownsForSoundex(java.lang.String searchFor, java.lang.String separator) throws java.rmi.RemoteException;
    public void reportErrorInFile(java.lang.String yourName, java.lang.String yourMail, java.lang.String yourMessage) throws java.rmi.RemoteException;
}
