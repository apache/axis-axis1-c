/**
 * AmazonSearchBindingStub.java
 *
 * This file was auto-generated from WSDL
 * by the Apache Axis WSDL2Java emitter.
 */

package com.bookshop.soap;

public class AmazonSearchBindingStub extends org.apache.axis.client.Stub implements com.bookshop.soap.AmazonSearchPort {
    private java.util.Vector cachedSerClasses = new java.util.Vector();
    private java.util.Vector cachedSerQNames = new java.util.Vector();
    private java.util.Vector cachedSerFactories = new java.util.Vector();
    private java.util.Vector cachedDeserFactories = new java.util.Vector();

    static org.apache.axis.description.OperationDesc [] _operations;

    static {
        _operations = new org.apache.axis.description.OperationDesc[23];
        org.apache.axis.description.OperationDesc oper;
        oper = new org.apache.axis.description.OperationDesc();
        oper.setName("KeywordSearchRequest");
        oper.addParameter(new javax.xml.namespace.QName("", "KeywordSearchRequest"), new javax.xml.namespace.QName("http://soap.bookshop.com", "KeywordRequest"), com.bookshop.soap.KeywordRequest.class, org.apache.axis.description.ParameterDesc.IN, false, false);
        oper.setReturnType(new javax.xml.namespace.QName("http://soap.bookshop.com", "ProductInfo"));
        oper.setReturnClass(com.bookshop.soap.ProductInfo.class);
        oper.setReturnQName(new javax.xml.namespace.QName("", "return"));
        oper.setStyle(org.apache.axis.enum.Style.RPC);
        oper.setUse(org.apache.axis.enum.Use.ENCODED);
        _operations[0] = oper;

        oper = new org.apache.axis.description.OperationDesc();
        oper.setName("PowerSearchRequest");
        oper.addParameter(new javax.xml.namespace.QName("", "PowerSearchRequest"), new javax.xml.namespace.QName("http://soap.bookshop.com", "PowerRequest"), com.bookshop.soap.PowerRequest.class, org.apache.axis.description.ParameterDesc.IN, false, false);
        oper.setReturnType(new javax.xml.namespace.QName("http://soap.bookshop.com", "ProductInfo"));
        oper.setReturnClass(com.bookshop.soap.ProductInfo.class);
        oper.setReturnQName(new javax.xml.namespace.QName("", "return"));
        oper.setStyle(org.apache.axis.enum.Style.RPC);
        oper.setUse(org.apache.axis.enum.Use.ENCODED);
        _operations[1] = oper;

        oper = new org.apache.axis.description.OperationDesc();
        oper.setName("BrowseNodeSearchRequest");
        oper.addParameter(new javax.xml.namespace.QName("", "BrowseNodeSearchRequest"), new javax.xml.namespace.QName("http://soap.bookshop.com", "BrowseNodeRequest"), com.bookshop.soap.BrowseNodeRequest.class, org.apache.axis.description.ParameterDesc.IN, false, false);
        oper.setReturnType(new javax.xml.namespace.QName("http://soap.bookshop.com", "ProductInfo"));
        oper.setReturnClass(com.bookshop.soap.ProductInfo.class);
        oper.setReturnQName(new javax.xml.namespace.QName("", "return"));
        oper.setStyle(org.apache.axis.enum.Style.RPC);
        oper.setUse(org.apache.axis.enum.Use.ENCODED);
        _operations[2] = oper;

        oper = new org.apache.axis.description.OperationDesc();
        oper.setName("AsinSearchRequest");
        oper.addParameter(new javax.xml.namespace.QName("", "AsinSearchRequest"), new javax.xml.namespace.QName("http://soap.bookshop.com", "AsinRequest"), com.bookshop.soap.AsinRequest.class, org.apache.axis.description.ParameterDesc.IN, false, false);
        oper.setReturnType(new javax.xml.namespace.QName("http://soap.bookshop.com", "ProductInfo"));
        oper.setReturnClass(com.bookshop.soap.ProductInfo.class);
        oper.setReturnQName(new javax.xml.namespace.QName("", "return"));
        oper.setStyle(org.apache.axis.enum.Style.RPC);
        oper.setUse(org.apache.axis.enum.Use.ENCODED);
        _operations[3] = oper;

        oper = new org.apache.axis.description.OperationDesc();
        oper.setName("BlendedSearchRequest");
        oper.addParameter(new javax.xml.namespace.QName("", "BlendedSearchRequest"), new javax.xml.namespace.QName("http://soap.bookshop.com", "BlendedRequest"), com.bookshop.soap.BlendedRequest.class, org.apache.axis.description.ParameterDesc.IN, false, false);
        oper.setReturnType(new javax.xml.namespace.QName("http://soap.bookshop.com", "ProductLineArray"));
        oper.setReturnClass(com.bookshop.soap.ProductLine[].class);
        oper.setReturnQName(new javax.xml.namespace.QName("", "return"));
        oper.setStyle(org.apache.axis.enum.Style.RPC);
        oper.setUse(org.apache.axis.enum.Use.ENCODED);
        _operations[4] = oper;

        oper = new org.apache.axis.description.OperationDesc();
        oper.setName("UpcSearchRequest");
        oper.addParameter(new javax.xml.namespace.QName("", "UpcSearchRequest"), new javax.xml.namespace.QName("http://soap.bookshop.com", "UpcRequest"), com.bookshop.soap.UpcRequest.class, org.apache.axis.description.ParameterDesc.IN, false, false);
        oper.setReturnType(new javax.xml.namespace.QName("http://soap.bookshop.com", "ProductInfo"));
        oper.setReturnClass(com.bookshop.soap.ProductInfo.class);
        oper.setReturnQName(new javax.xml.namespace.QName("", "return"));
        oper.setStyle(org.apache.axis.enum.Style.RPC);
        oper.setUse(org.apache.axis.enum.Use.ENCODED);
        _operations[5] = oper;

        oper = new org.apache.axis.description.OperationDesc();
        oper.setName("AuthorSearchRequest");
        oper.addParameter(new javax.xml.namespace.QName("", "AuthorSearchRequest"), new javax.xml.namespace.QName("http://soap.bookshop.com", "AuthorRequest"), com.bookshop.soap.AuthorRequest.class, org.apache.axis.description.ParameterDesc.IN, false, false);
        oper.setReturnType(new javax.xml.namespace.QName("http://soap.bookshop.com", "ProductInfo"));
        oper.setReturnClass(com.bookshop.soap.ProductInfo.class);
        oper.setReturnQName(new javax.xml.namespace.QName("", "return"));
        oper.setStyle(org.apache.axis.enum.Style.RPC);
        oper.setUse(org.apache.axis.enum.Use.ENCODED);
        _operations[6] = oper;

        oper = new org.apache.axis.description.OperationDesc();
        oper.setName("ArtistSearchRequest");
        oper.addParameter(new javax.xml.namespace.QName("", "ArtistSearchRequest"), new javax.xml.namespace.QName("http://soap.bookshop.com", "ArtistRequest"), com.bookshop.soap.ArtistRequest.class, org.apache.axis.description.ParameterDesc.IN, false, false);
        oper.setReturnType(new javax.xml.namespace.QName("http://soap.bookshop.com", "ProductInfo"));
        oper.setReturnClass(com.bookshop.soap.ProductInfo.class);
        oper.setReturnQName(new javax.xml.namespace.QName("", "return"));
        oper.setStyle(org.apache.axis.enum.Style.RPC);
        oper.setUse(org.apache.axis.enum.Use.ENCODED);
        _operations[7] = oper;

        oper = new org.apache.axis.description.OperationDesc();
        oper.setName("ActorSearchRequest");
        oper.addParameter(new javax.xml.namespace.QName("", "ActorSearchRequest"), new javax.xml.namespace.QName("http://soap.bookshop.com", "ActorRequest"), com.bookshop.soap.ActorRequest.class, org.apache.axis.description.ParameterDesc.IN, false, false);
        oper.setReturnType(new javax.xml.namespace.QName("http://soap.bookshop.com", "ProductInfo"));
        oper.setReturnClass(com.bookshop.soap.ProductInfo.class);
        oper.setReturnQName(new javax.xml.namespace.QName("", "return"));
        oper.setStyle(org.apache.axis.enum.Style.RPC);
        oper.setUse(org.apache.axis.enum.Use.ENCODED);
        _operations[8] = oper;

        oper = new org.apache.axis.description.OperationDesc();
        oper.setName("ManufacturerSearchRequest");
        oper.addParameter(new javax.xml.namespace.QName("", "ManufacturerSearchRequest"), new javax.xml.namespace.QName("http://soap.bookshop.com", "ManufacturerRequest"), com.bookshop.soap.ManufacturerRequest.class, org.apache.axis.description.ParameterDesc.IN, false, false);
        oper.setReturnType(new javax.xml.namespace.QName("http://soap.bookshop.com", "ProductInfo"));
        oper.setReturnClass(com.bookshop.soap.ProductInfo.class);
        oper.setReturnQName(new javax.xml.namespace.QName("", "return"));
        oper.setStyle(org.apache.axis.enum.Style.RPC);
        oper.setUse(org.apache.axis.enum.Use.ENCODED);
        _operations[9] = oper;

        oper = new org.apache.axis.description.OperationDesc();
        oper.setName("DirectorSearchRequest");
        oper.addParameter(new javax.xml.namespace.QName("", "DirectorSearchRequest"), new javax.xml.namespace.QName("http://soap.bookshop.com", "DirectorRequest"), com.bookshop.soap.DirectorRequest.class, org.apache.axis.description.ParameterDesc.IN, false, false);
        oper.setReturnType(new javax.xml.namespace.QName("http://soap.bookshop.com", "ProductInfo"));
        oper.setReturnClass(com.bookshop.soap.ProductInfo.class);
        oper.setReturnQName(new javax.xml.namespace.QName("", "return"));
        oper.setStyle(org.apache.axis.enum.Style.RPC);
        oper.setUse(org.apache.axis.enum.Use.ENCODED);
        _operations[10] = oper;

        oper = new org.apache.axis.description.OperationDesc();
        oper.setName("ExchangeSearchRequest");
        oper.addParameter(new javax.xml.namespace.QName("", "ExchangeSearchRequest"), new javax.xml.namespace.QName("http://soap.bookshop.com", "ExchangeRequest"), com.bookshop.soap.ExchangeRequest.class, org.apache.axis.description.ParameterDesc.IN, false, false);
        oper.setReturnType(new javax.xml.namespace.QName("http://soap.bookshop.com", "ListingProductDetails"));
        oper.setReturnClass(com.bookshop.soap.ListingProductDetails.class);
        oper.setReturnQName(new javax.xml.namespace.QName("", "return"));
        oper.setStyle(org.apache.axis.enum.Style.RPC);
        oper.setUse(org.apache.axis.enum.Use.ENCODED);
        _operations[11] = oper;

        oper = new org.apache.axis.description.OperationDesc();
        oper.setName("ListManiaSearchRequest");
        oper.addParameter(new javax.xml.namespace.QName("", "ListManiaSearchRequest"), new javax.xml.namespace.QName("http://soap.bookshop.com", "ListManiaRequest"), com.bookshop.soap.ListManiaRequest.class, org.apache.axis.description.ParameterDesc.IN, false, false);
        oper.setReturnType(new javax.xml.namespace.QName("http://soap.bookshop.com", "ProductInfo"));
        oper.setReturnClass(com.bookshop.soap.ProductInfo.class);
        oper.setReturnQName(new javax.xml.namespace.QName("", "return"));
        oper.setStyle(org.apache.axis.enum.Style.RPC);
        oper.setUse(org.apache.axis.enum.Use.ENCODED);
        _operations[12] = oper;

        oper = new org.apache.axis.description.OperationDesc();
        oper.setName("WishlistSearchRequest");
        oper.addParameter(new javax.xml.namespace.QName("", "WishlistSearchRequest"), new javax.xml.namespace.QName("http://soap.bookshop.com", "WishlistRequest"), com.bookshop.soap.WishlistRequest.class, org.apache.axis.description.ParameterDesc.IN, false, false);
        oper.setReturnType(new javax.xml.namespace.QName("http://soap.bookshop.com", "ProductInfo"));
        oper.setReturnClass(com.bookshop.soap.ProductInfo.class);
        oper.setReturnQName(new javax.xml.namespace.QName("", "return"));
        oper.setStyle(org.apache.axis.enum.Style.RPC);
        oper.setUse(org.apache.axis.enum.Use.ENCODED);
        _operations[13] = oper;

        oper = new org.apache.axis.description.OperationDesc();
        oper.setName("SellerProfileSearchRequest");
        oper.addParameter(new javax.xml.namespace.QName("", "SellerProfileSearchRequest"), new javax.xml.namespace.QName("http://soap.bookshop.com", "SellerProfileRequest"), com.bookshop.soap.SellerProfileRequest.class, org.apache.axis.description.ParameterDesc.IN, false, false);
        oper.setReturnType(new javax.xml.namespace.QName("http://soap.bookshop.com", "SellerProfile"));
        oper.setReturnClass(com.bookshop.soap.SellerProfile.class);
        oper.setReturnQName(new javax.xml.namespace.QName("", "return"));
        oper.setStyle(org.apache.axis.enum.Style.RPC);
        oper.setUse(org.apache.axis.enum.Use.ENCODED);
        _operations[14] = oper;

        oper = new org.apache.axis.description.OperationDesc();
        oper.setName("SellerSearchRequest");
        oper.addParameter(new javax.xml.namespace.QName("", "SellerSearchRequest"), new javax.xml.namespace.QName("http://soap.bookshop.com", "SellerRequest"), com.bookshop.soap.SellerRequest.class, org.apache.axis.description.ParameterDesc.IN, false, false);
        oper.setReturnType(new javax.xml.namespace.QName("http://soap.bookshop.com", "SellerSearch"));
        oper.setReturnClass(com.bookshop.soap.SellerSearch.class);
        oper.setReturnQName(new javax.xml.namespace.QName("", "return"));
        oper.setStyle(org.apache.axis.enum.Style.RPC);
        oper.setUse(org.apache.axis.enum.Use.ENCODED);
        _operations[15] = oper;

        oper = new org.apache.axis.description.OperationDesc();
        oper.setName("MarketplaceSearchRequest");
        oper.addParameter(new javax.xml.namespace.QName("", "MarketplaceSearchRequest"), new javax.xml.namespace.QName("http://soap.bookshop.com", "MarketplaceRequest"), com.bookshop.soap.MarketplaceRequest.class, org.apache.axis.description.ParameterDesc.IN, false, false);
        oper.setReturnType(new javax.xml.namespace.QName("http://soap.bookshop.com", "MarketplaceSearch"));
        oper.setReturnClass(com.bookshop.soap.MarketplaceSearch.class);
        oper.setReturnQName(new javax.xml.namespace.QName("", "return"));
        oper.setStyle(org.apache.axis.enum.Style.RPC);
        oper.setUse(org.apache.axis.enum.Use.ENCODED);
        _operations[16] = oper;

        oper = new org.apache.axis.description.OperationDesc();
        oper.setName("SimilaritySearchRequest");
        oper.addParameter(new javax.xml.namespace.QName("", "SimilaritySearchRequest"), new javax.xml.namespace.QName("http://soap.bookshop.com", "SimilarityRequest"), com.bookshop.soap.SimilarityRequest.class, org.apache.axis.description.ParameterDesc.IN, false, false);
        oper.setReturnType(new javax.xml.namespace.QName("http://soap.bookshop.com", "ProductInfo"));
        oper.setReturnClass(com.bookshop.soap.ProductInfo.class);
        oper.setReturnQName(new javax.xml.namespace.QName("", "return"));
        oper.setStyle(org.apache.axis.enum.Style.RPC);
        oper.setUse(org.apache.axis.enum.Use.ENCODED);
        _operations[17] = oper;

        oper = new org.apache.axis.description.OperationDesc();
        oper.setName("GetShoppingCartRequest");
        oper.addParameter(new javax.xml.namespace.QName("", "GetShoppingCartRequest"), new javax.xml.namespace.QName("http://soap.bookshop.com", "GetShoppingCartRequest"), com.bookshop.soap.GetShoppingCartRequest.class, org.apache.axis.description.ParameterDesc.IN, false, false);
        oper.setReturnType(new javax.xml.namespace.QName("http://soap.bookshop.com", "ShoppingCart"));
        oper.setReturnClass(com.bookshop.soap.ShoppingCart.class);
        oper.setReturnQName(new javax.xml.namespace.QName("", "ShoppingCart"));
        oper.setStyle(org.apache.axis.enum.Style.RPC);
        oper.setUse(org.apache.axis.enum.Use.ENCODED);
        _operations[18] = oper;

        oper = new org.apache.axis.description.OperationDesc();
        oper.setName("ClearShoppingCartRequest");
        oper.addParameter(new javax.xml.namespace.QName("", "ClearShoppingCartRequest"), new javax.xml.namespace.QName("http://soap.bookshop.com", "ClearShoppingCartRequest"), com.bookshop.soap.ClearShoppingCartRequest.class, org.apache.axis.description.ParameterDesc.IN, false, false);
        oper.setReturnType(new javax.xml.namespace.QName("http://soap.bookshop.com", "ShoppingCart"));
        oper.setReturnClass(com.bookshop.soap.ShoppingCart.class);
        oper.setReturnQName(new javax.xml.namespace.QName("", "ShoppingCart"));
        oper.setStyle(org.apache.axis.enum.Style.RPC);
        oper.setUse(org.apache.axis.enum.Use.ENCODED);
        _operations[19] = oper;

        oper = new org.apache.axis.description.OperationDesc();
        oper.setName("AddShoppingCartItemsRequest");
        oper.addParameter(new javax.xml.namespace.QName("", "AddShoppingCartItemsRequest"), new javax.xml.namespace.QName("http://soap.bookshop.com", "AddShoppingCartItemsRequest"), com.bookshop.soap.AddShoppingCartItemsRequest.class, org.apache.axis.description.ParameterDesc.IN, false, false);
        oper.setReturnType(new javax.xml.namespace.QName("http://soap.bookshop.com", "ShoppingCart"));
        oper.setReturnClass(com.bookshop.soap.ShoppingCart.class);
        oper.setReturnQName(new javax.xml.namespace.QName("", "ShoppingCart"));
        oper.setStyle(org.apache.axis.enum.Style.RPC);
        oper.setUse(org.apache.axis.enum.Use.ENCODED);
        _operations[20] = oper;

        oper = new org.apache.axis.description.OperationDesc();
        oper.setName("RemoveShoppingCartItemsRequest");
        oper.addParameter(new javax.xml.namespace.QName("", "RemoveShoppingCartItemsRequest"), new javax.xml.namespace.QName("http://soap.bookshop.com", "RemoveShoppingCartItemsRequest"), com.bookshop.soap.RemoveShoppingCartItemsRequest.class, org.apache.axis.description.ParameterDesc.IN, false, false);
        oper.setReturnType(new javax.xml.namespace.QName("http://soap.bookshop.com", "ShoppingCart"));
        oper.setReturnClass(com.bookshop.soap.ShoppingCart.class);
        oper.setReturnQName(new javax.xml.namespace.QName("", "ShoppingCart"));
        oper.setStyle(org.apache.axis.enum.Style.RPC);
        oper.setUse(org.apache.axis.enum.Use.ENCODED);
        _operations[21] = oper;

        oper = new org.apache.axis.description.OperationDesc();
        oper.setName("ModifyShoppingCartItemsRequest");
        oper.addParameter(new javax.xml.namespace.QName("", "ModifyShoppingCartItemsRequest"), new javax.xml.namespace.QName("http://soap.bookshop.com", "ModifyShoppingCartItemsRequest"), com.bookshop.soap.ModifyShoppingCartItemsRequest.class, org.apache.axis.description.ParameterDesc.IN, false, false);
        oper.setReturnType(new javax.xml.namespace.QName("http://soap.bookshop.com", "ShoppingCart"));
        oper.setReturnClass(com.bookshop.soap.ShoppingCart.class);
        oper.setReturnQName(new javax.xml.namespace.QName("", "ShoppingCart"));
        oper.setStyle(org.apache.axis.enum.Style.RPC);
        oper.setUse(org.apache.axis.enum.Use.ENCODED);
        _operations[22] = oper;

    }

