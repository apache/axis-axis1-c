/**
 * ListingProductDetails.java
 *
 * This file was auto-generated from WSDL
 * by the Apache Axis WSDL2Java emitter.
 */

package com.bookshop.soap;

public class ListingProductDetails  implements java.io.Serializable {
    private java.lang.String exchangeId;
    private java.lang.String listingId;
    private java.lang.String exchangeTitle;
    private java.lang.String exchangePrice;
    private java.lang.String exchangeAsin;
    private java.lang.String exchangeEndDate;
    private java.lang.String exchangeTinyImage;
    private java.lang.String exchangeSellerId;
    private java.lang.String exchangeSellerNickname;
    private java.lang.String exchangeStartDate;
    private java.lang.String exchangeStatus;
    private java.lang.String exchangeQuantity;
    private java.lang.String exchangeQuantityAllocated;
    private java.lang.String exchangeFeaturedCategory;
    private java.lang.String exchangeCondition;
    private java.lang.String exchangeConditionType;
    private java.lang.String exchangeAvailability;
    private java.lang.String exchangeOfferingType;
    private java.lang.String exchangeSellerState;
    private java.lang.String exchangeSellerCountry;
    private java.lang.String exchangeSellerRating;

    public ListingProductDetails() {
    }

    public java.lang.String getExchangeId() {
        return exchangeId;
    }

    public void setExchangeId(java.lang.String exchangeId) {
        this.exchangeId = exchangeId;
    }

    public java.lang.String getListingId() {
        return listingId;
    }

    public void setListingId(java.lang.String listingId) {
        this.listingId = listingId;
    }

    public java.lang.String getExchangeTitle() {
        return exchangeTitle;
    }

    public void setExchangeTitle(java.lang.String exchangeTitle) {
        this.exchangeTitle = exchangeTitle;
    }

    public java.lang.String getExchangePrice() {
        return exchangePrice;
    }

    public void setExchangePrice(java.lang.String exchangePrice) {
        this.exchangePrice = exchangePrice;
    }

    public java.lang.String getExchangeAsin() {
        return exchangeAsin;
    }

    public void setExchangeAsin(java.lang.String exchangeAsin) {
        this.exchangeAsin = exchangeAsin;
    }

    public java.lang.String getExchangeEndDate() {
        return exchangeEndDate;
    }

    public void setExchangeEndDate(java.lang.String exchangeEndDate) {
        this.exchangeEndDate = exchangeEndDate;
    }

    public java.lang.String getExchangeTinyImage() {
        return exchangeTinyImage;
    }

    public void setExchangeTinyImage(java.lang.String exchangeTinyImage) {
        this.exchangeTinyImage = exchangeTinyImage;
    }

    public java.lang.String getExchangeSellerId() {
        return exchangeSellerId;
    }

    public void setExchangeSellerId(java.lang.String exchangeSellerId) {
        this.exchangeSellerId = exchangeSellerId;
    }

    public java.lang.String getExchangeSellerNickname() {
        return exchangeSellerNickname;
    }

    public void setExchangeSellerNickname(java.lang.String exchangeSellerNickname) {
        this.exchangeSellerNickname = exchangeSellerNickname;
    }

    public java.lang.String getExchangeStartDate() {
        return exchangeStartDate;
    }

    public void setExchangeStartDate(java.lang.String exchangeStartDate) {
        this.exchangeStartDate = exchangeStartDate;
    }

    public java.lang.String getExchangeStatus() {
        return exchangeStatus;
    }

    public void setExchangeStatus(java.lang.String exchangeStatus) {
        this.exchangeStatus = exchangeStatus;
    }

    public java.lang.String getExchangeQuantity() {
        return exchangeQuantity;
    }

    public void setExchangeQuantity(java.lang.String exchangeQuantity) {
        this.exchangeQuantity = exchangeQuantity;
    }

    public java.lang.String getExchangeQuantityAllocated() {
        return exchangeQuantityAllocated;
    }

    public void setExchangeQuantityAllocated(java.lang.String exchangeQuantityAllocated) {
        this.exchangeQuantityAllocated = exchangeQuantityAllocated;
    }

