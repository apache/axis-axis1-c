/**
 * InteropTestSoapBindingStub.java
 *
 * This file was auto-generated from WSDL
 * by the Apache Axis WSDL2Java emitter.
 */

package org.soapinterop;

public class InteropTestSoapBindingStub extends org.apache.axis.client.Stub implements org.soapinterop.InteropTestPortType {
    private java.util.Vector cachedSerClasses = new java.util.Vector();
    private java.util.Vector cachedSerQNames = new java.util.Vector();
    private java.util.Vector cachedSerFactories = new java.util.Vector();
    private java.util.Vector cachedDeserFactories = new java.util.Vector();

    static org.apache.axis.description.OperationDesc [] _operations;

    static {
        _operations = new org.apache.axis.description.OperationDesc[28];
        org.apache.axis.description.OperationDesc oper;
        oper = new org.apache.axis.description.OperationDesc();
        oper.setName("echoString");
        oper.addParameter(new javax.xml.namespace.QName("", "inputString"), new javax.xml.namespace.QName("http://www.w3.org/2001/XMLSchema", "string"), java.lang.String.class, org.apache.axis.description.ParameterDesc.IN, false, false);
        oper.setReturnType(new javax.xml.namespace.QName("http://www.w3.org/2001/XMLSchema", "string"));
        oper.setReturnClass(java.lang.String.class);
        oper.setReturnQName(new javax.xml.namespace.QName("", "return"));
        oper.setStyle(org.apache.axis.enum.Style.RPC);
        oper.setUse(org.apache.axis.enum.Use.ENCODED);
        _operations[0] = oper;

        oper = new org.apache.axis.description.OperationDesc();
        oper.setName("echoStringArray");
        oper.addParameter(new javax.xml.namespace.QName("", "inputStringArray"), new javax.xml.namespace.QName("http://soapinterop.org/xsd", "ArrayOfstring"), java.lang.String[].class, org.apache.axis.description.ParameterDesc.IN, false, false);
        oper.setReturnType(new javax.xml.namespace.QName("http://soapinterop.org/xsd", "ArrayOfstring"));
        oper.setReturnClass(java.lang.String[].class);
        oper.setReturnQName(new javax.xml.namespace.QName("", "return"));
        oper.setStyle(org.apache.axis.enum.Style.RPC);
        oper.setUse(org.apache.axis.enum.Use.ENCODED);
        _operations[1] = oper;

        oper = new org.apache.axis.description.OperationDesc();
        oper.setName("echoInteger");
        oper.addParameter(new javax.xml.namespace.QName("", "inputInteger"), new javax.xml.namespace.QName("http://www.w3.org/2001/XMLSchema", "int"), int.class, org.apache.axis.description.ParameterDesc.IN, false, false);
        oper.setReturnType(new javax.xml.namespace.QName("http://www.w3.org/2001/XMLSchema", "int"));
        oper.setReturnClass(int.class);
        oper.setReturnQName(new javax.xml.namespace.QName("", "return"));
        oper.setStyle(org.apache.axis.enum.Style.RPC);
        oper.setUse(org.apache.axis.enum.Use.ENCODED);
        _operations[2] = oper;

        oper = new org.apache.axis.description.OperationDesc();
        oper.setName("echoIntegerArray");
        oper.addParameter(new javax.xml.namespace.QName("", "inputIntegerArray"), new javax.xml.namespace.QName("http://soapinterop.org/xsd", "ArrayOfint"), int[].class, org.apache.axis.description.ParameterDesc.IN, false, false);
        oper.setReturnType(new javax.xml.namespace.QName("http://soapinterop.org/xsd", "ArrayOfint"));
        oper.setReturnClass(int[].class);
        oper.setReturnQName(new javax.xml.namespace.QName("", "return"));
        oper.setStyle(org.apache.axis.enum.Style.RPC);
        oper.setUse(org.apache.axis.enum.Use.ENCODED);
        _operations[3] = oper;

        oper = new org.apache.axis.description.OperationDesc();
        oper.setName("echoFloat");
        oper.addParameter(new javax.xml.namespace.QName("", "inputFloat"), new javax.xml.namespace.QName("http://www.w3.org/2001/XMLSchema", "float"), float.class, org.apache.axis.description.ParameterDesc.IN, false, false);
        oper.setReturnType(new javax.xml.namespace.QName("http://www.w3.org/2001/XMLSchema", "float"));
        oper.setReturnClass(float.class);
        oper.setReturnQName(new javax.xml.namespace.QName("", "return"));
        oper.setStyle(org.apache.axis.enum.Style.RPC);
        oper.setUse(org.apache.axis.enum.Use.ENCODED);
        _operations[4] = oper;

        oper = new org.apache.axis.description.OperationDesc();
        oper.setName("echoFloatArray");
        oper.addParameter(new javax.xml.namespace.QName("", "inputFloatArray"), new javax.xml.namespace.QName("http://soapinterop.org/xsd", "ArrayOffloat"), float[].class, org.apache.axis.description.ParameterDesc.IN, false, false);
        oper.setReturnType(new javax.xml.namespace.QName("http://soapinterop.org/xsd", "ArrayOffloat"));
        oper.setReturnClass(float[].class);
        oper.setReturnQName(new javax.xml.namespace.QName("", "return"));
        oper.setStyle(org.apache.axis.enum.Style.RPC);
        oper.setUse(org.apache.axis.enum.Use.ENCODED);
        _operations[5] = oper;

        oper = new org.apache.axis.description.OperationDesc();
        oper.setName("echoStruct");
        oper.addParameter(new javax.xml.namespace.QName("", "inputStruct"), new javax.xml.namespace.QName("http://soapinterop.org/xsd", "SOAPStruct"), org.soapinterop.xsd.SOAPStruct.class, org.apache.axis.description.ParameterDesc.IN, false, false);
        oper.setReturnType(new javax.xml.namespace.QName("http://soapinterop.org/xsd", "SOAPStruct"));
        oper.setReturnClass(org.soapinterop.xsd.SOAPStruct.class);
        oper.setReturnQName(new javax.xml.namespace.QName("", "return"));
        oper.setStyle(org.apache.axis.enum.Style.RPC);
        oper.setUse(org.apache.axis.enum.Use.ENCODED);
        _operations[6] = oper;

        oper = new org.apache.axis.description.OperationDesc();
        oper.setName("echoStructArray");
        oper.addParameter(new javax.xml.namespace.QName("", "inputStructArray"), new javax.xml.namespace.QName("http://soapinterop.org/xsd", "ArrayOfSOAPStruct"), org.soapinterop.xsd.SOAPStruct[].class, org.apache.axis.description.ParameterDesc.IN, false, false);
        oper.setReturnType(new javax.xml.namespace.QName("http://soapinterop.org/xsd", "ArrayOfSOAPStruct"));
        oper.setReturnClass(org.soapinterop.xsd.SOAPStruct[].class);
        oper.setReturnQName(new javax.xml.namespace.QName("", "return"));
        oper.setStyle(org.apache.axis.enum.Style.RPC);
        oper.setUse(org.apache.axis.enum.Use.ENCODED);
        _operations[7] = oper;

        oper = new org.apache.axis.description.OperationDesc();
        oper.setName("echoVoid");
        oper.setReturnType(org.apache.axis.encoding.XMLType.AXIS_VOID);
        oper.setStyle(org.apache.axis.enum.Style.RPC);
        oper.setUse(org.apache.axis.enum.Use.ENCODED);
        _operations[8] = oper;

        oper = new org.apache.axis.description.OperationDesc();
        oper.setName("echoBase64");
        oper.addParameter(new javax.xml.namespace.QName("", "inputBase64"), new javax.xml.namespace.QName("http://www.w3.org/2001/XMLSchema", "base64Binary"), byte[].class, org.apache.axis.description.ParameterDesc.IN, false, false);
        oper.setReturnType(new javax.xml.namespace.QName("http://www.w3.org/2001/XMLSchema", "base64Binary"));
        oper.setReturnClass(byte[].class);
        oper.setReturnQName(new javax.xml.namespace.QName("", "return"));
        oper.setStyle(org.apache.axis.enum.Style.RPC);
        oper.setUse(org.apache.axis.enum.Use.ENCODED);
        _operations[9] = oper;

        oper = new org.apache.axis.description.OperationDesc();
        oper.setName("echoHexBinary");
        oper.addParameter(new javax.xml.namespace.QName("", "inputHexBinary"), new javax.xml.namespace.QName("http://www.w3.org/2001/XMLSchema", "hexBinary"), byte[].class, org.apache.axis.description.ParameterDesc.IN, false, false);
        oper.setReturnType(new javax.xml.namespace.QName("http://www.w3.org/2001/XMLSchema", "hexBinary"));
        oper.setReturnClass(byte[].class);
        oper.setReturnQName(new javax.xml.namespace.QName("", "return"));
        oper.setStyle(org.apache.axis.enum.Style.RPC);
        oper.setUse(org.apache.axis.enum.Use.ENCODED);
        _operations[10] = oper;

        oper = new org.apache.axis.description.OperationDesc();
        oper.setName("echoDecimal");
        oper.addParameter(new javax.xml.namespace.QName("", "inputDecimal"), new javax.xml.namespace.QName("http://www.w3.org/2001/XMLSchema", "decimal"), java.math.BigDecimal.class, org.apache.axis.description.ParameterDesc.IN, false, false);
        oper.setReturnType(new javax.xml.namespace.QName("http://www.w3.org/2001/XMLSchema", "decimal"));
        oper.setReturnClass(java.math.BigDecimal.class);
        oper.setReturnQName(new javax.xml.namespace.QName("", "return"));
        oper.setStyle(org.apache.axis.enum.Style.RPC);
        oper.setUse(org.apache.axis.enum.Use.ENCODED);
        _operations[11] = oper;

        oper = new org.apache.axis.description.OperationDesc();
        oper.setName("echoBoolean");
        oper.addParameter(new javax.xml.namespace.QName("", "inputBoolean"), new javax.xml.namespace.QName("http://www.w3.org/2001/XMLSchema", "boolean"), boolean.class, org.apache.axis.description.ParameterDesc.IN, false, false);
        oper.setReturnType(new javax.xml.namespace.QName("http://www.w3.org/2001/XMLSchema", "boolean"));
        oper.setReturnClass(boolean.class);
        oper.setReturnQName(new javax.xml.namespace.QName("", "return"));
        oper.setStyle(org.apache.axis.enum.Style.RPC);
        oper.setUse(org.apache.axis.enum.Use.ENCODED);
        _operations[12] = oper;

        oper = new org.apache.axis.description.OperationDesc();
        oper.setName("echoStructAsSimpleTypes");
        oper.addParameter(new javax.xml.namespace.QName("", "inputStruct"), new javax.xml.namespace.QName("http://soapinterop.org/xsd", "SOAPStruct"), org.soapinterop.xsd.SOAPStruct.class, org.apache.axis.description.ParameterDesc.IN, false, false);
        oper.addParameter(new javax.xml.namespace.QName("", "outputString"), new javax.xml.namespace.QName("http://www.w3.org/2001/XMLSchema", "string"), java.lang.String.class, org.apache.axis.description.ParameterDesc.OUT, false, false);
        oper.addParameter(new javax.xml.namespace.QName("", "outputInteger"), new javax.xml.namespace.QName("http://www.w3.org/2001/XMLSchema", "int"), int.class, org.apache.axis.description.ParameterDesc.OUT, false, false);
        oper.addParameter(new javax.xml.namespace.QName("", "outputFloat"), new javax.xml.namespace.QName("http://www.w3.org/2001/XMLSchema", "float"), float.class, org.apache.axis.description.ParameterDesc.OUT, false, false);
        oper.setReturnType(org.apache.axis.encoding.XMLType.AXIS_VOID);
        oper.setStyle(org.apache.axis.enum.Style.RPC);
        oper.setUse(org.apache.axis.enum.Use.ENCODED);
        _operations[13] = oper;

        oper = new org.apache.axis.description.OperationDesc();
        oper.setName("echoSimpleTypesAsStruct");
        oper.addParameter(new javax.xml.namespace.QName("", "inputString"), new javax.xml.namespace.QName("http://www.w3.org/2001/XMLSchema", "string"), java.lang.String.class, org.apache.axis.description.ParameterDesc.IN, false, false);
        oper.addParameter(new javax.xml.namespace.QName("", "inputInteger"), new javax.xml.namespace.QName("http://www.w3.org/2001/XMLSchema", "int"), int.class, org.apache.axis.description.ParameterDesc.IN, false, false);
        oper.addParameter(new javax.xml.namespace.QName("", "inputFloat"), new javax.xml.namespace.QName("http://www.w3.org/2001/XMLSchema", "float"), float.class, org.apache.axis.description.ParameterDesc.IN, false, false);
        oper.setReturnType(new javax.xml.namespace.QName("http://soapinterop.org/xsd", "SOAPStruct"));
        oper.setReturnClass(org.soapinterop.xsd.SOAPStruct.class);
        oper.setReturnQName(new javax.xml.namespace.QName("", "return"));
        oper.setStyle(org.apache.axis.enum.Style.RPC);
        oper.setUse(org.apache.axis.enum.Use.ENCODED);
        _operations[14] = oper;

        oper = new org.apache.axis.description.OperationDesc();
        oper.setName("echo2DStringArray");
        oper.addParameter(new javax.xml.namespace.QName("", "input2DStringArray"), new javax.xml.namespace.QName("http://soapinterop.org/xsd", "ArrayOfString2D"), java.lang.String[][].class, org.apache.axis.description.ParameterDesc.IN, false, false);
        oper.setReturnType(new javax.xml.namespace.QName("http://soapinterop.org/xsd", "ArrayOfString2D"));
        oper.setReturnClass(java.lang.String[][].class);
        oper.setReturnQName(new javax.xml.namespace.QName("", "return"));
        oper.setStyle(org.apache.axis.enum.Style.RPC);
        oper.setUse(org.apache.axis.enum.Use.ENCODED);
        _operations[15] = oper;

        oper = new org.apache.axis.description.OperationDesc();
        oper.setName("echoNestedStruct");
        oper.addParameter(new javax.xml.namespace.QName("", "inputStruct"), new javax.xml.namespace.QName("http://soapinterop.org/xsd", "SOAPStructStruct"), org.soapinterop.xsd.SOAPStructStruct.class, org.apache.axis.description.ParameterDesc.IN, false, false);
        oper.setReturnType(new javax.xml.namespace.QName("http://soapinterop.org/xsd", "SOAPStructStruct"));
        oper.setReturnClass(org.soapinterop.xsd.SOAPStructStruct.class);
        oper.setReturnQName(new javax.xml.namespace.QName("", "return"));
        oper.setStyle(org.apache.axis.enum.Style.RPC);
        oper.setUse(org.apache.axis.enum.Use.ENCODED);
        _operations[16] = oper;

        oper = new org.apache.axis.description.OperationDesc();
        oper.setName("echoNestedArray");
        oper.addParameter(new javax.xml.namespace.QName("", "inputStruct"), new javax.xml.namespace.QName("http://soapinterop.org/xsd", "SOAPArrayStruct"), org.soapinterop.xsd.SOAPArrayStruct.class, org.apache.axis.description.ParameterDesc.IN, false, false);
        oper.setReturnType(new javax.xml.namespace.QName("http://soapinterop.org/xsd", "SOAPArrayStruct"));
        oper.setReturnClass(org.soapinterop.xsd.SOAPArrayStruct.class);
        oper.setReturnQName(new javax.xml.namespace.QName("", "return"));
        oper.setStyle(org.apache.axis.enum.Style.RPC);
        oper.setUse(org.apache.axis.enum.Use.ENCODED);
        _operations[17] = oper;

        oper = new org.apache.axis.description.OperationDesc();
        oper.setName("echoToken");
        oper.addParameter(new javax.xml.namespace.QName("", "inputToken"), new javax.xml.namespace.QName("http://www.w3.org/2001/XMLSchema", "token"), org.apache.axis.types.Token.class, org.apache.axis.description.ParameterDesc.IN, false, false);
        oper.setReturnType(new javax.xml.namespace.QName("http://www.w3.org/2001/XMLSchema", "token"));
        oper.setReturnClass(org.apache.axis.types.Token.class);
        oper.setReturnQName(new javax.xml.namespace.QName("", "return"));
        oper.setStyle(org.apache.axis.enum.Style.RPC);
        oper.setUse(org.apache.axis.enum.Use.ENCODED);
        _operations[18] = oper;

        oper = new org.apache.axis.description.OperationDesc();
        oper.setName("echoNormalizedString");
        oper.addParameter(new javax.xml.namespace.QName("", "inputNormalizedString"), new javax.xml.namespace.QName("http://www.w3.org/2001/XMLSchema", "normalizedString"), org.apache.axis.types.NormalizedString.class, org.apache.axis.description.ParameterDesc.IN, false, false);
        oper.setReturnType(new javax.xml.namespace.QName("http://www.w3.org/2001/XMLSchema", "normalizedString"));
        oper.setReturnClass(org.apache.axis.types.NormalizedString.class);
        oper.setReturnQName(new javax.xml.namespace.QName("", "return"));
        oper.setStyle(org.apache.axis.enum.Style.RPC);
        oper.setUse(org.apache.axis.enum.Use.ENCODED);
        _operations[19] = oper;

        oper = new org.apache.axis.description.OperationDesc();
        oper.setName("echoUnsignedLong");
        oper.addParameter(new javax.xml.namespace.QName("", "inputUnsignedLong"), new javax.xml.namespace.QName("http://www.w3.org/2001/XMLSchema", "unsignedLong"), org.apache.axis.types.UnsignedLong.class, org.apache.axis.description.ParameterDesc.IN, false, false);
        oper.setReturnType(new javax.xml.namespace.QName("http://www.w3.org/2001/XMLSchema", "unsignedLong"));
        oper.setReturnClass(org.apache.axis.types.UnsignedLong.class);
        oper.setReturnQName(new javax.xml.namespace.QName("", "return"));
        oper.setStyle(org.apache.axis.enum.Style.RPC);
        oper.setUse(org.apache.axis.enum.Use.ENCODED);
        _operations[20] = oper;

        oper = new org.apache.axis.description.OperationDesc();
        oper.setName("echoUnsignedInt");
        oper.addParameter(new javax.xml.namespace.QName("", "inputUnsignedInt"), new javax.xml.namespace.QName("http://www.w3.org/2001/XMLSchema", "unsignedInt"), org.apache.axis.types.UnsignedInt.class, org.apache.axis.description.ParameterDesc.IN, false, false);
        oper.setReturnType(new javax.xml.namespace.QName("http://www.w3.org/2001/XMLSchema", "unsignedInt"));
        oper.setReturnClass(org.apache.axis.types.UnsignedInt.class);
        oper.setReturnQName(new javax.xml.namespace.QName("", "return"));
        oper.setStyle(org.apache.axis.enum.Style.RPC);
        oper.setUse(org.apache.axis.enum.Use.ENCODED);
        _operations[21] = oper;

        oper = new org.apache.axis.description.OperationDesc();
        oper.setName("echoUnsignedShort");
        oper.addParameter(new javax.xml.namespace.QName("", "inputUnsignedShort"), new javax.xml.namespace.QName("http://www.w3.org/2001/XMLSchema", "unsignedShort"), org.apache.axis.types.UnsignedShort.class, org.apache.axis.description.ParameterDesc.IN, false, false);
        oper.setReturnType(new javax.xml.namespace.QName("http://www.w3.org/2001/XMLSchema", "unsignedShort"));
        oper.setReturnClass(org.apache.axis.types.UnsignedShort.class);
        oper.setReturnQName(new javax.xml.namespace.QName("", "return"));
        oper.setStyle(org.apache.axis.enum.Style.RPC);
        oper.setUse(org.apache.axis.enum.Use.ENCODED);
        _operations[22] = oper;

        oper = new org.apache.axis.description.OperationDesc();
        oper.setName("echoUnsignedByte");
        oper.addParameter(new javax.xml.namespace.QName("", "inputUnsignedByte"), new javax.xml.namespace.QName("http://www.w3.org/2001/XMLSchema", "unsignedByte"), org.apache.axis.types.UnsignedByte.class, org.apache.axis.description.ParameterDesc.IN, false, false);
        oper.setReturnType(new javax.xml.namespace.QName("http://www.w3.org/2001/XMLSchema", "unsignedByte"));
        oper.setReturnClass(org.apache.axis.types.UnsignedByte.class);
        oper.setReturnQName(new javax.xml.namespace.QName("", "return"));
        oper.setStyle(org.apache.axis.enum.Style.RPC);
        oper.setUse(org.apache.axis.enum.Use.ENCODED);
        _operations[23] = oper;

        oper = new org.apache.axis.description.OperationDesc();
        oper.setName("echoNonNegativeInteger");
        oper.addParameter(new javax.xml.namespace.QName("", "inputNonNegativeInteger"), new javax.xml.namespace.QName("http://www.w3.org/2001/XMLSchema", "nonNegativeInteger"), org.apache.axis.types.NonNegativeInteger.class, org.apache.axis.description.ParameterDesc.IN, false, false);
        oper.setReturnType(new javax.xml.namespace.QName("http://www.w3.org/2001/XMLSchema", "nonNegativeInteger"));
        oper.setReturnClass(org.apache.axis.types.NonNegativeInteger.class);
        oper.setReturnQName(new javax.xml.namespace.QName("", "return"));
        oper.setStyle(org.apache.axis.enum.Style.RPC);
        oper.setUse(org.apache.axis.enum.Use.ENCODED);
        _operations[24] = oper;

        oper = new org.apache.axis.description.OperationDesc();
        oper.setName("echoPositiveInteger");
        oper.addParameter(new javax.xml.namespace.QName("", "inputPositiveInteger"), new javax.xml.namespace.QName("http://www.w3.org/2001/XMLSchema", "positiveInteger"), org.apache.axis.types.PositiveInteger.class, org.apache.axis.description.ParameterDesc.IN, false, false);
        oper.setReturnType(new javax.xml.namespace.QName("http://www.w3.org/2001/XMLSchema", "positiveInteger"));
        oper.setReturnClass(org.apache.axis.types.PositiveInteger.class);
        oper.setReturnQName(new javax.xml.namespace.QName("", "return"));
        oper.setStyle(org.apache.axis.enum.Style.RPC);
        oper.setUse(org.apache.axis.enum.Use.ENCODED);
        _operations[25] = oper;

        oper = new org.apache.axis.description.OperationDesc();
        oper.setName("echoNonPositiveInteger");
        oper.addParameter(new javax.xml.namespace.QName("", "inputNonPositiveInteger"), new javax.xml.namespace.QName("http://www.w3.org/2001/XMLSchema", "nonPositiveInteger"), org.apache.axis.types.NonPositiveInteger.class, org.apache.axis.description.ParameterDesc.IN, false, false);
        oper.setReturnType(new javax.xml.namespace.QName("http://www.w3.org/2001/XMLSchema", "nonPositiveInteger"));
        oper.setReturnClass(org.apache.axis.types.NonPositiveInteger.class);
        oper.setReturnQName(new javax.xml.namespace.QName("", "return"));
        oper.setStyle(org.apache.axis.enum.Style.RPC);
        oper.setUse(org.apache.axis.enum.Use.ENCODED);
        _operations[26] = oper;

        oper = new org.apache.axis.description.OperationDesc();
        oper.setName("echoNegativeInteger");
        oper.addParameter(new javax.xml.namespace.QName("", "inputNegativeInteger"), new javax.xml.namespace.QName("http://www.w3.org/2001/XMLSchema", "negativeInteger"), org.apache.axis.types.NegativeInteger.class, org.apache.axis.description.ParameterDesc.IN, false, false);
        oper.setReturnType(new javax.xml.namespace.QName("http://www.w3.org/2001/XMLSchema", "negativeInteger"));
        oper.setReturnClass(org.apache.axis.types.NegativeInteger.class);
        oper.setReturnQName(new javax.xml.namespace.QName("", "return"));
        oper.setStyle(org.apache.axis.enum.Style.RPC);
        oper.setUse(org.apache.axis.enum.Use.ENCODED);
        _operations[27] = oper;

    }