    public AmazonSearchBindingStub() throws org.apache.axis.AxisFault {
         this(null);
    }

    public AmazonSearchBindingStub(java.net.URL endpointURL, javax.xml.rpc.Service service) throws org.apache.axis.AxisFault {
         this(service);
         super.cachedEndpoint = endpointURL;
    }

    public AmazonSearchBindingStub(javax.xml.rpc.Service service) throws org.apache.axis.AxisFault {
        if (service == null) {
            super.service = new org.apache.axis.client.Service();
        } else {
            super.service = service;
        }
            java.lang.Class cls;
            javax.xml.namespace.QName qName;
            java.lang.Class beansf = org.apache.axis.encoding.ser.BeanSerializerFactory.class;
            java.lang.Class beandf = org.apache.axis.encoding.ser.BeanDeserializerFactory.class;
            java.lang.Class enumsf = org.apache.axis.encoding.ser.EnumSerializerFactory.class;
            java.lang.Class enumdf = org.apache.axis.encoding.ser.EnumDeserializerFactory.class;
            java.lang.Class arraysf = org.apache.axis.encoding.ser.ArraySerializerFactory.class;
            java.lang.Class arraydf = org.apache.axis.encoding.ser.ArrayDeserializerFactory.class;
            java.lang.Class simplesf = org.apache.axis.encoding.ser.SimpleSerializerFactory.class;
            java.lang.Class simpledf = org.apache.axis.encoding.ser.SimpleDeserializerFactory.class;
            qName = new javax.xml.namespace.QName("http://soap.bookshop.com", "Feedback");
            cachedSerQNames.add(qName);
            cls = com.bookshop.soap.Feedback.class;
            cachedSerClasses.add(cls);
            cachedSerFactories.add(beansf);
            cachedDeserFactories.add(beandf);

            qName = new javax.xml.namespace.QName("http://soap.bookshop.com", "KeyPhrase");
            cachedSerQNames.add(qName);
            cls = com.bookshop.soap.KeyPhrase.class;
            cachedSerClasses.add(cls);
            cachedSerFactories.add(beansf);
            cachedDeserFactories.add(beandf);

            qName = new javax.xml.namespace.QName("http://soap.bookshop.com", "Details");
            cachedSerQNames.add(qName);
            cls = com.bookshop.soap.Details.class;
            cachedSerClasses.add(cls);
            cachedSerFactories.add(beansf);
            cachedDeserFactories.add(beandf);

            qName = new javax.xml.namespace.QName("http://soap.bookshop.com", "SellerProfileRequest");
            cachedSerQNames.add(qName);
            cls = com.bookshop.soap.SellerProfileRequest.class;
            cachedSerClasses.add(cls);
            cachedSerFactories.add(beansf);
            cachedDeserFactories.add(beandf);

            qName = new javax.xml.namespace.QName("http://soap.bookshop.com", "ExchangeRequest");
            cachedSerQNames.add(qName);
            cls = com.bookshop.soap.ExchangeRequest.class;
            cachedSerClasses.add(cls);
            cachedSerFactories.add(beansf);
            cachedDeserFactories.add(beandf);

            qName = new javax.xml.namespace.QName("http://soap.bookshop.com", "AuthorRequest");
            cachedSerQNames.add(qName);
            cls = com.bookshop.soap.AuthorRequest.class;
            cachedSerClasses.add(cls);
            cachedSerFactories.add(beansf);
            cachedDeserFactories.add(beandf);

            qName = new javax.xml.namespace.QName("http://soap.bookshop.com", "UpcRequest");
            cachedSerQNames.add(qName);
            cls = com.bookshop.soap.UpcRequest.class;
            cachedSerClasses.add(cls);
            cachedSerFactories.add(beansf);
            cachedDeserFactories.add(beandf);

            qName = new javax.xml.namespace.QName("http://soap.bookshop.com", "FeedbackArray");
            cachedSerQNames.add(qName);
            cls = com.bookshop.soap.Feedback[].class;
            cachedSerClasses.add(cls);
            cachedSerFactories.add(arraysf);
            cachedDeserFactories.add(arraydf);

            qName = new javax.xml.namespace.QName("http://soap.bookshop.com", "Track");
            cachedSerQNames.add(qName);
            cls = com.bookshop.soap.Track.class;
            cachedSerClasses.add(cls);
            cachedSerFactories.add(beansf);
            cachedDeserFactories.add(beandf);

            qName = new javax.xml.namespace.QName("http://soap.bookshop.com", "ActorRequest");
            cachedSerQNames.add(qName);
            cls = com.bookshop.soap.ActorRequest.class;
            cachedSerClasses.add(cls);
            cachedSerFactories.add(beansf);
            cachedDeserFactories.add(beandf);

            qName = new javax.xml.namespace.QName("http://soap.bookshop.com", "ProductLine");
            cachedSerQNames.add(qName);
            cls = com.bookshop.soap.ProductLine.class;
            cachedSerClasses.add(cls);
            cachedSerFactories.add(beansf);
            cachedDeserFactories.add(beandf);

            qName = new javax.xml.namespace.QName("http://soap.bookshop.com", "AccessoryArray");
            cachedSerQNames.add(qName);
            cls = java.lang.String[].class;
            cachedSerClasses.add(cls);
            cachedSerFactories.add(arraysf);
            cachedDeserFactories.add(arraydf);

            qName = new javax.xml.namespace.QName("http://soap.bookshop.com", "MarketplaceSearchDetails");
            cachedSerQNames.add(qName);
            cls = com.bookshop.soap.MarketplaceSearchDetails.class;
            cachedSerClasses.add(cls);
            cachedSerFactories.add(beansf);
            cachedDeserFactories.add(beandf);

            qName = new javax.xml.namespace.QName("http://soap.bookshop.com", "DirectorArray");
            cachedSerQNames.add(qName);
            cls = java.lang.String[].class;
            cachedSerClasses.add(cls);
            cachedSerFactories.add(arraysf);
            cachedDeserFactories.add(arraydf);

            qName = new javax.xml.namespace.QName("http://soap.bookshop.com", "SellerProfile");
            cachedSerQNames.add(qName);
            cls = com.bookshop.soap.SellerProfile.class;
            cachedSerClasses.add(cls);
            cachedSerFactories.add(beansf);
            cachedDeserFactories.add(beandf);

            qName = new javax.xml.namespace.QName("http://soap.bookshop.com", "GetShoppingCartRequest");
            cachedSerQNames.add(qName);
            cls = com.bookshop.soap.GetShoppingCartRequest.class;
            cachedSerClasses.add(cls);
            cachedSerFactories.add(beansf);
            cachedDeserFactories.add(beandf);

            qName = new javax.xml.namespace.QName("http://soap.bookshop.com", "ArtistArray");
            cachedSerQNames.add(qName);
            cls = java.lang.String[].class;
            cachedSerClasses.add(cls);
            cachedSerFactories.add(arraysf);
            cachedDeserFactories.add(arraydf);

            qName = new javax.xml.namespace.QName("http://soap.bookshop.com", "Item");
            cachedSerQNames.add(qName);
            cls = com.bookshop.soap.Item.class;
            cachedSerClasses.add(cls);
            cachedSerFactories.add(beansf);
            cachedDeserFactories.add(beandf);

            qName = new javax.xml.namespace.QName("http://soap.bookshop.com", "ThirdPartyProductDetails");
            cachedSerQNames.add(qName);
            cls = com.bookshop.soap.ThirdPartyProductDetails.class;
            cachedSerClasses.add(cls);
            cachedSerFactories.add(beansf);
            cachedDeserFactories.add(beandf);

            qName = new javax.xml.namespace.QName("http://soap.bookshop.com", "ArtistRequest");
            cachedSerQNames.add(qName);
            cls = com.bookshop.soap.ArtistRequest.class;
            cachedSerClasses.add(cls);
            cachedSerFactories.add(beansf);
            cachedDeserFactories.add(beandf);

            qName = new javax.xml.namespace.QName("http://soap.bookshop.com", "ProductLineArray");
            cachedSerQNames.add(qName);
            cls = com.bookshop.soap.ProductLine[].class;
            cachedSerClasses.add(cls);
            cachedSerFactories.add(arraysf);
            cachedDeserFactories.add(arraydf);

            qName = new javax.xml.namespace.QName("http://soap.bookshop.com", "ListArray");
            cachedSerQNames.add(qName);
            cls = java.lang.String[].class;
            cachedSerClasses.add(cls);
            cachedSerFactories.add(arraysf);
            cachedDeserFactories.add(arraydf);

            qName = new javax.xml.namespace.QName("http://soap.bookshop.com", "SellerSearchDetails");
            cachedSerQNames.add(qName);
            cls = com.bookshop.soap.SellerSearchDetails.class;
            cachedSerClasses.add(cls);
            cachedSerFactories.add(beansf);
            cachedDeserFactories.add(beandf);

            qName = new javax.xml.namespace.QName("http://soap.bookshop.com", "SellerSearchDetailsArray");
            cachedSerQNames.add(qName);
            cls = com.bookshop.soap.SellerSearchDetails[].class;
            cachedSerClasses.add(cls);
            cachedSerFactories.add(arraysf);
            cachedDeserFactories.add(arraydf);

            qName = new javax.xml.namespace.QName("http://soap.bookshop.com", "KeyPhraseArray");
            cachedSerQNames.add(qName);
            cls = com.bookshop.soap.KeyPhrase[].class;
            cachedSerClasses.add(cls);
            cachedSerFactories.add(arraysf);
            cachedDeserFactories.add(arraydf);

            qName = new javax.xml.namespace.QName("http://soap.bookshop.com", "PowerRequest");
            cachedSerQNames.add(qName);
            cls = com.bookshop.soap.PowerRequest.class;
            cachedSerClasses.add(cls);
            cachedSerFactories.add(beansf);
            cachedDeserFactories.add(beandf);

            qName = new javax.xml.namespace.QName("http://soap.bookshop.com", "FeaturesArray");
            cachedSerQNames.add(qName);
            cls = java.lang.String[].class;
            cachedSerClasses.add(cls);
            cachedSerFactories.add(arraysf);
            cachedDeserFactories.add(arraydf);

            qName = new javax.xml.namespace.QName("http://soap.bookshop.com", "CustomerReviewArray");
            cachedSerQNames.add(qName);
            cls = com.bookshop.soap.CustomerReview[].class;
            cachedSerClasses.add(cls);
            cachedSerFactories.add(arraysf);
            cachedDeserFactories.add(arraydf);

            qName = new javax.xml.namespace.QName("http://soap.bookshop.com", "ListingProductDetailsArray");
            cachedSerQNames.add(qName);
            cls = com.bookshop.soap.ListingProductDetails[].class;
            cachedSerClasses.add(cls);
            cachedSerFactories.add(arraysf);
            cachedDeserFactories.add(arraydf);

            qName = new javax.xml.namespace.QName("http://soap.bookshop.com", "SellerFeedback");
            cachedSerQNames.add(qName);
            cls = com.bookshop.soap.SellerFeedback.class;
            cachedSerClasses.add(cls);
            cachedSerFactories.add(beansf);
            cachedDeserFactories.add(beandf);

            qName = new javax.xml.namespace.QName("http://soap.bookshop.com", "ClearShoppingCartRequest");
            cachedSerQNames.add(qName);
            cls = com.bookshop.soap.ClearShoppingCartRequest.class;
            cachedSerClasses.add(cls);
            cachedSerFactories.add(beansf);
            cachedDeserFactories.add(beandf);

            qName = new javax.xml.namespace.QName("http://soap.bookshop.com", "BrowseNodeArray");
            cachedSerQNames.add(qName);
            cls = com.bookshop.soap.BrowseNode[].class;
            cachedSerClasses.add(cls);
            cachedSerFactories.add(arraysf);
            cachedDeserFactories.add(arraydf);

            qName = new javax.xml.namespace.QName("http://soap.bookshop.com", "CustomerReview");
            cachedSerQNames.add(qName);
            cls = com.bookshop.soap.CustomerReview.class;
            cachedSerClasses.add(cls);
            cachedSerFactories.add(beansf);
            cachedDeserFactories.add(beandf);

            qName = new javax.xml.namespace.QName("http://soap.bookshop.com", "MarketplaceRequest");
            cachedSerQNames.add(qName);
            cls = com.bookshop.soap.MarketplaceRequest.class;
            cachedSerClasses.add(cls);
            cachedSerFactories.add(beansf);
            cachedDeserFactories.add(beandf);

            qName = new javax.xml.namespace.QName("http://soap.bookshop.com", "DirectorRequest");
            cachedSerQNames.add(qName);
            cls = com.bookshop.soap.DirectorRequest.class;
            cachedSerClasses.add(cls);
            cachedSerFactories.add(beansf);
            cachedDeserFactories.add(beandf);

            qName = new javax.xml.namespace.QName("http://soap.bookshop.com", "ModifyShoppingCartItemsRequest");
            cachedSerQNames.add(qName);
            cls = com.bookshop.soap.ModifyShoppingCartItemsRequest.class;
            cachedSerClasses.add(cls);
            cachedSerFactories.add(beansf);
            cachedDeserFactories.add(beandf);

            qName = new javax.xml.namespace.QName("http://soap.bookshop.com", "SimilarProductsArray");
            cachedSerQNames.add(qName);
            cls = java.lang.String[].class;
            cachedSerClasses.add(cls);
            cachedSerFactories.add(arraysf);
            cachedDeserFactories.add(arraydf);

            qName = new javax.xml.namespace.QName("http://soap.bookshop.com", "ItemQuantityArray");
            cachedSerQNames.add(qName);
            cls = com.bookshop.soap.ItemQuantity[].class;
            cachedSerClasses.add(cls);
            cachedSerFactories.add(arraysf);
            cachedDeserFactories.add(arraydf);

            qName = new javax.xml.namespace.QName("http://soap.bookshop.com", "ItemArray");
            cachedSerQNames.add(qName);
            cls = com.bookshop.soap.Item[].class;
            cachedSerClasses.add(cls);
            cachedSerFactories.add(arraysf);
            cachedDeserFactories.add(arraydf);

            qName = new javax.xml.namespace.QName("http://soap.bookshop.com", "ListingProductInfo");
            cachedSerQNames.add(qName);
            cls = com.bookshop.soap.ListingProductInfo.class;
            cachedSerClasses.add(cls);
            cachedSerFactories.add(beansf);
            cachedDeserFactories.add(beandf);

            qName = new javax.xml.namespace.QName("http://soap.bookshop.com", "SellerProfileDetails");
            cachedSerQNames.add(qName);
            cls = com.bookshop.soap.SellerProfileDetails.class;
            cachedSerClasses.add(cls);
            cachedSerFactories.add(beansf);
            cachedDeserFactories.add(beandf);

            qName = new javax.xml.namespace.QName("http://soap.bookshop.com", "AsinRequest");
            cachedSerQNames.add(qName);
            cls = com.bookshop.soap.AsinRequest.class;
            cachedSerClasses.add(cls);
            cachedSerFactories.add(beansf);
            cachedDeserFactories.add(beandf);

            qName = new javax.xml.namespace.QName("http://soap.bookshop.com", "BrowseNodeRequest");
            cachedSerQNames.add(qName);
            cls = com.bookshop.soap.BrowseNodeRequest.class;
            cachedSerClasses.add(cls);
            cachedSerFactories.add(beansf);
            cachedDeserFactories.add(beandf);

            qName = new javax.xml.namespace.QName("http://soap.bookshop.com", "PlatformArray");
            cachedSerQNames.add(qName);
            cls = java.lang.String[].class;
            cachedSerClasses.add(cls);
            cachedSerFactories.add(arraysf);
            cachedDeserFactories.add(arraydf);

            qName = new javax.xml.namespace.QName("http://soap.bookshop.com", "SimilarityRequest");
            cachedSerQNames.add(qName);
            cls = com.bookshop.soap.SimilarityRequest.class;
            cachedSerClasses.add(cls);
            cachedSerFactories.add(beansf);
            cachedDeserFactories.add(beandf);

            qName = new javax.xml.namespace.QName("http://soap.bookshop.com", "ProductInfo");
            cachedSerQNames.add(qName);
            cls = com.bookshop.soap.ProductInfo.class;
            cachedSerClasses.add(cls);
            cachedSerFactories.add(beansf);
            cachedDeserFactories.add(beandf);

            qName = new javax.xml.namespace.QName("http://soap.bookshop.com", "DetailsArray");
            cachedSerQNames.add(qName);
            cls = com.bookshop.soap.Details[].class;
            cachedSerClasses.add(cls);
            cachedSerFactories.add(arraysf);
            cachedDeserFactories.add(arraydf);

            qName = new javax.xml.namespace.QName("http://soap.bookshop.com", "WishlistRequest");
            cachedSerQNames.add(qName);
            cls = com.bookshop.soap.WishlistRequest.class;
            cachedSerClasses.add(cls);
            cachedSerFactories.add(beansf);
            cachedDeserFactories.add(beandf);

            qName = new javax.xml.namespace.QName("http://soap.bookshop.com", "ThirdPartyProductInfo");
            cachedSerQNames.add(qName);
            cls = com.bookshop.soap.ThirdPartyProductInfo.class;
            cachedSerClasses.add(cls);
            cachedSerFactories.add(beansf);
            cachedDeserFactories.add(beandf);

            qName = new javax.xml.namespace.QName("http://soap.bookshop.com", "BrowseNode");
            cachedSerQNames.add(qName);
            cls = com.bookshop.soap.BrowseNode.class;
            cachedSerClasses.add(cls);
            cachedSerFactories.add(beansf);
            cachedDeserFactories.add(beandf);

            qName = new javax.xml.namespace.QName("http://soap.bookshop.com", "ManufacturerRequest");
            cachedSerQNames.add(qName);
            cls = com.bookshop.soap.ManufacturerRequest.class;
            cachedSerClasses.add(cls);
            cachedSerFactories.add(beansf);
            cachedDeserFactories.add(beandf);

            qName = new javax.xml.namespace.QName("http://soap.bookshop.com", "SellerSearch");
            cachedSerQNames.add(qName);
            cls = com.bookshop.soap.SellerSearch.class;
            cachedSerClasses.add(cls);
            cachedSerFactories.add(beansf);
            cachedDeserFactories.add(beandf);

            qName = new javax.xml.namespace.QName("http://soap.bookshop.com", "AuthorArray");
            cachedSerQNames.add(qName);
            cls = java.lang.String[].class;
            cachedSerClasses.add(cls);
            cachedSerFactories.add(arraysf);
            cachedDeserFactories.add(arraydf);

            qName = new javax.xml.namespace.QName("http://soap.bookshop.com", "ThirdPartyProductDetailsArray");
            cachedSerQNames.add(qName);
            cls = com.bookshop.soap.ThirdPartyProductDetails[].class;
            cachedSerClasses.add(cls);
            cachedSerFactories.add(arraysf);
            cachedDeserFactories.add(arraydf);

            qName = new javax.xml.namespace.QName("http://soap.bookshop.com", "KeywordRequest");
            cachedSerQNames.add(qName);
            cls = com.bookshop.soap.KeywordRequest.class;
            cachedSerClasses.add(cls);
            cachedSerFactories.add(beansf);
            cachedDeserFactories.add(beandf);

            qName = new javax.xml.namespace.QName("http://soap.bookshop.com", "SellerProfileDetailsArray");
            cachedSerQNames.add(qName);
            cls = com.bookshop.soap.SellerProfileDetails[].class;
            cachedSerClasses.add(cls);
            cachedSerFactories.add(arraysf);
            cachedDeserFactories.add(arraydf);

            qName = new javax.xml.namespace.QName("http://soap.bookshop.com", "SellerRequest");
            cachedSerQNames.add(qName);
            cls = com.bookshop.soap.SellerRequest.class;
            cachedSerClasses.add(cls);
            cachedSerFactories.add(beansf);
            cachedDeserFactories.add(beandf);

            qName = new javax.xml.namespace.QName("http://soap.bookshop.com", "Reviews");
            cachedSerQNames.add(qName);
            cls = com.bookshop.soap.Reviews.class;
            cachedSerClasses.add(cls);
            cachedSerFactories.add(beansf);
            cachedDeserFactories.add(beandf);

            qName = new javax.xml.namespace.QName("http://soap.bookshop.com", "MarketplaceSearch");
            cachedSerQNames.add(qName);
            cls = com.bookshop.soap.MarketplaceSearch.class;
            cachedSerClasses.add(cls);
            cachedSerFactories.add(beansf);
            cachedDeserFactories.add(beandf);

            qName = new javax.xml.namespace.QName("http://soap.bookshop.com", "RemoveShoppingCartItemsRequest");
            cachedSerQNames.add(qName);
            cls = com.bookshop.soap.RemoveShoppingCartItemsRequest.class;
            cachedSerClasses.add(cls);
            cachedSerFactories.add(beansf);
            cachedDeserFactories.add(beandf);

            qName = new javax.xml.namespace.QName("http://soap.bookshop.com", "AddItem");
            cachedSerQNames.add(qName);
            cls = com.bookshop.soap.AddItem.class;
            cachedSerClasses.add(cls);
            cachedSerFactories.add(beansf);
            cachedDeserFactories.add(beandf);

            qName = new javax.xml.namespace.QName("http://soap.bookshop.com", "BlendedRequest");
            cachedSerQNames.add(qName);
            cls = com.bookshop.soap.BlendedRequest.class;
            cachedSerClasses.add(cls);
            cachedSerFactories.add(beansf);
            cachedDeserFactories.add(beandf);

            qName = new javax.xml.namespace.QName("http://soap.bookshop.com", "ShoppingCart");
            cachedSerQNames.add(qName);
            cls = com.bookshop.soap.ShoppingCart.class;
            cachedSerClasses.add(cls);
            cachedSerFactories.add(beansf);
            cachedDeserFactories.add(beandf);

            qName = new javax.xml.namespace.QName("http://soap.bookshop.com", "AddShoppingCartItemsRequest");
            cachedSerQNames.add(qName);
            cls = com.bookshop.soap.AddShoppingCartItemsRequest.class;
            cachedSerClasses.add(cls);
            cachedSerFactories.add(beansf);
            cachedDeserFactories.add(beandf);

            qName = new javax.xml.namespace.QName("http://soap.bookshop.com", "ItemIdArray");
            cachedSerQNames.add(qName);
            cls = java.lang.String[].class;
            cachedSerClasses.add(cls);
            cachedSerFactories.add(arraysf);
            cachedDeserFactories.add(arraydf);

            qName = new javax.xml.namespace.QName("http://soap.bookshop.com", "MarketplaceSearchDetailsArray");
            cachedSerQNames.add(qName);
            cls = com.bookshop.soap.MarketplaceSearchDetails[].class;
            cachedSerClasses.add(cls);
            cachedSerFactories.add(arraysf);
            cachedDeserFactories.add(arraydf);

            qName = new javax.xml.namespace.QName("http://soap.bookshop.com", "TrackArray");
            cachedSerQNames.add(qName);
            cls = com.bookshop.soap.Track[].class;
            cachedSerClasses.add(cls);
            cachedSerFactories.add(arraysf);
            cachedDeserFactories.add(arraydf);

            qName = new javax.xml.namespace.QName("http://soap.bookshop.com", "ListingProductDetails");
            cachedSerQNames.add(qName);
            cls = com.bookshop.soap.ListingProductDetails.class;
            cachedSerClasses.add(cls);
            cachedSerFactories.add(beansf);
            cachedDeserFactories.add(beandf);

            qName = new javax.xml.namespace.QName("http://soap.bookshop.com", "AddItemArray");
            cachedSerQNames.add(qName);
            cls = com.bookshop.soap.AddItem[].class;
            cachedSerClasses.add(cls);
            cachedSerFactories.add(arraysf);
            cachedDeserFactories.add(arraydf);

            qName = new javax.xml.namespace.QName("http://soap.bookshop.com", "StarringArray");
            cachedSerQNames.add(qName);
            cls = java.lang.String[].class;
            cachedSerClasses.add(cls);
            cachedSerFactories.add(arraysf);
            cachedDeserFactories.add(arraydf);

            qName = new javax.xml.namespace.QName("http://soap.bookshop.com", "ListManiaRequest");
            cachedSerQNames.add(qName);
            cls = com.bookshop.soap.ListManiaRequest.class;
            cachedSerClasses.add(cls);
            cachedSerFactories.add(beansf);
            cachedDeserFactories.add(beandf);

            qName = new javax.xml.namespace.QName("http://soap.bookshop.com", "ItemQuantity");
            cachedSerQNames.add(qName);
            cls = com.bookshop.soap.ItemQuantity.class;
            cachedSerClasses.add(cls);
            cachedSerFactories.add(beansf);
            cachedDeserFactories.add(beandf);

    }

