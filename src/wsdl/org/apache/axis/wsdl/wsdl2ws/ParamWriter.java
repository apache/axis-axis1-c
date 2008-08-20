/*
 *   Copyright 2003-2004 The Apache Software Foundation.
// (c) Copyright IBM Corp. 2004, 2005 All Rights Reserved
 *
 *   Licensed under the Apache License, Version 2.0 (the "License");
 *   you may not use this file except in compliance with the License.
 *   You may obtain a copy of the License at
 *
 *       http://www.apache.org/licenses/LICENSE-2.0
 *
 *   Unless required by applicable law or agreed to in writing, software
 *   distributed under the License is distributed on an "AS IS" BASIS,
 *   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *   See the License for the specific language governing permissions and
 *   limitations under the License.
 */

/**
 * This class has the basic logic of the genarating Param classes (Type wrappers).
 * The responsibility of writing serializing and desirializing code is given to the
 * concreate subclasses.
 * @author JayaKumaran
 * @author Susantha Kumara(susantha@opensource.lk, skumara@virtusa.com)
 */

package org.apache.axis.wsdl.wsdl2ws;

import java.io.IOException;
import java.util.ArrayList;
import java.util.Iterator;

import org.apache.axis.wsdl.wsdl2ws.info.ParameterInfo;
import org.apache.axis.wsdl.wsdl2ws.info.Type;
import org.apache.axis.wsdl.wsdl2ws.info.WebServiceContext;
import org.apache.axis.wsdl.symbolTable.CContainedAttribute;
import org.apache.axis.wsdl.symbolTable.CElementDecl;

public abstract class ParamWriter extends BasicFileWriter
{
    protected ParameterInfo extensionBaseAttrib = null;

    // first attributeParamCount of attribs will be treated as attributes
    protected int attributeParamCount = 0;
   
    // array of parameter types and attributes 
    protected ParameterInfo[] attribs;

    protected WebServiceContext wscontext;

    // Type of this param 
    protected Type type;

    public ParamWriter(WebServiceContext wscontext, Type type) throws WrapperFault
    {
        super(CUtils.getLanguageTypeName4Type(type));
        this.wscontext = wscontext;
        this.type = type;
        populateAttribList();
    }

    protected void writeClassComment() throws WrapperFault
    {
        try
        {
            writer.write("/*\n");
            writer.write(" * Copyright 2003-2006 The Apache Software Foundation.\n\n");
            writer.write(" *\n");
            writer.write(" * Licensed under the Apache License, Version 2.0 (the \"License\");\n");
            writer.write(" * you may not use this file except in compliance with the License.\n");
            writer.write(" * You may obtain a copy of the License at\n");
            writer.write(" *\n");
            writer.write(" *\t\thttp://www.apache.org/licenses/LICENSE-2.0\n");
            writer.write(" *\n");
            writer.write(" * Unless required by applicable law or agreed to in writing, software\n");
            writer.write(" * distributed under the License is distributed on an \"AS IS\" BASIS,\n");
            writer.write(" * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.\n");
            writer.write(" * See the License for the specific language governing permissions and\n");
            writer.write(" * limitations under the License.\n");
            writer.write(" *\n");
            writer.write(" * This file was auto-generated by the Axis C++ Web Service Generator (WSDL2Ws)\n");
            writer.write(" * This file contains functions to manipulate type " + this.classname + "\n");
            writer.write(" */\n\n");
        }
        catch (IOException e)
        {
            throw new WrapperFault(e);
        }
    }

