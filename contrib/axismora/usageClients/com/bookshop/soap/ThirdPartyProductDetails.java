/**
 * ThirdPartyProductDetails.java
 *
 * This file was auto-generated from WSDL
 * by the Apache Axis WSDL2Java emitter.
 */

package com.bookshop.soap;

public class ThirdPartyProductDetails  implements java.io.Serializable {
    private java.lang.String offeringType;
    private java.lang.String sellerId;
    private java.lang.String sellerNickname;
    private java.lang.String exchangeId;
    private java.lang.String offeringPrice;
    private java.lang.String condition;
    private java.lang.String conditionType;
    private java.lang.String exchangeAvailability;
    private java.lang.String sellerCountry;
    private java.lang.String sellerState;
    private java.lang.String shipComments;
    private java.lang.String sellerRating;

    public ThirdPartyProductDetails() {
    }

    public java.lang.String getOfferingType() {
        return offeringType;
    }

    public void setOfferingType(java.lang.String offeringType) {
        this.offeringType = offeringType;
    }

    public java.lang.String getSellerId() {
        return sellerId;
    }

    public void setSellerId(java.lang.String sellerId) {
        this.sellerId = sellerId;
    }

    public java.lang.String getSellerNickname() {
        return sellerNickname;
    }

    public void setSellerNickname(java.lang.String sellerNickname) {
        this.sellerNickname = sellerNickname;
    }

    public java.lang.String getExchangeId() {
        return exchangeId;
    }

    public void setExchangeId(java.lang.String exchangeId) {
        this.exchangeId = exchangeId;
    }

    public java.lang.String getOfferingPrice() {
        return offeringPrice;
    }

    public void setOfferingPrice(java.lang.String offeringPrice) {
        this.offeringPrice = offeringPrice;
    }

    public java.lang.String getCondition() {
        return condition;
    }

    public void setCondition(java.lang.String condition) {
        this.condition = condition;
    }

    public java.lang.String getConditionType() {
        return conditionType;
    }

    public void setConditionType(java.lang.String conditionType) {
        this.conditionType = conditionType;
    }

    public java.lang.String getExchangeAvailability() {
        return exchangeAvailability;
    }

    public void setExchangeAvailability(java.lang.String exchangeAvailability) {
        this.exchangeAvailability = exchangeAvailability;
    }

    public java.lang.String getSellerCountry() {
        return sellerCountry;
    }

    public void setSellerCountry(java.lang.String sellerCountry) {
        this.sellerCountry = sellerCountry;
    }

    public java.lang.String getSellerState() {
        return sellerState;
    }

    public void setSellerState(java.lang.String sellerState) {
        this.sellerState = sellerState;
    }

    public java.lang.String getShipComments() {
        return shipComments;
    }

    public void setShipComments(java.lang.String shipComments) {
        this.shipComments = shipComments;
    }

    public java.lang.String getSellerRating() {
        return sellerRating;
    }

    public void setSellerRating(java.lang.String sellerRating) {
        this.sellerRating = sellerRating;
    }

    private java.lang.Object __equalsCalc = null;
    public synchronized boolean equals(java.lang.Object obj) {
        if (!(obj instanceof ThirdPartyProductDetails)) return false;
        ThirdPartyProductDetails other = (ThirdPartyProductDetails) obj;
        if (obj == null) return false;
        if (this == obj) return true;
        if (__equalsCalc != null) {
            return (__equalsCalc == obj);
        }
        __equalsCalc = obj;
        boolean _equals;
        _equals = true && 
            ((this.offeringType==null && other.getOfferingType()==null) || 
             (this.offeringType!=null &&
              this.offeringType.equals(other.getOfferingType()))) &&
            ((this.sellerId==null && other.getSellerId()==null) || 
             (this.sellerId!=null &&
              this.sellerId.equals(other.getSellerId()))) &&
            ((this.sellerNickname==null && other.getSellerNickname()==null) || 
             (this.sellerNickname!=null &&
              this.sellerNickname.equals(other.getSellerNickname()))) &&
            ((this.exchangeId==null && other.getExchangeId()==null) || 
             (this.exchangeId!=null &&
              this.exchangeId.equals(other.getExchangeId()))) &&
            ((this.offeringPrice==null && other.getOfferingPrice()==null) || 
             (this.offeringPrice!=null &&
              this.offeringPrice.equals(other.getOfferingPrice()))) &&
            ((this.condition==null && other.getCondition()==null) || 
             (this.condition!=null &&
              this.condition.equals(other.getCondition()))) &&
            ((this.conditionType==null && other.getConditionType()==null) || 
             (this.conditionType!=null &&
              this.conditionType.equals(other.getConditionType()))) &&
            ((this.exchangeAvailability==null && other.getExchangeAvailability()==null) || 
             (this.exchangeAvailability!=null &&
              this.exchangeAvailability.equals(other.getExchangeAvailability()))) &&
            ((this.sellerCountry==null && other.getSellerCountry()==null) || 
             (this.sellerCountry!=null &&
              this.sellerCountry.equals(other.getSellerCountry()))) &&
            ((this.sellerState==null && other.getSellerState()==null) || 
             (this.sellerState!=null &&
              this.sellerState.equals(other.getSellerState()))) &&
            ((this.shipComments==null && other.getShipComments()==null) || 
             (this.shipComments!=null &&
              this.shipComments.equals(other.getShipComments()))) &&
            ((this.sellerRating==null && other.getSellerRating()==null) || 
             (this.sellerRating!=null &&
              this.sellerRating.equals(other.getSellerRating())));
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
        if (getOfferingType() != null) {
            _hashCode += getOfferingType().hashCode();
        }
        if (getSellerId() != null) {
            _hashCode += getSellerId().hashCode();
        }
        if (getSellerNickname() != null) {
            _hashCode += getSellerNickname().hashCode();
        }
        if (getExchangeId() != null) {
            _hashCode += getExchangeId().hashCode();
        }
        if (getOfferingPrice() != null) {
            _hashCode += getOfferingPrice().hashCode();
        }
        if (getCondition() != null) {
            _hashCode += getCondition().hashCode();
        }
        if (getConditionType() != null) {
            _hashCode += getConditionType().hashCode();
        }
        if (getExchangeAvailability() != null) {
            _hashCode += getExchangeAvailability().hashCode();
        }
        if (getSellerCountry() != null) {
            _hashCode += getSellerCountry().hashCode();
        }
        if (getSellerState() != null) {
            _hashCode += getSellerState().hashCode();
        }
        if (getShipComments() != null) {
            _hashCode += getShipComments().hashCode();
        }
        if (getSellerRating() != null) {
            _hashCode += getSellerRating().hashCode();
        }
        __hashCodeCalc = false;
        return _hashCode;
    }