    private org.apache.axis.client.Call createCall() throws java.rmi.RemoteException {
        try {
            org.apache.axis.client.Call _call =
                    (org.apache.axis.client.Call) super.service.createCall();
            if (super.maintainSessionSet) {
                _call.setMaintainSession(super.maintainSession);
            }
            if (super.cachedUsername != null) {
                _call.setUsername(super.cachedUsername);
            }
            if (super.cachedPassword != null) {
                _call.setPassword(super.cachedPassword);
            }
            if (super.cachedEndpoint != null) {
                _call.setTargetEndpointAddress(super.cachedEndpoint);
            }
            if (super.cachedTimeout != null) {
                _call.setTimeout(super.cachedTimeout);
            }
            if (super.cachedPortName != null) {
                _call.setPortName(super.cachedPortName);
            }
            java.util.Enumeration keys = super.cachedProperties.keys();
            while (keys.hasMoreElements()) {
                java.lang.String key = (java.lang.String) keys.nextElement();
                _call.setProperty(key, super.cachedProperties.get(key));
            }
            // All the type mapping information is registered
            // when the first call is made.
            // The type mapping information is actually registered in
            // the TypeMappingRegistry of the service, which
            // is the reason why registration is only needed for the first call.
            synchronized (this) {
                if (firstCall()) {
                    // must set encoding style before registering serializers
                    _call.setSOAPVersion(org.apache.axis.soap.SOAPConstants.SOAP11_CONSTANTS);
                    _call.setEncodingStyle(org.apache.axis.Constants.URI_SOAP11_ENC);
                    for (int i = 0; i < cachedSerFactories.size(); ++i) {
                        java.lang.Class cls = (java.lang.Class) cachedSerClasses.get(i);
                        javax.xml.namespace.QName qName =
                                (javax.xml.namespace.QName) cachedSerQNames.get(i);
                        java.lang.Class sf = (java.lang.Class)
                                 cachedSerFactories.get(i);
                        java.lang.Class df = (java.lang.Class)
                                 cachedDeserFactories.get(i);
                        _call.registerTypeMapping(cls, qName, sf, df, false);
                    }
                }
            }
            return _call;
        }
        catch (java.lang.Throwable t) {
            throw new org.apache.axis.AxisFault("Failure trying to get the Call object", t);
        }
    }

