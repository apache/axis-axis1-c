/**
 * BasicStruct.java
 *
 * This file was auto-generated from WSDL
 * by the Apache Axis WSDL2Java emitter.
 */

package usageTests.types;

public class BasicStruct  implements java.io.Serializable {
    private java.lang.String valA1;
    private int valA2;
    private long valA3;
    private java.lang.String valA4;
    private java.lang.String valA5;

    public BasicStruct() {
    }

    public java.lang.String getValA1() {
        return valA1;
    }

    public void setValA1(java.lang.String valA1) {
        this.valA1 = valA1;
    }

    public int getValA2() {
        return valA2;
    }

    public void setValA2(int valA2) {
        this.valA2 = valA2;
    }

    public long getValA3() {
        return valA3;
    }

    public void setValA3(long valA3) {
        this.valA3 = valA3;
    }

    public java.lang.String getValA4() {
        return valA4;
    }

    public void setValA4(java.lang.String valA4) {
        this.valA4 = valA4;
    }

    public java.lang.String getValA5() {
        return valA5;
    }

    public void setValA5(java.lang.String valA5) {
        this.valA5 = valA5;
    }

    private java.lang.Object __equalsCalc = null;
    public synchronized boolean equals(java.lang.Object obj) {
        if (!(obj instanceof BasicStruct)) return false;
        BasicStruct other = (BasicStruct) obj;
        if (obj == null) return false;
        if (this == obj) return true;
        if (__equalsCalc != null) {
            return (__equalsCalc == obj);
        }
        __equalsCalc = obj;
        boolean _equals;
        _equals = true && 
            ((this.valA1==null && other.getValA1()==null) || 
             (this.valA1!=null &&
              this.valA1.equals(other.getValA1()))) &&
            this.valA2 == other.getValA2() &&
            this.valA3 == other.getValA3() &&
            ((this.valA4==null && other.getValA4()==null) || 
             (this.valA4!=null &&
              this.valA4.equals(other.getValA4()))) &&
            ((this.valA5==null && other.getValA5()==null) || 
             (this.valA5!=null &&
              this.valA5.equals(other.getValA5())));
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
        if (getValA1() != null) {
            _hashCode += getValA1().hashCode();
        }
        _hashCode += getValA2();
        _hashCode += new Long(getValA3()).hashCode();
        if (getValA4() != null) {
            _hashCode += getValA4().hashCode();
        }
        if (getValA5() != null) {
            _hashCode += getValA5().hashCode();
        }
        __hashCodeCalc = false;
        return _hashCode;
    }

    // Type metadata
    private static org.apache.axis.description.TypeDesc typeDesc =
        new org.apache.axis.description.TypeDesc(BasicStruct.class);

    static {
        typeDesc.setXmlType(new javax.xml.namespace.QName("http://usageTests/types", "BasicStruct"));
        org.apache.axis.description.ElementDesc elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("valA1");
        elemField.setXmlName(new javax.xml.namespace.QName("", "valA1"));
        elemField.setXmlType(new javax.xml.namespace.QName("http://www.w3.org/2001/XMLSchema", "string"));
        typeDesc.addFieldDesc(elemField);
        elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("valA2");
        elemField.setXmlName(new javax.xml.namespace.QName("", "valA2"));
        elemField.setXmlType(new javax.xml.namespace.QName("http://www.w3.org/2001/XMLSchema", "int"));
        typeDesc.addFieldDesc(elemField);
        elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("valA3");
        elemField.setXmlName(new javax.xml.namespace.QName("", "valA3"));
        elemField.setXmlType(new javax.xml.namespace.QName("http://www.w3.org/2001/XMLSchema", "long"));
        typeDesc.addFieldDesc(elemField);
        elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("valA4");
        elemField.setXmlName(new javax.xml.namespace.QName("", "valA4"));
        elemField.setXmlType(new javax.xml.namespace.QName("http://www.w3.org/2001/XMLSchema", "string"));
        typeDesc.addFieldDesc(elemField);
        elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("valA5");
        elemField.setXmlName(new javax.xml.namespace.QName("", "valA5"));
        elemField.setXmlType(new javax.xml.namespace.QName("http://www.w3.org/2001/XMLSchema", "string"));
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