    public java.lang.String getExchangeFeaturedCategory() {
        return exchangeFeaturedCategory;
    }

    public void setExchangeFeaturedCategory(java.lang.String exchangeFeaturedCategory) {
        this.exchangeFeaturedCategory = exchangeFeaturedCategory;
    }

    public java.lang.String getExchangeCondition() {
        return exchangeCondition;
    }

    public void setExchangeCondition(java.lang.String exchangeCondition) {
        this.exchangeCondition = exchangeCondition;
    }

    public java.lang.String getExchangeConditionType() {
        return exchangeConditionType;
    }

    public void setExchangeConditionType(java.lang.String exchangeConditionType) {
        this.exchangeConditionType = exchangeConditionType;
    }

    public java.lang.String getExchangeAvailability() {
        return exchangeAvailability;
    }

    public void setExchangeAvailability(java.lang.String exchangeAvailability) {
        this.exchangeAvailability = exchangeAvailability;
    }

    public java.lang.String getExchangeOfferingType() {
        return exchangeOfferingType;
    }

    public void setExchangeOfferingType(java.lang.String exchangeOfferingType) {
        this.exchangeOfferingType = exchangeOfferingType;
    }

    public java.lang.String getExchangeSellerState() {
        return exchangeSellerState;
    }

    public void setExchangeSellerState(java.lang.String exchangeSellerState) {
        this.exchangeSellerState = exchangeSellerState;
    }

    public java.lang.String getExchangeSellerCountry() {
        return exchangeSellerCountry;
    }

    public void setExchangeSellerCountry(java.lang.String exchangeSellerCountry) {
        this.exchangeSellerCountry = exchangeSellerCountry;
    }

    public java.lang.String getExchangeSellerRating() {
        return exchangeSellerRating;
    }

    public void setExchangeSellerRating(java.lang.String exchangeSellerRating) {
        this.exchangeSellerRating = exchangeSellerRating;
    }