    public com.bookshop.soap.ProductInfo keywordSearchRequest(com.bookshop.soap.KeywordRequest keywordSearchRequest) throws java.rmi.RemoteException {
        if (super.cachedEndpoint == null) {
            throw new org.apache.axis.NoEndPointException();
        }
        org.apache.axis.client.Call _call = createCall();
        _call.setOperation(_operations[0]);
        _call.setUseSOAPAction(true);
        _call.setSOAPActionURI("BookShop");
        _call.setSOAPVersion(org.apache.axis.soap.SOAPConstants.SOAP11_CONSTANTS);
        _call.setOperationName(new javax.xml.namespace.QName("http://soap.bookshop.com", "KeywordSearchRequest"));

        setRequestHeaders(_call);
        setAttachments(_call);
        java.lang.Object _resp = _call.invoke(new java.lang.Object[] {keywordSearchRequest});

        if (_resp instanceof java.rmi.RemoteException) {
            throw (java.rmi.RemoteException)_resp;
        }
        else {
            extractAttachments(_call);
            try {
                return (com.bookshop.soap.ProductInfo) _resp;
            } catch (java.lang.Exception _exception) {
                return (com.bookshop.soap.ProductInfo) org.apache.axis.utils.JavaUtils.convert(_resp, com.bookshop.soap.ProductInfo.class);
            }
        }
    }