    public InteropTestSoapBindingStub() throws org.apache.axis.AxisFault {
         this(null);
    }

    public InteropTestSoapBindingStub(java.net.URL endpointURL, javax.xml.rpc.Service service) throws org.apache.axis.AxisFault {
         this(service);
         super.cachedEndpoint = endpointURL;
    }

    public InteropTestSoapBindingStub(javax.xml.rpc.Service service) throws org.apache.axis.AxisFault {
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
            qName = new javax.xml.namespace.QName("http://soapinterop.org/xsd", "ArrayOfint");
            cachedSerQNames.add(qName);
            cls = int[].class;
            cachedSerClasses.add(cls);
            cachedSerFactories.add(arraysf);
            cachedDeserFactories.add(arraydf);

            qName = new javax.xml.namespace.QName("http://soapinterop.org/xsd", "ArrayOfString2D");
            cachedSerQNames.add(qName);
            cls = java.lang.String[][].class;
            cachedSerClasses.add(cls);
            cachedSerFactories.add(arraysf);
            cachedDeserFactories.add(arraydf);

            qName = new javax.xml.namespace.QName("http://soapinterop.org/xsd", "ArrayOfSOAPStruct");
            cachedSerQNames.add(qName);
            cls = org.soapinterop.xsd.SOAPStruct[].class;
            cachedSerClasses.add(cls);
            cachedSerFactories.add(arraysf);
            cachedDeserFactories.add(arraydf);

            qName = new javax.xml.namespace.QName("http://soapinterop.org/xsd", "SOAPStructStruct");
            cachedSerQNames.add(qName);
            cls = org.soapinterop.xsd.SOAPStructStruct.class;
            cachedSerClasses.add(cls);
            cachedSerFactories.add(beansf);
            cachedDeserFactories.add(beandf);

            qName = new javax.xml.namespace.QName("http://soapinterop.org/xsd", "SOAPArrayStruct");
            cachedSerQNames.add(qName);
            cls = org.soapinterop.xsd.SOAPArrayStruct.class;
            cachedSerClasses.add(cls);
            cachedSerFactories.add(beansf);
            cachedDeserFactories.add(beandf);

            qName = new javax.xml.namespace.QName("http://soapinterop.org/xsd", "ArrayOfstring");
            cachedSerQNames.add(qName);
            cls = java.lang.String[].class;
            cachedSerClasses.add(cls);
            cachedSerFactories.add(arraysf);
            cachedDeserFactories.add(arraydf);

            qName = new javax.xml.namespace.QName("http://soapinterop.org/xsd", "ArrayOffloat");
            cachedSerQNames.add(qName);
            cls = float[].class;
            cachedSerClasses.add(cls);
            cachedSerFactories.add(arraysf);
            cachedDeserFactories.add(arraydf);

            qName = new javax.xml.namespace.QName("http://soapinterop.org/xsd", "SOAPStruct");
            cachedSerQNames.add(qName);
            cls = org.soapinterop.xsd.SOAPStruct.class;
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

    public java.lang.String echoString(java.lang.String inputString) throws java.rmi.RemoteException {
        if (super.cachedEndpoint == null) {
            throw new org.apache.axis.NoEndPointException();
        }
        org.apache.axis.client.Call _call = createCall();
        _call.setOperation(_operations[0]);
        _call.setUseSOAPAction(true);
        _call.setSOAPActionURI("InteropTests");
        _call.setSOAPVersion(org.apache.axis.soap.SOAPConstants.SOAP11_CONSTANTS);
        _call.setOperationName(new javax.xml.namespace.QName("http://soapinterop.org/", "echoString"));

        setRequestHeaders(_call);
        setAttachments(_call);
        java.lang.Object _resp = _call.invoke(new java.lang.Object[] {inputString});

        if (_resp instanceof java.rmi.RemoteException) {
            throw (java.rmi.RemoteException)_resp;
        }
        else {
            extractAttachments(_call);
            try {
                return (java.lang.String) _resp;
            } catch (java.lang.Exception _exception) {
                return (java.lang.String) org.apache.axis.utils.JavaUtils.convert(_resp, java.lang.String.class);
            }
        }
    }

    public java.lang.String[] echoStringArray(java.lang.String[] inputStringArray) throws java.rmi.RemoteException {
        if (super.cachedEndpoint == null) {
            throw new org.apache.axis.NoEndPointException();
        }
        org.apache.axis.client.Call _call = createCall();
        _call.setOperation(_operations[1]);
        _call.setUseSOAPAction(true);
        _call.setSOAPActionURI("InteropTests");
        _call.setSOAPVersion(org.apache.axis.soap.SOAPConstants.SOAP11_CONSTANTS);
        _call.setOperationName(new javax.xml.namespace.QName("http://soapinterop.org/", "echoStringArray"));

        setRequestHeaders(_call);
        setAttachments(_call);
        java.lang.Object _resp = _call.invoke(new java.lang.Object[] {inputStringArray});

        if (_resp instanceof java.rmi.RemoteException) {
            throw (java.rmi.RemoteException)_resp;
        }
        else {
            extractAttachments(_call);
            try {
                return (java.lang.String[]) _resp;
            } catch (java.lang.Exception _exception) {
                return (java.lang.String[]) org.apache.axis.utils.JavaUtils.convert(_resp, java.lang.String[].class);
            }
        }
    }

    public int echoInteger(int inputInteger) throws java.rmi.RemoteException {
        if (super.cachedEndpoint == null) {
            throw new org.apache.axis.NoEndPointException();
        }
        org.apache.axis.client.Call _call = createCall();
        _call.setOperation(_operations[2]);
        _call.setUseSOAPAction(true);
        _call.setSOAPActionURI("InteropTests");
        _call.setSOAPVersion(org.apache.axis.soap.SOAPConstants.SOAP11_CONSTANTS);
        _call.setOperationName(new javax.xml.namespace.QName("http://soapinterop.org/", "echoInteger"));

        setRequestHeaders(_call);
        setAttachments(_call);
        java.lang.Object _resp = _call.invoke(new java.lang.Object[] {new java.lang.Integer(inputInteger)});

        if (_resp instanceof java.rmi.RemoteException) {
            throw (java.rmi.RemoteException)_resp;
        }
        else {
            extractAttachments(_call);
            try {
                return ((java.lang.Integer) _resp).intValue();
            } catch (java.lang.Exception _exception) {
                return ((java.lang.Integer) org.apache.axis.utils.JavaUtils.convert(_resp, int.class)).intValue();
            }
        }
    }

    public int[] echoIntegerArray(int[] inputIntegerArray) throws java.rmi.RemoteException {
        if (super.cachedEndpoint == null) {
            throw new org.apache.axis.NoEndPointException();
        }
        org.apache.axis.client.Call _call = createCall();
        _call.setOperation(_operations[3]);
        _call.setUseSOAPAction(true);
        _call.setSOAPActionURI("InteropTests");
        _call.setSOAPVersion(org.apache.axis.soap.SOAPConstants.SOAP11_CONSTANTS);
        _call.setOperationName(new javax.xml.namespace.QName("http://soapinterop.org/", "echoIntegerArray"));

        setRequestHeaders(_call);
        setAttachments(_call);
        java.lang.Object _resp = _call.invoke(new java.lang.Object[] {inputIntegerArray});

        if (_resp instanceof java.rmi.RemoteException) {
            throw (java.rmi.RemoteException)_resp;
        }
        else {
            extractAttachments(_call);
            try {
                return (int[]) _resp;
            } catch (java.lang.Exception _exception) {
                return (int[]) org.apache.axis.utils.JavaUtils.convert(_resp, int[].class);
            }
        }
    }

    public float echoFloat(float inputFloat) throws java.rmi.RemoteException {
        if (super.cachedEndpoint == null) {
            throw new org.apache.axis.NoEndPointException();
        }
        org.apache.axis.client.Call _call = createCall();
        _call.setOperation(_operations[4]);
        _call.setUseSOAPAction(true);
        _call.setSOAPActionURI("InteropTests");
        _call.setSOAPVersion(org.apache.axis.soap.SOAPConstants.SOAP11_CONSTANTS);
        _call.setOperationName(new javax.xml.namespace.QName("http://soapinterop.org/", "echoFloat"));

        setRequestHeaders(_call);
        setAttachments(_call);
        java.lang.Object _resp = _call.invoke(new java.lang.Object[] {new java.lang.Float(inputFloat)});

        if (_resp instanceof java.rmi.RemoteException) {
            throw (java.rmi.RemoteException)_resp;
        }
        else {
            extractAttachments(_call);
            try {
                return ((java.lang.Float) _resp).floatValue();
            } catch (java.lang.Exception _exception) {
                return ((java.lang.Float) org.apache.axis.utils.JavaUtils.convert(_resp, float.class)).floatValue();
            }
        }
    }

    public float[] echoFloatArray(float[] inputFloatArray) throws java.rmi.RemoteException {
        if (super.cachedEndpoint == null) {
            throw new org.apache.axis.NoEndPointException();
        }
        org.apache.axis.client.Call _call = createCall();
        _call.setOperation(_operations[5]);
        _call.setUseSOAPAction(true);
        _call.setSOAPActionURI("InteropTests");
        _call.setSOAPVersion(org.apache.axis.soap.SOAPConstants.SOAP11_CONSTANTS);
        _call.setOperationName(new javax.xml.namespace.QName("http://soapinterop.org/", "echoFloatArray"));

        setRequestHeaders(_call);
        setAttachments(_call);
        java.lang.Object _resp = _call.invoke(new java.lang.Object[] {inputFloatArray});

        if (_resp instanceof java.rmi.RemoteException) {
            throw (java.rmi.RemoteException)_resp;
        }
        else {
            extractAttachments(_call);
            try {
                return (float[]) _resp;
            } catch (java.lang.Exception _exception) {
                return (float[]) org.apache.axis.utils.JavaUtils.convert(_resp, float[].class);
            }
        }
    }

    public org.soapinterop.xsd.SOAPStruct echoStruct(org.soapinterop.xsd.SOAPStruct inputStruct) throws java.rmi.RemoteException {
        if (super.cachedEndpoint == null) {
            throw new org.apache.axis.NoEndPointException();
        }
        org.apache.axis.client.Call _call = createCall();
        _call.setOperation(_operations[6]);
        _call.setUseSOAPAction(true);
        _call.setSOAPActionURI("InteropTests");
        _call.setSOAPVersion(org.apache.axis.soap.SOAPConstants.SOAP11_CONSTANTS);
        _call.setOperationName(new javax.xml.namespace.QName("http://soapinterop.org/", "echoStruct"));

        setRequestHeaders(_call);
        setAttachments(_call);
        java.lang.Object _resp = _call.invoke(new java.lang.Object[] {inputStruct});

        if (_resp instanceof java.rmi.RemoteException) {
            throw (java.rmi.RemoteException)_resp;
        }
        else {
            extractAttachments(_call);
            try {
                return (org.soapinterop.xsd.SOAPStruct) _resp;
            } catch (java.lang.Exception _exception) {
                return (org.soapinterop.xsd.SOAPStruct) org.apache.axis.utils.JavaUtils.convert(_resp, org.soapinterop.xsd.SOAPStruct.class);
            }
        }
    }

    public org.soapinterop.xsd.SOAPStruct[] echoStructArray(org.soapinterop.xsd.SOAPStruct[] inputStructArray) throws java.rmi.RemoteException {
        if (super.cachedEndpoint == null) {
            throw new org.apache.axis.NoEndPointException();
        }
        org.apache.axis.client.Call _call = createCall();
        _call.setOperation(_operations[7]);
        _call.setUseSOAPAction(true);
        _call.setSOAPActionURI("InteropTests");
        _call.setSOAPVersion(org.apache.axis.soap.SOAPConstants.SOAP11_CONSTANTS);
        _call.setOperationName(new javax.xml.namespace.QName("http://soapinterop.org/", "echoStructArray"));

        setRequestHeaders(_call);
        setAttachments(_call);
        java.lang.Object _resp = _call.invoke(new java.lang.Object[] {inputStructArray});

        if (_resp instanceof java.rmi.RemoteException) {
            throw (java.rmi.RemoteException)_resp;
        }
        else {
            extractAttachments(_call);
            try {
                return (org.soapinterop.xsd.SOAPStruct[]) _resp;
            } catch (java.lang.Exception _exception) {
                return (org.soapinterop.xsd.SOAPStruct[]) org.apache.axis.utils.JavaUtils.convert(_resp, org.soapinterop.xsd.SOAPStruct[].class);
            }
        }
    }

    public void echoVoid() throws java.rmi.RemoteException {
        if (super.cachedEndpoint == null) {
            throw new org.apache.axis.NoEndPointException();
        }
        org.apache.axis.client.Call _call = createCall();
        _call.setOperation(_operations[8]);
        _call.setUseSOAPAction(true);
        _call.setSOAPActionURI("InteropTests");
        _call.setSOAPVersion(org.apache.axis.soap.SOAPConstants.SOAP11_CONSTANTS);
        _call.setOperationName(new javax.xml.namespace.QName("http://soapinterop.org/", "echoVoid"));

        setRequestHeaders(_call);
        setAttachments(_call);
        java.lang.Object _resp = _call.invoke(new java.lang.Object[] {});

        if (_resp instanceof java.rmi.RemoteException) {
            throw (java.rmi.RemoteException)_resp;
        }
        extractAttachments(_call);
    }

    public byte[] echoBase64(byte[] inputBase64) throws java.rmi.RemoteException {
        if (super.cachedEndpoint == null) {
            throw new org.apache.axis.NoEndPointException();
        }
        org.apache.axis.client.Call _call = createCall();
        _call.setOperation(_operations[9]);
        _call.setUseSOAPAction(true);
        _call.setSOAPActionURI("InteropTests");
        _call.setSOAPVersion(org.apache.axis.soap.SOAPConstants.SOAP11_CONSTANTS);
        _call.setOperationName(new javax.xml.namespace.QName("http://soapinterop.org/", "echoBase64"));

        setRequestHeaders(_call);
        setAttachments(_call);
        java.lang.Object _resp = _call.invoke(new java.lang.Object[] {inputBase64});

        if (_resp instanceof java.rmi.RemoteException) {
            throw (java.rmi.RemoteException)_resp;
        }
        else {
            extractAttachments(_call);
            try {
                return (byte[]) _resp;
            } catch (java.lang.Exception _exception) {
                return (byte[]) org.apache.axis.utils.JavaUtils.convert(_resp, byte[].class);
            }
        }
    }

    public byte[] echoHexBinary(byte[] inputHexBinary) throws java.rmi.RemoteException {
        if (super.cachedEndpoint == null) {
            throw new org.apache.axis.NoEndPointException();
        }
        org.apache.axis.client.Call _call = createCall();
        _call.setOperation(_operations[10]);
        _call.setUseSOAPAction(true);
        _call.setSOAPActionURI("InteropTests");
        _call.setSOAPVersion(org.apache.axis.soap.SOAPConstants.SOAP11_CONSTANTS);
        _call.setOperationName(new javax.xml.namespace.QName("http://soapinterop.org/", "echoHexBinary"));

        setRequestHeaders(_call);
        setAttachments(_call);
        java.lang.Object _resp = _call.invoke(new java.lang.Object[] {new org.apache.axis.types.HexBinary(inputHexBinary)});

        if (_resp instanceof java.rmi.RemoteException) {
            throw (java.rmi.RemoteException)_resp;
        }
        else {
            extractAttachments(_call);
            try {
                return (byte[]) _resp;
            } catch (java.lang.Exception _exception) {
                return (byte[]) org.apache.axis.utils.JavaUtils.convert(_resp, byte[].class);
            }
        }
    }

    public java.math.BigDecimal echoDecimal(java.math.BigDecimal inputDecimal) throws java.rmi.RemoteException {
        if (super.cachedEndpoint == null) {
            throw new org.apache.axis.NoEndPointException();
        }
        org.apache.axis.client.Call _call = createCall();
        _call.setOperation(_operations[11]);
        _call.setUseSOAPAction(true);
        _call.setSOAPActionURI("InteropTests");
        _call.setSOAPVersion(org.apache.axis.soap.SOAPConstants.SOAP11_CONSTANTS);
        _call.setOperationName(new javax.xml.namespace.QName("http://soapinterop.org/", "echoDecimal"));

        setRequestHeaders(_call);
        setAttachments(_call);
        java.lang.Object _resp = _call.invoke(new java.lang.Object[] {inputDecimal});

        if (_resp instanceof java.rmi.RemoteException) {
            throw (java.rmi.RemoteException)_resp;
        }
        else {
            extractAttachments(_call);
            try {
                return (java.math.BigDecimal) _resp;
            } catch (java.lang.Exception _exception) {
                return (java.math.BigDecimal) org.apache.axis.utils.JavaUtils.convert(_resp, java.math.BigDecimal.class);
            }
        }
    }

    public boolean echoBoolean(boolean inputBoolean) throws java.rmi.RemoteException {
        if (super.cachedEndpoint == null) {
            throw new org.apache.axis.NoEndPointException();
        }
        org.apache.axis.client.Call _call = createCall();
        _call.setOperation(_operations[12]);
        _call.setUseSOAPAction(true);
        _call.setSOAPActionURI("InteropTests");
        _call.setSOAPVersion(org.apache.axis.soap.SOAPConstants.SOAP11_CONSTANTS);
        _call.setOperationName(new javax.xml.namespace.QName("http://soapinterop.org/", "echoBoolean"));

        setRequestHeaders(_call);
        setAttachments(_call);
        java.lang.Object _resp = _call.invoke(new java.lang.Object[] {new java.lang.Boolean(inputBoolean)});

        if (_resp instanceof java.rmi.RemoteException) {
            throw (java.rmi.RemoteException)_resp;
        }
        else {
            extractAttachments(_call);
            try {
                return ((java.lang.Boolean) _resp).booleanValue();
            } catch (java.lang.Exception _exception) {
                return ((java.lang.Boolean) org.apache.axis.utils.JavaUtils.convert(_resp, boolean.class)).booleanValue();
            }
        }
    }

    public void echoStructAsSimpleTypes(org.soapinterop.xsd.SOAPStruct inputStruct, javax.xml.rpc.holders.StringHolder outputString, javax.xml.rpc.holders.IntHolder outputInteger, javax.xml.rpc.holders.FloatHolder outputFloat) throws java.rmi.RemoteException {
        if (super.cachedEndpoint == null) {
            throw new org.apache.axis.NoEndPointException();
        }
        org.apache.axis.client.Call _call = createCall();
        _call.setOperation(_operations[13]);
        _call.setUseSOAPAction(true);
        _call.setSOAPActionURI("InteropTests");
        _call.setSOAPVersion(org.apache.axis.soap.SOAPConstants.SOAP11_CONSTANTS);
        _call.setOperationName(new javax.xml.namespace.QName("http://soapinterop.org/", "echoStructAsSimpleTypes"));

        setRequestHeaders(_call);
        setAttachments(_call);
        java.lang.Object _resp = _call.invoke(new java.lang.Object[] {inputStruct});

        if (_resp instanceof java.rmi.RemoteException) {
            throw (java.rmi.RemoteException)_resp;
        }
        else {
            extractAttachments(_call);
            java.util.Map _output;
            _output = _call.getOutputParams();
            try {
                outputString.value = (java.lang.String) _output.get(new javax.xml.namespace.QName("", "outputString"));
            } catch (java.lang.Exception _exception) {
                outputString.value = (java.lang.String) org.apache.axis.utils.JavaUtils.convert(_output.get(new javax.xml.namespace.QName("", "outputString")), java.lang.String.class);
            }
            try {
                outputInteger.value = ((java.lang.Integer) _output.get(new javax.xml.namespace.QName("", "outputInteger"))).intValue();
            } catch (java.lang.Exception _exception) {
                outputInteger.value = ((java.lang.Integer) org.apache.axis.utils.JavaUtils.convert(_output.get(new javax.xml.namespace.QName("", "outputInteger")), int.class)).intValue();
            }
            try {
                outputFloat.value = ((java.lang.Float) _output.get(new javax.xml.namespace.QName("", "outputFloat"))).floatValue();
            } catch (java.lang.Exception _exception) {
                outputFloat.value = ((java.lang.Float) org.apache.axis.utils.JavaUtils.convert(_output.get(new javax.xml.namespace.QName("", "outputFloat")), float.class)).floatValue();
            }
        }
    }

    public org.soapinterop.xsd.SOAPStruct echoSimpleTypesAsStruct(java.lang.String inputString, int inputInteger, float inputFloat) throws java.rmi.RemoteException {
        if (super.cachedEndpoint == null) {
            throw new org.apache.axis.NoEndPointException();
        }
        org.apache.axis.client.Call _call = createCall();
        _call.setOperation(_operations[14]);
        _call.setUseSOAPAction(true);
        _call.setSOAPActionURI("InteropTests");
        _call.setSOAPVersion(org.apache.axis.soap.SOAPConstants.SOAP11_CONSTANTS);
        _call.setOperationName(new javax.xml.namespace.QName("http://soapinterop.org/", "echoSimpleTypesAsStruct"));

        setRequestHeaders(_call);
        setAttachments(_call);
        java.lang.Object _resp = _call.invoke(new java.lang.Object[] {inputString, new java.lang.Integer(inputInteger), new java.lang.Float(inputFloat)});

        if (_resp instanceof java.rmi.RemoteException) {
            throw (java.rmi.RemoteException)_resp;
        }
        else {
            extractAttachments(_call);
            try {
                return (org.soapinterop.xsd.SOAPStruct) _resp;
            } catch (java.lang.Exception _exception) {
                return (org.soapinterop.xsd.SOAPStruct) org.apache.axis.utils.JavaUtils.convert(_resp, org.soapinterop.xsd.SOAPStruct.class);
            }
        }
    }

    public java.lang.String[][] echo2DStringArray(java.lang.String[][] input2DStringArray) throws java.rmi.RemoteException {
        if (super.cachedEndpoint == null) {
            throw new org.apache.axis.NoEndPointException();
        }
        org.apache.axis.client.Call _call = createCall();
        _call.setOperation(_operations[15]);
        _call.setUseSOAPAction(true);
        _call.setSOAPActionURI("InteropTests");
        _call.setSOAPVersion(org.apache.axis.soap.SOAPConstants.SOAP11_CONSTANTS);
        _call.setOperationName(new javax.xml.namespace.QName("http://soapinterop.org/", "echo2DStringArray"));

        setRequestHeaders(_call);
        setAttachments(_call);
        java.lang.Object _resp = _call.invoke(new java.lang.Object[] {input2DStringArray});

        if (_resp instanceof java.rmi.RemoteException) {
            throw (java.rmi.RemoteException)_resp;
        }
        else {
            extractAttachments(_call);
            try {
                return (java.lang.String[][]) _resp;
            } catch (java.lang.Exception _exception) {
                return (java.lang.String[][]) org.apache.axis.utils.JavaUtils.convert(_resp, java.lang.String[][].class);
            }
        }
    }

    public org.soapinterop.xsd.SOAPStructStruct echoNestedStruct(org.soapinterop.xsd.SOAPStructStruct inputStruct) throws java.rmi.RemoteException {
        if (super.cachedEndpoint == null) {
            throw new org.apache.axis.NoEndPointException();
        }
        org.apache.axis.client.Call _call = createCall();
        _call.setOperation(_operations[16]);
        _call.setUseSOAPAction(true);
        _call.setSOAPActionURI("InteropTests");
        _call.setSOAPVersion(org.apache.axis.soap.SOAPConstants.SOAP11_CONSTANTS);
        _call.setOperationName(new javax.xml.namespace.QName("http://soapinterop.org/", "echoNestedStruct"));

        setRequestHeaders(_call);
        setAttachments(_call);
        java.lang.Object _resp = _call.invoke(new java.lang.Object[] {inputStruct});

        if (_resp instanceof java.rmi.RemoteException) {
            throw (java.rmi.RemoteException)_resp;
        }
        else {
            extractAttachments(_call);
            try {
                return (org.soapinterop.xsd.SOAPStructStruct) _resp;
            } catch (java.lang.Exception _exception) {
                return (org.soapinterop.xsd.SOAPStructStruct) org.apache.axis.utils.JavaUtils.convert(_resp, org.soapinterop.xsd.SOAPStructStruct.class);
            }
        }
    }

    public org.soapinterop.xsd.SOAPArrayStruct echoNestedArray(org.soapinterop.xsd.SOAPArrayStruct inputStruct) throws java.rmi.RemoteException {
        if (super.cachedEndpoint == null) {
            throw new org.apache.axis.NoEndPointException();
        }
        org.apache.axis.client.Call _call = createCall();
        _call.setOperation(_operations[17]);
        _call.setUseSOAPAction(true);
        _call.setSOAPActionURI("InteropTests");
        _call.setSOAPVersion(org.apache.axis.soap.SOAPConstants.SOAP11_CONSTANTS);
        _call.setOperationName(new javax.xml.namespace.QName("http://soapinterop.org/", "echoNestedArray"));

        setRequestHeaders(_call);
        setAttachments(_call);
        java.lang.Object _resp = _call.invoke(new java.lang.Object[] {inputStruct});

        if (_resp instanceof java.rmi.RemoteException) {
            throw (java.rmi.RemoteException)_resp;
        }
        else {
            extractAttachments(_call);
            try {
                return (org.soapinterop.xsd.SOAPArrayStruct) _resp;
            } catch (java.lang.Exception _exception) {
                return (org.soapinterop.xsd.SOAPArrayStruct) org.apache.axis.utils.JavaUtils.convert(_resp, org.soapinterop.xsd.SOAPArrayStruct.class);
            }
        }
    }

    public org.apache.axis.types.Token echoToken(org.apache.axis.types.Token inputToken) throws java.rmi.RemoteException {
        if (super.cachedEndpoint == null) {
            throw new org.apache.axis.NoEndPointException();
        }
        org.apache.axis.client.Call _call = createCall();
        _call.setOperation(_operations[18]);
        _call.setUseSOAPAction(true);
        _call.setSOAPActionURI("InteropTests");
        _call.setSOAPVersion(org.apache.axis.soap.SOAPConstants.SOAP11_CONSTANTS);
        _call.setOperationName(new javax.xml.namespace.QName("http://soapinterop.org/", "echoToken"));

        setRequestHeaders(_call);
        setAttachments(_call);
        java.lang.Object _resp = _call.invoke(new java.lang.Object[] {inputToken});

        if (_resp instanceof java.rmi.RemoteException) {
            throw (java.rmi.RemoteException)_resp;
        }
        else {
            extractAttachments(_call);
            try {
                return (org.apache.axis.types.Token) _resp;
            } catch (java.lang.Exception _exception) {
                return (org.apache.axis.types.Token) org.apache.axis.utils.JavaUtils.convert(_resp, org.apache.axis.types.Token.class);
            }
        }
    }

    public org.apache.axis.types.NormalizedString echoNormalizedString(org.apache.axis.types.NormalizedString inputNormalizedString) throws java.rmi.RemoteException {
        if (super.cachedEndpoint == null) {
            throw new org.apache.axis.NoEndPointException();
        }
        org.apache.axis.client.Call _call = createCall();
        _call.setOperation(_operations[19]);
        _call.setUseSOAPAction(true);
        _call.setSOAPActionURI("InteropTests");
        _call.setSOAPVersion(org.apache.axis.soap.SOAPConstants.SOAP11_CONSTANTS);
        _call.setOperationName(new javax.xml.namespace.QName("http://soapinterop.org/", "echoNormalizedString"));

        setRequestHeaders(_call);
        setAttachments(_call);
        java.lang.Object _resp = _call.invoke(new java.lang.Object[] {inputNormalizedString});

        if (_resp instanceof java.rmi.RemoteException) {
            throw (java.rmi.RemoteException)_resp;
        }
        else {
            extractAttachments(_call);
            try {
                return (org.apache.axis.types.NormalizedString) _resp;
            } catch (java.lang.Exception _exception) {
                return (org.apache.axis.types.NormalizedString) org.apache.axis.utils.JavaUtils.convert(_resp, org.apache.axis.types.NormalizedString.class);
            }
        }
    }

    public org.apache.axis.types.UnsignedLong echoUnsignedLong(org.apache.axis.types.UnsignedLong inputUnsignedLong) throws java.rmi.RemoteException {
        if (super.cachedEndpoint == null) {
            throw new org.apache.axis.NoEndPointException();
        }
        org.apache.axis.client.Call _call = createCall();
        _call.setOperation(_operations[20]);
        _call.setUseSOAPAction(true);
        _call.setSOAPActionURI("InteropTests");
        _call.setSOAPVersion(org.apache.axis.soap.SOAPConstants.SOAP11_CONSTANTS);
        _call.setOperationName(new javax.xml.namespace.QName("http://soapinterop.org/", "echoUnsignedLong"));

        setRequestHeaders(_call);
        setAttachments(_call);
        java.lang.Object _resp = _call.invoke(new java.lang.Object[] {inputUnsignedLong});

        if (_resp instanceof java.rmi.RemoteException) {
            throw (java.rmi.RemoteException)_resp;
        }
        else {
            extractAttachments(_call);
            try {
                return (org.apache.axis.types.UnsignedLong) _resp;
            } catch (java.lang.Exception _exception) {
                return (org.apache.axis.types.UnsignedLong) org.apache.axis.utils.JavaUtils.convert(_resp, org.apache.axis.types.UnsignedLong.class);
            }
        }
    }

    public org.apache.axis.types.UnsignedInt echoUnsignedInt(org.apache.axis.types.UnsignedInt inputUnsignedInt) throws java.rmi.RemoteException {
        if (super.cachedEndpoint == null) {
            throw new org.apache.axis.NoEndPointException();
        }
        org.apache.axis.client.Call _call = createCall();
        _call.setOperation(_operations[21]);
        _call.setUseSOAPAction(true);
        _call.setSOAPActionURI("InteropTests");
        _call.setSOAPVersion(org.apache.axis.soap.SOAPConstants.SOAP11_CONSTANTS);
        _call.setOperationName(new javax.xml.namespace.QName("http://soapinterop.org/", "echoUnsignedInt"));

        setRequestHeaders(_call);
        setAttachments(_call);
        java.lang.Object _resp = _call.invoke(new java.lang.Object[] {inputUnsignedInt});

        if (_resp instanceof java.rmi.RemoteException) {
            throw (java.rmi.RemoteException)_resp;
        }
        else {
            extractAttachments(_call);
            try {
                return (org.apache.axis.types.UnsignedInt) _resp;
            } catch (java.lang.Exception _exception) {
                return (org.apache.axis.types.UnsignedInt) org.apache.axis.utils.JavaUtils.convert(_resp, org.apache.axis.types.UnsignedInt.class);
            }
        }
    }

    public org.apache.axis.types.UnsignedShort echoUnsignedShort(org.apache.axis.types.UnsignedShort inputUnsignedShort) throws java.rmi.RemoteException {
        if (super.cachedEndpoint == null) {
            throw new org.apache.axis.NoEndPointException();
        }
        org.apache.axis.client.Call _call = createCall();
        _call.setOperation(_operations[22]);
        _call.setUseSOAPAction(true);
        _call.setSOAPActionURI("InteropTests");
        _call.setSOAPVersion(org.apache.axis.soap.SOAPConstants.SOAP11_CONSTANTS);
        _call.setOperationName(new javax.xml.namespace.QName("http://soapinterop.org/", "echoUnsignedShort"));

        setRequestHeaders(_call);
        setAttachments(_call);
        java.lang.Object _resp = _call.invoke(new java.lang.Object[] {inputUnsignedShort});

        if (_resp instanceof java.rmi.RemoteException) {
            throw (java.rmi.RemoteException)_resp;
        }
        else {
            extractAttachments(_call);
            try {
                return (org.apache.axis.types.UnsignedShort) _resp;
            } catch (java.lang.Exception _exception) {
                return (org.apache.axis.types.UnsignedShort) org.apache.axis.utils.JavaUtils.convert(_resp, org.apache.axis.types.UnsignedShort.class);
            }
        }
    }

    public org.apache.axis.types.UnsignedByte echoUnsignedByte(org.apache.axis.types.UnsignedByte inputUnsignedByte) throws java.rmi.RemoteException {
        if (super.cachedEndpoint == null) {
            throw new org.apache.axis.NoEndPointException();
        }
        org.apache.axis.client.Call _call = createCall();
        _call.setOperation(_operations[23]);
        _call.setUseSOAPAction(true);
        _call.setSOAPActionURI("InteropTests");
        _call.setSOAPVersion(org.apache.axis.soap.SOAPConstants.SOAP11_CONSTANTS);
        _call.setOperationName(new javax.xml.namespace.QName("http://soapinterop.org/", "echoUnsignedByte"));

        setRequestHeaders(_call);
        setAttachments(_call);
        java.lang.Object _resp = _call.invoke(new java.lang.Object[] {inputUnsignedByte});

        if (_resp instanceof java.rmi.RemoteException) {
            throw (java.rmi.RemoteException)_resp;
        }
        else {
            extractAttachments(_call);
            try {
                return (org.apache.axis.types.UnsignedByte) _resp;
            } catch (java.lang.Exception _exception) {
                return (org.apache.axis.types.UnsignedByte) org.apache.axis.utils.JavaUtils.convert(_resp, org.apache.axis.types.UnsignedByte.class);
            }
        }
    }

    public org.apache.axis.types.NonNegativeInteger echoNonNegativeInteger(org.apache.axis.types.NonNegativeInteger inputNonNegativeInteger) throws java.rmi.RemoteException {
        if (super.cachedEndpoint == null) {
            throw new org.apache.axis.NoEndPointException();
        }
        org.apache.axis.client.Call _call = createCall();
        _call.setOperation(_operations[24]);
        _call.setUseSOAPAction(true);
        _call.setSOAPActionURI("InteropTests");
        _call.setSOAPVersion(org.apache.axis.soap.SOAPConstants.SOAP11_CONSTANTS);
        _call.setOperationName(new javax.xml.namespace.QName("http://soapinterop.org/", "echoNonNegativeInteger"));

        setRequestHeaders(_call);
        setAttachments(_call);
        java.lang.Object _resp = _call.invoke(new java.lang.Object[] {inputNonNegativeInteger});

        if (_resp instanceof java.rmi.RemoteException) {
            throw (java.rmi.RemoteException)_resp;
        }
        else {
            extractAttachments(_call);
            try {
                return (org.apache.axis.types.NonNegativeInteger) _resp;
            } catch (java.lang.Exception _exception) {
                return (org.apache.axis.types.NonNegativeInteger) org.apache.axis.utils.JavaUtils.convert(_resp, org.apache.axis.types.NonNegativeInteger.class);
            }
        }
    }

    public org.apache.axis.types.PositiveInteger echoPositiveInteger(org.apache.axis.types.PositiveInteger inputPositiveInteger) throws java.rmi.RemoteException {
        if (super.cachedEndpoint == null) {
            throw new org.apache.axis.NoEndPointException();
        }
        org.apache.axis.client.Call _call = createCall();
        _call.setOperation(_operations[25]);
        _call.setUseSOAPAction(true);
        _call.setSOAPActionURI("InteropTests");
        _call.setSOAPVersion(org.apache.axis.soap.SOAPConstants.SOAP11_CONSTANTS);
        _call.setOperationName(new javax.xml.namespace.QName("http://soapinterop.org/", "echoPositiveInteger"));

        setRequestHeaders(_call);
        setAttachments(_call);
        java.lang.Object _resp = _call.invoke(new java.lang.Object[] {inputPositiveInteger});

        if (_resp instanceof java.rmi.RemoteException) {
            throw (java.rmi.RemoteException)_resp;
        }
        else {
            extractAttachments(_call);
            try {
                return (org.apache.axis.types.PositiveInteger) _resp;
            } catch (java.lang.Exception _exception) {
                return (org.apache.axis.types.PositiveInteger) org.apache.axis.utils.JavaUtils.convert(_resp, org.apache.axis.types.PositiveInteger.class);
            }
        }
    }

    public org.apache.axis.types.NonPositiveInteger echoNonPositiveInteger(org.apache.axis.types.NonPositiveInteger inputNonPositiveInteger) throws java.rmi.RemoteException {
        if (super.cachedEndpoint == null) {
            throw new org.apache.axis.NoEndPointException();
        }
        org.apache.axis.client.Call _call = createCall();
        _call.setOperation(_operations[26]);
        _call.setUseSOAPAction(true);
        _call.setSOAPActionURI("InteropTests");
        _call.setSOAPVersion(org.apache.axis.soap.SOAPConstants.SOAP11_CONSTANTS);
        _call.setOperationName(new javax.xml.namespace.QName("http://soapinterop.org/", "echoNonPositiveInteger"));

        setRequestHeaders(_call);
        setAttachments(_call);
        java.lang.Object _resp = _call.invoke(new java.lang.Object[] {inputNonPositiveInteger});

        if (_resp instanceof java.rmi.RemoteException) {
            throw (java.rmi.RemoteException)_resp;
        }
        else {
            extractAttachments(_call);
            try {
                return (org.apache.axis.types.NonPositiveInteger) _resp;
            } catch (java.lang.Exception _exception) {
                return (org.apache.axis.types.NonPositiveInteger) org.apache.axis.utils.JavaUtils.convert(_resp, org.apache.axis.types.NonPositiveInteger.class);
            }
        }
    }

    public org.apache.axis.types.NegativeInteger echoNegativeInteger(org.apache.axis.types.NegativeInteger inputNegativeInteger) throws java.rmi.RemoteException {
        if (super.cachedEndpoint == null) {
            throw new org.apache.axis.NoEndPointException();
        }
        org.apache.axis.client.Call _call = createCall();
        _call.setOperation(_operations[27]);
        _call.setUseSOAPAction(true);
        _call.setSOAPActionURI("InteropTests");
        _call.setSOAPVersion(org.apache.axis.soap.SOAPConstants.SOAP11_CONSTANTS);
        _call.setOperationName(new javax.xml.namespace.QName("http://soapinterop.org/", "echoNegativeInteger"));

        setRequestHeaders(_call);
        setAttachments(_call);
        java.lang.Object _resp = _call.invoke(new java.lang.Object[] {inputNegativeInteger});

        if (_resp instanceof java.rmi.RemoteException) {
            throw (java.rmi.RemoteException)_resp;
        }
        else {
            extractAttachments(_call);
            try {
                return (org.apache.axis.types.NegativeInteger) _resp;
            } catch (java.lang.Exception _exception) {
                return (org.apache.axis.types.NegativeInteger) org.apache.axis.utils.JavaUtils.convert(_resp, org.apache.axis.types.NegativeInteger.class);
            }
        }
    }

}
