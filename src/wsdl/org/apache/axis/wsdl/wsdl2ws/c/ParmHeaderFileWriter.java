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
        super(wscontext, type, CUtils.getHeaderFileExtension());
    }

    public void writeSource() throws WrapperFault
    {
        try
        {
            c_writer = new BufferedWriter(new FileWriter(getFilePath(false), false));
            writeClassComment();

            // if this headerfile not defined define it 
            c_writer.write("#if !defined(__" + c_classname.toUpperCase() + "_H__INCLUDED_)\n");
            c_writer.write("#define __" + c_classname.toUpperCase() + "_H__INCLUDED_\n\n");
            
            if (type.isSimpleType())
                writeSimpleTypeWithRestrictions();
            else
            {
                writePreprocessorStatements();

                c_writer.write("\n#ifdef __cplusplus\n extern \"C\" {\n#endif\n\n");

                c_writer.write("\n");
                c_writer.write("/* ********************************************************************* */\n");
                c_writer.write("/* --- Custom type                                                   --- */\n");
                c_writer.write("/* ********************************************************************* */\n");
                c_writer.write("\n");                
                
                c_writer.write("typedef struct " + c_classname + "Tag {\n");
                writeAttributes();
                c_writer.write("} " + c_classname + ";\n\n");
                
                writeFunctionPrototypes();
                c_writer.write("\n#ifdef __cplusplus\n }\n#endif\n");
            }
            
            c_writer.write("\n");
            c_writer.write("#endif /* !defined(__" + c_classname.toUpperCase() + "_H__INCLUDED_)*/\n");
            
            c_writer.flush();
            c_writer.close();
            
            if (WSDL2Ws.c_veryVerbose)
                System.out.println(getFilePath(false).getAbsolutePath() + " created.....");
        }
        catch (IOException e)
        {
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
            c_writer.write("#include <axis/AxisUserAPI.h>\n");

            Vector restrictionData = type.getEnumerationdata();
            if (restrictionData == null)
                return;            
            
            TypeEntry baseEType = (TypeEntry) restrictionData.firstElement();
            QName baseType = baseEType.getQName();
            if (!CUtils.isSimpleType(baseType))
                return;
            
            String baseTypeName = CUtils.getSimpleType(baseType);
            String langTypeName;
            
            // User defined simple type based on another user-defined simple type
            String  restrictionBaseType = type.getRestrictionBaseType();
            if (null != restrictionBaseType )
            {  
                langTypeName = CUtils.sanitizeString(restrictionBaseType);               
                c_writer.write( "#include \"" + langTypeName + ".h\"\n\n");
            }
            else
                langTypeName = baseTypeName;
            


            c_writer.write("\n");
            c_writer.write("/* ********************************************************************* */\n");
            c_writer.write("/* --- Simple types and restrictions                                 --- */\n");
            c_writer.write("/* ********************************************************************* */\n");
            c_writer.write("\n");  
            
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
            
            c_writer.write("typedef ");
            if (CUtils.isPointerType(baseTypeName) 
                    || "xsdc__base64Binary".equals(baseTypeName) 
                    || "xsdc__hexBinary".equals(baseTypeName))
            {
                c_writer.write(langTypeName + " " + c_classname + ";\n");
                c_writer.write("typedef " + langTypeName + "_Array " + c_classname + "_Array;\n");
                c_writer.write("\n");
                
                for (int i = 1; i < restrictionData.size(); i++)
                {
                    QName value = (QName) restrictionData.elementAt(i);
                    if ("enumeration".equals(value.getLocalPart()))
                    {
                        c_writer.write("static const " + c_classname + " " + c_classname + "_");
                        if (validEnumIdentifier)
                            c_writer.write(value.getNamespaceURI());
                        else
                            c_writer.write("ENUM" + i);
                        c_writer.write(" = \"" + value.getNamespaceURI() + "\";\n");
                    } 
                    else if ("maxLength".equals(value.getLocalPart()))
                    {
                        c_writer.write("static const int " + c_classname
                                + "_MaxLength = " + value.getNamespaceURI() + ";\n");
                    } 
                    else if ("minLength".equals(value.getLocalPart()))
                    {
                        c_writer.write("static const int " + c_classname
                                + "_MinLength = " + value.getNamespaceURI() + ";\n");
                    }
                }
            } 
            else if ("int".equals(baseType.getLocalPart()))
            {
                c_writer.write(langTypeName + " " + c_classname + ";\n");
                c_writer.write("typedef " + langTypeName + "_Array " + c_classname + "_Array;\n");
            
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
                                c_writer.write(", ");
                            else
                                c_writer.write("typedef enum { ");

                            c_writer.write("ENUM" + c_classname.toUpperCase() + "_"
                                    + value.getNamespaceURI() + "="
                                    + value.getNamespaceURI());
                        } 
                        else if ("minInclusive".equals(value.getLocalPart()))
                        {
                            c_writer.write("static const int " + c_classname
                                    + "_MinInclusive = " + value.getNamespaceURI() + ";\n");
                        } 
                        else if ("maxInclusive".equals(value.getLocalPart()))
                        {
                            c_writer.write("static const int " + c_classname
                                    + "_MaxInclusive = " + value.getNamespaceURI() + ";\n");
                        }
                    }
                    
                    if (isEnum)
                        c_writer.write("} " + c_classname + "_Enum;\n");
                } 
            } 
            else
            {
                c_writer.write(langTypeName + " " + c_classname + ";\n");
                c_writer.write("typedef " + langTypeName + "_Array " + c_classname + "_Array;\n");
                
                for (int i = 1; i < restrictionData.size(); i++)
                {
                    QName value = (QName) restrictionData.elementAt(i);
                    if ("enumeration".equals(value.getLocalPart()))
                    {
                        c_writer.write("static const " + c_classname + " " + c_classname + "_");
                        if (validEnumIdentifier)
                            c_writer.write(value.getNamespaceURI());
                        else
                            c_writer.write("ENUM" + i);
                        c_writer.write(" = \"" + value.getNamespaceURI() + "\";\n");
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
                // Following will set the correct type 
                String paramType = getCorrectParmNameConsideringArraysAndComplexTypes(attribs[i]);
                
                // Following will set param name - if xsd:any, we index param name
                String paramName = attribs[i].getParamNameAsMember();
                if(attribs[i].isAnyElement())
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
                c_writer.write("\t" + paramType + " " + paramName + ";\n");
            }
            
            if (extensionBaseAttrib != null &&
                getCorrectParmNameConsideringArraysAndComplexTypes(extensionBaseAttrib) != null)
            {
                c_writer.write("\t"
                             + getCorrectParmNameConsideringArraysAndComplexTypes(extensionBaseAttrib)
                             + "  "
                             + extensionBaseAttrib.getParamNameAsMember() + ";\n");
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
                        || !typeName.equals(c_classname))
                    continue;
                
                typeSet.add(typeName);
            }
            
            Iterator itr = typeSet.iterator();
            
            if (itr.hasNext())
            {
                c_writer.write("\n");
                c_writer.write("/* ********************************************************************* */\n");
                c_writer.write("/* --- Functions to create/delete, serialize/deserialize custom type --- */\n");
                c_writer.write("/* ********************************************************************* */\n");
                c_writer.write("\n");                
            }
            
            while (itr.hasNext())
            {
                typeName = itr.next().toString();
                c_writer.write("extern int Axis_DeSerialize_" + typeName
                             + "(" + typeName + "* param, AXISCHANDLE pDZ);\n");
                c_writer.write("extern void* Axis_Create_" + typeName + "(int nSize);\n");
                c_writer.write("extern void Axis_Delete_" + typeName
                             + "(" + typeName + "* param, int nSize);\n");
                c_writer.write("extern int Axis_Serialize_" + typeName
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
            c_writer.write("#include <axis/Axis.h>\n");
            c_writer.write("#include <axis/GDefine.h>\n");
            c_writer.write("#include <axis/AxisUserAPI.h>\n");
            c_writer.write("#include <axis/SoapEnvVersions.h>\n");
            c_writer.write("#include <axis/WSDDDefines.h>\n");
            c_writer.write("#include <axis/TypeMapping.h>\n");

            if (this.type.isFault())
                c_writer.write("#include <axis/SoapFaultException.h>\n");
            
            HashSet typeSet = new HashSet();
            for (int i = 0; i < attribs.length; i++)
            {
                String basicType = attribs[i].getTypeName();
                Type theType = attribs[i].getType();

                if (theType.isRestriction() && !CUtils.isPrimitiveType(basicType))
                    typeSet.add(basicType);
                else if (!attribs[i].isSimpleType() && !attribs[i].isAnyElement())
                {
                    if ((attribs[i].isArray()) && !theType.isSimpleType())
                        typeSet.add(basicType + "_Array");
    
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

                if (!CUtils.isPrimitiveType(extBaseType))
                    typeSet.add(extBaseType);
            }            
            
            Iterator itr = typeSet.iterator();
            if (itr.hasNext())
                c_writer.write("\n");    
            
            while (itr.hasNext())
            {
                // Do not want to include the header file we are generating!
                String includeFile = itr.next().toString();
                if (!includeFile.equals(c_classname))
                   c_writer.write("#include \"" + includeFile + CUtils.getHeaderFileExtension() + "\"\n");
            }

            c_writer.write("\n");
            //Local name and the URI for the type
            c_writer.write("/* Local name and the URI for the type */\n");
            c_writer.write("static const char Axis_URI_" + c_classname + "[] = \""
                    + type.getName().getNamespaceURI() + "\";\n");
            c_writer.write("static const char Axis_TypeName_" + c_classname
                    + "[] = \"" + type.getName().getLocalPart() + "\";\n\n");
        }
        catch (IOException e)
        {
            throw new WrapperFault(e);
        }
    }
}