    public com.bookshop.soap.ProductInfo powerSearchRequest(com.bookshop.soap.PowerRequest powerSearchRequest) throws java.rmi.RemoteException {
        if (super.cachedEndpoint == null) {
            throw new org.apache.axis.NoEndPointException();
        }
        org.apache.axis.client.Call _call = createCall();
        _call.setOperation(_operations[1]);
        _call.setUseSOAPAction(true);
        _call.setSOAPActionURI("BookShop");
        _call.setSOAPVersion(org.apache.axis.soap.SOAPConstants.SOAP11_CONSTANTS);
        _call.setOperationName(new javax.xml.namespace.QName("http://soap.bookshop.com", "PowerSearchRequest"));

        setRequestHeaders(_call);
        setAttachments(_call);
        java.lang.Object _resp = _call.invoke(new java.lang.Object[] {powerSearchRequest});

        if (_resp instanceof java.rmi.RemoteException) {
            throw (java.rmi.RemoteException)_resp;
        }
        else {
            extractAttachments(_call);
            try {
                return (com.bookshop.soap.ProductInfo) _resp;
            } catch (java.lang.Exception _exception) {
                return (com.bookshop.soap.ProductInfo) org.apache.axis.utils.JavaUtils.convert(_resp, com.bookshop.soap.ProductInfo.class);
            }
        }
    }

