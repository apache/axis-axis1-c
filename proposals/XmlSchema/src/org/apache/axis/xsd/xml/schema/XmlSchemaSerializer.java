/*
 * XmlSchemaSerializer.java
 * 
 * Construct Document of given XmlSchema component
 *
 * @author  joni
 *
 * Feb 13th 2002 - Joni - First working version
 * Feb 18th 2002 - Joni - add serializer method that just return current
 *                        XmlSchema obj.
 *                        Move functions createDocument and getParts from XUtil.
 * Feb 19th 2002 - Joni - Adding namespace for xml:lang and setting 
 *                        targetNamespace xmlns to targetNamespace if not 
 *                        specified.
 * Feb 20th 2002 - Joni - Problems with include.
 * Feb 21th 2002 - Joni - Porting to using core common util
 */

package org.apache.axis.xsd.xml.schema;


import java.io.FileReader;
import java.util.Enumeration;
import java.util.ArrayList;
import java.util.Hashtable;

import org.apache.axis.xsd.xml.QualifiedName;

import org.w3c.dom.DocumentFragment;
import org.w3c.dom.Element;
import org.w3c.dom.Document;
import org.w3c.dom.NodeList;
import org.w3c.dom.NamedNodeMap;
import org.w3c.dom.Node;
import org.w3c.dom.Text;
import org.w3c.dom.Attr;

import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.ParserConfigurationException;

import org.xml.sax.InputSource;
import org.xml.sax.SAXException;


public class XmlSchemaSerializer {
    private Hashtable schema_ns;
    
    static String xsdPrefix="xs";
    public static final String xsdNamespace="http://www.w3.org/2001/XMLSchema";
    ArrayList docs;
    Element schemaElement;

    private XmlSchemaSerializer() {
		docs = new ArrayList();
		schema_ns = new Hashtable();
    }
    
    public static void main(String[] args) throws Exception{    
        XmlSchema schema = XmlSchema.read(new java.io.FileReader(
																 "E:/projects/core/xml/schema/test/serializerTestCase/"
																 +"Test8ElementRefTest.xsd"), null);
        //XmlSchemaSerializer serializer = new XmlSchemaSerializer();
        Document[] serializedSchemas = XmlSchemaSerializer.serializeSchema(schema, true);
    }
    
    
    /************************************************************************
	 * Document[]  serializeSchema(XmlSchema schemaObj, 
	 *   boolean serializeIncluded)
	 *
	 * Serialize XmlSchema object pass back the document containing a schema
	 * element as its root.
	 *
	 * Parameter:
	 * schemaObj - Schema object to serialize.
	 * serialzeIncluded - whether to serialize the included(imported) 
	 *                    schema or not. pass true for serialize all included 
	 *                    schema. 
	 *
	 * Return:
	 * Array of Documents that include/imported. 
	 ************************************************************************/
    public static Document[] serializeSchema(XmlSchema schemaObj, 
											 boolean serializeIncluded) throws XmlSchemaSerializerException{
        return new XmlSchemaSerializer().serializeSchemaElement(schemaObj, 
																serializeIncluded);
    }
    
    Document[]  serializeSchemaElement(XmlSchema schemaObj, 
									   boolean serializeIncluded) throws XmlSchemaSerializerException{
     
        XmlSchemaObjectCollection items = schemaObj.getItems();
		Document serializedSchemaDocs = null;
		try{    
			DocumentBuilderFactory docFac = DocumentBuilderFactory.newInstance();            
			docFac.setNamespaceAware(true);
			DocumentBuilder builder = docFac.newDocumentBuilder();
			serializedSchemaDocs = builder.newDocument();
		}catch( ParserConfigurationException e ){
			throw new XmlSchemaException(e.getMessage());	
		}

        Element serializedSchema;
       
		serializedSchema = setupNamespaces(serializedSchemaDocs, schemaObj);
		schemaElement = serializedSchema;
        
        if(schemaObj.targetNamespace != null){
            serializedSchema.setAttributeNS(schemaObj.SCHEMA_NS, 
											"targetNamespace",schemaObj.targetNamespace);

            Object targetNS = 
                schema_ns.get(schemaObj.targetNamespace);
            
            //if the namespace is not entered then add 
            //the targetNamespace as its
            if(targetNS == null){
                serializedSchema.setAttributeNS("http://www.w3.org/2000/xmlns/", 
												"xmlns", schemaObj.targetNamespace);
                schema_ns.put(schemaObj.targetNamespace.toString(), "");
            }
        }
        
        
        //todo: implement xml:lang, 
        if(schemaObj.attributeFormDefault != null ){ 
            String formQualified =  schemaObj.attributeFormDefault.getValue();
            
            if(!formQualified.equals("None"))
                serializedSchema.setAttributeNS(schemaObj.SCHEMA_NS, 
												"attributeFormDefault",convertString(formQualified));
        }
        
        if(schemaObj.elementFormDefault != null){
            String formQualified =  schemaObj.elementFormDefault.getValue();
            
            if(!formQualified.equals("None"))
                serializedSchema.setAttributeNS(schemaObj.SCHEMA_NS, 
												"elementFormDefault",convertString(formQualified));
        }
        
        
        if(schemaObj.annotation != null){
            Element annotation = serializeAnnotation(serializedSchemaDocs,
													 schemaObj.annotation, schemaObj);
            serializedSchema.appendChild(annotation);
        }
        if(schemaObj.id != null){
            serializedSchema.setAttributeNS(schemaObj.SCHEMA_NS, "id", 
											schemaObj.id);
        }
        if(schemaObj.blockDefault != null){
            String blockDefault = schemaObj.blockDefault.getValue();
            if(!blockDefault.equals("None")){
                blockDefault = convertString(blockDefault);
                serializedSchema.setAttributeNS(schemaObj.SCHEMA_NS, 
												"blockDefault", blockDefault);
            }
        }
        if(schemaObj.finalDefault != null){
            String finalDefault = schemaObj.finalDefault.getValue();
            if(!finalDefault.equals("None")){
                finalDefault = convertString(finalDefault);
                serializedSchema.setAttributeNS(schemaObj.SCHEMA_NS, 
												"finalDefault", finalDefault);
            }
        }
        
        if(schemaObj.version != null){
            serializedSchema.setAttributeNS(schemaObj.SCHEMA_NS, 
											"version", schemaObj.version);
        }
        
        //after serialize the schema add into documentation 
        //and add to document collection array  which at the end 
        //returned
        serializeSchemaChild(items,serializedSchema, serializedSchemaDocs, 
							 schemaObj, serializeIncluded);
    
        serializedSchemaDocs.appendChild(serializedSchema);
        docs.add(serializedSchemaDocs);

        
        Document[] serializedDocs = new Document[docs.size()];
        docs.toArray(serializedDocs);
        
        return serializedDocs;
    }
    
    private void serializeSchemaChild(XmlSchemaObjectCollection items,
									  Element serializedSchema, Document serializedSchemaDocs, 
									  XmlSchema schemaObj, boolean serializeIncluded) 
        throws XmlSchemaSerializerException{
            
        int itemsLength = items.getCount();
        /**
         * For each of the items that belong to this schema, 
         * serialize each member found.  
         * Permittable member is: element, simpleType, complexType,
         * group, attrributeGroup, Attribute, include, import and redefine.
         * if any of the member found then serialize the component.
         */
        for(int i=0;i < itemsLength ;i++){
            XmlSchemaObject obj = items.getItem(i);
            
            if(obj instanceof XmlSchemaElement){
                Element e = serializeElement(serializedSchemaDocs, 
											 (XmlSchemaElement)obj, schemaObj);
                serializedSchema.appendChild(e);
                
            }else if(obj instanceof XmlSchemaSimpleType){
                Element e = serializeSimpleType(serializedSchemaDocs, 
												(XmlSchemaSimpleType)obj, schemaObj);
                serializedSchema.appendChild(e);
            }else if(obj instanceof XmlSchemaComplexType){
                Element e = serializeComplexType(serializedSchemaDocs, 
												 (XmlSchemaComplexType)obj, schemaObj);
                serializedSchema.appendChild(e);
            }else if(obj instanceof XmlSchemaGroup){
                Element e = serializeGroup(serializedSchemaDocs,
										   (XmlSchemaGroup)obj, schemaObj);
                serializedSchema.appendChild(e);
            }else if(obj instanceof XmlSchemaAttributeGroup){
                Element e = serializeAttributeGroup(serializedSchemaDocs, 
													(XmlSchemaAttributeGroup)obj, schemaObj);
                serializedSchema.appendChild(e);
            }else if(obj instanceof XmlSchemaAttribute){
                Element e = serializeAttribute(serializedSchemaDocs, 
											   (XmlSchemaAttribute)obj, schemaObj);
                serializedSchema.appendChild(e);
            }else if(obj instanceof XmlSchemaRedefine){
                Element e = serializeRedefine(serializedSchemaDocs, 
											  (XmlSchemaRedefine)obj, schemaObj);
                serializedSchema.appendChild(e);
            }else if(obj instanceof XmlSchemaInclude ){
                Element e = serializeInclude(serializedSchemaDocs, 
											 (XmlSchemaInclude)obj, schemaObj, serializeIncluded);
                serializedSchema.appendChild(e);
            }else if(obj instanceof XmlSchemaImport){
                Element e = serializeImport(serializedSchemaDocs, 
											(XmlSchemaImport)obj, schemaObj, serializeIncluded);
                serializedSchema.appendChild(e);
            }
        }
    }
    
    /**
     * Set up <schema> namespaces appropriately and append that attr
     * into specified element
     */
    private Element setupNamespaces(Document schemaDocs, XmlSchema schemaObj){
        Enumeration prefixs = schemaObj.namespaces.keys();
        Enumeration values = schemaObj.namespaces.elements();

        /**
         * check all namespace added and register all namespace in 
         * hashtable.  When finish then set namespace to schema 
         * element appropriatelly.
         */
        for(;prefixs.hasMoreElements() && values.hasMoreElements();){
            String namespace = values.nextElement().toString();
            String prefix = prefixs.nextElement().toString();
            /*
             * if the prefix is there 
             * check whether it is an xsd schema namespace
             * set prefix and namespace to the default attribute
             * then register the prefix on hashtable
             */
            if(/*prefix.trim().length()<1 &&*/ namespace.equals(xsdNamespace)){
                xsdPrefix = prefix;
                schemaObj.schema_ns_prefix = xsdPrefix;
            }
			
            schema_ns.put(namespace, prefix);
        }
		//for schema that not set the xmlns attrib member
        if(schema_ns.get(xsdNamespace)== null){    
            schema_ns.put(xsdNamespace, xsdPrefix);
            schemaObj.schema_ns_prefix = xsdPrefix;
        }

        Element schemaEl = createNewElement(schemaDocs, "schema" , 
											schemaObj.schema_ns_prefix ,schemaObj.SCHEMA_NS);

        Enumeration keys = schema_ns.keys();

        while(keys.hasMoreElements()){
            //let it crash for null pointer because then either the schema
            //is wrong(namespace not set properly or bug in setting ns)
            String key = keys.nextElement().toString();
            String value = schema_ns.get(key).toString();
            value = (value.length()>1)? "xmlns:"+value : "xmlns";
            schemaEl.setAttributeNS("http://www.w3.org/2000/xmlns/", 
									value, key);
        }
        return schemaEl;
    }

    /************************************************************************
     * Element serializeInclude(Document doc, XmlSchemaInclude includeObj,
     *      XmlSchema schema)throws XmlSchemaSerializerException 
     *
     * set appropriate attribute as per this object attribute availability.
     * Call included schema to append to this schema document collection.
     * Then add the document created into document pool.
     *
     * Parameter:
     * doc          - Document the parent use.
     * includeObj   - XmlSchemaInclude that will be serialized.
     * schema       - Schema Document object of the parent.
     *
     * Return:
     * Element object representation of XmlSchemaInclude
     ************************************************************************/
    Element serializeInclude(Document doc, XmlSchemaInclude includeObj,
							 XmlSchema schema, boolean serializeIncluded)
        throws XmlSchemaSerializerException {
        
        Element includeEl = createNewElement(doc, "include", 
											 schema.schema_ns_prefix, schema.SCHEMA_NS);
        
        if(includeObj.schemaLocation != null){
            includeEl.setAttributeNS(schema.SCHEMA_NS, "schemaLocation", 
									 includeObj.schemaLocation);
        }
        
        if(includeObj.id != null)
            includeEl.setAttributeNS(schema.SCHEMA_NS, "id", includeObj.id);
        
        if(includeObj.annotation != null){
            Element annotation = serializeAnnotation(doc,
													 includeObj.annotation, schema);
            includeEl.appendChild(annotation);
        }

        //Get the XmlSchema obj and append that to the content
        XmlSchema includedSchemaObj = includeObj.getSchema();
        if(includedSchemaObj != null && serializeIncluded){
            XmlSchemaSerializer includeSeri = new XmlSchemaSerializer();
            includeSeri.serializeSchemaElement(includedSchemaObj, true);
            XmlSchemaObjectCollection ii = includedSchemaObj.getItems();
            Document d = (Document)includeSeri.docs.get(0);
            docs.addAll(includeSeri.docs);
        }
        
        return includeEl;
    }

