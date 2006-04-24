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
 * @author Srinath Perera(hemapani@openource.lk)
 * @author Susantha Kumara(susantha@opensource.lk, skumara@virtusa.com)
 * @author Samisa Abeysinghe (sabeysinghe@virtusa.com)
 */

package org.apache.axis.wsdl.wsdl2ws.c;

import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Iterator;
import java.util.Vector;
import java.util.HashSet;

import javax.xml.namespace.QName;

import org.apache.axis.wsdl.symbolTable.TypeEntry;
import org.apache.axis.wsdl.wsdl2ws.CUtils;
import org.apache.axis.wsdl.wsdl2ws.ParamWriter;
import org.apache.axis.wsdl.wsdl2ws.WSDL2Ws;
import org.apache.axis.wsdl.wsdl2ws.WrapperFault;
import org.apache.axis.wsdl.wsdl2ws.WrapperUtils;
import org.apache.axis.wsdl.wsdl2ws.info.Type;
import org.apache.axis.wsdl.wsdl2ws.info.WebServiceContext;

public class ParmHeaderFileWriter extends ParamWriter
{
    /**
     * @param wscontext
     * @param type
     * @throws WrapperFault
     */
    public ParmHeaderFileWriter(WebServiceContext wscontext, Type type) throws WrapperFault
    {
        super(wscontext, type);
    }

    /* (non-Javadoc)
     * @see org.apache.axis.wsdl.wsdl2ws.SourceWriter#writeSource()
     */
    public void writeSource() throws WrapperFault
    {
        try
        {
            this.writer = new BufferedWriter(new FileWriter(getFilePath(), false));
            writeClassComment();

            // if this headerfile not defined define it 
            this.writer.write("#if !defined(__" + classname.toUpperCase() + "_H__INCLUDED_)\n");
            this.writer.write("#define __" + classname.toUpperCase() + "_H__INCLUDED_\n\n");
            
            if (type.isSimpleType())
                writeSimpleTypeWithEnumerations();
            else
            {
                writePreprocessorStatements();
                this.writer.write("typedef struct " + classname + "Tag {\n");
                this.writer.write("\n");
                writeAttributes();
                this.writer.write("\n");
                this.writer.write("} " + classname + ";\n\n");
                writeFunctionPrototypes();
            }
            
            writer.write("\n");
            this.writer.write("#endif /* !defined(__" + classname.toUpperCase() + "_H__INCLUDED_)*/\n");
            
            writer.flush();
            writer.close();
            
            if (WSDL2Ws.verbose)
                System.out.println(getFilePath().getAbsolutePath() + " created.....");
        }
        catch (IOException e)
        {
            e.printStackTrace();
            throw new WrapperFault(e);
        }
    }