    // Type metadata
    private static org.apache.axis.description.TypeDesc typeDesc =
        new org.apache.axis.description.TypeDesc(ThirdPartyProductDetails.class);

    static {
        typeDesc.setXmlType(new javax.xml.namespace.QName("http://soap.bookshop.com", "ThirdPartyProductDetails"));
        org.apache.axis.description.ElementDesc elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("offeringType");
        elemField.setXmlName(new javax.xml.namespace.QName("", "OfferingType"));
        elemField.setXmlType(new javax.xml.namespace.QName("http://www.w3.org/2001/XMLSchema", "string"));
        elemField.setMinOccurs(0);
        typeDesc.addFieldDesc(elemField);
        elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("sellerId");
        elemField.setXmlName(new javax.xml.namespace.QName("", "SellerId"));
        elemField.setXmlType(new javax.xml.namespace.QName("http://www.w3.org/2001/XMLSchema", "string"));
        elemField.setMinOccurs(0);
        typeDesc.addFieldDesc(elemField);
        elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("sellerNickname");
        elemField.setXmlName(new javax.xml.namespace.QName("", "SellerNickname"));
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
        elemField.setFieldName("offeringPrice");
        elemField.setXmlName(new javax.xml.namespace.QName("", "OfferingPrice"));
        elemField.setXmlType(new javax.xml.namespace.QName("http://www.w3.org/2001/XMLSchema", "string"));
        elemField.setMinOccurs(0);
        typeDesc.addFieldDesc(elemField);
        elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("condition");
        elemField.setXmlName(new javax.xml.namespace.QName("", "Condition"));
        elemField.setXmlType(new javax.xml.namespace.QName("http://www.w3.org/2001/XMLSchema", "string"));
        elemField.setMinOccurs(0);
        typeDesc.addFieldDesc(elemField);
        elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("conditionType");
        elemField.setXmlName(new javax.xml.namespace.QName("", "ConditionType"));
        elemField.setXmlType(new javax.xml.namespace.QName("http://www.w3.org/2001/XMLSchema", "string"));
        elemField.setMinOccurs(0);
        typeDesc.addFieldDesc(elemField);
        elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("exchangeAvailability");
        elemField.setXmlName(new javax.xml.namespace.QName("", "ExchangeAvailability"));
        elemField.setXmlType(new javax.xml.namespace.QName("http://www.w3.org/2001/XMLSchema", "string"));
        elemField.setMinOccurs(0);
        typeDesc.addFieldDesc(elemField);
        elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("sellerCountry");
        elemField.setXmlName(new javax.xml.namespace.QName("", "SellerCountry"));
        elemField.setXmlType(new javax.xml.namespace.QName("http://www.w3.org/2001/XMLSchema", "string"));
        elemField.setMinOccurs(0);
        typeDesc.addFieldDesc(elemField);
        elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("sellerState");
        elemField.setXmlName(new javax.xml.namespace.QName("", "SellerState"));
        elemField.setXmlType(new javax.xml.namespace.QName("http://www.w3.org/2001/XMLSchema", "string"));
        elemField.setMinOccurs(0);
        typeDesc.addFieldDesc(elemField);
        elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("shipComments");
        elemField.setXmlName(new javax.xml.namespace.QName("", "ShipComments"));
        elemField.setXmlType(new javax.xml.namespace.QName("http://www.w3.org/2001/XMLSchema", "string"));
        elemField.setMinOccurs(0);
        typeDesc.addFieldDesc(elemField);
        elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("sellerRating");
        elemField.setXmlName(new javax.xml.namespace.QName("", "SellerRating"));
        elemField.setXmlType(new javax.xml.namespace.QName("http://www.w3.org/2001/XMLSchema", "string"));
        elemField.setMinOccurs(0);
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