    /************************************************************************
     * Element serializeImport(Document doc, XmlSchemaImport importObj,
     *      XmlSchema schema)throws XmlSchemaSerializerException 
     *
     * Add each of the attribute of XmlSchemaImport obj into import Element 
     * Then serialize schema that is included by this import.  Include the 
     * serialized schema into document pool.
     *
     * Parameter:
     * doc          - Document the parent use.
     * includeObj   - XmlSchemaInclude that will be serialized.
     * schema       - Schema Document object of the parent.
     *
     * Return:
     * Element object representation of XmlSchemaImport
     ************************************************************************/
    Element serializeImport(Document doc, XmlSchemaImport importObj, 
							XmlSchema schema, boolean serializeIncluded)
        throws XmlSchemaSerializerException {
        
        Element importEl = createNewElement(doc, "import", 
											schema.schema_ns_prefix, schema.SCHEMA_NS);

        if(importObj.namespace != null)
            importEl.setAttributeNS(schema.SCHEMA_NS, "namespace", 
									importObj.namespace);
        
        if(importObj.schemaLocation != null && !importObj.schemaLocation.trim().equals(""))
            importEl.setAttributeNS(schema.SCHEMA_NS, "schemaLocation", 
									importObj.schemaLocation);

        if(importObj.id != null)
            importEl.setAttributeNS(schema.SCHEMA_NS, "id", importObj.id);
        
        if(importObj.annotation != null){
            Element annotation = serializeAnnotation(doc, 
													 importObj.annotation, schema);
            
            importEl.appendChild(annotation);
        }

        if(importObj.schema != null&& serializeIncluded ){
            
            
            XmlSchemaSerializer importSeri = new XmlSchemaSerializer();
            importSeri.serializeSchemaElement(importObj.schema,serializeIncluded);
            docs.addAll(importSeri.docs);
        }
        
        return importEl;
    }
    
    /************************************************************************
     * Element serializeRedefine(Document doc, XmlSchemaRedefine redefineObj, 
     *      XmlSchema schema)throws XmlSchemaSerializerException  
     *
     * Add each of the attribute of XmlSchemaImport obj into import Element 
     * Then serialize schema that is included by this import.  Include the 
     * serialized schema into document pool.
     *
     * Parameter:
     * doc           - Document the parent use.
     * redefineObj   - XmlSchemaInclude that will be serialized.
     * schema        - Schema Document object of the parent.
     *
     * Return:
     * Element object representation of XmlSchemaRedefine
     ************************************************************************/
    Element serializeRedefine(Document doc, XmlSchemaRedefine redefineObj, 
							  XmlSchema schema)throws XmlSchemaSerializerException {

        Element redefine = createNewElement(doc, "redefine", 
											schema.schema_ns_prefix, schema.SCHEMA_NS);
        
        if(redefineObj.schemaLocation != null)
            redefine.setAttributeNS(schema.SCHEMA_NS, "schemaLocation", 
									redefineObj.schemaLocation);
        else
            throw new XmlSchemaSerializerException("redefine must have "
												   + "schemaLocation fields fill");

        if(redefineObj.id != null)
            redefine.setAttributeNS(schema.SCHEMA_NS, "id", redefineObj.id);
        
        if(redefineObj.annotation != null){
            Element annotation = serializeAnnotation(doc, 
													 redefineObj.annotation, schema);
            redefine.appendChild(annotation);
        }
        int itemsLength = redefineObj.items.getCount();
        for(int i=0;i<itemsLength;i++){
            XmlSchemaObject obj = redefineObj.items.getItem(i);
            if(obj instanceof XmlSchemaSimpleType){
                Element simpleType = serializeSimpleType(doc, 
														 (XmlSchemaSimpleType)obj, schema);
                redefine.appendChild(simpleType);
            }else if(obj instanceof XmlSchemaComplexType){
                Element complexType = serializeComplexType(doc, 
														   (XmlSchemaComplexType)obj, schema);
                redefine.appendChild(complexType);
            }else if(obj instanceof XmlSchemaGroupRef){
                Element groupRef = serializeGroupRef(doc, 
													 (XmlSchemaGroupRef)obj, schema);
                redefine.appendChild(groupRef);
            }else if(obj instanceof XmlSchemaGroup){
                Element group = serializeGroup(doc, 
											   (XmlSchemaGroup)obj, schema);
                redefine.appendChild(group);
            }else if(obj instanceof XmlSchemaAttributeGroup){
                Element attributeGroup = serializeAttributeGroup(doc, 
																 (XmlSchemaAttributeGroup)obj, schema);
                redefine.appendChild(attributeGroup);
            }else if(obj instanceof XmlSchemaAttributeGroupRef){
                Element attributeGroupRef = serializeAttributeGroupRef(doc, 
																	   (XmlSchemaAttributeGroupRef)obj, schema);
                redefine.appendChild(attributeGroupRef);
            }
        }
        return redefine;
    }
    
    /************************************************************************
	 * Element serializeElement(Document doc, XmlSchemaElement elementObj, 
	 *   XmlSchema schema) throws XmlSchemaSerializerException
	 *
	 * Each member of Element will be appended and pass the element
	 * created.  Element processed according to w3c Recommendation
	 * May 2 2001. 
	 *
	 * Parameter:
	 * doc           - Document the parent use.
	 * elementObj   - XmlSchemaInclude that will be serialized.
	 * schema        - Schema Document object of the parent.
	 *
	 * Return:
	 * Element object of element.
	 ************************************************************************/
    Element serializeElement(Document doc, XmlSchemaElement elementObj, 
							 XmlSchema schema) throws XmlSchemaSerializerException{
        Element serializedEl = createNewElement(doc, "element" , 
												schema.schema_ns_prefix ,schema.SCHEMA_NS);

        
        if(elementObj.refName != null){
            
            String resolvedName = resolveQualifiedName(
													   elementObj.refName, schema);
            serializedEl.setAttributeNS(schema.SCHEMA_NS, "ref", resolvedName);
        }
        
        else if(elementObj.name != null && elementObj.name.length() > 0){
            serializedEl.setAttributeNS(schema.SCHEMA_NS, "name", 
										elementObj.name);
        }
        
        if(elementObj.isAbstract)
            serializedEl.setAttributeNS(schema.SCHEMA_NS, "abstract", "true");

        String block =elementObj.block.getValue(); 
        if(!block.equals("None")){
            block = convertString(block);
            serializedEl.setAttributeNS(schema.SCHEMA_NS,"block",block);
        }
        if(elementObj.defaultValue != null)
            serializedEl.setAttributeNS(schema.SCHEMA_NS,"default",
										elementObj.defaultValue);

        String finalDerivation = elementObj.finalDerivation.getValue(); 
        if(!finalDerivation.equals("None")){
            finalDerivation = convertString(finalDerivation);
            serializedEl.setAttributeNS(schema.SCHEMA_NS,"final",
										finalDerivation);
        }
        if(elementObj.fixedValue!=null)
            serializedEl.setAttributeNS(schema.SCHEMA_NS,"fixed",
										elementObj.fixedValue);

        String formDef = elementObj.form.getValue();
        if(!formDef.equals("None")){
            formDef = convertString(formDef);
            serializedEl.setAttributeNS(schema.SCHEMA_NS,"form",formDef);
        }
        if(elementObj.id != null)
            serializedEl.setAttributeNS(schema.SCHEMA_NS,"id",elementObj.id);

        if(elementObj.maxOccurs < Long.MAX_VALUE && elementObj.maxOccurs > 1)
            serializedEl.setAttributeNS(schema.SCHEMA_NS, "maxOccurs", 
										elementObj.maxOccurs +"");
        else if(elementObj.maxOccurs == Long.MAX_VALUE)
            serializedEl.setAttributeNS(schema.SCHEMA_NS, "maxOccurs", 
										"unbounded");
        //else not serialized
        
        /*if(elementObj.minOccurs >1)
		  serializedEl.setAttributeNS(schema.SCHEMA_NS, "minOccurs", 
		  elementObj.minOccurs + "");*/
        
        //Change - SK and Ragu cos it wasnt picking up
        // minOccurs = 0
        if(elementObj.minOccurs < Long.MAX_VALUE && elementObj.minOccurs != 1)
            serializedEl.setAttributeNS(schema.SCHEMA_NS, "minOccurs", 
										elementObj.minOccurs +"");
        else if(elementObj.minOccurs == Long.MAX_VALUE)
            serializedEl.setAttributeNS(schema.SCHEMA_NS, "minOccurs", 
										"unbounded");
            
        /*
		  if(elementObj.maxOccursString != null)
		  serializedEl.setAttributeNS(schema.SCHEMA_NS, "maxOccurs", 
		  elementObj.maxOccursString);
		  else if(elementObj.maxOccurs > 1)
		  serializedEl.setAttributeNS(schema.SCHEMA_NS, "maxOccurs", 
		  elementObj.maxOccurs + "");

		  if(elementObj.minOccurs > 1)
		  serializedEl.setAttributeNS(schema.SCHEMA_NS, "minOccurs", 
		  elementObj.minOccurs + "");
		*/
        if(elementObj.substitutionGroup != null){
            String resolvedQName = resolveQualifiedName(
														elementObj.substitutionGroup, schema);
            serializedEl.setAttributeNS(schema.SCHEMA_NS, "substitutionGroup", 
										resolvedQName);
        }
        if(elementObj.schemaTypeName  != null){
            String resolvedName = resolveQualifiedName(
													   elementObj.schemaTypeName, schema);
            serializedEl.setAttributeNS(schema.SCHEMA_NS, "type", resolvedName);
        }
        if(elementObj.annotation != null){
            Element annotationEl = serializeAnnotation(doc, 
													   elementObj.annotation, schema);
            serializedEl.appendChild(annotationEl);
        }
        if(elementObj.schemaType != null){
            if(elementObj.schemaType instanceof XmlSchemaComplexType){
                Element complexType  = serializeComplexType(doc, 
															(XmlSchemaComplexType)elementObj.schemaType, schema);
                serializedEl.appendChild(complexType);
            }else if(elementObj.schemaType instanceof XmlSchemaSimpleType){
                Element simpleType  = serializeSimpleType(doc, 
														  (XmlSchemaSimpleType)elementObj.schemaType, schema);
                serializedEl.appendChild(simpleType);
            }
        }
        if(elementObj.constraints.getCount() > 0){
            for(int i=0; i<elementObj.constraints.getCount();i++){
                Element constraint = serializeIdentityConstraint(doc, 
																 (XmlSchemaIdentityConstraint)elementObj.constraints.getItem(i), 
																 schema);
                serializedEl.appendChild(constraint);
            }
        }

        return serializedEl;
    }
    