    private java.lang.Object __equalsCalc = null;
    public synchronized boolean equals(java.lang.Object obj) {
        if (!(obj instanceof ListingProductDetails)) return false;
        ListingProductDetails other = (ListingProductDetails) obj;
        if (obj == null) return false;
        if (this == obj) return true;
        if (__equalsCalc != null) {
            return (__equalsCalc == obj);
        }
        __equalsCalc = obj;
        boolean _equals;
        _equals = true && 
            ((this.exchangeId==null && other.getExchangeId()==null) || 
             (this.exchangeId!=null &&
              this.exchangeId.equals(other.getExchangeId()))) &&
            ((this.listingId==null && other.getListingId()==null) || 
             (this.listingId!=null &&
              this.listingId.equals(other.getListingId()))) &&
            ((this.exchangeTitle==null && other.getExchangeTitle()==null) || 
             (this.exchangeTitle!=null &&
              this.exchangeTitle.equals(other.getExchangeTitle()))) &&
            ((this.exchangePrice==null && other.getExchangePrice()==null) || 
             (this.exchangePrice!=null &&
              this.exchangePrice.equals(other.getExchangePrice()))) &&
            ((this.exchangeAsin==null && other.getExchangeAsin()==null) || 
             (this.exchangeAsin!=null &&
              this.exchangeAsin.equals(other.getExchangeAsin()))) &&
            ((this.exchangeEndDate==null && other.getExchangeEndDate()==null) || 
             (this.exchangeEndDate!=null &&
              this.exchangeEndDate.equals(other.getExchangeEndDate()))) &&
            ((this.exchangeTinyImage==null && other.getExchangeTinyImage()==null) || 
             (this.exchangeTinyImage!=null &&
              this.exchangeTinyImage.equals(other.getExchangeTinyImage()))) &&
            ((this.exchangeSellerId==null && other.getExchangeSellerId()==null) || 
             (this.exchangeSellerId!=null &&
              this.exchangeSellerId.equals(other.getExchangeSellerId()))) &&
            ((this.exchangeSellerNickname==null && other.getExchangeSellerNickname()==null) || 
             (this.exchangeSellerNickname!=null &&
              this.exchangeSellerNickname.equals(other.getExchangeSellerNickname()))) &&
            ((this.exchangeStartDate==null && other.getExchangeStartDate()==null) || 
             (this.exchangeStartDate!=null &&
              this.exchangeStartDate.equals(other.getExchangeStartDate()))) &&
            ((this.exchangeStatus==null && other.getExchangeStatus()==null) || 
             (this.exchangeStatus!=null &&
              this.exchangeStatus.equals(other.getExchangeStatus()))) &&
            ((this.exchangeQuantity==null && other.getExchangeQuantity()==null) || 
             (this.exchangeQuantity!=null &&
              this.exchangeQuantity.equals(other.getExchangeQuantity()))) &&
            ((this.exchangeQuantityAllocated==null && other.getExchangeQuantityAllocated()==null) || 
             (this.exchangeQuantityAllocated!=null &&
              this.exchangeQuantityAllocated.equals(other.getExchangeQuantityAllocated()))) &&
            ((this.exchangeFeaturedCategory==null && other.getExchangeFeaturedCategory()==null) || 
             (this.exchangeFeaturedCategory!=null &&
              this.exchangeFeaturedCategory.equals(other.getExchangeFeaturedCategory()))) &&
            ((this.exchangeCondition==null && other.getExchangeCondition()==null) || 
             (this.exchangeCondition!=null &&
              this.exchangeCondition.equals(other.getExchangeCondition()))) &&
            ((this.exchangeConditionType==null && other.getExchangeConditionType()==null) || 
             (this.exchangeConditionType!=null &&
              this.exchangeConditionType.equals(other.getExchangeConditionType()))) &&
            ((this.exchangeAvailability==null && other.getExchangeAvailability()==null) || 
             (this.exchangeAvailability!=null &&
              this.exchangeAvailability.equals(other.getExchangeAvailability()))) &&
            ((this.exchangeOfferingType==null && other.getExchangeOfferingType()==null) || 
             (this.exchangeOfferingType!=null &&
              this.exchangeOfferingType.equals(other.getExchangeOfferingType()))) &&
            ((this.exchangeSellerState==null && other.getExchangeSellerState()==null) || 
             (this.exchangeSellerState!=null &&
              this.exchangeSellerState.equals(other.getExchangeSellerState()))) &&
            ((this.exchangeSellerCountry==null && other.getExchangeSellerCountry()==null) || 
             (this.exchangeSellerCountry!=null &&
              this.exchangeSellerCountry.equals(other.getExchangeSellerCountry()))) &&
            ((this.exchangeSellerRating==null && other.getExchangeSellerRating()==null) || 
             (this.exchangeSellerRating!=null &&
              this.exchangeSellerRating.equals(other.getExchangeSellerRating())));
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
        if (getExchangeId() != null) {
            _hashCode += getExchangeId().hashCode();
        }
        if (getListingId() != null) {
            _hashCode += getListingId().hashCode();
        }
        if (getExchangeTitle() != null) {
            _hashCode += getExchangeTitle().hashCode();
        }
        if (getExchangePrice() != null) {
            _hashCode += getExchangePrice().hashCode();
        }
        if (getExchangeAsin() != null) {
            _hashCode += getExchangeAsin().hashCode();
        }
        if (getExchangeEndDate() != null) {
            _hashCode += getExchangeEndDate().hashCode();
        }
        if (getExchangeTinyImage() != null) {
            _hashCode += getExchangeTinyImage().hashCode();
        }
        if (getExchangeSellerId() != null) {
            _hashCode += getExchangeSellerId().hashCode();
        }
        if (getExchangeSellerNickname() != null) {
            _hashCode += getExchangeSellerNickname().hashCode();
        }
        if (getExchangeStartDate() != null) {
            _hashCode += getExchangeStartDate().hashCode();
        }
        if (getExchangeStatus() != null) {
            _hashCode += getExchangeStatus().hashCode();
        }
        if (getExchangeQuantity() != null) {
            _hashCode += getExchangeQuantity().hashCode();
        }
        if (getExchangeQuantityAllocated() != null) {
            _hashCode += getExchangeQuantityAllocated().hashCode();
        }
        if (getExchangeFeaturedCategory() != null) {
            _hashCode += getExchangeFeaturedCategory().hashCode();
        }
        if (getExchangeCondition() != null) {
            _hashCode += getExchangeCondition().hashCode();
        }
        if (getExchangeConditionType() != null) {
            _hashCode += getExchangeConditionType().hashCode();
        }
        if (getExchangeAvailability() != null) {
            _hashCode += getExchangeAvailability().hashCode();
        }
        if (getExchangeOfferingType() != null) {
            _hashCode += getExchangeOfferingType().hashCode();
        }
        if (getExchangeSellerState() != null) {
            _hashCode += getExchangeSellerState().hashCode();
        }
        if (getExchangeSellerCountry() != null) {
            _hashCode += getExchangeSellerCountry().hashCode();
        }
        if (getExchangeSellerRating() != null) {
            _hashCode += getExchangeSellerRating().hashCode();
        }
        __hashCodeCalc = false;
        return _hashCode;
    }

