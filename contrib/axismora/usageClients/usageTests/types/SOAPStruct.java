/**
 * SOAPStruct.java
 *
 * This file was auto-generated from WSDL
 * by the Apache Axis WSDL2Java emitter.
 */

package usageTests.types;

public class SOAPStruct  implements java.io.Serializable {
    private java.lang.String val1;
    private java.lang.String[] val10;
    private int[] val11;
    private short[] val12;
    private double[] val13;
    private float[] val14;
    private long[] val15;
    private byte[] val17;
    private boolean[] val18;
    private usageTests.types.BasicStruct val19;
    private int val2;
    private usageTests.types.BasicStruct[] val20;
    private usageTests.types.BasicStruct val21;
    private short val3;
    private double val4;
    private float val5;
    private long val6;
    private byte val8;
    private boolean val9;

    public SOAPStruct() {
    }

    public java.lang.String getVal1() {
        return val1;
    }

    public void setVal1(java.lang.String val1) {
        this.val1 = val1;
    }

    public java.lang.String[] getVal10() {
        return val10;
    }

    public void setVal10(java.lang.String[] val10) {
        this.val10 = val10;
    }

    public int[] getVal11() {
        return val11;
    }

    public void setVal11(int[] val11) {
        this.val11 = val11;
    }

    public short[] getVal12() {
        return val12;
    }

    public void setVal12(short[] val12) {
        this.val12 = val12;
    }

    public double[] getVal13() {
        return val13;
    }

    public void setVal13(double[] val13) {
        this.val13 = val13;
    }

    public float[] getVal14() {
        return val14;
    }

    public void setVal14(float[] val14) {
        this.val14 = val14;
    }

    public long[] getVal15() {
        return val15;
    }

    public void setVal15(long[] val15) {
        this.val15 = val15;
    }

    public byte[] getVal17() {
        return val17;
    }

    public void setVal17(byte[] val17) {
        this.val17 = val17;
    }

    public boolean[] getVal18() {
        return val18;
    }

    public void setVal18(boolean[] val18) {
        this.val18 = val18;
    }

    public usageTests.types.BasicStruct getVal19() {
        return val19;
    }

    public void setVal19(usageTests.types.BasicStruct val19) {
        this.val19 = val19;
    }

    public int getVal2() {
        return val2;
    }

    public void setVal2(int val2) {
        this.val2 = val2;
    }

    public usageTests.types.BasicStruct[] getVal20() {
        return val20;
    }

    public void setVal20(usageTests.types.BasicStruct[] val20) {
        this.val20 = val20;
    }

    public usageTests.types.BasicStruct getVal21() {
        return val21;
    }

    public void setVal21(usageTests.types.BasicStruct val21) {
        this.val21 = val21;
    }

    public short getVal3() {
        return val3;
    }

    public void setVal3(short val3) {
        this.val3 = val3;
    }

    public double getVal4() {
        return val4;
    }

    public void setVal4(double val4) {
        this.val4 = val4;
    }

    public float getVal5() {
        return val5;
    }

    public void setVal5(float val5) {
        this.val5 = val5;
    }

    public long getVal6() {
        return val6;
    }

    public void setVal6(long val6) {
        this.val6 = val6;
    }


    public boolean isVal9() {
        return val9;
    }

    public void setVal9(boolean val9) {
        this.val9 = val9;
    }