    /************************************************************************
	 * Element serializeSimpleType(Document doc, 
	 *    XmlSchemaSimpleType simpleTypeObj, XmlSchema schema) 
	 *    throws XmlSchemaSerializerException{
	 *
	 * Each member of simple type will be appended and pass the element
	 * created.  Simple type processed according to w3c Recommendation
	 * May 2 2001. 
	 *
	 * Parameter:
	 * doc               - Document the parent use.
	 * simpleTypeObj     - XmlSchemaSimpleType that will be serialized.
	 * schema            - Schema Document object of the parent.
	 *
	 * Return:
	 * Element object of SimpleType
	 ************************************************************************/
    Element serializeSimpleType(Document doc, XmlSchemaSimpleType simpleTypeObj, 
								XmlSchema schema) throws XmlSchemaSerializerException{
        
		Element serializedSimpleType = createNewElement(doc, "simpleType",
														schema.schema_ns_prefix, schema.SCHEMA_NS);
        
        
        String tmp;
        tmp = simpleTypeObj.finalDerivation.getValue();
        if(!tmp.equals("None")){

            tmp = convertString(tmp);
            serializedSimpleType.setAttributeNS(schema.SCHEMA_NS, "final", tmp);
        }
        if(simpleTypeObj.id != null)
            serializedSimpleType.setAttributeNS(schema.SCHEMA_NS, "id", 
												simpleTypeObj.id);
        if((simpleTypeObj.name != null)&&(!simpleTypeObj.name.equals("")))
            serializedSimpleType.setAttributeNS(schema.SCHEMA_NS, "name", 
												simpleTypeObj.name);
        if(simpleTypeObj.annotation != null){
            Element annotationEl = serializeAnnotation(doc, 
													   simpleTypeObj.annotation, schema);
            serializedSimpleType.appendChild(annotationEl);
        }
        if(simpleTypeObj.content != null){
            if(simpleTypeObj.content instanceof XmlSchemaSimpleTypeRestriction){
                Element restEl = serializeSimpleTypeRestriction(doc, 
																(XmlSchemaSimpleTypeRestriction)simpleTypeObj.content, 
																schema);
                serializedSimpleType.appendChild(restEl);
            }else if(simpleTypeObj.content instanceof XmlSchemaSimpleTypeList){
                Element listEl = serializeSimpleTypeList(doc, 
														 (XmlSchemaSimpleTypeList)simpleTypeObj.content, schema);
                serializedSimpleType.appendChild(listEl);
            }else if(simpleTypeObj.content instanceof XmlSchemaSimpleTypeUnion){
                Element unionEl = serializeSimpleTypeUnion(doc, 
														   (XmlSchemaSimpleTypeUnion)simpleTypeObj.content, schema);
                serializedSimpleType.appendChild(unionEl);
            }/*else 
			   throw new XmlSchemaSerializerException("Invalid type inserted "
			   + "in simpleType content, the content is: " 
			   + simpleTypeObj.content.getClass().getName()
			   + " valid content should be XmlSchemaSimpleTypeunion, "
			   + "XmlSchemaSimpleTyperestriction or list");*/
        }/*else
		   throw new XmlSchemaSerializerException("simple type must be set "
		   + "with content, either union, restriction or list");*/
        
        return serializedSimpleType;
    }
    
    /************************************************************************
	 * Element serializeSimpleTypeRestriction(Document doc, 
	 *    XmlSchemaSimpleTypeRestriction restrictionObj, XmlSchema schema) 
	 *    throws XmlSchemaSerializerException{
	 *
	 * Each member of simple type will be appended and pass the element
	 * created.  Simple type's <restriction> processed according to w3c 
	 * Recommendation May 2 2001. 
	 *
	 * Parameter:
	 * doc               - Document the parent use.
	 * restrictionObj    - XmlSchemaRestriction that will be serialized.
	 * schema            - Schema Document object of the parent.
	 *
	 * Return:
	 * Element of simple type restriction and its child.
	 ************************************************************************/
    Element serializeSimpleTypeRestriction(Document doc, 
										   XmlSchemaSimpleTypeRestriction restrictionObj, XmlSchema schema) 
        throws XmlSchemaSerializerException{
        //todo: need to implement any attribute that related to non schema namespace
        Element serializedRestriction = createNewElement(doc, "restriction" , 
														 schema.schema_ns_prefix ,schema.SCHEMA_NS);

        if(schema.schema_ns_prefix.length()>0)
            serializedRestriction.setPrefix(schema.schema_ns_prefix);
        if(restrictionObj.baseTypeName != null){
            String baseType = resolveQualifiedName(restrictionObj.baseTypeName, schema);
            serializedRestriction.setAttributeNS(schema.SCHEMA_NS, "base",baseType);
        }else if(restrictionObj.baseType != null && restrictionObj.baseType
				 instanceof XmlSchemaSimpleType){
            Element inlineSimpleType = serializeSimpleType(doc, 
														   (XmlSchemaSimpleType)restrictionObj.baseType, schema);
            serializedRestriction.appendChild(inlineSimpleType);
        }else 
            throw new XmlSchemaSerializerException("restriction must be define "
												   + "with specifying base or inline simpleType");
            
        if(restrictionObj.id != null)
            serializedRestriction.setAttributeNS(schema.SCHEMA_NS, "id", 
												 restrictionObj.id);
       
        if(restrictionObj.annotation != null){
            Element annotation = serializeAnnotation(doc, 
													 restrictionObj.annotation, schema);
            serializedRestriction.appendChild(annotation);
        }
        if(restrictionObj.facets.getCount() >0){
            int facetsNum =restrictionObj.facets.getCount(); 
            for(int i=0;i<facetsNum;i++){
                Element facetEl = serializeFacet(doc, 
												 (XmlSchemaFacet)restrictionObj.facets.getItem(i), schema);
                serializedRestriction.appendChild(facetEl);
            }
        }
        return serializedRestriction;
    }    
    /************************************************************************
	 * Element serializeFacet(Document doc, XmlSchemaFacet facetObj, 
	 *   XmlSchema schema) throws XmlSchemaSerializerException{
	 *
	 * detect what type of facet and cass appropriatelly, 
	 * construct the element and pass it.
	 *
	 * Parameter:
	 * doc       - Document the parent use.
	 * facetObj  - XmlSchemaFacet that will be serialized.
	 * schema    - Schema Document object of the parent.
	 *
	 * Return:
	 * Element of simple type with facet.
	 ************************************************************************/
    Element serializeFacet(Document doc, XmlSchemaFacet facetObj, 
						   XmlSchema schema) throws XmlSchemaSerializerException{
        
        Element serializedFacet;
        String facetName = facetObj.getClass().getName();
        
        if(facetObj instanceof XmlSchemaMinExclusiveFacet)
            serializedFacet = constructFacet(facetObj, doc,schema, 
											 "minExclusive");
        else if(facetObj instanceof  XmlSchemaMinInclusiveFacet)
            serializedFacet = constructFacet(facetObj, doc,schema, 
											 "minInclusive");
        else if(facetObj instanceof XmlSchemaMaxExclusiveFacet)
            serializedFacet = constructFacet(facetObj, doc,schema, 
											 "maxExclusive");
        else if(facetObj instanceof XmlSchemaMaxInclusiveFacet)   
            serializedFacet = constructFacet(facetObj, doc,schema, 
											 "maxInclusive");
        else if(facetObj instanceof XmlSchemaTotalDigitsFacet)
            serializedFacet = constructFacet(facetObj, doc,schema, 
											 "totalDigits");
        else if(facetObj instanceof XmlSchemaFractionDigitsFacet)
            serializedFacet = constructFacet(facetObj, doc,schema, 
											 "fractionDigits");
        else if(facetObj instanceof XmlSchemaLengthFacet)
            serializedFacet = constructFacet(facetObj, doc,schema, 
											 "length");
        else if(facetObj instanceof XmlSchemaMinLengthFacet)
            serializedFacet = constructFacet(facetObj, doc,schema, 
											 "minLength");
        else if(facetObj instanceof XmlSchemaMaxLengthFacet)
            serializedFacet = constructFacet(facetObj, doc,schema,
											 "maxLength");
        else if(facetObj instanceof XmlSchemaEnumerationFacet)
            serializedFacet = constructFacet(facetObj, doc,schema, 
											 "enumeration");
        else if(facetObj instanceof  XmlSchemaWhiteSpaceFacet)
            serializedFacet = constructFacet(facetObj, doc,schema, 
											 "whiteSpace");
        else if(facetObj instanceof XmlSchemaPatternFacet)
            serializedFacet = constructFacet(facetObj, doc,schema, 
											 "pattern");
        else
            throw new XmlSchemaSerializerException("facet not exist " 
												   + facetObj.getClass().getName() );
    
        if(facetObj.id != null)
            serializedFacet.setAttributeNS(schema.SCHEMA_NS, "id", facetObj.id);
        if(facetObj.annotation != null){
            Element annotation = serializeAnnotation(doc, facetObj.annotation, 
													 schema);
            serializedFacet.appendChild(annotation);
        }
             
        return serializedFacet;
    }
    
    private Element constructFacet(XmlSchemaFacet facetObj, Document doc, 
								   XmlSchema schema, String tagName){
            
        Element facetEl = createNewElement(doc, tagName , 
										   schema.schema_ns_prefix ,schema.SCHEMA_NS);

        facetEl.setAttributeNS(schema.SCHEMA_NS, "value", 
							   facetObj.value.toString());
        if(facetObj.fixed)
            facetEl.setAttributeNS(schema.SCHEMA_NS, "fixed", "true");
        
        if(facetObj.annotation != null){
            Element annotation = serializeAnnotation(doc, 
													 facetObj.annotation,  schema);
            facetEl.appendChild(annotation);
        }
        return facetEl;
    }
    
    /************************************************************************
	 * Element serializeComplexType(Document doc, 
	 *    XmlSchemaComplexType complexTypeObj, XmlSchema schema) 
	 *    throws XmlSchemaSerializerException{
	 *   
	 * Each member of complex type will be appended and pass the element
	 * created.  Complex type processed according to w3c Recommendation
	 * May 2 2001. 
	 *
	 * Parameter:
	 * doc             - Document the parent use.
	 * complexTypeObj  - XmlSchemaFacet that will be serialized.
	 * schema          - Schema Document object of the parent.
	 *
	 * Return:
	 * Element of complexType.
	 ************************************************************************/
    Element serializeComplexType(Document doc, 
								 XmlSchemaComplexType complexTypeObj, XmlSchema schema) 
        throws XmlSchemaSerializerException{
        
        //todo: need to implement abstract, id, mixed
        Element serializedComplexType = createNewElement(doc , 
														 "complexType", schema.schema_ns_prefix, schema.SCHEMA_NS  );
        
        if ((complexTypeObj.name != null)&&(!complexTypeObj.name.equals("")))
            serializedComplexType.setAttributeNS(schema.SCHEMA_NS, "name", 
												 complexTypeObj.name);
        /*if(complexTypeObj.annotation != null){
		  Element annotationEl = serializeAnnotation(doc, 
		  complexTypeObj.annotation, schema);
		  serializedComplexType.appendChild(annotationEl);
		  }*/
        
        if(complexTypeObj.isMixed)
            serializedComplexType.setAttributeNS(schema.SCHEMA_NS, 
												 "mixed", "true");
        if(complexTypeObj.isAbstract)
            serializedComplexType.setAttributeNS(schema.SCHEMA_NS, 
												 "abstract", "true");
        if(complexTypeObj.id != null)
            serializedComplexType.setAttributeNS(schema.SCHEMA_NS, "id", 
												 complexTypeObj.id);      
            
        if(complexTypeObj.contentModel instanceof XmlSchemaSimpleContent){
            Element simpleContent = serializeSimpleContent(doc, 
														   (XmlSchemaSimpleContent)complexTypeObj.contentModel, schema);
            serializedComplexType.appendChild(simpleContent);
        }else if(complexTypeObj.contentModel instanceof 
				 XmlSchemaComplexContent){
            
            Element complexContent = serializeComplexContent(doc, 
															 (XmlSchemaComplexContent)complexTypeObj.contentModel, schema);
            serializedComplexType.appendChild(complexContent);
        }

        if(complexTypeObj.particle instanceof XmlSchemaSequence){
            Element sequence = serializeSequence(doc, 
												 (XmlSchemaSequence)complexTypeObj.particle, schema);
            serializedComplexType.appendChild(sequence);
        }else if(complexTypeObj.particle instanceof XmlSchemaChoice){
            Element choice = serializeChoice(doc, 
											 (XmlSchemaChoice)complexTypeObj.particle, schema);
            serializedComplexType.appendChild(choice);
        }else if(complexTypeObj.particle instanceof XmlSchemaAll){
            Element all = serializeAll(doc, 
									   (XmlSchemaAll)complexTypeObj.particle, schema);
            serializedComplexType.appendChild(all);
        }else if(complexTypeObj.particle instanceof XmlSchemaGroupRef){
            Element group = serializeGroupRef(doc, 
											  (XmlSchemaGroupRef)complexTypeObj.particle, schema);
            serializedComplexType.appendChild(group);
        }
        
        String block = complexTypeObj.block.getValue();
        if(!block.equals("None")){
            block = convertString(block);
            serializedComplexType.setAttributeNS(schema.SCHEMA_NS, 
												 "block", block);
        }
        String finalDerivation = complexTypeObj.finalDerivation.getValue();
        if(!finalDerivation.equals("None")){
            finalDerivation = convertString(finalDerivation);
            serializedComplexType.setAttributeNS(schema.SCHEMA_NS, "final", 
												 finalDerivation);
        }
        
        XmlSchemaObjectCollection attrColl = complexTypeObj.attributes;
        if(attrColl.getCount() > 0)
            setupAttr(doc, attrColl, schema,serializedComplexType);
        
        return serializedComplexType;
    } 
    
