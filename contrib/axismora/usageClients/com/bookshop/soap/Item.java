/**
 * Item.java
 *
 * This file was auto-generated from WSDL
 * by the Apache Axis WSDL2Java emitter.
 */

package com.bookshop.soap;

public class Item  implements java.io.Serializable {
    private java.lang.String itemId;
    private java.lang.String productName;
    private java.lang.String catalog;
    private java.lang.String asin;
    private java.lang.String exchangeId;
    private java.lang.String quantity;
    private java.lang.String listPrice;
    private java.lang.String ourPrice;

    public Item() {
    }

    public java.lang.String getItemId() {
        return itemId;
    }

    public void setItemId(java.lang.String itemId) {
        this.itemId = itemId;
    }

    public java.lang.String getProductName() {
        return productName;
    }

    public void setProductName(java.lang.String productName) {
        this.productName = productName;
    }

    public java.lang.String getCatalog() {
        return catalog;
    }

    public void setCatalog(java.lang.String catalog) {
        this.catalog = catalog;
    }

    public java.lang.String getAsin() {
        return asin;
    }

    public void setAsin(java.lang.String asin) {
        this.asin = asin;
    }

    public java.lang.String getExchangeId() {
        return exchangeId;
    }

    public void setExchangeId(java.lang.String exchangeId) {
        this.exchangeId = exchangeId;
    }

    public java.lang.String getQuantity() {
        return quantity;
    }

    public void setQuantity(java.lang.String quantity) {
        this.quantity = quantity;
    }

    public java.lang.String getListPrice() {
        return listPrice;
    }

    public void setListPrice(java.lang.String listPrice) {
        this.listPrice = listPrice;
    }

    public java.lang.String getOurPrice() {
        return ourPrice;
    }

    public void setOurPrice(java.lang.String ourPrice) {
        this.ourPrice = ourPrice;
    }

    private java.lang.Object __equalsCalc = null;
    public synchronized boolean equals(java.lang.Object obj) {
        if (!(obj instanceof Item)) return false;
        Item other = (Item) obj;
        if (obj == null) return false;
        if (this == obj) return true;
        if (__equalsCalc != null) {
            return (__equalsCalc == obj);
        }
        __equalsCalc = obj;
        boolean _equals;
        _equals = true && 
            ((this.itemId==null && other.getItemId()==null) || 
             (this.itemId!=null &&
              this.itemId.equals(other.getItemId()))) &&
            ((this.productName==null && other.getProductName()==null) || 
             (this.productName!=null &&
              this.productName.equals(other.getProductName()))) &&
            ((this.catalog==null && other.getCatalog()==null) || 
             (this.catalog!=null &&
              this.catalog.equals(other.getCatalog()))) &&
            ((this.asin==null && other.getAsin()==null) || 
             (this.asin!=null &&
              this.asin.equals(other.getAsin()))) &&
            ((this.exchangeId==null && other.getExchangeId()==null) || 
             (this.exchangeId!=null &&
              this.exchangeId.equals(other.getExchangeId()))) &&
            ((this.quantity==null && other.getQuantity()==null) || 
             (this.quantity!=null &&
              this.quantity.equals(other.getQuantity()))) &&
            ((this.listPrice==null && other.getListPrice()==null) || 
             (this.listPrice!=null &&
              this.listPrice.equals(other.getListPrice()))) &&
            ((this.ourPrice==null && other.getOurPrice()==null) || 
             (this.ourPrice!=null &&
              this.ourPrice.equals(other.getOurPrice())));
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
        if (getItemId() != null) {
            _hashCode += getItemId().hashCode();
        }
        if (getProductName() != null) {
            _hashCode += getProductName().hashCode();
        }
        if (getCatalog() != null) {
            _hashCode += getCatalog().hashCode();
        }
        if (getAsin() != null) {
            _hashCode += getAsin().hashCode();
        }
        if (getExchangeId() != null) {
            _hashCode += getExchangeId().hashCode();
        }
        if (getQuantity() != null) {
            _hashCode += getQuantity().hashCode();
        }
        if (getListPrice() != null) {
            _hashCode += getListPrice().hashCode();
        }
        if (getOurPrice() != null) {
            _hashCode += getOurPrice().hashCode();
        }
        __hashCodeCalc = false;
        return _hashCode;
    }

    // Type metadata
    private static org.apache.axis.description.TypeDesc typeDesc =
        new org.apache.axis.description.TypeDesc(Item.class);

    static {
        typeDesc.setXmlType(new javax.xml.namespace.QName("http://soap.bookshop.com", "Item"));
        org.apache.axis.description.ElementDesc elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("itemId");
        elemField.setXmlName(new javax.xml.namespace.QName("", "ItemId"));
        elemField.setXmlType(new javax.xml.namespace.QName("http://www.w3.org/2001/XMLSchema", "string"));
        typeDesc.addFieldDesc(elemField);
        elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("productName");
        elemField.setXmlName(new javax.xml.namespace.QName("", "ProductName"));
        elemField.setXmlType(new javax.xml.namespace.QName("http://www.w3.org/2001/XMLSchema", "string"));
        typeDesc.addFieldDesc(elemField);
        elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("catalog");
        elemField.setXmlName(new javax.xml.namespace.QName("", "Catalog"));
        elemField.setXmlType(new javax.xml.namespace.QName("http://www.w3.org/2001/XMLSchema", "string"));
        typeDesc.addFieldDesc(elemField);
        elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("asin");
        elemField.setXmlName(new javax.xml.namespace.QName("", "Asin"));
        elemField.setXmlType(new javax.xml.namespace.QName("http://www.w3.org/2001/XMLSchema", "string"));
        elemField.setMinOccurs(0);
        typeDesc.addFieldDesc(elemField);
        elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("exchangeId");
        elemField.setXmlName(new javax.xml.namespace.QName("", "ExchangeId"));
        elemField.setXmlType(new javax.xml.namespace.QName("http://www.w3.org/2001/XMLSchema", "string"));
        elemField.setMinOccurs(0);
        typeDesc.addFieldDesc(elemField);
        elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("quantity");
        elemField.setXmlName(new javax.xml.namespace.QName("", "Quantity"));
        elemField.setXmlType(new javax.xml.namespace.QName("http://www.w3.org/2001/XMLSchema", "string"));
        typeDesc.addFieldDesc(elemField);
        elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("listPrice");
        elemField.setXmlName(new javax.xml.namespace.QName("", "ListPrice"));
        elemField.setXmlType(new javax.xml.namespace.QName("http://www.w3.org/2001/XMLSchema", "string"));
        elemField.setMinOccurs(0);
        typeDesc.addFieldDesc(elemField);
        elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("ourPrice");
        elemField.setXmlName(new javax.xml.namespace.QName("", "OurPrice"));
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