    /**
     * @throws WrapperFault
     */
    protected void writeSimpleTypeWithEnumerations() throws WrapperFault
    {
        try
        {
            writer.write("#include <axis/AxisUserAPI.h>\n");
            writer.write("#include <axis/AxisUserAPIArrays.h>\n");
            writer.write("\n");

            Vector restrictionData = type.getEnumerationdata();
            if (restrictionData == null)
                return;

            TypeEntry baseEType = (TypeEntry) restrictionData.firstElement();
            QName baseType = baseEType.getQName();
            if (!CUtils.isSimpleType(baseType))
                return;

            String langTypeName = CUtils.getclass4qname(baseType);
            writer.write("typedef ");
            if (CUtils.isPointerType(CUtils.getclass4qname(baseType)) 
                    || "xsdc__base64Binary".equals(CUtils.getclass4qname(baseType)) 
                    || "xsdc__hexBinary".equals(CUtils.getclass4qname(baseType)))
            {
                writer.write(langTypeName + " " + classname + ";\n");
                writer.write("typedef " + langTypeName + "_Array " + classname + "_Array;\n");
                
                for (int i = 1; i < restrictionData.size(); i++)
                {
                    QName value = (QName) restrictionData.elementAt(i);
                    if ("enumeration".equals(value.getLocalPart()))
                    {
                        writer.write("static const " + classname + " "
                                + classname + "_" + value.getNamespaceURI()
                                + " = \"" + value.getNamespaceURI() + "\";\n");
                    } 
                    else if ("maxLength".equals(value.getLocalPart()))
                    {
                        writer.write("static const int " + classname
                                + "_MaxLength = " + value.getNamespaceURI() + ";\n");
                    } 
                    else if ("minLength".equals(value.getLocalPart()))
                    {
                        writer.write("static const int " + classname
                                + "_MinLength = " + value.getNamespaceURI() + ";\n");
                    }
                }
            } 
            else if ("int".equals(baseType.getLocalPart()))
            {
                if (restrictionData.size() > 1)
                {
                    //there are enumerations or min/maxInclusive
                    boolean isEnum = false;
                    boolean hasRestrictionItems = false;
                    for (int i = 1; i < restrictionData.size(); i++)
                    {
                        QName value = (QName) restrictionData.elementAt(i);
                        if ("enumeration".equals(value.getLocalPart()))
                        {
                            isEnum = true;
                            if (i > 1)
                                writer.write(", ");
                            else
                                writer.write(" enum { ");

                            writer.write("ENUM" + classname.toUpperCase() + "_"
                                    + value.getNamespaceURI() + "="
                                    + value.getNamespaceURI());
                        } 
                        else if ("minInclusive".equals(value.getLocalPart()))
                        {
                            hasRestrictionItems = true;
                            if (i <= 1)
                                writer.write(langTypeName + " " + classname + ";\n");
                            
                            writer.write("static const int " + classname
                                    + "_MinInclusive = " + value.getNamespaceURI() + ";\n");
                        } 
                        else if ("maxInclusive".equals(value.getLocalPart()))
                        {
                            hasRestrictionItems = true;
                            if (i <= 1)
                                writer.write(langTypeName + " " + classname + ";\n");

                            writer.write("static const int " + classname
                                    + "_MaxInclusive = " + value.getNamespaceURI() + ";\n");
                        }
                    }
                    
                    if (isEnum)
                        writer.write("} " + classname + ";\n");
                    else if (!hasRestrictionItems)
                        writer.write(langTypeName + " " + classname + ";\n");
                } 
                else
                    writer.write(langTypeName + " " + classname + ";\n");
            } 
            else
            {
                writer.write(langTypeName + " " + classname + ";\n");
                for (int i = 1; i < restrictionData.size(); i++)
                {
                    QName value = (QName) restrictionData.elementAt(i);
                    if ("enumeration".equals(value.getLocalPart()))
                    {
                        writer.write("static const " + classname + " "
                                + classname + "_" + value.getNamespaceURI()
                                + " = \"" + value.getNamespaceURI() + "\";\n");
                    }
                }
            }
        }
        catch (IOException e)
        {
            throw new WrapperFault(e);
        }
    }
    
    
    /* (non-Javadoc)
     * @see org.apache.axis.wsdl.wsdl2ws.BasicFileWriter#writeAttributes()
     */
    protected void writeAttributes() throws WrapperFault
    {
        int anyCounter = 0;
        
        if (type.isArray())
            return;
        
        try
        {
            for (int i = 0; i < attribs.length; i++)
            {
                attribs[i].setParamName( CUtils.sanitiseAttributeName( classname, attribs[i].getParamName()));
                
                if (isElementNillable(i) 
                        || attribs[i].isArray() 
                        || isElementOptional(i) 
                        && !attribs[i].getAllElement())
                {
                    if(attribs[i].isAnyType())
                    {
                        anyCounter += 1;
                        writer.write(
                                  getCorrectParmNameConsideringArraysAndComplexTypes(attribs[i])
                                + " * " + attribs[i].getParamName()
                                + Integer.toString(anyCounter)
                                + ";\n");
                    }
                    else if( attribs[i].isArray())
                    {
                        String paramName = getCorrectParmNameConsideringArraysAndComplexTypes(attribs[i]);
                        if (!paramName.endsWith("*"))
                            paramName += " *";

                        writer.write(paramName + " " + attribs[i].getParamName() + ";\n");
                    }
                    else if(attribs[i].getChoiceElement() && !isElementNillable(i))
                        writer.write(
                               getCorrectParmNameConsideringArraysAndComplexTypes(attribs[i])
                             + " " + attribs[i].getParamName()
                             + ";\n");
                    else
                        writer.write(
                                   getCorrectParmNameConsideringArraysAndComplexTypes(attribs[i])
                                 + " * " + attribs[i].getParamName()
                                 + ";\n");
                } 
                else if(attribs[i].getAllElement() || attribs[i].getChoiceElement() )
                {
                    writer.write(
                               getCorrectParmNameConsideringArraysAndComplexTypes(attribs[i])
                             + " " + attribs[i].getParamName()
                             + ";\n");
                }
                else if(attribs[i].isAnyType())
                {
                    anyCounter += 1;
                    writer.write(
                              getCorrectParmNameConsideringArraysAndComplexTypes(attribs[i])
                            + " " + attribs[i].getParamName()
                            + Integer.toString(anyCounter)
                            + ";\n");
                }                   
                else
                {
                    writer.write(
                                  getCorrectParmNameConsideringArraysAndComplexTypes(attribs[i])
                                + " " + attribs[i].getParamNameWithoutSymbols()
                                + ";\n");
                }
            }
            
            if (extensionBaseAttrib != null &&
                getCorrectParmNameConsideringArraysAndComplexTypes(extensionBaseAttrib) != null)
            {
                writer.write(
                               getCorrectParmNameConsideringArraysAndComplexTypes(extensionBaseAttrib)
                             + " "
                             + extensionBaseAttrib.getParamNameWithoutSymbols() + ";\n");
            }            
        }
        catch (IOException e)
        {
            throw new WrapperFault(e);
        }
    }

    /* (non-Javadoc)
     * @see org.apache.axis.wsdl.wsdl2ws.BasicFileWriter#writeConstructors()
     */
    protected void writeConstructors() throws WrapperFault
    {}