    /************************************************************************
	 * Element serializeSequence(Document doc, XmlSchemaSequence sequenceObj, 
	 *    XmlSchema schema)throws XmlSchemaSerializerException{
	 *   
	 * Each member of complex type will be appended and pass the element
	 * created.  `Complex type processed according to w3c Recommendation
	 * May 2 2001. 
	 *
	 * Parameter:
	 * doc             - Document the parent use.
	 * sequenceObj  - XmlSchemaFacet that will be serialized.
	 * schema          - Schema Document object of the parent.
	 *
	 * Return:
	 * Element of sequence particle.
	 ************************************************************************/
    Element serializeSequence(Document doc, XmlSchemaSequence sequenceObj, 
							  XmlSchema schema)throws XmlSchemaSerializerException{
        
        Element sequence = createNewElement(doc, "sequence", 
											schema.schema_ns_prefix, schema.SCHEMA_NS);
       
        
        if(sequenceObj.id != null)
            sequence.setAttributeNS(schema.SCHEMA_NS, "id", sequenceObj.id);

        
        if(sequenceObj.maxOccurs < Long.MAX_VALUE && sequenceObj.maxOccurs > 1)
            sequence.setAttributeNS(schema.SCHEMA_NS, "maxOccurs", 
									sequenceObj.maxOccurs +"");
        else if(sequenceObj.maxOccurs == Long.MAX_VALUE)
            sequence.setAttributeNS(schema.SCHEMA_NS, "maxOccurs", 
									"unbounded");
        //else not serialized
        
            
        if(sequenceObj.minOccurs > 1)
            sequence.setAttributeNS(schema.SCHEMA_NS, "minOccurs", 
									sequenceObj.minOccurs + "");
        
        XmlSchemaObjectCollection seqColl = sequenceObj.items;
        int containLength = seqColl.getCount();
        for(int i=0; i<containLength;i++){
            XmlSchemaObject obj = seqColl.getItem(i);
            if(obj instanceof XmlSchemaElement){
                Element el = serializeElement(doc, 
											  (XmlSchemaElement)obj, schema);
                sequence.appendChild(el);
            }else if(obj instanceof XmlSchemaGroupRef){
                Element group = serializeGroupRef(doc, 
												  (XmlSchemaGroupRef)obj, schema);
                sequence.appendChild(group);
            }else if(obj instanceof XmlSchemaChoice){
                Element choice = serializeChoice(doc, 
												 (XmlSchemaChoice)obj, schema);
                sequence.appendChild(choice);
            }else if(obj instanceof XmlSchemaSequence){
                Element sequenceChild = serializeSequence(doc, 
														  (XmlSchemaSequence)obj, schema);
                sequence.appendChild(sequenceChild);
            }else if(obj instanceof XmlSchemaAny){
                Element any = serializeAny(doc,(XmlSchemaAny)obj, schema);
                sequence.appendChild(any);
            }
        }
        return sequence;
    }
    /************************************************************************
	 * Element serializeAttribute(Document doc, XmlSchemaAttribute attributeObj, 
	 *    XmlSchema schema) throws XmlSchemaSerializerException{
	 *   
	 * Each member of complex type will be appended and pass the element
	 * created.  `Complex type processed according to w3c Recommendation
	 * May 2 2001. 
	 *
	 * Parameter:
	 * doc             - Document the parent use.
	 * attributeObj    - XmlSchemaAttribute that will be serialized.
	 * schema          - Schema Document object of the parent.
	 *
	 * Return:
	 * Element of attribute.
	 ************************************************************************/
    Element serializeAttribute(Document doc, XmlSchemaAttribute attributeObj, 
							   XmlSchema schema) throws XmlSchemaSerializerException{
        
		Element attribute = createNewElement(doc, "attribute", 
											 schema.schema_ns_prefix, schema.SCHEMA_NS);
		if(attributeObj.refName != null){
            String refName =  
                resolveQualifiedName(attributeObj.refName, schema);
            attribute.setAttributeNS(schema.SCHEMA_NS, "ref", refName);
        }
        else if(attributeObj.name != null)
            attribute.setAttributeNS(schema.SCHEMA_NS, "name", 
									 attributeObj.name);
            
        if(attributeObj.schemaTypeName != null){
            String typeName =  
                resolveQualifiedName(attributeObj.schemaTypeName, schema);
            attribute.setAttributeNS(schema.SCHEMA_NS, "type", typeName);
        }
        
        if(attributeObj.defaultValue != null)
            attribute.setAttributeNS(schema.SCHEMA_NS, "default",
									 attributeObj.defaultValue);
        if(attributeObj.fixedValue != null)
            attribute.setAttributeNS(schema.SCHEMA_NS, "fixed", 
									 attributeObj.fixedValue);
        
        String formType = attributeObj.form.getValue(); 
        if(!formType.equals("None")){
            formType = convertString(formType);
            attribute.setAttributeNS(schema.SCHEMA_NS, "form", formType);
        }
        if(attributeObj.id != null)
            attribute.setAttributeNS(schema.SCHEMA_NS, "id", attributeObj.id);
       
        String useType =attributeObj.use.getValue(); 
        if(!useType.equals("None")){
            useType = convertString(useType);
            attribute.setAttributeNS(schema.SCHEMA_NS, "use", useType);
        }
        if(attributeObj.annotation != null){
            Element annotation = serializeAnnotation(doc, 
													 attributeObj.annotation, schema);
            attribute.appendChild(annotation);
        }
        
        
        if(attributeObj.schemaType != null){
            try{
                XmlSchemaSimpleType simpleType = 
                    (XmlSchemaSimpleType)attributeObj.schemaType;
                Element simpleTypeEl = serializeSimpleType(doc, 
														   simpleType, schema);
                attribute.appendChild(simpleTypeEl);
            }catch(ClassCastException e){
                throw new XmlSchemaSerializerException(
													   "only inline simple type allow as attribute's inline type");
            }
        }
		
		Attr[] unhandled = attributeObj.getUnhandledAttributes();

		Hashtable namespaces = new Hashtable();
		
		if (unhandled != null){
			
			// this is to make the wsdl:arrayType work 
			// since unhandles attributes are not handled this is a special case
			// but the basic idea is to see if there is any attibute whose value has ":"
			// if it is present then it is likely that it is a namespace prefix
			// do what is neccesary to get the real namespace for it and make 
			// required changes to the prefix 
			
			for (int i=0;i<unhandled.length;i++){ 
				String name = unhandled[i].getNodeName();
				String value = unhandled[i].getNodeValue();
				if(  name.equals( "xmlns") ) {
					namespaces.put( "", value);
				}else if( name.startsWith( "xmlns" )){
					namespaces.put( name.substring(name.indexOf(":") + 1) , value);
				}
			}
			
			for (int i=0;i<unhandled.length;i++){
				String value = unhandled[i].getNodeValue();
				String nodeName = unhandled[i].getNodeName();
				if( value.indexOf( ":") > -1 && ! nodeName.startsWith( "xmlns") ) {
					String prefix = value.substring( 0, value.indexOf( ":" ));
					String oldNamespace = null;
					if(( oldNamespace =  ( String) namespaces.get( prefix )) != null) {
						value = value.substring( value.indexOf(":") + 1 );
						Hashtable realNamespaces = schema.getPrefixToNamespaceMap();
						java.util.Iterator iter = realNamespaces.keySet().iterator();
						while( iter.hasNext()){
							prefix = ( String) iter.next();
							String namespace = ( String ) realNamespaces.get( prefix );
							if( namespace.equals( oldNamespace)) 
								value = prefix + ":" + value;
						}
					}
					
				}
				if (unhandled[i].getNamespaceURI()!= null)
					attribute.setAttributeNS(unhandled[i].getNamespaceURI(),nodeName,value);
			    else
					attribute.setAttribute(nodeName,value);
			}
		}
        return attribute;
    }
    /************************************************************************
	 * Element serializeChoice(Document doc, XmlSchemaChoice choiceObj, 
	 *   XmlSchema schema) throws XmlSchemaSerializerException{
	 *   
	 * Each member of complex type will be appended and pass the element
	 * created.  Complex type processed according to w3c Recommendation
	 * May 2 2001. 
	 *
	 * Parameter:
	 * doc             - Document the parent use.
	 * choiceObj       - XmlSchemaChoice that will be serialized.
	 * schema          - Schema Document object of the parent.
	 *
	 * Return:
	 * Element of choice schema object.
	 ************************************************************************/
    Element serializeChoice(Document doc, XmlSchemaChoice choiceObj, 
							XmlSchema schema) throws XmlSchemaSerializerException{
        //todo: handle any non schema attri ?
        
        Element choice = createNewElement(doc, "choice", 
										  schema.schema_ns_prefix,  schema.SCHEMA_NS);
        if(choiceObj.id!= null)
            if(choiceObj.id.length()>0)
                choice.setAttributeNS(schema.SCHEMA_NS, "id", choiceObj.id);
        
         
        if(choiceObj.maxOccurs < Long.MAX_VALUE && choiceObj.maxOccurs > 1)
            choice.setAttributeNS(schema.SCHEMA_NS, "maxOccurs", 
								  choiceObj.maxOccurs +"");
        else if(choiceObj.maxOccurs == Long.MAX_VALUE)
            choice.setAttributeNS(schema.SCHEMA_NS, "maxOccurs", 
								  "unbounded");
        //else not serialized
        
        if(choiceObj.minOccurs >1)
            choice.setAttributeNS(schema.SCHEMA_NS, "minOccurs", 
								  choiceObj.minOccurs + "");
               

        /*
		  if(choiceObj.maxOccursString != null)
		  choice.setAttributeNS(schema.SCHEMA_NS, "maxOccurs", 
		  choiceObj.maxOccursString);
		  else if(choiceObj.maxOccurs > 1)
		  choice.setAttributeNS(schema.SCHEMA_NS, "maxOccurs", 
		  choiceObj.maxOccurs +"");
		*/  
            
        
        if(choiceObj.annotation != null){
            Element annotation = serializeAnnotation(doc, 
													 choiceObj.annotation, schema);
            choice.appendChild(annotation);
        }
            
        
        XmlSchemaObjectCollection itemColl = choiceObj.items;

        if(itemColl != null){
            int itemLength = itemColl.getCount();

            for(int i=0;i<itemLength;i++){
                XmlSchemaObject obj = itemColl.getItem(i);

                if(obj instanceof  XmlSchemaElement){
                    Element el = serializeElement(doc, 
												  (XmlSchemaElement)obj, schema);
                    choice.appendChild(el);
                }else if(obj instanceof XmlSchemaGroupRef){
                    Element group = serializeGroupRef(doc, 
													  (XmlSchemaGroupRef)obj, schema);
                    choice.appendChild(group);
                }else if(obj instanceof XmlSchemaChoice){
                    Element inlineChoice = serializeChoice(doc,
														   (XmlSchemaChoice)obj, schema);
                    choice.appendChild(inlineChoice);
                }else if(obj instanceof XmlSchemaSequence){
                    Element inlineSequence = serializeSequence(doc, 
															   (XmlSchemaSequence)obj, schema);
                    choice.appendChild(inlineSequence);
                }else if(obj instanceof XmlSchemaAny){
                    Element any = serializeAny(doc, (XmlSchemaAny)obj, schema);
                    choice.appendChild(any);
                }
            }
        }
        return choice;
    }
    /************************************************************************
	 * Element serializeAll(Document doc, XmlSchemaAll allObj, XmlSchema schema) 
	 *    throws XmlSchemaSerializerException{
	 *   
	 * Each member of complex type will be appended and pass the element
	 * created.  Complex type processed according to w3c Recommendation
	 * May 2 2001. 
	 *
	 * Parameter:
	 * doc             - Document the parent use.
	 * allObj          - XmlSchemaAll that will be serialized.
	 * schema          - Schema Document object of the parent.
	 *
	 * Return:
	 * Element of particle all.
	 ************************************************************************/
    Element serializeAll(Document doc, XmlSchemaAll allObj, XmlSchema schema) 
        throws XmlSchemaSerializerException{
        Element allEl = createNewElement(doc, "all", schema.schema_ns_prefix, 
										 schema.SCHEMA_NS);
        
		if(allObj.minOccurs == 0)
            allEl.setAttributeNS(schema.SCHEMA_NS, "minOccurs", "0");

        
        if(allObj.annotation != null){
            Element annotation = serializeAnnotation(doc, allObj.annotation,
													 schema);
            allEl.appendChild(annotation);
        }

        XmlSchemaObjectCollection itemColl = allObj.items;
        
        if(itemColl != null){
            int itemLength = itemColl.getCount();

            for(int i=0;i<itemLength;i++){
                XmlSchemaObject obj = itemColl.getItem(i);
                if(obj instanceof XmlSchemaElement){
                    Element el = serializeElement(doc, (XmlSchemaElement)obj, 
												  schema);
                    allEl.appendChild(el);
                }else
                    throw new XmlSchemaSerializerException("Only element "
														   + "allowed as child of all model type");
            }
        }
        
        return allEl;
    }