    private java.lang.Object __equalsCalc = null;
    public synchronized boolean equals(java.lang.Object obj) {
        if (!(obj instanceof SOAPStruct)) return false;
        SOAPStruct other = (SOAPStruct) obj;
        if (obj == null) return false;
        if (this == obj) return true;
        if (__equalsCalc != null) {
            return (__equalsCalc == obj);
        }
        __equalsCalc = obj;
        boolean _equals;
        _equals = true && 
            ((this.val1==null && other.getVal1()==null) || 
             (this.val1!=null &&
              this.val1.equals(other.getVal1()))) &&
            ((this.val10==null && other.getVal10()==null) || 
             (this.val10!=null &&
              java.util.Arrays.equals(this.val10, other.getVal10()))) &&
            ((this.val11==null && other.getVal11()==null) || 
             (this.val11!=null &&
              java.util.Arrays.equals(this.val11, other.getVal11()))) &&
            ((this.val12==null && other.getVal12()==null) || 
             (this.val12!=null &&
              java.util.Arrays.equals(this.val12, other.getVal12()))) &&
            ((this.val13==null && other.getVal13()==null) || 
             (this.val13!=null &&
              java.util.Arrays.equals(this.val13, other.getVal13()))) &&
            ((this.val14==null && other.getVal14()==null) || 
             (this.val14!=null &&
              java.util.Arrays.equals(this.val14, other.getVal14()))) &&
            ((this.val15==null && other.getVal15()==null) || 
             (this.val15!=null &&
              java.util.Arrays.equals(this.val15, other.getVal15()))) &&
            ((this.val17==null && other.getVal17()==null) || 
             (this.val17!=null &&
              java.util.Arrays.equals(this.val17, other.getVal17()))) &&
            ((this.val18==null && other.getVal18()==null) || 
             (this.val18!=null &&
              java.util.Arrays.equals(this.val18, other.getVal18()))) &&
            ((this.val19==null && other.getVal19()==null) || 
             (this.val19!=null &&
              this.val19.equals(other.getVal19()))) &&
            this.val2 == other.getVal2() &&
            ((this.val20==null && other.getVal20()==null) || 
             (this.val20!=null &&
              java.util.Arrays.equals(this.val20, other.getVal20()))) &&
            ((this.val21==null && other.getVal21()==null) || 
             (this.val21!=null &&
              this.val21.equals(other.getVal21()))) &&
            this.val3 == other.getVal3() &&
            this.val4 == other.getVal4() &&
            this.val5 == other.getVal5() &&
            this.val6 == other.getVal6() &&
            this.val9 == other.isVal9();
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
        if (getVal1() != null) {
            _hashCode += getVal1().hashCode();
        }
        if (getVal10() != null) {
            for (int i=0;
                 i<java.lang.reflect.Array.getLength(getVal10());
                 i++) {
                java.lang.Object obj = java.lang.reflect.Array.get(getVal10(), i);
                if (obj != null &&
                    !obj.getClass().isArray()) {
                    _hashCode += obj.hashCode();
                }
            }
        }
        if (getVal11() != null) {
            for (int i=0;
                 i<java.lang.reflect.Array.getLength(getVal11());
                 i++) {
                java.lang.Object obj = java.lang.reflect.Array.get(getVal11(), i);
                if (obj != null &&
                    !obj.getClass().isArray()) {
                    _hashCode += obj.hashCode();
                }
            }
        }
        if (getVal12() != null) {
            for (int i=0;
                 i<java.lang.reflect.Array.getLength(getVal12());
                 i++) {
                java.lang.Object obj = java.lang.reflect.Array.get(getVal12(), i);
                if (obj != null &&
                    !obj.getClass().isArray()) {
                    _hashCode += obj.hashCode();
                }
            }
        }
        if (getVal13() != null) {
            for (int i=0;
                 i<java.lang.reflect.Array.getLength(getVal13());
                 i++) {
                java.lang.Object obj = java.lang.reflect.Array.get(getVal13(), i);
                if (obj != null &&
                    !obj.getClass().isArray()) {
                    _hashCode += obj.hashCode();
                }
            }
        }
        if (getVal14() != null) {
            for (int i=0;
                 i<java.lang.reflect.Array.getLength(getVal14());
                 i++) {
                java.lang.Object obj = java.lang.reflect.Array.get(getVal14(), i);
                if (obj != null &&
                    !obj.getClass().isArray()) {
                    _hashCode += obj.hashCode();
                }
            }
        }
        if (getVal15() != null) {
            for (int i=0;
                 i<java.lang.reflect.Array.getLength(getVal15());
                 i++) {
                java.lang.Object obj = java.lang.reflect.Array.get(getVal15(), i);
                if (obj != null &&
                    !obj.getClass().isArray()) {
                    _hashCode += obj.hashCode();
                }
            }
        }
        if (getVal17() != null) {
            for (int i=0;
                 i<java.lang.reflect.Array.getLength(getVal17());
                 i++) {
                java.lang.Object obj = java.lang.reflect.Array.get(getVal17(), i);
                if (obj != null &&
                    !obj.getClass().isArray()) {
                    _hashCode += obj.hashCode();
                }
            }
        }
        if (getVal18() != null) {
            for (int i=0;
                 i<java.lang.reflect.Array.getLength(getVal18());
                 i++) {
                java.lang.Object obj = java.lang.reflect.Array.get(getVal18(), i);
                if (obj != null &&
                    !obj.getClass().isArray()) {
                    _hashCode += obj.hashCode();
                }
            }
        }
        if (getVal19() != null) {
            _hashCode += getVal19().hashCode();
        }
        _hashCode += getVal2();
        if (getVal20() != null) {
            for (int i=0;
                 i<java.lang.reflect.Array.getLength(getVal20());
                 i++) {
                java.lang.Object obj = java.lang.reflect.Array.get(getVal20(), i);
                if (obj != null &&
                    !obj.getClass().isArray()) {
                    _hashCode += obj.hashCode();
                }
            }
        }
        if (getVal21() != null) {
            _hashCode += getVal21().hashCode();
        }
        _hashCode += getVal3();
        _hashCode += new Double(getVal4()).hashCode();
        _hashCode += new Float(getVal5()).hashCode();
        _hashCode += new Long(getVal6()).hashCode();
        _hashCode += new Boolean(isVal9()).hashCode();
        __hashCodeCalc = false;
        return _hashCode;
    }

    // Type metadata
    private static org.apache.axis.description.TypeDesc typeDesc =
        new org.apache.axis.description.TypeDesc(SOAPStruct.class);