    /* (non-Javadoc)
     * @see org.apache.axis.wsdl.wsdl2ws.BasicFileWriter#writeDestructors()
     */
    protected void writeDestructors() throws WrapperFault
    {}

    /* (non-Javadoc)
     * @see org.apache.axis.wsdl.wsdl2ws.BasicFileWriter#writeMethods()
     */
    protected void writeMethods() throws WrapperFault
    {}

    /* (non-Javadoc)
     * @see org.apache.axis.wsdl.wsdl2ws.BasicFileWriter#getFilePath()
     */
    protected File getFilePath() throws WrapperFault
    {
        return this.getFilePath(false);
    }

    /* (non-Javadoc)
     * @see org.apache.axis.wsdl.wsdl2ws.BasicFileWriter#getFilePath(boolean)
     */
    protected File getFilePath(boolean useServiceName) throws WrapperFault
    {
        String targetOutputLocation = this.wscontext.getWrapInfo().getTargetOutputLocation();
        if (targetOutputLocation.endsWith("/"))
            targetOutputLocation = targetOutputLocation.substring(0,targetOutputLocation.length() - 1);
        new File(targetOutputLocation).mkdirs();

        String fileName = targetOutputLocation + "/" + classname + CUtils.C_HEADER_SUFFIX;

        if (useServiceName)
        {
            fileName = targetOutputLocation + "/"
                    + this.wscontext.getSerInfo().getServicename() + "_"
                    + classname + CUtils.C_HEADER_SUFFIX;
        }

        return new File(fileName);
    }

    protected void writeFunctionPrototypes() throws WrapperFault
    {
        Iterator types = wscontext.getTypemap().getTypes().iterator();
        HashSet typeSet = new HashSet();
        String typeName;
        Type type;
        try
        {
            while (types.hasNext())
            {
                type = (Type) types.next();
                
                if (type.isSimpleType())
                    continue;
                
                if (type.isArray())
                    continue;
                
                typeName = type.getLanguageSpecificName();
                if (typeName.startsWith(">") || !typeName.equals(classname))
                    continue;
                
                typeSet.add(typeName);
            }
            
            Iterator itr = typeSet.iterator();
            while (itr.hasNext())
            {
                typeName = itr.next().toString();
                this.writer.write("extern int Axis_DeSerialize_" + typeName
                             + "(" + typeName + "* param, AXISCHANDLE pDZ);\n");
                this.writer.write("extern void* Axis_Create_" + typeName + "(void);\n");
                this.writer.write("extern void Axis_Delete_" + typeName
                             + "(" + typeName + "* param, AxiscBool bArray, int nSize);\n");
                this.writer.write("extern int Axis_Serialize_" + typeName
                             + "(" + typeName + "* param, AXISCHANDLE pSZ, AxiscBool bArray);\n");
                this.writer.write("extern int Axis_GetSize_" + typeName + "(void);\n\n");
            }
        }
        catch (IOException e)
        {
            throw new WrapperFault(e);
        }
    }
    

    /* (non-Javadoc)
     * @see org.apache.axis.wsdl.wsdl2ws.BasicFileWriter#writePreprocessorStatements()
     */
    protected void writePreprocessorStatements() throws WrapperFault
    {
        try
        {
            Type atype;
            Iterator types = this.wscontext.getTypemap().getTypes().iterator();

            writer.write("#include <axis/Axis.h>\n");
            writer.write("#include <axis/GDefine.h>\n");
            writer.write("#include <axis/AxisUserAPI.h>\n");
            writer.write("#include <axis/AxisUserAPIArrays.h>\n");
            writer.write("#include <axis/SoapEnvVersions.h>\n");
            writer.write("#include <axis/WSDDDefines.h>\n");
            writer.write("#include <axis/TypeMapping.h>\n");

            if (this.type.isFault())
                writer.write("#include <axis/SoapFaultException.h>\n");
            
            HashSet typeSet = new HashSet();
            for (int i = 0; i < attribs.length; i++)
            {
                if ((attribs[i].isArray()) && 
                        !(attribs[i].isSimpleType() || attribs[i].getType().isSimpleType()))
                    typeSet.add(attribs[i].getTypeName() + "_Array");

                if (!(attribs[i].isSimpleType() || attribs[i].isAnyType()))
                    typeSet.add(attribs[i].getTypeName());
            }
            
            Iterator itr = typeSet.iterator();
            while (itr.hasNext())
            {
                writer.write("#include \"" + itr.next().toString() + CUtils.C_HEADER_SUFFIX + "\"\n");
            }

            writer.write("\n");
            //Local name and the URI for the type
            writer.write("/*Local name and the URI for the type*/\n");
            writer.write("static const char* Axis_URI_" + classname + " = \""
                    + type.getName().getNamespaceURI() + "\";\n");
            writer.write("static const char* Axis_TypeName_" + classname
                    + " = \"" + type.getName().getLocalPart() + "\";\n\n");
        }
        catch (IOException e)
        {
            throw new WrapperFault(e);
        }
    }
}