    /************************************************************************
	 * Element serializeSimpleTypeList(Document doc, 
	 *    XmlSchemaSimpleTypeList listObj, XmlSchema schema)
	 *        throws XmlSchemaSerializerException{
	 *   
	 * Each member of complex type will be appended and pass the element
	 * created.  Complex type processed according to w3c Recommendation
	 * May 2 2001. 
	 *
	 * Parameter:
	 * doc             - Document the parent use.
	 * listObj         - XmlSchemaSimpleTypeList that will be serialized.
	 * schema          - Schema Document object of the parent.
	 *
	 * Return:
	 * Element of simple type with list method.
	 ************************************************************************/
    Element serializeSimpleTypeList(Document doc, 
									XmlSchemaSimpleTypeList listObj, XmlSchema schema)
		throws XmlSchemaSerializerException{

        Element list = createNewElement(doc, "list" , 
										schema.schema_ns_prefix ,schema.SCHEMA_NS);

        if(listObj.itemTypeName != null){
            String listItemType = resolveQualifiedName(listObj.itemTypeName,
													   schema);
            list.setAttributeNS(schema.SCHEMA_NS, "itemType", listItemType);
        }
        if(listObj.id != null)
            list.setAttributeNS(schema.SCHEMA_NS, "id", listObj.id);
        
        else if(listObj.itemType != null){
            Element inlineSimpleEl = serializeSimpleType(doc, listObj.itemType, 
														 schema);
            list.appendChild(inlineSimpleEl);
        }
        if(listObj.annotation != null){
            Element annotation = serializeAnnotation(doc, listObj.annotation, schema);
            list.appendChild(annotation);
        }
        return list;
    }
    
    /************************************************************************
	 * Element serializeSimpleTypeUnion(Document doc, 
	 *    XmlSchemaSimpleTypeUnion unionObj, XmlSchema schema) 
	 *    throws XmlSchemaSerializerException{
	 *   
	 * Each member of complex type will be appended and pass the element
	 * created.  Complex type processed according to w3c Recommendation
	 * May 2 2001. 
	 *
	 * Parameter:
	 * doc              - Document the parent use.
	 * unionObj         - XmlSchemaSimpleTypeUnion that will be serialized.
	 * schema           - Schema Document object of the parent.
	 *
	 * Return:
	 * Element of simple type with union method.
	 ************************************************************************/
    Element serializeSimpleTypeUnion(Document doc, 
									 XmlSchemaSimpleTypeUnion unionObj, XmlSchema schema) 
        throws XmlSchemaSerializerException{
        
        
        Element union = createNewElement(doc, "union", 
										 schema.schema_ns_prefix, schema.SCHEMA_NS);
        if(unionObj.id != null)
            union.setAttributeNS(schema.SCHEMA_NS, "id", unionObj.id);
        
        if(unionObj.memberTypesSource != null)
            union.setAttributeNS(schema.SCHEMA_NS, "memberTypes", 
								 unionObj.memberTypesSource);
        else if(unionObj.baseTypes.getCount() > 0){
            int baseTypesLength = unionObj.baseTypes.getCount();
            Element baseType;
            for(int i=0; i<baseTypesLength; i++){
                try{
                    baseType = serializeSimpleType(doc, 
												   (XmlSchemaSimpleType)unionObj.baseTypes.getItem(i), 
												   schema);
                    union.appendChild(baseType);
                }catch(ClassCastException e){
                    throw new XmlSchemaSerializerException(
														   "only inline simple type allow as attribute's "
														   + "inline type");
                }
            }
        }
        if(unionObj.annotation != null){
            Element annotation = serializeAnnotation(doc, unionObj.annotation, 
													 schema);
            union.appendChild(annotation);
        }
        return union;
    }    

    /************************************************************************
	 * Element serializeAny(Document doc, XmlSchemaAny anyObj, XmlSchema schema)
	 *   
	 * Each member of complex type will be appended and pass the element
	 * created.  Complex type processed according to w3c Recommendation
	 * May 2 2001. 
	 *
	 * Parameter:
	 * doc              - Document the parent use.
	 * anyObj           - XmlSchemaAny that will be serialized.
	 * schema           - Schema Document object of the parent.
	 *
	 * Return:
	 * Element of any that is part of its parent.
	 ************************************************************************/
    Element serializeAny(Document doc, XmlSchemaAny anyObj, XmlSchema schema){
        Element anyEl = createNewElement(doc, "any", schema.schema_ns_prefix , 
										 schema.SCHEMA_NS);
        if(anyObj.id != null)
            if(anyObj.id.length()>0)
                anyEl.setAttributeNS(schema.SCHEMA_NS, "id", anyObj.id);
 
        
		if(anyObj.maxOccurs < Long.MAX_VALUE && anyObj.maxOccurs > 1)
            anyEl.setAttributeNS(schema.SCHEMA_NS, "maxOccurs", 
								 anyObj.maxOccurs +"");
        else if(anyObj.maxOccurs == Long.MAX_VALUE)
            anyEl.setAttributeNS(schema.SCHEMA_NS, "maxOccurs", 
								 "unbounded");
        //else not serialized
        
        if(anyObj.minOccurs >1)
            anyEl.setAttributeNS(schema.SCHEMA_NS, "minOccurs", 
								 anyObj.minOccurs + "");
 
        if(anyObj.namespace != null)
            anyEl.setAttributeNS(schema.SCHEMA_NS, "namespace", 
								 anyObj.namespace);
        
        if(anyObj.processContent != null){
            String value = anyObj.processContent.getValue();
            if(!value.equals("None")){
                String processContent = convertString(value);
                anyEl.setAttributeNS(schema.SCHEMA_NS, "processContents", 
									 processContent);
            }
        }
        if(anyObj.annotation != null){
            Element annotation = serializeAnnotation(doc, 
													 anyObj.annotation, schema);
            anyEl.appendChild(annotation);
        }
        
        return anyEl;
    }
    
    /************************************************************************
	 * Element serializeGroup(Document doc, XmlSchemaGroup groupObj, 
	 *    XmlSchema schema) throws XmlSchemaSerializerException{
	 *   
	 * Each member of complex type will be appended and pass the element
	 * created.  Complex type processed according to w3c Recommendation
	 * May 2 2001. 
	 *
	 * Parameter:
	 * doc                - Document the parent use.
	 * groupObj           - XmlSchemaGroup that will be serialized.
	 * schema             - Schema Document object of the parent.
	 *
	 * Return:
	 * Element of group elements.
	 ************************************************************************/
    Element serializeGroup(Document doc, XmlSchemaGroup groupObj, 
						   XmlSchema schema) throws XmlSchemaSerializerException{
            
        Element group = createNewElement(doc, "group", 
										 schema.schema_ns_prefix,schema.SCHEMA_NS);
        
        if(groupObj.name != null){
            if(groupObj.name.length() > 0){
                group.setAttributeNS(schema.SCHEMA_NS, "name", groupObj.name);
            }
        }else
            throw new XmlSchemaSerializerException("Group must have " + 
												   "name or ref");
                
        
        if(groupObj.particle instanceof XmlSchemaSequence){
            Element sequence = serializeSequence(doc, 
												 (XmlSchemaSequence)groupObj.particle, schema);
            group.appendChild(sequence);
        }else if(groupObj.particle instanceof XmlSchemaChoice){
            Element choice = serializeChoice(doc, 
											 (XmlSchemaChoice)groupObj.particle, schema);
            group.appendChild(choice);
        }else if(groupObj.particle instanceof XmlSchemaAll){
            Element all = serializeAll(doc, 
									   (XmlSchemaAll)groupObj.particle, schema);
            group.appendChild(all);
        }
        if(groupObj.annotation != null){
            Element annotation = serializeAnnotation(doc, 
													 groupObj.annotation, schema);
            group.appendChild(annotation);
        }
        return group;
    }
    
    /************************************************************************
	 * Element serializeGroupRef(Document doc, XmlSchemaGroupRef groupRefObj, 
	 *    XmlSchema schema) throws XmlSchemaSerializerException{
	 *   
	 * Each member of complex type will be appended and pass the element
	 * created.  Complex type processed according to w3c Recommendation
	 * May 2 2001. 
	 *
	 * Parameter:
	 * doc                   - Document the parent use.
	 * groupRefObj           - XmlSchemaGroupRef that will be serialized.
	 * schema                - Schema Document object of the parent.
	 *
	 * Return:
	 * Element of group elements ref inside its parent.
	 ************************************************************************/
    Element serializeGroupRef(Document doc, XmlSchemaGroupRef groupRefObj, 
							  XmlSchema schema) throws XmlSchemaSerializerException{
        
        Element groupRef = createNewElement(doc, "group", 
											schema.schema_ns_prefix,schema.SCHEMA_NS);
        
        if(groupRefObj.refName != null){
            String groupRefName = resolveQualifiedName(groupRefObj.refName, 
													   schema);
            groupRef.setAttributeNS(schema.SCHEMA_NS, "ref", groupRefName);
        }else 
            throw new XmlSchemaSerializerException("Group must have name or ref");
        
        if(groupRefObj.maxOccurs < Long.MAX_VALUE && groupRefObj.maxOccurs > 1)
            groupRef.setAttributeNS(schema.SCHEMA_NS, "maxOccurs", 
									groupRefObj.maxOccurs +"");
        else if(groupRefObj.maxOccurs == Long.MAX_VALUE)
            groupRef.setAttributeNS(schema.SCHEMA_NS, "maxOccurs", 
									"unbounded");
        //else not serialized
        
        if(groupRefObj.minOccurs >1)
            groupRef.setAttributeNS(schema.SCHEMA_NS, "minOccurs", 
									groupRefObj.minOccurs + "");

        
        /*
		  if(groupRefObj.maxOccursString != null)
		  groupRef.setAttributeNS(schema.SCHEMA_NS, 
		  "maxOccurs", groupRefObj.maxOccursString);
		  else if(groupRefObj.maxOccurs > 1)
		  groupRef.setAttributeNS(schema.SCHEMA_NS, 
		  "maxOccurs", groupRefObj.maxOccurs + "");
		*/
        
        if(groupRefObj.particle != null){
            Element particleEl;
            if(groupRefObj.particle instanceof XmlSchemaChoice)
                particleEl = serializeChoice(doc,
											 (XmlSchemaChoice)groupRefObj.particle, schema);
            else if(groupRefObj.particle instanceof XmlSchemaSequence)
                particleEl = serializeSequence(doc, 
											   (XmlSchemaSequence)groupRefObj.particle, schema);
            else if(groupRefObj.particle instanceof XmlSchemaAll)
                particleEl = serializeAll(doc, 
										  (XmlSchemaAll)groupRefObj.particle, schema);
            else
                throw new XmlSchemaSerializerException("The content of group "
													   + "ref particle should be"
													   + " sequence, choice or all reference:  " 
													   + "www.w3.org/TR/xmlschema-1#element-group-3.7.2");
        }
        if(groupRefObj.annotation != null){
            Element annotation = serializeAnnotation(doc, 
													 groupRefObj.annotation, schema);
            groupRef.appendChild(annotation);
        }
        
        return groupRef;
    }
    
