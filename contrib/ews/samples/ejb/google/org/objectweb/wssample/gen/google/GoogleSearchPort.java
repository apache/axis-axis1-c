/**
 * GoogleSearchPort.java
 *
 * This file was auto-generated from WSDL
 * by the Apache Axis 1.2alpha Feb 10, 2004 (12:04:50 GMT+06:00) WSDL2Java emitter.
 */

package org.objectweb.wssample.gen.google;

public interface GoogleSearchPort extends java.rmi.Remote {
    public byte[] doGetCachedPage(java.lang.String key, java.lang.String url) throws java.rmi.RemoteException;
    public java.lang.String doSpellingSuggestion(java.lang.String key, java.lang.String phrase) throws java.rmi.RemoteException;
    public org.objectweb.wssample.gen.google.MyGoogleSearchResult doGoogleSearch(java.lang.String key, java.lang.String q, int start, int maxResults, boolean filter, java.lang.String restrict, boolean safeSearch, java.lang.String lr, java.lang.String ie, java.lang.String oe) throws java.rmi.RemoteException;
}