    public com.bookshop.soap.ProductInfo browseNodeSearchRequest(com.bookshop.soap.BrowseNodeRequest browseNodeSearchRequest) throws java.rmi.RemoteException {
        if (super.cachedEndpoint == null) {
            throw new org.apache.axis.NoEndPointException();
        }
        org.apache.axis.client.Call _call = createCall();
        _call.setOperation(_operations[2]);
        _call.setUseSOAPAction(true);
        _call.setSOAPActionURI("BookShop");
        _call.setSOAPVersion(org.apache.axis.soap.SOAPConstants.SOAP11_CONSTANTS);
        _call.setOperationName(new javax.xml.namespace.QName("http://soap.bookshop.com", "BrowseNodeSearchRequest"));

        setRequestHeaders(_call);
        setAttachments(_call);
        java.lang.Object _resp = _call.invoke(new java.lang.Object[] {browseNodeSearchRequest});

        if (_resp instanceof java.rmi.RemoteException) {
            throw (java.rmi.RemoteException)_resp;
        }
        else {
            extractAttachments(_call);
            try {
                return (com.bookshop.soap.ProductInfo) _resp;
            } catch (java.lang.Exception _exception) {
                return (com.bookshop.soap.ProductInfo) org.apache.axis.utils.JavaUtils.convert(_resp, com.bookshop.soap.ProductInfo.class);
            }
        }
    }

    public com.bookshop.soap.ProductInfo asinSearchRequest(com.bookshop.soap.AsinRequest asinSearchRequest) throws java.rmi.RemoteException {
        if (super.cachedEndpoint == null) {
            throw new org.apache.axis.NoEndPointException();
        }
        org.apache.axis.client.Call _call = createCall();
        _call.setOperation(_operations[3]);
        _call.setUseSOAPAction(true);
        _call.setSOAPActionURI("BookShop");
        _call.setSOAPVersion(org.apache.axis.soap.SOAPConstants.SOAP11_CONSTANTS);
        _call.setOperationName(new javax.xml.namespace.QName("http://soap.bookshop.com", "AsinSearchRequest"));

        setRequestHeaders(_call);
        setAttachments(_call);
        java.lang.Object _resp = _call.invoke(new java.lang.Object[] {asinSearchRequest});

        if (_resp instanceof java.rmi.RemoteException) {
            throw (java.rmi.RemoteException)_resp;
        }
        else {
            extractAttachments(_call);
            try {
                return (com.bookshop.soap.ProductInfo) _resp;
            } catch (java.lang.Exception _exception) {
                return (com.bookshop.soap.ProductInfo) org.apache.axis.utils.JavaUtils.convert(_resp, com.bookshop.soap.ProductInfo.class);
            }
        }
    }

    public com.bookshop.soap.ProductLine[] blendedSearchRequest(com.bookshop.soap.BlendedRequest blendedSearchRequest) throws java.rmi.RemoteException {
        if (super.cachedEndpoint == null) {
            throw new org.apache.axis.NoEndPointException();
        }
        org.apache.axis.client.Call _call = createCall();
        _call.setOperation(_operations[4]);
        _call.setUseSOAPAction(true);
        _call.setSOAPActionURI("BookShop");
        _call.setSOAPVersion(org.apache.axis.soap.SOAPConstants.SOAP11_CONSTANTS);
        _call.setOperationName(new javax.xml.namespace.QName("http://soap.bookshop.com", "BlendedSearchRequest"));

        setRequestHeaders(_call);
        setAttachments(_call);
        java.lang.Object _resp = _call.invoke(new java.lang.Object[] {blendedSearchRequest});

        if (_resp instanceof java.rmi.RemoteException) {
            throw (java.rmi.RemoteException)_resp;
        }
        else {
            extractAttachments(_call);
            try {
                return (com.bookshop.soap.ProductLine[]) _resp;
            } catch (java.lang.Exception _exception) {
                return (com.bookshop.soap.ProductLine[]) org.apache.axis.utils.JavaUtils.convert(_resp, com.bookshop.soap.ProductLine[].class);
            }
        }
    }

    public com.bookshop.soap.ProductInfo upcSearchRequest(com.bookshop.soap.UpcRequest upcSearchRequest) throws java.rmi.RemoteException {
        if (super.cachedEndpoint == null) {
            throw new org.apache.axis.NoEndPointException();
        }
        org.apache.axis.client.Call _call = createCall();
        _call.setOperation(_operations[5]);
        _call.setUseSOAPAction(true);
        _call.setSOAPActionURI("BookShop");
        _call.setSOAPVersion(org.apache.axis.soap.SOAPConstants.SOAP11_CONSTANTS);
        _call.setOperationName(new javax.xml.namespace.QName("http://soap.bookshop.com", "UpcSearchRequest"));

        setRequestHeaders(_call);
        setAttachments(_call);
        java.lang.Object _resp = _call.invoke(new java.lang.Object[] {upcSearchRequest});

        if (_resp instanceof java.rmi.RemoteException) {
            throw (java.rmi.RemoteException)_resp;
        }
        else {
            extractAttachments(_call);
            try {
                return (com.bookshop.soap.ProductInfo) _resp;
            } catch (java.lang.Exception _exception) {
                return (com.bookshop.soap.ProductInfo) org.apache.axis.utils.JavaUtils.convert(_resp, com.bookshop.soap.ProductInfo.class);
            }
        }
    }

    public com.bookshop.soap.ProductInfo authorSearchRequest(com.bookshop.soap.AuthorRequest authorSearchRequest) throws java.rmi.RemoteException {
        if (super.cachedEndpoint == null) {
            throw new org.apache.axis.NoEndPointException();
        }
        org.apache.axis.client.Call _call = createCall();
        _call.setOperation(_operations[6]);
        _call.setUseSOAPAction(true);
        _call.setSOAPActionURI("BookShop");
        _call.setSOAPVersion(org.apache.axis.soap.SOAPConstants.SOAP11_CONSTANTS);
        _call.setOperationName(new javax.xml.namespace.QName("http://soap.bookshop.com", "AuthorSearchRequest"));

        setRequestHeaders(_call);
        setAttachments(_call);
        java.lang.Object _resp = _call.invoke(new java.lang.Object[] {authorSearchRequest});

        if (_resp instanceof java.rmi.RemoteException) {
            throw (java.rmi.RemoteException)_resp;
        }
        else {
            extractAttachments(_call);
            try {
                return (com.bookshop.soap.ProductInfo) _resp;
            } catch (java.lang.Exception _exception) {
                return (com.bookshop.soap.ProductInfo) org.apache.axis.utils.JavaUtils.convert(_resp, com.bookshop.soap.ProductInfo.class);
            }
        }
    }

    public com.bookshop.soap.ProductInfo artistSearchRequest(com.bookshop.soap.ArtistRequest artistSearchRequest) throws java.rmi.RemoteException {
        if (super.cachedEndpoint == null) {
            throw new org.apache.axis.NoEndPointException();
        }
        org.apache.axis.client.Call _call = createCall();
        _call.setOperation(_operations[7]);
        _call.setUseSOAPAction(true);
        _call.setSOAPActionURI("BookShop");
        _call.setSOAPVersion(org.apache.axis.soap.SOAPConstants.SOAP11_CONSTANTS);
        _call.setOperationName(new javax.xml.namespace.QName("http://soap.bookshop.com", "ArtistSearchRequest"));

        setRequestHeaders(_call);
        setAttachments(_call);
        java.lang.Object _resp = _call.invoke(new java.lang.Object[] {artistSearchRequest});

        if (_resp instanceof java.rmi.RemoteException) {
            throw (java.rmi.RemoteException)_resp;
        }
        else {
            extractAttachments(_call);
            try {
                return (com.bookshop.soap.ProductInfo) _resp;
            } catch (java.lang.Exception _exception) {
                return (com.bookshop.soap.ProductInfo) org.apache.axis.utils.JavaUtils.convert(_resp, com.bookshop.soap.ProductInfo.class);
            }
        }
    }