    /************************************************************************
	 * Element serializeSimpleContent(Document doc, 
	 *    XmlSchemaSimpleContent simpleContentObj, XmlSchema schema) 
	 *        throws XmlSchemaSerializerException{
	 *   
	 * Each member of complex type will be appended and pass the element
	 * created.  Complex type processed according to w3c Recommendation
	 * May 2 2001. 
	 *
	 * Parameter:
	 * doc               - Document the parent use.
	 * simpleContentObj  - XmlSchemaSimpleContent that will be serialized.
	 * schema            - Schema Document object of the parent.
	 *
	 * Return:
	 * Element of complex type simple content.
	 ************************************************************************/
    Element serializeSimpleContent(Document doc, 
								   XmlSchemaSimpleContent simpleContentObj, XmlSchema schema) 
		throws XmlSchemaSerializerException{
        Element simpleContent = createNewElement(doc, "simpleContent", 
												 schema.schema_ns_prefix, schema.SCHEMA_NS);
       
        Element content;
        if(simpleContentObj.annotation != null){
            Element annotation = serializeAnnotation(doc, 
													 simpleContentObj.annotation, schema);
            simpleContent.appendChild(annotation);
        }
        if(simpleContentObj.content instanceof 
		   XmlSchemaSimpleContentRestriction)
            content = serializeSimpleContentRestriction(doc, 
														(XmlSchemaSimpleContentRestriction)simpleContentObj.content, 
														schema);
        else if(simpleContentObj.content instanceof 
				XmlSchemaSimpleContentExtension)
            content = serializeSimpleContentExtension(doc, 
													  (XmlSchemaSimpleContentExtension)simpleContentObj.content, 
													  schema);
        else 
            throw new XmlSchemaSerializerException("content of simple content "
												   +"must be restriction or extension");
         
        simpleContent.appendChild(content);
        return simpleContent;
    }
    
    /************************************************************************
	 * Element serializeComplexContent(Document doc, 
	 *    XmlSchemaComplexContent complexContentObj, XmlSchema schema) 
	 *    throws XmlSchemaSerializerException{
	 *   
	 * Each member of complex type will be appended and pass the element
	 * created.  Complex type processed according to w3c Recommendation
	 * May 2 2001. 
	 *
	 * Parameter:
	 * doc                - Document the parent use.
	 * complexContentObj  - XmlSchemaComplexContent that will be serialized.
	 * schema             - Schema Document object of the parent.
	 *
	 * Return:
	 * Element of complex type complex content.
	 ************************************************************************/
    Element serializeComplexContent(Document doc, 
									XmlSchemaComplexContent complexContentObj, XmlSchema schema) 
        throws XmlSchemaSerializerException{
        
        Element complexContent = createNewElement(doc, "complexContent", 
												  schema.schema_ns_prefix, schema.SCHEMA_NS);


        if(complexContentObj.annotation != null){
            Element annotation = serializeAnnotation(doc, 
													 complexContentObj.annotation, schema);
            complexContent.appendChild(annotation);
        }

        if(complexContentObj.mixed)
            complexContent.setAttributeNS(schema.SCHEMA_NS, "mixed", "true");
        if(complexContentObj.id != null)
            complexContent.setAttributeNS(schema.SCHEMA_NS, "id", 
										  complexContentObj.id);
        
        Element content;
        if(complexContentObj.content instanceof 
		   XmlSchemaComplexContentRestriction)
            
            content = serializeComplexContentRestriction(doc, 
														 (XmlSchemaComplexContentRestriction)complexContentObj.content, 
														 schema);
        else if(complexContentObj.content instanceof
				XmlSchemaComplexContentExtension)
            content = serializeComplexContentExtension(doc, 
													   (XmlSchemaComplexContentExtension)complexContentObj.content, 
													   schema);
        else 
            throw new XmlSchemaSerializerException("content of complexContent "
												   +"must be restriction or extension");
         
        complexContent.appendChild(content);
         
        return complexContent;
    }
    
    /************************************************************************
	 * Element serializeIdentityConstraint(Document doc, 
	 *    XmlSchemaIdentityConstraint constraintObj, XmlSchema schema) 
	 *        throws XmlSchemaSerializerException{
	 *   
	 * Each member of complex type will be appended and pass the element
	 * created.  Complex type processed according to w3c Recommendation
	 * May 2 2001. 
	 *
	 * Parameter:
	 * doc               - Document the parent use.
	 * constraintObj     - XmlSchemaIdentityConstraint that will be serialized.
	 * schema            - Schema Document object of the parent.
	 *
	 * Return:
	 * Element of key, keyref or unique that part of its parent.
	 ************************************************************************/
    Element serializeIdentityConstraint(Document doc, 
										XmlSchemaIdentityConstraint constraintObj, XmlSchema schema) 
		throws XmlSchemaSerializerException{

        Element constraint;
        
        if(constraintObj instanceof XmlSchemaUnique)
            constraint = createNewElement(doc, "unique", 
										  schema.schema_ns_prefix, schema.SCHEMA_NS);
        else if(constraintObj instanceof XmlSchemaKey)
            constraint = createNewElement(doc, "key", 
										  schema.schema_ns_prefix, schema.SCHEMA_NS);
        else if(constraintObj instanceof XmlSchemaKeyref){
            constraint = createNewElement(doc, "keyref", 
										  schema.schema_ns_prefix, schema.SCHEMA_NS);
            XmlSchemaKeyref keyref = (XmlSchemaKeyref)constraintObj;
            if(keyref.refer != null){
                String keyrefStr = resolveQualifiedName(keyref.refer, schema);
                constraint.setAttributeNS(schema.SCHEMA_NS, 
										  "refer", keyrefStr);
            }
        }else
            throw new XmlSchemaSerializerException("not valid identity "
												   + "constraint");
        
        if(constraintObj.name != null)
            constraint.setAttributeNS(schema.SCHEMA_NS, "name", 
									  constraintObj.name);
        if(constraintObj.annotation != null){
            Element annotation = serializeAnnotation(doc, 
													 constraintObj.annotation, schema);
            constraint.appendChild(annotation);
        }
        
        if(constraintObj.selector != null){
            Element selector = serializeSelector(doc, 
												 constraintObj.selector, schema);
            constraint.appendChild(selector);
        }
        XmlSchemaObjectCollection fieldColl = constraintObj.fields;
        if(fieldColl != null){
            int fieldLength = fieldColl.getCount();
            for(int i=0; i<fieldLength;i++){
                Element field = serializeField(doc, 
											   (XmlSchemaXPath)fieldColl.getItem(i), schema);
                constraint.appendChild(field);
            }
        }       
        return constraint;
    }    

    /************************************************************************
	 * Element serializeSelector(Document doc, XmlSchemaXPath selectorObj,
	 *    XmlSchema schema) throws XmlSchemaSerializerException{
	 *   
	 * Each member of complex type will be appended and pass the element
	 * created.  Complex type processed according to w3c Recommendation
	 * May 2 2001. 
	 *
	 * Parameter:
	 * doc               - Document the parent use.
	 * selectorObj      - XmlSchemaXPath that will be serialized.
	 * schema            - Schema Document object of the parent.
	 *
	 * Return:
	 * Element of selector with collection of xpath as its attrib.  The selector
	 * itself is the part of identity type.  eg <key><selector xpath="..."
	 ************************************************************************/
    Element serializeSelector(Document doc, XmlSchemaXPath selectorObj,
							  XmlSchema schema) throws XmlSchemaSerializerException{
    
        Element selector = createNewElement(doc, "selector", 
											schema.schema_ns_prefix, schema.SCHEMA_NS);
    
        if(selectorObj.xpath != null)
            selector.setAttributeNS(schema.SCHEMA_NS, "xpath", 
									selectorObj.xpath);
        else
            throw new XmlSchemaSerializerException("xpath can't be null");
        
        if(selectorObj.annotation != null){
            Element annotation = serializeAnnotation(doc, 
													 selectorObj.annotation, schema);
            selector.appendChild(annotation);
        }
        return selector;
    }
   
    /************************************************************************
	 * Element serializeField(Document doc, XmlSchemaXPath fieldObj, 
	 *    XmlSchema schema) throws XmlSchemaSerializerException
	 *   
	 * Each member of complex type will be appended and pass the element
	 * created.  Complex type processed according to w3c Recommendation
	 * May 2 2001. 
	 *
	 * Parameter:
	 * doc           - Document the parent use.
	 * fieldObj      - XmlSchemaXPath that will be serialized.
	 * schema        - Schema Document object of the parent.
	 *
	 * Return:
	 * field element that part of constraint.
	 ************************************************************************/
    Element serializeField(Document doc, XmlSchemaXPath fieldObj, 
						   XmlSchema schema) throws XmlSchemaSerializerException{
    
        Element field = createNewElement(doc, "field", schema.schema_ns_prefix, 
										 schema.SCHEMA_NS);
    
        if(fieldObj.xpath != null)
            field.setAttributeNS(schema.SCHEMA_NS, "xpath", fieldObj.xpath);
        else
            throw new XmlSchemaSerializerException("xpath can't be null");
        
        if(fieldObj.annotation != null){
            Element annotation = serializeAnnotation(doc, 
													 fieldObj.annotation, schema);
            field.appendChild(annotation);
        }
        
        return field;
    }
    
    /************************************************************************
	 * Element serializeAnnotation(Document doc, XmlSchemaAnnotation 
	 *    annotationObj, XmlSchema schema) 
	 *
	 *   
	 * Each member of complex type will be appended and pass the element
	 * created.  Complex type processed according to w3c Recommendation
	 * May 2 2001. 
	 *
	 * Parameter:
	 * doc               - Document the parent use.
	 * annotationObj      - XmlSchemaAnnotation that will be serialized.
	 * schema            - Schema Document object of the parent.
	 *
	 * Return:
	 * annotation element that part of any type. will contain document and 
	 * appinfo for child.
	 ************************************************************************/
    Element serializeAnnotation(Document doc, XmlSchemaAnnotation annotationObj, 
								XmlSchema schema){
            
        Element annotation = createNewElement(doc, "annotation", 
											  schema.schema_ns_prefix,schema.SCHEMA_NS);
        
        XmlSchemaObjectCollection contents = annotationObj.items;
        int contentLength = contents.getCount();
        
        for(int i=0; i<contentLength; i++){
            XmlSchemaObject obj = contents.getItem(i);
            
            if(obj instanceof XmlSchemaAppInfo){
                XmlSchemaAppInfo appinfo = (XmlSchemaAppInfo)obj;
                Element appInfoEl = serializeAppInfo(doc, appinfo, schema);
                annotation.appendChild(appInfoEl);
            }else if(obj instanceof XmlSchemaDocumentation){
                XmlSchemaDocumentation documentation = 
                    (XmlSchemaDocumentation)obj;
                
                Element documentationEl = serializeDocumentation(doc, 
																 documentation, schema);
                
                
                annotation.appendChild(documentationEl);
            }
        }
 
        return annotation;
    }    
 
    /************************************************************************
	 * Element serializeAppInfo(Document doc,XmlSchemaAppInfo appInfoObj,
	 *    XmlSchema schema)
	 *
	 *   
	 * Each member of complex type will be appended and pass the element
	 * created.  Complex type processed according to w3c Recommendation
	 * May 2 2001. 
	 *
	 * Parameter:
	 * doc               - Document the parent use.
	 * appInfoObj        - XmlSchemaAppInfo that will be serialized.
	 * schema            - Schema Document object of the parent.
	 *
	 * Return:
	 * App info element that is part of the annotation.
	 ************************************************************************/
    Element serializeAppInfo(Document doc,XmlSchemaAppInfo appInfoObj,
							 XmlSchema schema){
            
        Element appInfoEl = createNewElement(doc, "appinfo", 
											 schema.schema_ns_prefix, schema.SCHEMA_NS);
        if(appInfoObj.source != null)
            appInfoEl.setAttributeNS(schema.SCHEMA_NS, "source", 
									 appInfoObj.source);

        if(appInfoObj.markup != null){
            int markupLength = appInfoObj.markup.getLength();
            for(int j=0;j<markupLength; j++){
                Node n = appInfoObj.markup.item(j);
                switch(n.getNodeType()){
				case Node.ELEMENT_NODE:
					appendElement(doc, appInfoEl, n, schema);
					break;
				case Node.TEXT_NODE:
					Text t = doc.createTextNode(n.getNodeValue()); 
					appInfoEl.appendChild(t);
					break;
				default:
					break;
                }
            }
        }

        return appInfoEl;
    }
 