    // Type metadata
    private static org.apache.axis.description.TypeDesc typeDesc =
        new org.apache.axis.description.TypeDesc(ListingProductDetails.class);

    static {
        typeDesc.setXmlType(new javax.xml.namespace.QName("http://soap.bookshop.com", "ListingProductDetails"));
        org.apache.axis.description.ElementDesc elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("exchangeId");
        elemField.setXmlName(new javax.xml.namespace.QName("", "ExchangeId"));
        elemField.setXmlType(new javax.xml.namespace.QName("http://www.w3.org/2001/XMLSchema", "string"));
        elemField.setMinOccurs(0);
        typeDesc.addFieldDesc(elemField);
        elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("listingId");
        elemField.setXmlName(new javax.xml.namespace.QName("", "ListingId"));
        elemField.setXmlType(new javax.xml.namespace.QName("http://www.w3.org/2001/XMLSchema", "string"));
        elemField.setMinOccurs(0);
        typeDesc.addFieldDesc(elemField);
        elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("exchangeTitle");
        elemField.setXmlName(new javax.xml.namespace.QName("", "ExchangeTitle"));
        elemField.setXmlType(new javax.xml.namespace.QName("http://www.w3.org/2001/XMLSchema", "string"));
        elemField.setMinOccurs(0);
        typeDesc.addFieldDesc(elemField);
        elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("exchangePrice");
        elemField.setXmlName(new javax.xml.namespace.QName("", "ExchangePrice"));
        elemField.setXmlType(new javax.xml.namespace.QName("http://www.w3.org/2001/XMLSchema", "string"));
        elemField.setMinOccurs(0);
        typeDesc.addFieldDesc(elemField);
        elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("exchangeAsin");
        elemField.setXmlName(new javax.xml.namespace.QName("", "ExchangeAsin"));
        elemField.setXmlType(new javax.xml.namespace.QName("http://www.w3.org/2001/XMLSchema", "string"));
        elemField.setMinOccurs(0);
        typeDesc.addFieldDesc(elemField);
        elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("exchangeEndDate");
        elemField.setXmlName(new javax.xml.namespace.QName("", "ExchangeEndDate"));
        elemField.setXmlType(new javax.xml.namespace.QName("http://www.w3.org/2001/XMLSchema", "string"));
        elemField.setMinOccurs(0);
        typeDesc.addFieldDesc(elemField);
        elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("exchangeTinyImage");
        elemField.setXmlName(new javax.xml.namespace.QName("", "ExchangeTinyImage"));
        elemField.setXmlType(new javax.xml.namespace.QName("http://www.w3.org/2001/XMLSchema", "string"));
        elemField.setMinOccurs(0);
        typeDesc.addFieldDesc(elemField);
        elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("exchangeSellerId");
        elemField.setXmlName(new javax.xml.namespace.QName("", "ExchangeSellerId"));
        elemField.setXmlType(new javax.xml.namespace.QName("http://www.w3.org/2001/XMLSchema", "string"));
        elemField.setMinOccurs(0);
        typeDesc.addFieldDesc(elemField);
        elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("exchangeSellerNickname");
        elemField.setXmlName(new javax.xml.namespace.QName("", "ExchangeSellerNickname"));
        elemField.setXmlType(new javax.xml.namespace.QName("http://www.w3.org/2001/XMLSchema", "string"));
        elemField.setMinOccurs(0);
        typeDesc.addFieldDesc(elemField);
        elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("exchangeStartDate");
        elemField.setXmlName(new javax.xml.namespace.QName("", "ExchangeStartDate"));
        elemField.setXmlType(new javax.xml.namespace.QName("http://www.w3.org/2001/XMLSchema", "string"));
        elemField.setMinOccurs(0);
        typeDesc.addFieldDesc(elemField);
        elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("exchangeStatus");
        elemField.setXmlName(new javax.xml.namespace.QName("", "ExchangeStatus"));
        elemField.setXmlType(new javax.xml.namespace.QName("http://www.w3.org/2001/XMLSchema", "string"));
        elemField.setMinOccurs(0);
        typeDesc.addFieldDesc(elemField);
        elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("exchangeQuantity");
        elemField.setXmlName(new javax.xml.namespace.QName("", "ExchangeQuantity"));
        elemField.setXmlType(new javax.xml.namespace.QName("http://www.w3.org/2001/XMLSchema", "string"));
        elemField.setMinOccurs(0);
        typeDesc.addFieldDesc(elemField);
        elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("exchangeQuantityAllocated");
        elemField.setXmlName(new javax.xml.namespace.QName("", "ExchangeQuantityAllocated"));
        elemField.setXmlType(new javax.xml.namespace.QName("http://www.w3.org/2001/XMLSchema", "string"));
        elemField.setMinOccurs(0);
        typeDesc.addFieldDesc(elemField);
        elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("exchangeFeaturedCategory");
        elemField.setXmlName(new javax.xml.namespace.QName("", "ExchangeFeaturedCategory"));
        elemField.setXmlType(new javax.xml.namespace.QName("http://www.w3.org/2001/XMLSchema", "string"));
        elemField.setMinOccurs(0);
        typeDesc.addFieldDesc(elemField);
        elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("exchangeCondition");
        elemField.setXmlName(new javax.xml.namespace.QName("", "ExchangeCondition"));
        elemField.setXmlType(new javax.xml.namespace.QName("http://www.w3.org/2001/XMLSchema", "string"));
        elemField.setMinOccurs(0);
        typeDesc.addFieldDesc(elemField);
        elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("exchangeConditionType");
        elemField.setXmlName(new javax.xml.namespace.QName("", "ExchangeConditionType"));
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
        elemField.setFieldName("exchangeOfferingType");
        elemField.setXmlName(new javax.xml.namespace.QName("", "ExchangeOfferingType"));
        elemField.setXmlType(new javax.xml.namespace.QName("http://www.w3.org/2001/XMLSchema", "string"));
        elemField.setMinOccurs(0);
        typeDesc.addFieldDesc(elemField);
        elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("exchangeSellerState");
        elemField.setXmlName(new javax.xml.namespace.QName("", "ExchangeSellerState"));
        elemField.setXmlType(new javax.xml.namespace.QName("http://www.w3.org/2001/XMLSchema", "string"));
        elemField.setMinOccurs(0);
        typeDesc.addFieldDesc(elemField);
        elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("exchangeSellerCountry");
        elemField.setXmlName(new javax.xml.namespace.QName("", "ExchangeSellerCountry"));
        elemField.setXmlType(new javax.xml.namespace.QName("http://www.w3.org/2001/XMLSchema", "string"));
        elemField.setMinOccurs(0);
        typeDesc.addFieldDesc(elemField);
        elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("exchangeSellerRating");
        elemField.setXmlName(new javax.xml.namespace.QName("", "ExchangeSellerRating"));
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