    public com.bookshop.soap.ProductInfo actorSearchRequest(com.bookshop.soap.ActorRequest actorSearchRequest) throws java.rmi.RemoteException {
        if (super.cachedEndpoint == null) {
            throw new org.apache.axis.NoEndPointException();
        }
        org.apache.axis.client.Call _call = createCall();
        _call.setOperation(_operations[8]);
        _call.setUseSOAPAction(true);
        _call.setSOAPActionURI("BookShop");
        _call.setSOAPVersion(org.apache.axis.soap.SOAPConstants.SOAP11_CONSTANTS);
        _call.setOperationName(new javax.xml.namespace.QName("http://soap.bookshop.com", "ActorSearchRequest"));

        setRequestHeaders(_call);
        setAttachments(_call);
        java.lang.Object _resp = _call.invoke(new java.lang.Object[] {actorSearchRequest});

        if (_resp instanceof java.rmi.RemoteException) {
            throw (java.rmi.RemoteException)_resp;
        }
        else {
            extractAttachments(_call);
            try {
                return (com.bookshop.soap.ProductInfo) _resp;
            } catch (java.lang.Exception _exception) {
                return (com.bookshop.soap.ProductInfo) org.apache.axis.utils.JavaUtils.convert(_resp, com.bookshop.soap.ProductInfo.class);
            }
        }
    }

    public com.bookshop.soap.ProductInfo manufacturerSearchRequest(com.bookshop.soap.ManufacturerRequest manufacturerSearchRequest) throws java.rmi.RemoteException {
        if (super.cachedEndpoint == null) {
            throw new org.apache.axis.NoEndPointException();
        }
        org.apache.axis.client.Call _call = createCall();
        _call.setOperation(_operations[9]);
        _call.setUseSOAPAction(true);
        _call.setSOAPActionURI("BookShop");
        _call.setSOAPVersion(org.apache.axis.soap.SOAPConstants.SOAP11_CONSTANTS);
        _call.setOperationName(new javax.xml.namespace.QName("http://soap.bookshop.com", "ManufacturerSearchRequest"));

        setRequestHeaders(_call);
        setAttachments(_call);
        java.lang.Object _resp = _call.invoke(new java.lang.Object[] {manufacturerSearchRequest});

        if (_resp instanceof java.rmi.RemoteException) {
            throw (java.rmi.RemoteException)_resp;
        }
        else {
            extractAttachments(_call);
            try {
                return (com.bookshop.soap.ProductInfo) _resp;
            } catch (java.lang.Exception _exception) {
                return (com.bookshop.soap.ProductInfo) org.apache.axis.utils.JavaUtils.convert(_resp, com.bookshop.soap.ProductInfo.class);
            }
        }
    }

    public com.bookshop.soap.ProductInfo directorSearchRequest(com.bookshop.soap.DirectorRequest directorSearchRequest) throws java.rmi.RemoteException {
        if (super.cachedEndpoint == null) {
            throw new org.apache.axis.NoEndPointException();
        }
        org.apache.axis.client.Call _call = createCall();
        _call.setOperation(_operations[10]);
        _call.setUseSOAPAction(true);
        _call.setSOAPActionURI("BookShop");
        _call.setSOAPVersion(org.apache.axis.soap.SOAPConstants.SOAP11_CONSTANTS);
        _call.setOperationName(new javax.xml.namespace.QName("http://soap.bookshop.com", "DirectorSearchRequest"));

        setRequestHeaders(_call);
        setAttachments(_call);
        java.lang.Object _resp = _call.invoke(new java.lang.Object[] {directorSearchRequest});

        if (_resp instanceof java.rmi.RemoteException) {
            throw (java.rmi.RemoteException)_resp;
        }
        else {
            extractAttachments(_call);
            try {
                return (com.bookshop.soap.ProductInfo) _resp;
            } catch (java.lang.Exception _exception) {
                return (com.bookshop.soap.ProductInfo) org.apache.axis.utils.JavaUtils.convert(_resp, com.bookshop.soap.ProductInfo.class);
            }
        }
    }

    public com.bookshop.soap.ListingProductDetails exchangeSearchRequest(com.bookshop.soap.ExchangeRequest exchangeSearchRequest) throws java.rmi.RemoteException {
        if (super.cachedEndpoint == null) {
            throw new org.apache.axis.NoEndPointException();
        }
        org.apache.axis.client.Call _call = createCall();
        _call.setOperation(_operations[11]);
        _call.setUseSOAPAction(true);
        _call.setSOAPActionURI("BookShop");
        _call.setSOAPVersion(org.apache.axis.soap.SOAPConstants.SOAP11_CONSTANTS);
        _call.setOperationName(new javax.xml.namespace.QName("http://soap.bookshop.com", "ExchangeSearchRequest"));

        setRequestHeaders(_call);
        setAttachments(_call);
        java.lang.Object _resp = _call.invoke(new java.lang.Object[] {exchangeSearchRequest});

        if (_resp instanceof java.rmi.RemoteException) {
            throw (java.rmi.RemoteException)_resp;
        }
        else {
            extractAttachments(_call);
            try {
                return (com.bookshop.soap.ListingProductDetails) _resp;
            } catch (java.lang.Exception _exception) {
                return (com.bookshop.soap.ListingProductDetails) org.apache.axis.utils.JavaUtils.convert(_resp, com.bookshop.soap.ListingProductDetails.class);
            }
        }
    }

    public com.bookshop.soap.ProductInfo listManiaSearchRequest(com.bookshop.soap.ListManiaRequest listManiaSearchRequest) throws java.rmi.RemoteException {
        if (super.cachedEndpoint == null) {
            throw new org.apache.axis.NoEndPointException();
        }
        org.apache.axis.client.Call _call = createCall();
        _call.setOperation(_operations[12]);
        _call.setUseSOAPAction(true);
        _call.setSOAPActionURI("BookShop");
        _call.setSOAPVersion(org.apache.axis.soap.SOAPConstants.SOAP11_CONSTANTS);
        _call.setOperationName(new javax.xml.namespace.QName("http://soap.bookshop.com", "ListManiaSearchRequest"));

        setRequestHeaders(_call);
        setAttachments(_call);
        java.lang.Object _resp = _call.invoke(new java.lang.Object[] {listManiaSearchRequest});

        if (_resp instanceof java.rmi.RemoteException) {
            throw (java.rmi.RemoteException)_resp;
        }
        else {
            extractAttachments(_call);
            try {
                return (com.bookshop.soap.ProductInfo) _resp;
            } catch (java.lang.Exception _exception) {
                return (com.bookshop.soap.ProductInfo) org.apache.axis.utils.JavaUtils.convert(_resp, com.bookshop.soap.ProductInfo.class);
            }
        }
    }

    public com.bookshop.soap.ProductInfo wishlistSearchRequest(com.bookshop.soap.WishlistRequest wishlistSearchRequest) throws java.rmi.RemoteException {
        if (super.cachedEndpoint == null) {
            throw new org.apache.axis.NoEndPointException();
        }
        org.apache.axis.client.Call _call = createCall();
        _call.setOperation(_operations[13]);
        _call.setUseSOAPAction(true);
        _call.setSOAPActionURI("BookShop");
        _call.setSOAPVersion(org.apache.axis.soap.SOAPConstants.SOAP11_CONSTANTS);
        _call.setOperationName(new javax.xml.namespace.QName("http://soap.bookshop.com", "WishlistSearchRequest"));

        setRequestHeaders(_call);
        setAttachments(_call);
        java.lang.Object _resp = _call.invoke(new java.lang.Object[] {wishlistSearchRequest});

        if (_resp instanceof java.rmi.RemoteException) {
            throw (java.rmi.RemoteException)_resp;
        }
        else {
            extractAttachments(_call);
            try {
                return (com.bookshop.soap.ProductInfo) _resp;
            } catch (java.lang.Exception _exception) {
                return (com.bookshop.soap.ProductInfo) org.apache.axis.utils.JavaUtils.convert(_resp, com.bookshop.soap.ProductInfo.class);
            }
        }
    }

    public com.bookshop.soap.SellerProfile sellerProfileSearchRequest(com.bookshop.soap.SellerProfileRequest sellerProfileSearchRequest) throws java.rmi.RemoteException {
        if (super.cachedEndpoint == null) {
            throw new org.apache.axis.NoEndPointException();
        }
        org.apache.axis.client.Call _call = createCall();
        _call.setOperation(_operations[14]);
        _call.setUseSOAPAction(true);
        _call.setSOAPActionURI("BookShop");
        _call.setSOAPVersion(org.apache.axis.soap.SOAPConstants.SOAP11_CONSTANTS);
        _call.setOperationName(new javax.xml.namespace.QName("http://soap.bookshop.com", "SellerProfileSearchRequest"));

        setRequestHeaders(_call);
        setAttachments(_call);
        java.lang.Object _resp = _call.invoke(new java.lang.Object[] {sellerProfileSearchRequest});

        if (_resp instanceof java.rmi.RemoteException) {
            throw (java.rmi.RemoteException)_resp;
        }
        else {
            extractAttachments(_call);
            try {
                return (com.bookshop.soap.SellerProfile) _resp;
            } catch (java.lang.Exception _exception) {
                return (com.bookshop.soap.SellerProfile) org.apache.axis.utils.JavaUtils.convert(_resp, com.bookshop.soap.SellerProfile.class);
            }
        }
    }

    public com.bookshop.soap.SellerSearch sellerSearchRequest(com.bookshop.soap.SellerRequest sellerSearchRequest) throws java.rmi.RemoteException {
        if (super.cachedEndpoint == null) {
            throw new org.apache.axis.NoEndPointException();
        }
        org.apache.axis.client.Call _call = createCall();
        _call.setOperation(_operations[15]);
        _call.setUseSOAPAction(true);
        _call.setSOAPActionURI("BookShop");
        _call.setSOAPVersion(org.apache.axis.soap.SOAPConstants.SOAP11_CONSTANTS);
        _call.setOperationName(new javax.xml.namespace.QName("http://soap.bookshop.com", "SellerSearchRequest"));

        setRequestHeaders(_call);
        setAttachments(_call);
        java.lang.Object _resp = _call.invoke(new java.lang.Object[] {sellerSearchRequest});

        if (_resp instanceof java.rmi.RemoteException) {
            throw (java.rmi.RemoteException)_resp;
        }
        else {
            extractAttachments(_call);
            try {
                return (com.bookshop.soap.SellerSearch) _resp;
            } catch (java.lang.Exception _exception) {
                return (com.bookshop.soap.SellerSearch) org.apache.axis.utils.JavaUtils.convert(_resp, com.bookshop.soap.SellerSearch.class);
            }
        }
    }

