/**
 * InvalidIsbnException.java
 *
 * This file was auto-generated from WSDL
 * by the Apache Axis 1.2alpha Feb 10, 2004 (12:04:50 GMT+06:00) WSDL2Java emitter.
 */

package com.jwsbook.jaxrpc;

public class InvalidIsbnException extends org.apache.axis.AxisFault {
    public java.lang.String message;
    public java.lang.String getMessage() {
        return this.message;
    }

    public InvalidIsbnException() {
    }

      public InvalidIsbnException(java.lang.String message) {
        this.message = message;
    }

    /**
     * Writes the exception data to the faultDetails
     */
    public void writeDetails(javax.xml.namespace.QName qname, org.apache.axis.encoding.SerializationContext context) throws java.io.IOException {
        context.serialize(qname, null, message);
    }
}
