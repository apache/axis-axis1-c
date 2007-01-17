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
import java.util.HashSet;
import java.util.Iterator;
import java.util.Vector;

import javax.xml.namespace.QName;

import org.apache.axis.wsdl.symbolTable.TypeEntry;
import org.apache.axis.wsdl.wsdl2ws.CUtils;
import org.apache.axis.wsdl.wsdl2ws.ParamWriter;
import org.apache.axis.wsdl.wsdl2ws.WSDL2Ws;
import org.apache.axis.wsdl.wsdl2ws.WrapperFault;
import org.apache.axis.wsdl.wsdl2ws.info.Type;
import org.apache.axis.wsdl.wsdl2ws.info.WebServiceContext;

public class ParmHeaderFileWriter extends ParamWriter
{
    public ParmHeaderFileWriter(WebServiceContext wscontext, Type type) throws WrapperFault
    {
        super(wscontext, type);
    }

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
                writeSimpleTypeWithRestrictions();
            else
            {
                writePreprocessorStatements();

                this.writer.write("\n#ifdef __cplusplus\n extern \"C\" {\n#endif\n\n");

                writer.write("\n");
                writer.write("/* ********************************************************************* */\n");
                writer.write("/* --- Custom type                                                   --- */\n");
                writer.write("/* ********************************************************************* */\n");
                writer.write("\n");                
                
                this.writer.write("typedef struct " + classname + "Tag {\n");
                writeAttributes();
                this.writer.write("} " + classname + ";\n\n");
                
                writeFunctionPrototypes();
                this.writer.write("\n#ifdef __cplusplus\n }\n#endif\n");
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
    protected void writeSimpleTypeWithRestrictions() throws WrapperFault
    {
        try
        {
            writer.write("#include <axis/AxisUserAPI.h>\n");

            Vector restrictionData = type.getEnumerationdata();
            if (restrictionData == null)
                return;            
            
            TypeEntry baseEType = (TypeEntry) restrictionData.firstElement();
            QName baseType = baseEType.getQName();
            if (!CUtils.isSimpleType(baseType))
                return;
            
            String baseTypeName = CUtils.getclass4qname(baseType);
            String langTypeName;
            
            // User defined simple type based on another user-defined simple type
            String  restrictionBaseType = type.getRestrictionBaseType();
            if (null != restrictionBaseType )
            {  
                langTypeName = CUtils.sanitiseClassName(restrictionBaseType);               
                writer.write( "#include \"" + langTypeName + ".hpp\"\n\n");
            }
            else
                langTypeName = baseTypeName;
            


            writer.write("\n");
            writer.write("/* ********************************************************************* */\n");
            writer.write("/* --- Simple types and restrictions                                 --- */\n");
            writer.write("/* ********************************************************************* */\n");
            writer.write("\n");  
            
            // Need to determine what to use for enumeration identifiers.  That is, if a string
            // enumeration value is "foobar", then we can generate an enumerator identifer of 
            // [type]_foobar.  However, if the value is "foo bar", then we are forced to generate
            // identifiers in the following format: [type]_ENUM[#], where [#] is a number starting
            // at 1. We need to go through all the enumerators to determine what to do.
            boolean validEnumIdentifier = true;
            for (int i = 1; i < restrictionData.size(); i++)
            {
                QName value = (QName) restrictionData.elementAt(i);
                if ("enumeration".equals(value.getLocalPart()))
                    validEnumIdentifier = CUtils.isValidCIdentifier(value.getNamespaceURI(), false);
                if (!validEnumIdentifier)
                    break;
            }
            
            writer.write("typedef ");
            if (CUtils.isPointerType(baseTypeName) 
                    || "xsdc__base64Binary".equals(baseTypeName) 
                    || "xsdc__hexBinary".equals(baseTypeName))
            {
                writer.write(langTypeName + " " + classname + ";\n");
                writer.write("typedef " + langTypeName + "_Array " + classname + "_Array;\n");
                writer.write("\n");
                
                for (int i = 1; i < restrictionData.size(); i++)
                {
                    QName value = (QName) restrictionData.elementAt(i);
                    if ("enumeration".equals(value.getLocalPart()))
                    {
                        writer.write("static const " + classname + " " + classname + "_");
                        if (validEnumIdentifier)
                            writer.write(value.getNamespaceURI());
                        else
                            writer.write("ENUM" + i);
                        writer.write(" = \"" + value.getNamespaceURI() + "\";\n");
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
                writer.write(langTypeName + " " + classname + ";\n");
                writer.write("typedef " + langTypeName + "_Array " + classname + "_Array;\n");
            
                if (restrictionData.size() > 1)
                {
                    //there are enumerations or min/maxInclusive
                    boolean isEnum = false;

                    for (int i = 1; i < restrictionData.size(); i++)
                    {
                        QName value = (QName) restrictionData.elementAt(i);
                        if ("enumeration".equals(value.getLocalPart()))
                        {
                            isEnum = true;
                            if (i > 1)
                                writer.write(", ");
                            else
                                writer.write("typedef enum { ");

                            writer.write("ENUM" + classname.toUpperCase() + "_"
                                    + value.getNamespaceURI() + "="
                                    + value.getNamespaceURI());
                        } 
                        else if ("minInclusive".equals(value.getLocalPart()))
                        {
                            writer.write("static const int " + classname
                                    + "_MinInclusive = " + value.getNamespaceURI() + ";\n");
                        } 
                        else if ("maxInclusive".equals(value.getLocalPart()))
                        {
                            writer.write("static const int " + classname
                                    + "_MaxInclusive = " + value.getNamespaceURI() + ";\n");
                        }
                    }
                    
                    if (isEnum)
                        writer.write("} " + classname + "_Enum;\n");
                } 
            } 
            else
            {
                writer.write(langTypeName + " " + classname + ";\n");
                writer.write("typedef " + langTypeName + "_Array " + classname + "_Array;\n");
                
                for (int i = 1; i < restrictionData.size(); i++)
                {
                    QName value = (QName) restrictionData.elementAt(i);
                    if ("enumeration".equals(value.getLocalPart()))
                    {
                        writer.write("static const " + classname + " " + classname + "_");
                        if (validEnumIdentifier)
                            writer.write(value.getNamespaceURI());
                        else
                            writer.write("ENUM" + i);
                        writer.write(" = \"" + value.getNamespaceURI() + "\";\n");
                    }
                }
            }
        }
        catch (IOException e)
        {
            throw new WrapperFault(e);
        }
    }
    
    protected void writeAttributes() throws WrapperFault
    {
        int anyCounter = 0;
        
        if (type.isArray())
            return;
        
        try
        {
            for (int i = 0; i < attribs.length; i++)
            {  
                // Ensure field name is valid and does not cause conflict with class names
                String sanitizedAttrName = CUtils.sanitiseAttributeName(attribs[i].getParamName());
                if (CUtils.classExists(wscontext, sanitizedAttrName))
                    sanitizedAttrName += "_Ref";
                attribs[i].setParamName(sanitizedAttrName);
                
                // Following will set the correct type 
                String paramType = getCorrectParmNameConsideringArraysAndComplexTypes(attribs[i]);
                
                // Following will set param name - if anyType, we index param name
                String paramName = attribs[i].getParamName();
                if(attribs[i].isAnyType())
                {
                    anyCounter += 1;
                    paramName  += Integer.toString(anyCounter);
                    
                    paramType = "Axisc" + paramType;
                }
                
                // we pass arrays as pointers - ensure this
                if (attribs[i].isArray())
                {
                    // TODO - work on removing the following if-check, should not be needed if we
                    // let getCorrectParmNameConsideringArraysAndComplexTypes() perform check.
                    if (!paramType.endsWith("*"))
                        paramType += "*";                 
                }

                // Print out field.
                writer.write("\t" + paramType + " " + paramName + ";\n");
            }
            
            if (extensionBaseAttrib != null &&
                getCorrectParmNameConsideringArraysAndComplexTypes(extensionBaseAttrib) != null)
            {
                writer.write("\t"
                             + getCorrectParmNameConsideringArraysAndComplexTypes(extensionBaseAttrib)
                             + "  "
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
                if ((type.isAnonymous() && !type.isExternalized())
                        || !typeName.equals(classname))
                    continue;
                
                typeSet.add(typeName);
            }
            
            Iterator itr = typeSet.iterator();
            
            if (itr.hasNext())
            {
                writer.write("\n");
                writer.write("/* ********************************************************************* */\n");
                writer.write("/* --- Functions to create/delete, serialize/deserialize custom type --- */\n");
                writer.write("/* ********************************************************************* */\n");
                writer.write("\n");                
            }
            
            while (itr.hasNext())
            {
                typeName = itr.next().toString();
                this.writer.write("extern int Axis_DeSerialize_" + typeName
                             + "(" + typeName + "* param, AXISCHANDLE pDZ);\n");
                this.writer.write("extern void* Axis_Create_" + typeName + "(int nSize);\n");
                this.writer.write("extern void Axis_Delete_" + typeName
                             + "(" + typeName + "* param, int nSize);\n");
                this.writer.write("extern int Axis_Serialize_" + typeName
                             + "(" + typeName + "* param, AXISCHANDLE pSZ, AxiscBool bArray);\n\n");
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
            writer.write("#include <axis/SoapEnvVersions.h>\n");
            writer.write("#include <axis/WSDDDefines.h>\n");
            writer.write("#include <axis/TypeMapping.h>\n");

            if (this.type.isFault())
                writer.write("#include <axis/SoapFaultException.h>\n");
            
            HashSet typeSet = new HashSet();
            for (int i = 0; i < attribs.length; i++)
            {
                String basicType = attribs[i].getTypeName();
                Type theType = attribs[i].getType();

                if (theType.isRestriction() && !CUtils.isSimpleType(basicType))
                    typeSet.add(basicType);
                else if (!attribs[i].isSimpleType())
                {
                    if ((attribs[i].isArray()) && !theType.isSimpleType())
                        typeSet.add(basicType + "_Array");
    
                    if (!attribs[i].isAnyType())
                        typeSet.add(basicType);
                }
            }
            
            // TODO we really do not support xsd:extension correctly or completely!
            if (extensionBaseAttrib != null 
                    && getCorrectParmNameConsideringArraysAndComplexTypes(extensionBaseAttrib) != null)
            {
                String extBaseType = getCorrectParmNameConsideringArraysAndComplexTypes(extensionBaseAttrib);
                
                // TODO following is hack till we really support xsd:extension correctly
                if (extBaseType.lastIndexOf("*") > -1)
                    extBaseType = extBaseType.substring(0, extBaseType.lastIndexOf("*"));

                if (!CUtils.isSimpleType(extBaseType))
                    typeSet.add(extBaseType);
            }            
            
            Iterator itr = typeSet.iterator();
            if (itr.hasNext())
                writer.write("\n");    
            
            while (itr.hasNext())
            {
                // Do not want to include the header file we are generating!
                String includeFile = itr.next().toString();
                if (!includeFile.equals(classname))
                   writer.write("#include \"" + includeFile + CUtils.C_HEADER_SUFFIX + "\"\n");
            }

            writer.write("\n");
            //Local name and the URI for the type
            writer.write("/* Local name and the URI for the type */\n");
            writer.write("static const char Axis_URI_" + classname + "[] = \""
                    + type.getName().getNamespaceURI() + "\";\n");
            writer.write("static const char Axis_TypeName_" + classname
                    + "[] = \"" + type.getName().getLocalPart() + "\";\n\n");
        }
        catch (IOException e)
        {
            throw new WrapperFault(e);
        }
    }
}