    public com.bookshop.soap.MarketplaceSearch marketplaceSearchRequest(com.bookshop.soap.MarketplaceRequest marketplaceSearchRequest) throws java.rmi.RemoteException {
        if (super.cachedEndpoint == null) {
            throw new org.apache.axis.NoEndPointException();
        }
        org.apache.axis.client.Call _call = createCall();
        _call.setOperation(_operations[16]);
        _call.setUseSOAPAction(true);
        _call.setSOAPActionURI("BookShop");
        _call.setSOAPVersion(org.apache.axis.soap.SOAPConstants.SOAP11_CONSTANTS);
        _call.setOperationName(new javax.xml.namespace.QName("http://soap.bookshop.com", "MarketplaceSearchRequest"));

        setRequestHeaders(_call);
        setAttachments(_call);
        java.lang.Object _resp = _call.invoke(new java.lang.Object[] {marketplaceSearchRequest});

        if (_resp instanceof java.rmi.RemoteException) {
            throw (java.rmi.RemoteException)_resp;
        }
        else {
            extractAttachments(_call);
            try {
                return (com.bookshop.soap.MarketplaceSearch) _resp;
            } catch (java.lang.Exception _exception) {
                return (com.bookshop.soap.MarketplaceSearch) org.apache.axis.utils.JavaUtils.convert(_resp, com.bookshop.soap.MarketplaceSearch.class);
            }
        }
    }

    public com.bookshop.soap.ProductInfo similaritySearchRequest(com.bookshop.soap.SimilarityRequest similaritySearchRequest) throws java.rmi.RemoteException {
        if (super.cachedEndpoint == null) {
            throw new org.apache.axis.NoEndPointException();
        }
        org.apache.axis.client.Call _call = createCall();
        _call.setOperation(_operations[17]);
        _call.setUseSOAPAction(true);
        _call.setSOAPActionURI("BookShop");
        _call.setSOAPVersion(org.apache.axis.soap.SOAPConstants.SOAP11_CONSTANTS);
        _call.setOperationName(new javax.xml.namespace.QName("http://soap.bookshop.com", "SimilaritySearchRequest"));

        setRequestHeaders(_call);
        setAttachments(_call);
        java.lang.Object _resp = _call.invoke(new java.lang.Object[] {similaritySearchRequest});

        if (_resp instanceof java.rmi.RemoteException) {
            throw (java.rmi.RemoteException)_resp;
        }
        else {
            extractAttachments(_call);
            try {
                return (com.bookshop.soap.ProductInfo) _resp;
            } catch (java.lang.Exception _exception) {
                return (com.bookshop.soap.ProductInfo) org.apache.axis.utils.JavaUtils.convert(_resp, com.bookshop.soap.ProductInfo.class);
            }
        }
    }

    public com.bookshop.soap.ShoppingCart getShoppingCartRequest(com.bookshop.soap.GetShoppingCartRequest getShoppingCartRequest) throws java.rmi.RemoteException {
        if (super.cachedEndpoint == null) {
            throw new org.apache.axis.NoEndPointException();
        }
        org.apache.axis.client.Call _call = createCall();
        _call.setOperation(_operations[18]);
        _call.setUseSOAPAction(true);
        _call.setSOAPActionURI("BookShop");
        _call.setSOAPVersion(org.apache.axis.soap.SOAPConstants.SOAP11_CONSTANTS);
        _call.setOperationName(new javax.xml.namespace.QName("http://soap.bookshop.com", "GetShoppingCartRequest"));

        setRequestHeaders(_call);
        setAttachments(_call);
        java.lang.Object _resp = _call.invoke(new java.lang.Object[] {getShoppingCartRequest});

        if (_resp instanceof java.rmi.RemoteException) {
            throw (java.rmi.RemoteException)_resp;
        }
        else {
            extractAttachments(_call);
            try {
                return (com.bookshop.soap.ShoppingCart) _resp;
            } catch (java.lang.Exception _exception) {
                return (com.bookshop.soap.ShoppingCart) org.apache.axis.utils.JavaUtils.convert(_resp, com.bookshop.soap.ShoppingCart.class);
            }
        }
    }

    public com.bookshop.soap.ShoppingCart clearShoppingCartRequest(com.bookshop.soap.ClearShoppingCartRequest clearShoppingCartRequest) throws java.rmi.RemoteException {
        if (super.cachedEndpoint == null) {
            throw new org.apache.axis.NoEndPointException();
        }
        org.apache.axis.client.Call _call = createCall();
        _call.setOperation(_operations[19]);
        _call.setUseSOAPAction(true);
        _call.setSOAPActionURI("BookShop");
        _call.setSOAPVersion(org.apache.axis.soap.SOAPConstants.SOAP11_CONSTANTS);
        _call.setOperationName(new javax.xml.namespace.QName("http://soap.bookshop.com", "ClearShoppingCartRequest"));

        setRequestHeaders(_call);
        setAttachments(_call);
        java.lang.Object _resp = _call.invoke(new java.lang.Object[] {clearShoppingCartRequest});

        if (_resp instanceof java.rmi.RemoteException) {
            throw (java.rmi.RemoteException)_resp;
        }
        else {
            extractAttachments(_call);
            try {
                return (com.bookshop.soap.ShoppingCart) _resp;
            } catch (java.lang.Exception _exception) {
                return (com.bookshop.soap.ShoppingCart) org.apache.axis.utils.JavaUtils.convert(_resp, com.bookshop.soap.ShoppingCart.class);
            }
        }
    }

    public com.bookshop.soap.ShoppingCart addShoppingCartItemsRequest(com.bookshop.soap.AddShoppingCartItemsRequest addShoppingCartItemsRequest) throws java.rmi.RemoteException {
        if (super.cachedEndpoint == null) {
            throw new org.apache.axis.NoEndPointException();
        }
        org.apache.axis.client.Call _call = createCall();
        _call.setOperation(_operations[20]);
        _call.setUseSOAPAction(true);
        _call.setSOAPActionURI("BookShop");
        _call.setSOAPVersion(org.apache.axis.soap.SOAPConstants.SOAP11_CONSTANTS);
        _call.setOperationName(new javax.xml.namespace.QName("http://soap.bookshop.com", "AddShoppingCartItemsRequest"));

        setRequestHeaders(_call);
        setAttachments(_call);
        java.lang.Object _resp = _call.invoke(new java.lang.Object[] {addShoppingCartItemsRequest});

        if (_resp instanceof java.rmi.RemoteException) {
            throw (java.rmi.RemoteException)_resp;
        }
        else {
            extractAttachments(_call);
            try {
                return (com.bookshop.soap.ShoppingCart) _resp;
            } catch (java.lang.Exception _exception) {
                return (com.bookshop.soap.ShoppingCart) org.apache.axis.utils.JavaUtils.convert(_resp, com.bookshop.soap.ShoppingCart.class);
            }
        }
    }

    public com.bookshop.soap.ShoppingCart removeShoppingCartItemsRequest(com.bookshop.soap.RemoveShoppingCartItemsRequest removeShoppingCartItemsRequest) throws java.rmi.RemoteException {
        if (super.cachedEndpoint == null) {
            throw new org.apache.axis.NoEndPointException();
        }
        org.apache.axis.client.Call _call = createCall();
        _call.setOperation(_operations[21]);
        _call.setUseSOAPAction(true);
        _call.setSOAPActionURI("BookShop");
        _call.setSOAPVersion(org.apache.axis.soap.SOAPConstants.SOAP11_CONSTANTS);
        _call.setOperationName(new javax.xml.namespace.QName("http://soap.bookshop.com", "RemoveShoppingCartItemsRequest"));

        setRequestHeaders(_call);
        setAttachments(_call);
        java.lang.Object _resp = _call.invoke(new java.lang.Object[] {removeShoppingCartItemsRequest});

        if (_resp instanceof java.rmi.RemoteException) {
            throw (java.rmi.RemoteException)_resp;
        }
        else {
            extractAttachments(_call);
            try {
                return (com.bookshop.soap.ShoppingCart) _resp;
            } catch (java.lang.Exception _exception) {
                return (com.bookshop.soap.ShoppingCart) org.apache.axis.utils.JavaUtils.convert(_resp, com.bookshop.soap.ShoppingCart.class);
            }
        }
    }

    public com.bookshop.soap.ShoppingCart modifyShoppingCartItemsRequest(com.bookshop.soap.ModifyShoppingCartItemsRequest modifyShoppingCartItemsRequest) throws java.rmi.RemoteException {
        if (super.cachedEndpoint == null) {
            throw new org.apache.axis.NoEndPointException();
        }
        org.apache.axis.client.Call _call = createCall();
        _call.setOperation(_operations[22]);
        _call.setUseSOAPAction(true);
        _call.setSOAPActionURI("BookShop");
        _call.setSOAPVersion(org.apache.axis.soap.SOAPConstants.SOAP11_CONSTANTS);
        _call.setOperationName(new javax.xml.namespace.QName("http://soap.bookshop.com", "ModifyShoppingCartItemsRequest"));

        setRequestHeaders(_call);
        setAttachments(_call);
        java.lang.Object _resp = _call.invoke(new java.lang.Object[] {modifyShoppingCartItemsRequest});

        if (_resp instanceof java.rmi.RemoteException) {
            throw (java.rmi.RemoteException)_resp;
        }
        else {
            extractAttachments(_call);
            try {
                return (com.bookshop.soap.ShoppingCart) _resp;
            } catch (java.lang.Exception _exception) {
                return (com.bookshop.soap.ShoppingCart) org.apache.axis.utils.JavaUtils.convert(_resp, com.bookshop.soap.ShoppingCart.class);
            }
        }
    }

}