    /* genarate the attribs array */
    private void populateAttribList() throws WrapperFault
    {
        CElementDecl elemi = type.getExtensionBaseType();
        if (elemi != null)
        {
            extensionBaseAttrib = new ParameterInfo();
            extensionBaseAttrib.setParamName(elemi.getName().getLocalPart(), wscontext.getTypemap());
            
            Type elementType = elemi.getType();

            if (CUtils.getSimpleType(elementType.getName()) != null)
                extensionBaseAttrib.setTypeName(CUtils.getSimpleType(elementType.getName()));
            else
            {
                extensionBaseAttrib.setTypeName(elementType.getLanguageSpecificName());
                extensionBaseAttrib.setSimpleType(false);
            }
            
            extensionBaseAttrib.setType(elemi.getType());
            extensionBaseAttrib.setElementName(elemi.getName());
        }
        
        ArrayList attribfields = new ArrayList();
        ArrayList elementfields = new ArrayList();

        Iterator names = type.getAttributes();
        if (names != null)
            while (names.hasNext())
                attribfields.add(names.next());
        
        names = type.getElementnames();
        while (names.hasNext())
        {
            elementfields.add(names.next());
        }
        
        int intAttrFieldSz = attribfields.size();
        attributeParamCount = intAttrFieldSz;
        int intEleFieldSz = elementfields.size();
        this.attribs = new ParameterInfo[intAttrFieldSz + intEleFieldSz];
        for (int i = 0; i < intAttrFieldSz; i++)
        {
            CContainedAttribute attr = (CContainedAttribute)attribfields.get(i);
            
            this.attribs[i] = new ParameterInfo();
            this.attribs[i].setParamName(attr.getName(), wscontext.getTypemap());
            if (CUtils.isSimpleType(attr.getType().getName()))
                this.attribs[i].setTypeName(CUtils.getSimpleType(attr.getType().getName()));
            else
            {
                this.attribs[i].setTypeName(attr.getType().getLanguageSpecificName());
                this.attribs[i].setSimpleType(false);
            }
            this.attribs[i].setType(attr.getType());
            this.attribs[i].setAttribute(true);
            this.attribs[i].setElementName(attr.getType().getName());
            this.attribs[i].setOptional(attr.isOptional());           
        }

        for (int i = intAttrFieldSz; i < intAttrFieldSz + intEleFieldSz; i++)
        {
            this.attribs[i] = new ParameterInfo();
            this.attribs[i].setParamName((String) elementfields.get(i - attributeParamCount), wscontext.getTypemap());
            CElementDecl elem = type.getElementForElementName(this.attribs[i].getParamName());
            Type elementType = elem.getType();
            if (CUtils.isAnyType(elementType.getName()))
                this.attribs[i].setAnyType(true);

            if (CUtils.isSimpleType(elementType.getName()))
                this.attribs[i].setTypeName(CUtils.getSimpleType(elementType.getName()));
            else
            {
                this.attribs[i].setTypeName(elementType.getLanguageSpecificName());
                this.attribs[i].setSimpleType(false);
            }
            
            this.attribs[i].setType(elementType);
            this.attribs[i].setElementName(elem.getName());
            this.attribs[i].setChoiceElement(elem.getChoiceElement());
            this.attribs[i].setAllElement(elem.getAllElement());
            this.attribs[i].setNsQualified(elem.getNsQualified());            
            this.attribs[i].setMinOccurs(elem.getMinOccurs());
            this.attribs[i].setMaxOccurs(elem.getMaxOccurs());
            this.attribs[i].setNillable(elem.isNillable());

            
            if (elementType.isArray())
            { 
                Type arrayType = CUtils.getArrayType(elementType);
                
                //get contained type
                this.attribs[i].setArray(true);
                if (CUtils.isSimpleType(arrayType.getName()))
                {
                    this.attribs[i].setTypeName(CUtils.getSimpleType(arrayType.getName()));
                    this.attribs[i].setSimpleType(true);
                }
                else
                {
                    this.attribs[i].setTypeName(arrayType.getLanguageSpecificName());
                    this.attribs[i].setSimpleType(false);
                }
                
                this.attribs[i].setType(arrayType);
            }
            else if (elem.getMaxOccurs() > 1)
            {
                //arrays but the same type as was set above
                this.attribs[i].setArray(true);
            }
            
            if (elem.getMinOccurs() == 0)
                this.attribs[i].setOptional(true);
        }
    }

    protected String getCorrectParmNameConsideringArraysAndComplexTypes(ParameterInfo attrib)
        throws WrapperFault
    {
        if (attrib.isArray())
        {
            if (attrib.isSimpleType())
                return CUtils.getArrayNameforSimpleType(attrib.getTypeName());
            else
                return CUtils.getArrayNameForComplexType(attrib.getSchemaName());
        }
        else if (!(attrib.isSimpleType() || attrib.getType().isSimpleType()))
            return attrib.getTypeName() + "*";
        else
        {            
            // If pointer type, just return type
            boolean isPtrType;
            if (attrib.isSimpleType())
                isPtrType = CUtils.isPointerType(attrib.getTypeName());
            else 
                isPtrType = CUtils.isPointerType(CUtils.getSimpleType(attrib.getType().getBaseType()));
            
            if (isPtrType)
                return attrib.getTypeName();
            
            //  if the element is nillable, a choice or all element, or optional, define as ptr
            if(attrib.getChoiceElement() || attrib.getAllElement() || attrib.isNillable() || attrib.isOptional())
                    return attrib.getTypeName() + "*";

            // Just return type
            return attrib.getTypeName();
        }
    }
    
    protected boolean isElementNillable(int index)
    {
        boolean bNillable = false;
        
        if (!attribs[index].isArray())
        {
            if (attribs[index].isSimpleType())
            {
                if (!CUtils.isPointerType(attribs[index].getTypeName()))
                    bNillable = attribs[index].isNillable();
            }
            else if (attribs[index].getType().isSimpleType())
            {
                if (!CUtils.isPointerType(CUtils.getSimpleType(attribs[index].getType().getBaseType())))
                    bNillable = attribs[index].isNillable();
            }
        }
        return bNillable;
    }

    protected boolean isElementOptional(int index)
    {
        boolean bOptional = false;
        
        if (!attribs[index].isArray())
        {
            if (attribs[index].isSimpleType())
            {
                if (!CUtils.isPointerType(attribs[index].getTypeName()))
                    bOptional = attribs[index].isOptional();
            }
            else if (attribs[index].getType().isSimpleType())
            {
                if (!CUtils.isPointerType(CUtils.getSimpleType(attribs[index].getType().getBaseType())))
                    bOptional = attribs[index].isOptional();
            }
        }
        return bOptional;
    }
}