    /************************************************************************
	 * Element serializeDocumentation(Document doc,XmlSchemaDocumentation 
	 *    documentationObj, XmlSchema schema){
	 *
	 *   
	 * Each member of complex type will be appended and pass the element
	 * created.  Complex type processed according to w3c Recommendation
	 * May 2 2001. 
	 *
	 * Parameter:
	 * doc               - Document the parent use.
	 * documentationObj        - XmlSchemaAppInfo that will be serialized.
	 * schema            - Schema Document object of the parent.
	 *
	 * Return:
	 * Element representation of documentation that is part of annotation.
	 ************************************************************************/
    Element serializeDocumentation(Document doc,XmlSchemaDocumentation 
								   documentationObj, XmlSchema schema){
        
            
            
        Element documentationEl = createNewElement(doc, "documentation",
												   schema.schema_ns_prefix, schema.SCHEMA_NS);
        if(documentationObj.source != null)
            documentationEl.setAttributeNS(schema.SCHEMA_NS, "source", 
										   documentationObj.source);
        if(documentationObj.language != null)
            documentationEl.setAttributeNS(
										   "http://www.w3.org/XML/1998/namespace", "xml:lang",
										   documentationObj.language);

        if(documentationObj.markup != null){
            int markupLength = documentationObj.markup.getLength();
            for(int j=0;j<markupLength; j++){
                Node n = documentationObj.markup.item(j);
                
                switch(n.getNodeType()){
				case Node.ELEMENT_NODE:
					appendElement(doc, documentationEl, n, schema);
					break;
				case Node.TEXT_NODE:
					Text t = doc.createTextNode(n.getNodeValue()); 
					documentationEl.appendChild(t);
					break;
				default:
					break;
                }
            }
        }
        return documentationEl;
    }       
 
    /************************************************************************
	 * Element serializeSimpleContentRestriction(Document doc, 
	 *    XmlSchemaSimpleContentRestriction restrictionObj, XmlSchema schema) 
	 *    throws XmlSchemaSerializerException{
	 *
	 *   
	 * Each member of complex type will be appended and pass the element
	 * created.  Complex type processed according to w3c Recommendation
	 * May 2 2001. 
	 *
	 * Parameter:
	 * doc               - Document the parent use.
	 * restrictionObj    - XmlSchemaSimpleContentRestriction that will be 
	 *                       serialized.
	 * schema            - Schema Document object of the parent.
	 *
	 * Return:
	 *   Element of simple content restriction.
	 ************************************************************************/
    Element serializeSimpleContentRestriction(Document doc, 
											  XmlSchemaSimpleContentRestriction restrictionObj, XmlSchema schema) 
        throws XmlSchemaSerializerException{
        
        Element restriction = createNewElement(doc, "restriction", 
											   schema.schema_ns_prefix, schema.SCHEMA_NS);

        if(restrictionObj.baseTypeName != null){
            String baseTypeName = 
                resolveQualifiedName(restrictionObj.baseTypeName, schema);
            
            restriction.setAttributeNS(schema.SCHEMA_NS, "base",baseTypeName);
        
        }
        if(restrictionObj.id != null)
			restriction.setAttributeNS(schema.SCHEMA_NS, "id",restrictionObj.id);
            
        if(restrictionObj.annotation != null){
            Element annotation = serializeAnnotation(doc, 
													 restrictionObj.annotation, schema);
            restriction.appendChild(annotation);
        }
        int attrCollLength = restrictionObj.attributes.getCount();
        for(int i=0; i<attrCollLength;i++){
            XmlSchemaObject obj = restrictionObj.attributes.getItem(i);
            
            if(obj instanceof XmlSchemaAttribute){
                Element attribute = serializeAttribute(doc, 
													   (XmlSchemaAttribute)obj, schema);
                restriction.appendChild(attribute);
            }else if(obj instanceof XmlSchemaAttributeGroupRef){
                Element attributeGroup = serializeAttributeGroupRef(doc, 
																	(XmlSchemaAttributeGroupRef)obj, schema);
                restriction.appendChild(attributeGroup);
            }
        }
        if(restrictionObj.baseType != null){
            Element inlineSimpleType = serializeSimpleType(doc, 
														   restrictionObj.baseType, schema);
            restriction.appendChild(inlineSimpleType);
        }
        if(restrictionObj.anyAttribute != null){
            Element anyAttribute = serializeAnyAttribute(doc, 
														 restrictionObj.anyAttribute, schema);
            restriction.appendChild(anyAttribute);
        }
        XmlSchemaObjectCollection facets = restrictionObj.facets;
        int facetLength = facets.getCount();
        for(int i=0;i<facetLength;i++){
            Element facet = serializeFacet(doc, 
										   (XmlSchemaFacet)facets.getItem(i), schema);
            restriction.appendChild(facet);
        }
        return restriction;
    }    
    
    /************************************************************************
	 * Element serializeSimpleContentExtension(Document doc, 
	 *    XmlSchemaSimpleContentExtension extensionObj, XmlSchema schema)
	 *        throws XmlSchemaSerializerException{
	 *
	 *   
	 * Each member of complex type will be appended and pass the element
	 * created.  Complex type processed according to w3c Recommendation
	 * May 2 2001. 
	 *
	 * Parameter:
	 * doc                 - Document the parent use.
	 * extensionObj        - XmlSchemaSimpleContentExtension 
	 *                       that will be serialized.
	 * schema              - Schema Document object of the parent.
	 *
	 * Return:
	 *   Element of simple content extension.
	 ************************************************************************/
    Element serializeSimpleContentExtension(Document doc, 
											XmlSchemaSimpleContentExtension extensionObj, XmlSchema schema)
		throws XmlSchemaSerializerException{
        
        Element extension = createNewElement(doc, "extension",
											 schema.schema_ns_prefix, schema.SCHEMA_NS);
       
        if(extensionObj.baseTypeName != null){
            String baseTypeName = 
                resolveQualifiedName(extensionObj.baseTypeName, schema);
            
            extension.setAttributeNS(schema.SCHEMA_NS, "base", baseTypeName);
        }
        
        if(extensionObj.id != null)
            extension.setAttributeNS(schema.SCHEMA_NS, "id", extensionObj.id);
        
        if(extensionObj.annotation != null){
            Element annotation = serializeAnnotation(doc, 
													 extensionObj.annotation, schema);
            extension.appendChild(annotation);
        }
        if(extensionObj.anyAttribute != null){
            Element anyAttribute = serializeAnyAttribute(doc,
														 extensionObj.anyAttribute, schema);
            extension.appendChild(anyAttribute);
        }
        
        XmlSchemaObjectCollection attributes = extensionObj.attributes;
        int attributeLength = attributes.getCount();
        for(int i=0;i<attributeLength;i++){
            XmlSchemaObject obj = attributes.getItem(i);
            
            if(obj instanceof XmlSchemaAttribute){
                Element attribute = serializeAttribute(doc, 
													   (XmlSchemaAttribute)obj, schema);
                extension.appendChild(attribute);
            }else if(obj instanceof XmlSchemaAttributeGroupRef){
                Element attributeGroupRef = serializeAttributeGroupRef(doc, 
																	   (XmlSchemaAttributeGroupRef)obj, schema);
                extension.appendChild(attributeGroupRef);
            }
        }
        return extension;
    }    
    /************************************************************************
	 * Element serializeComplexContentRestriction(Document doc, 
	 *    XmlSchemaComplexContentRestriction restrictionObj, XmlSchema schema) 
	 *    throws XmlSchemaSerializerException{
	 *   
	 * Each member of complex type will be appended and pass the element
	 * created.  Complex type processed according to w3c Recommendation
	 * May 2 2001. 
	 *
	 * Parameter:
	 * doc                 - Document the parent use.
	 * restrictionObj        - XmlSchemaSimpleContentRestriction 
	 *                       that will be serialized.
	 * schema              - Schema Document object of the parent.
	 *
	 * Return:
	 *   Element of simple content restriction.
	 ************************************************************************/
    Element serializeComplexContentRestriction(Document doc, 
											   XmlSchemaComplexContentRestriction restrictionObj, XmlSchema schema) 
        throws XmlSchemaSerializerException{
        
        Element restriction = createNewElement(doc, "restriction", 
											   schema.schema_ns_prefix, schema.SCHEMA_NS);
        
        if(restrictionObj.baseTypeName != null){
            String baseTypeName = resolveQualifiedName(
													   restrictionObj.baseTypeName, schema);
            restriction.setAttributeNS(schema.SCHEMA_NS, 
									   "base", baseTypeName);
        }
        
        if(restrictionObj.id != null)
            restriction.setAttributeNS(schema.SCHEMA_NS, "id",
									   restrictionObj.id);
        
        if(restrictionObj.annotation != null){
            Element annotation = serializeAnnotation(doc, 
													 restrictionObj.annotation, schema);
            restriction.appendChild(annotation);
        }

        if(restrictionObj.particle instanceof XmlSchemaSequence){
            Element sequenceParticle = serializeSequence(doc,
														 (XmlSchemaSequence)restrictionObj.particle, schema);
            restriction.appendChild(sequenceParticle);
        }else if(restrictionObj.particle instanceof XmlSchemaChoice){
            Element choiceParticle = serializeChoice(doc, 
													 (XmlSchemaChoice)restrictionObj.particle, schema);
            restriction.appendChild(choiceParticle);
        }else if(restrictionObj.particle instanceof XmlSchemaAll){
            Element allParticle = serializeAll(doc, 
											   (XmlSchemaAll)restrictionObj.particle, schema);
            restriction.appendChild(allParticle);
        }else if(restrictionObj.particle instanceof XmlSchemaGroupRef){
            Element groupRefParticle = serializeGroupRef(doc, 
														 (XmlSchemaGroupRef)restrictionObj.particle, schema);
            restriction.appendChild(groupRefParticle);
        }
            
        int attributesLength = restrictionObj.attributes.getCount();
        for(int i=0;i<attributesLength;i++){
            XmlSchemaObject obj = restrictionObj.attributes.getItem(i);
            
            if(obj instanceof XmlSchemaAttribute){
                Element attr = serializeAttribute(doc, 
												  (XmlSchemaAttribute)obj, schema);
                restriction.appendChild(attr);
            }else if(obj instanceof XmlSchemaAttribute){
                Element attrGroup = serializeAttributeGroupRef(doc, 
															   (XmlSchemaAttributeGroupRef)obj, schema);
                restriction.appendChild(attrGroup);
            }
        }
    
        if(restrictionObj.anyAttribute != null){
            Element anyAttribute = serializeAnyAttribute(doc, 
														 restrictionObj.anyAttribute, schema);
            restriction.appendChild(anyAttribute);
        }
            
        return restriction;
    }    
    
