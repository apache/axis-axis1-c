/**
 * InvalidIsbnFault.java
 *
 * This file was auto-generated from WSDL
 * by the Apache Axis 1.2dev Nov 22, 2003 (10:36:07 GMT+06:00) WSDL2Java emitter.
 */

package com.jwsbook.jaxrpc;

public class InvalidIsbnFault extends org.apache.axis.AxisFault {
    public java.lang.String message;
    public java.lang.String getMessage() {
        return this.message;
    }

    public InvalidIsbnFault() {
    }

      public InvalidIsbnFault(java.lang.String message) {
        this.message = message;
    }

    /**
     * Writes the exception data to the faultDetails
     */
    public void writeDetails(javax.xml.namespace.QName qname, org.apache.axis.encoding.SerializationContext context) throws java.io.IOException {
        context.serialize(qname, null, message);
    }
}