    static {
        typeDesc.setXmlType(new javax.xml.namespace.QName("http://usageTests/types", "SOAPStruct"));
        org.apache.axis.description.ElementDesc elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("val1");
        elemField.setXmlName(new javax.xml.namespace.QName("", "val1"));
        elemField.setXmlType(new javax.xml.namespace.QName("http://www.w3.org/2001/XMLSchema", "string"));
        typeDesc.addFieldDesc(elemField);
        elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("val10");
        elemField.setXmlName(new javax.xml.namespace.QName("", "val10"));
        elemField.setXmlType(new javax.xml.namespace.QName("http://www.w3.org/2001/XMLSchema", "string"));
        typeDesc.addFieldDesc(elemField);
        elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("val11");
        elemField.setXmlName(new javax.xml.namespace.QName("", "val11"));
        elemField.setXmlType(new javax.xml.namespace.QName("http://www.w3.org/2001/XMLSchema", "int"));
        typeDesc.addFieldDesc(elemField);
        elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("val12");
        elemField.setXmlName(new javax.xml.namespace.QName("", "val12"));
        elemField.setXmlType(new javax.xml.namespace.QName("http://www.w3.org/2001/XMLSchema", "short"));
        typeDesc.addFieldDesc(elemField);
        elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("val13");
        elemField.setXmlName(new javax.xml.namespace.QName("", "val13"));
        elemField.setXmlType(new javax.xml.namespace.QName("http://www.w3.org/2001/XMLSchema", "double"));
        typeDesc.addFieldDesc(elemField);
        elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("val14");
        elemField.setXmlName(new javax.xml.namespace.QName("", "val14"));
        elemField.setXmlType(new javax.xml.namespace.QName("http://www.w3.org/2001/XMLSchema", "float"));
        typeDesc.addFieldDesc(elemField);
        elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("val15");
        elemField.setXmlName(new javax.xml.namespace.QName("", "val15"));
        elemField.setXmlType(new javax.xml.namespace.QName("http://www.w3.org/2001/XMLSchema", "long"));
        typeDesc.addFieldDesc(elemField);
        elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("val17");
        elemField.setXmlName(new javax.xml.namespace.QName("", "val17"));
        elemField.setXmlType(new javax.xml.namespace.QName("http://www.w3.org/2001/XMLSchema", "base64Binary"));
        typeDesc.addFieldDesc(elemField);
        elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("val18");
        elemField.setXmlName(new javax.xml.namespace.QName("", "val18"));
        elemField.setXmlType(new javax.xml.namespace.QName("http://www.w3.org/2001/XMLSchema", "boolean"));
        typeDesc.addFieldDesc(elemField);
        elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("val19");
        elemField.setXmlName(new javax.xml.namespace.QName("", "val19"));
        elemField.setXmlType(new javax.xml.namespace.QName("http://usageTests/types", "BasicStruct"));
        typeDesc.addFieldDesc(elemField);
        elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("val2");
        elemField.setXmlName(new javax.xml.namespace.QName("", "val2"));
        elemField.setXmlType(new javax.xml.namespace.QName("http://www.w3.org/2001/XMLSchema", "int"));
        typeDesc.addFieldDesc(elemField);
        elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("val20");
        elemField.setXmlName(new javax.xml.namespace.QName("", "val20"));
        elemField.setXmlType(new javax.xml.namespace.QName("http://usageTests/types", "BasicStruct"));
        typeDesc.addFieldDesc(elemField);
        elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("val21");
        elemField.setXmlName(new javax.xml.namespace.QName("", "val21"));
        elemField.setXmlType(new javax.xml.namespace.QName("http://usageTests/types", "BasicStruct"));
        typeDesc.addFieldDesc(elemField);
        elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("val3");
        elemField.setXmlName(new javax.xml.namespace.QName("", "val3"));
        elemField.setXmlType(new javax.xml.namespace.QName("http://www.w3.org/2001/XMLSchema", "short"));
        typeDesc.addFieldDesc(elemField);
        elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("val4");
        elemField.setXmlName(new javax.xml.namespace.QName("", "val4"));
        elemField.setXmlType(new javax.xml.namespace.QName("http://www.w3.org/2001/XMLSchema", "double"));
        typeDesc.addFieldDesc(elemField);
        elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("val5");
        elemField.setXmlName(new javax.xml.namespace.QName("", "val5"));
        elemField.setXmlType(new javax.xml.namespace.QName("http://www.w3.org/2001/XMLSchema", "float"));
        typeDesc.addFieldDesc(elemField);
        elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("val6");
        elemField.setXmlName(new javax.xml.namespace.QName("", "val6"));
        elemField.setXmlType(new javax.xml.namespace.QName("http://www.w3.org/2001/XMLSchema", "long"));
        typeDesc.addFieldDesc(elemField);
        elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("val8");
        elemField.setXmlName(new javax.xml.namespace.QName("", "val8"));
        elemField.setXmlType(new javax.xml.namespace.QName("http://www.w3.org/2001/XMLSchema", "byte"));
        typeDesc.addFieldDesc(elemField);
        elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("val9");
        elemField.setXmlName(new javax.xml.namespace.QName("", "val9"));
        elemField.setXmlType(new javax.xml.namespace.QName("http://www.w3.org/2001/XMLSchema", "boolean"));
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

	/**
	 * @return
	 */
	public byte getVal8() {
		return val8;
	}

	/**
	 * @param b
	 */
	public void setVal8(byte b) {
		val8 = b;
	}

}
