/**
 * DirectoryCategory.java
 *
 * This file was auto-generated from WSDL
 * by the Apache Axis 1.2alpha Feb 10, 2004 (12:04:50 GMT+06:00) WSDL2Java emitter.
 */

package org.objectweb.wssample.gen.google;

public class DirectoryCategory  implements java.io.Serializable {
    private java.lang.String fullViewableName;
    private java.lang.String specialEncoding;

    public DirectoryCategory() {
    }


    /**
     * Gets the fullViewableName value for this DirectoryCategory.
     * 
     * @return fullViewableName 
     */
    public java.lang.String getFullViewableName() {
        return fullViewableName;
    }


    /**
     * Sets the fullViewableName value for this DirectoryCategory.
     * 
     * @param fullViewableName 
     */
    public void setFullViewableName(java.lang.String fullViewableName) {
        this.fullViewableName = fullViewableName;
    }


    /**
     * Gets the specialEncoding value for this DirectoryCategory.
     * 
     * @return specialEncoding 
     */
    public java.lang.String getSpecialEncoding() {
        return specialEncoding;
    }


    /**
     * Sets the specialEncoding value for this DirectoryCategory.
     * 
     * @param specialEncoding 
     */
    public void setSpecialEncoding(java.lang.String specialEncoding) {
        this.specialEncoding = specialEncoding;
    }

    private java.lang.Object __equalsCalc = null;
    public synchronized boolean equals(java.lang.Object obj) {
        if (!(obj instanceof DirectoryCategory)) return false;
        DirectoryCategory other = (DirectoryCategory) obj;
        if (obj == null) return false;
        if (this == obj) return true;
        if (__equalsCalc != null) {
            return (__equalsCalc == obj);
        }
        __equalsCalc = obj;
        boolean _equals;
        _equals = true && 
            ((this.fullViewableName==null && other.getFullViewableName()==null) || 
             (this.fullViewableName!=null &&
              this.fullViewableName.equals(other.getFullViewableName()))) &&
            ((this.specialEncoding==null && other.getSpecialEncoding()==null) || 
             (this.specialEncoding!=null &&
              this.specialEncoding.equals(other.getSpecialEncoding())));
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
        if (getFullViewableName() != null) {
            _hashCode += getFullViewableName().hashCode();
        }
        if (getSpecialEncoding() != null) {
            _hashCode += getSpecialEncoding().hashCode();
        }
        __hashCodeCalc = false;
        return _hashCode;
    }

}
