/**
 * SellerSearch.java
 *
 * This file was auto-generated from WSDL
 * by the Apache Axis WSDL2Java emitter.
 */

package com.bookshop.soap;

public class SellerSearch  implements java.io.Serializable {
    private com.bookshop.soap.SellerSearchDetails[] sellerSearchDetails;

    public SellerSearch() {
    }

    public com.bookshop.soap.SellerSearchDetails[] getSellerSearchDetails() {
        return sellerSearchDetails;
    }

    public void setSellerSearchDetails(com.bookshop.soap.SellerSearchDetails[] sellerSearchDetails) {
        this.sellerSearchDetails = sellerSearchDetails;
    }

    private java.lang.Object __equalsCalc = null;
    public synchronized boolean equals(java.lang.Object obj) {
        if (!(obj instanceof SellerSearch)) return false;
        SellerSearch other = (SellerSearch) obj;
        if (obj == null) return false;
        if (this == obj) return true;
        if (__equalsCalc != null) {
            return (__equalsCalc == obj);
        }
        __equalsCalc = obj;
        boolean _equals;
        _equals = true && 
            ((this.sellerSearchDetails==null && other.getSellerSearchDetails()==null) || 
             (this.sellerSearchDetails!=null &&
              java.util.Arrays.equals(this.sellerSearchDetails, other.getSellerSearchDetails())));
        __equalsCalc = null;
        return _equals;
    }

    private boolean __hashCodeCalc = false;
    public synchronized int hashCode() {
        if (__hashCodeCalc) {
            return 0;
        }
        __hashCodeCalc = true;
        int _hashCode = 1;
        if (getSellerSearchDetails() != null) {
            for (int i=0;
                 i<java.lang.reflect.Array.getLength(getSellerSearchDetails());
                 i++) {
                java.lang.Object obj = java.lang.reflect.Array.get(getSellerSearchDetails(), i);
                if (obj != null &&
                    !obj.getClass().isArray()) {
                    _hashCode += obj.hashCode();
                }
            }
        }
        __hashCodeCalc = false;
        return _hashCode;
    }

    // Type metadata
    private static org.apache.axis.description.TypeDesc typeDesc =
        new org.apache.axis.description.TypeDesc(SellerSearch.class);

    static {
        typeDesc.setXmlType(new javax.xml.namespace.QName("http://soap.bookshop.com", "SellerSearch"));
        org.apache.axis.description.ElementDesc elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("sellerSearchDetails");
        elemField.setXmlName(new javax.xml.namespace.QName("", "SellerSearchDetails"));
        elemField.setXmlType(new javax.xml.namespace.QName("http://soap.bookshop.com", "SellerSearchDetails"));
        typeDesc.addFieldDesc(elemField);
    }

    /**
     * Return type metadata object
     */
    public static org.apache.axis.description.TypeDesc getTypeDesc() {
        return typeDesc;
    }

    /**
     * Get Custom Serializer
     */
    public static org.apache.axis.encoding.Serializer getSerializer(
           java.lang.String mechType, 
           java.lang.Class _javaType,  
           javax.xml.namespace.QName _xmlType) {
        return 
          new  org.apache.axis.encoding.ser.BeanSerializer(
            _javaType, _xmlType, typeDesc);
    }

    /**
     * Get Custom Deserializer
     */
    public static org.apache.axis.encoding.Deserializer getDeserializer(
           java.lang.String mechType, 
           java.lang.Class _javaType,  
           javax.xml.namespace.QName _xmlType) {
        return 
          new  org.apache.axis.encoding.ser.BeanDeserializer(
            _javaType, _xmlType, typeDesc);
    }

}