    /************************************************************************
	 * Element serializeComplexContentExtension(Document doc, 
	 *    XmlSchemaComplexContentExtension extensionObj, XmlSchema schema) 
	 *    throws XmlSchemaSerializerException{
	 *   
	 * Each member of complex type will be appended and pass the element
	 * created.  Complex type processed according to w3c Recommendation
	 * May 2 2001. 
	 *
	 * Parameter:
	 * doc                 - Document the parent use.
	 * extensionObj        - XmlSchemaComplexContentRestriction 
	 *                       that will be serialized.
	 * schema              - Schema Document object of the parent.
	 *
	 * Return:
	 * Element of complex content extension.
	 ************************************************************************/
    Element serializeComplexContentExtension(Document doc, 
											 XmlSchemaComplexContentExtension extensionObj, XmlSchema schema) 
        throws XmlSchemaSerializerException{
        
        Element extension = createNewElement(doc, "extension", 
											 schema.schema_ns_prefix, schema.SCHEMA_NS);
        if(extensionObj.baseTypeName != null){
            String baseType = resolveQualifiedName(extensionObj.baseTypeName, 
												   schema);
            extension.setAttributeNS(schema.SCHEMA_NS,"base", baseType);
        }
        if(extensionObj.annotation != null){
            Element annotation = serializeAnnotation(doc, 
													 extensionObj.annotation, schema );
            extension.appendChild(annotation);
        }
        

        if(extensionObj.particle instanceof XmlSchemaSequence){
            Element sequenceParticle = serializeSequence(doc,
														 (XmlSchemaSequence)extensionObj.particle, schema);
            extension.appendChild(sequenceParticle);
        }else if(extensionObj.particle instanceof XmlSchemaChoice){
            Element choiceParticle = serializeChoice(doc, 
													 (XmlSchemaChoice)extensionObj.particle, schema);
            extension.appendChild(choiceParticle);
        }else if(extensionObj.particle instanceof XmlSchemaAll){
            Element allParticle = serializeAll(doc, 
											   (XmlSchemaAll)extensionObj.particle, schema);
            extension.appendChild(allParticle);
        }else if(extensionObj.particle instanceof XmlSchemaGroupRef){
            Element groupRefParticle = serializeGroupRef(doc, 
														 (XmlSchemaGroupRef)extensionObj.particle, schema);
            extension.appendChild(groupRefParticle);
        }
            
        int attributesLength = extensionObj.attributes.getCount();
        for(int i=0;i<attributesLength;i++){
            XmlSchemaObject obj = extensionObj.attributes.getItem(i);
            
            if(obj instanceof XmlSchemaAttribute){
                Element attr = serializeAttribute(doc,
												  (XmlSchemaAttribute)obj, schema);
                extension.appendChild(attr);
            }else if(obj instanceof XmlSchemaAttributeGroupRef){
                Element attrGroup = serializeAttributeGroupRef(doc, 
															   (XmlSchemaAttributeGroupRef)obj, schema);
                extension.appendChild(attrGroup);
            }
        }
    
        if(extensionObj.anyAttribute != null){
            Element anyAttribute = serializeAnyAttribute(doc, 
														 extensionObj.anyAttribute, schema);
            extension.appendChild(anyAttribute);
        }
        
        return extension;
    }    
    /************************************************************************
	 * Element serializeAnyAttribute(Document doc,
	 *    XmlSchemaAnyAttribute anyAttributeObj, XmlSchema schema)
	 *   
	 * Each member of complex type will be appended and pass the element
	 * created.  Complex type processed according to w3c Recommendation
	 * May 2 2001. 
	 *
	 * Parameter:
	 * doc                 - Document the parent use.
	 * anyAttributeObj     - XmlSchemaAnyAttribute 
	 *                       that will be serialized.
	 * schema              - Schema Document object of the parent.
	 *
	 * Return:
	 * Element of any attribute element.
	 ************************************************************************/
    Element serializeAnyAttribute(Document doc,
								  XmlSchemaAnyAttribute anyAttributeObj, XmlSchema schema){
        
        Element anyAttribute = createNewElement(doc, "anyAttribute", 
												schema.schema_ns_prefix, schema.SCHEMA_NS);
        
        
        if(anyAttributeObj.namespace != null)
            anyAttribute.setAttributeNS(schema.SCHEMA_NS, "namespace", 
										anyAttributeObj.namespace);
        
        if(anyAttributeObj.id != null)
            anyAttribute.setAttributeNS(schema.SCHEMA_NS, "id", 
										anyAttributeObj.id);
        
        if(anyAttributeObj.processContent != null){
            String processContent = anyAttributeObj.processContent.getValue();
            processContent = convertString(processContent);
            anyAttribute.setAttributeNS(schema.SCHEMA_NS, "processContents", 
										processContent);
        }
        if(anyAttributeObj.annotation != null){
            Element annotation = serializeAnnotation(doc, 
													 anyAttributeObj.annotation, schema);
            anyAttribute.appendChild(annotation);
        }

        return anyAttribute;
    }    
    /************************************************************************
	 * Element serializeAttributeGroupRef(Document doc, 
	 *    XmlSchemaAttributeGroupRef attributeGroupObj, XmlSchema schema) 
	 *   throws XmlSchemaSerializerException
	 *   
	 * Each member of complex type will be appended and pass the element
	 * created.  Complex type processed according to w3c Recommendation
	 * May 2 2001. 
	 *
	 * Parameter:
	 * doc                 - Document the parent use.
	 * attributeGroupObj     - XmlSchemaAttributeGroupRef 
	 *                       that will be serialized.
	 * schema              - Schema Document object of the parent.
	 *
	 * Return:
	 * Element of attribute group ref that part of type.
	 ************************************************************************/
    Element serializeAttributeGroupRef(Document doc, 
									   XmlSchemaAttributeGroupRef attributeGroupObj, XmlSchema schema) 
        throws XmlSchemaSerializerException{
        
        Element attributeGroupRef = createNewElement(doc, "attributeGroup", 
													 schema.schema_ns_prefix, schema.SCHEMA_NS);
        
        if(attributeGroupObj.refName != null){
            String refName = resolveQualifiedName(attributeGroupObj.refName, 
												  schema);
            attributeGroupRef.setAttributeNS(schema.SCHEMA_NS, "ref", refName);
        }else
            throw new XmlSchemaSerializerException("Attribute group must have "
												   + "ref name set");
        
        if(attributeGroupObj.id != null)
            attributeGroupRef.setAttributeNS(schema.SCHEMA_NS,"id", 
											 attributeGroupObj.id);
        
        if(attributeGroupObj.annotation != null){
            Element annotation = serializeAnnotation(doc,
													 attributeGroupObj.annotation, schema);
            attributeGroupRef.appendChild(annotation);
        }
        return attributeGroupRef;
    }
    /************************************************************************
	 * Element serializeAttributeGroup(Document doc, 
	 *    XmlSchemaAttributeGroup attributeGroupObj, XmlSchema schema) 
	 *    throws XmlSchemaSerializerException{
	 *   
	 * Each member of complex type will be appended and pass the element
	 * created.  Complex type processed according to w3c Recommendation
	 * May 2 2001. 
	 *
	 * Parameter:
	 * doc                 - Document the parent use.
	 * attributeGroupObj     - XmlSchemaAttributeGroup
	 *                       that will be serialized.
	 * schema              - Schema Document object of the parent.
	 *
	 * Return:
	 * Element of attribute group.
	 ************************************************************************/
    Element serializeAttributeGroup(Document doc, 
									XmlSchemaAttributeGroup attributeGroupObj, XmlSchema schema) 
        throws XmlSchemaSerializerException{
    
        Element attributeGroup = createNewElement(doc, "attributeGroup", 
												  schema.schema_ns_prefix, schema.SCHEMA_NS);
        
        if(attributeGroupObj.name != null)
            attributeGroup.setAttributeNS(schema.SCHEMA_NS, "name", 
										  attributeGroupObj.name);
        else
            throw new XmlSchemaSerializerException("Attribute group must"
												   + "have name");
        if(attributeGroupObj.id != null)
            attributeGroup.setAttributeNS(schema.SCHEMA_NS, "id", 
										  attributeGroupObj.id);
        
        if(attributeGroupObj.annotation != null){
            Element annotation = serializeAnnotation(doc,
													 attributeGroupObj.annotation, schema);
            attributeGroup.appendChild(annotation);
        }
        int attributesLength = attributeGroupObj.attributes.getCount();
        for(int i=0;i<attributesLength;i++){
            XmlSchemaObject obj = attributeGroupObj.attributes.getItem(i);
            
            if(obj instanceof XmlSchemaAttribute){
                Element attr = serializeAttribute(doc, (XmlSchemaAttribute)obj,
												  schema);
                attributeGroup.appendChild(attr);
            }else if(obj instanceof XmlSchemaAttributeGroupRef){
                Element attrGroup = serializeAttributeGroupRef(doc, 
															   (XmlSchemaAttributeGroupRef)obj, schema);
                attributeGroup.appendChild(attrGroup);
            }
        }
    
        if(attributeGroupObj.anyAttribute != null){
            Element anyAttribute = serializeAnyAttribute(doc, 
														 attributeGroupObj.anyAttribute, schema);
            attributeGroup.appendChild(anyAttribute);
        }
        
        return attributeGroup;
    }
    
    //recursively add any attribute, text and children append all 
    //found children base on parent as its root.
    private void appendElement(Document doc, Element parent, 
							   Node children, XmlSchema schema){
        Element elTmp = (Element) children;
        Element el = createNewElement(doc, elTmp.getTagName(), 
									  schema.schema_ns_prefix, schema.SCHEMA_NS);
        NamedNodeMap attributes = el.getAttributes();
        //check if child node has attribute  
        //create new element and append it if found
        int attributeLength = attributes.getLength();
        for(int i=0;i<attributeLength;i++){
            Node n = attributes.item(i); 
            //assuming attributes got to throw exception if not later
            el.setAttributeNS(schema.SCHEMA_NS,n.getNodeName(),
							  n.getNodeValue());
        }
        
        //check any descendant of this node
        //if there then append its child
        NodeList decendants = el.getChildNodes();
        int decendantLength = decendants.getLength();
        for(int i=0;i<decendantLength;i++){
            Node n = decendants.item(i);
            short nodeType = n.getNodeType();
            if(nodeType == Node.TEXT_NODE){
                String nValue = n.getNodeValue();
                Text t = doc.createTextNode(nValue);
                el.appendChild(t);
            }else if(nodeType == Node.ELEMENT_NODE){
                appendElement(doc, el, n, schema);
            }
        }
    }
    
    //break string with prefix into two parts part[0]:prefix , part[1]:namespace
    private static String[] getParts(String name){
        String[] parts = new String[2];		

        int index = name.indexOf(":");
        if( index > -1) {
			parts[0]= name.substring(0, index);
			parts[1]= name.substring(index + 1);
        } else {
			parts[0] = "";
			parts[1] = name;
        }		
        return parts;
    }
    
    //Convert given string to lower case or w3c standard
    private String convertString(String convert){
        String input = convert.trim();
        if(input.equals("All")){
            return "#all";
        }else
            return input.toLowerCase();
    }
    //Create new element with given local name and namespaces check whether
    //the prefix is there or not.
    private Element createNewElement(Document docs, String localName, 
									 String prefix, String namespace){
        String elementName = ((prefix.length()>0)? prefix += ":"  : "" )   
            + localName; 
        return docs.createElementNS(namespace, elementName);
    }

    //will search whether the prefix is available in global hash table, if it
    //is there than append the prefix to the element name.  If not then it will
    //create new prefix corresponding to that namespace and store that in 
    //hash table.  Finally add the new prefix and namespace to <schema> 
    //element
    private String resolveQualifiedName(QualifiedName names, 
										XmlSchema schemaObj){
        
        String namespace = names.getNameSpace();
        String type[] = getParts(names.getName());
        String typeName = (type.length > 1)? type[1]: type[0];
        String prefixStr;
        
        Object prefix = schema_ns.get(namespace);
        
        if(prefix==null){
            int magicNumber = new java.util.Random().nextInt(999);
            prefix = "gen" +  magicNumber;
            schema_ns.put(namespace, prefix);

            
            //setting xmlns in schema
            schemaElement.setAttributeNS("http://www.w3.org/2000/xmlns/", 
										 "xmlns:" +prefix.toString() ,  namespace);
        }
            
        prefixStr = prefix.toString();
        prefixStr = (prefixStr.trim().length()>0)?  prefixStr + ":" : "";

        return prefixStr + typeName;
    }
    
    //for each collection if it is an attribute serialize attribute and 
    //append that child to container element.
    void setupAttr(Document doc, XmlSchemaObjectCollection collectionObj, 
				   XmlSchema schema, Element container) throws XmlSchemaSerializerException{
        int collectionLength = collectionObj.getCount();
        for(int i=0;i<collectionLength;i++){
            XmlSchemaObject obj = collectionObj.getItem(i);
            if(obj instanceof XmlSchemaAttribute){
                XmlSchemaAttribute attr = (XmlSchemaAttribute)obj;
                Element attrEl = serializeAttribute(doc, attr, schema);
                container.appendChild(attrEl);
            }
            else if (obj instanceof XmlSchemaAttributeGroupRef){
                XmlSchemaAttributeGroupRef attr= (XmlSchemaAttributeGroupRef)obj;
                Element attrEl = serializeAttributeGroupRef(doc, attr, schema);
                container.appendChild(attrEl);
            }
        }
    }
    
	public static class XmlSchemaSerializerException extends Exception {
        
        public XmlSchemaSerializerException(String msg){
            super(msg);
        }
    }
}
