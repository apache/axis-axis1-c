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

package org.apache.axis.wsdl.wsdl2ws.cpp;

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
    public ParmHeaderFileWriter(WebServiceContext wscontext, Type type)
            throws WrapperFault
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
            this.writer.write("#if !defined(__" + classname.toUpperCase() + "_"
                    + getFileType().toUpperCase() + "_H__INCLUDED_)\n");
            this.writer.write("#define __" + classname.toUpperCase() + "_"
                    + getFileType().toUpperCase() + "_H__INCLUDED_\n\n");

            if (type.isSimpleType())
                writeSimpleTypeWithRestrictions();
            else
            {
                writePreprocessorStatements();

                writer.write("\n");
                writer.write("/* ********************************************************************* */\n");
                writer.write("/* --- Custom type                                                   --- */\n");
                writer.write("/* ********************************************************************* */\n");
                writer.write("\n");                
                
                
                classname = CUtils.sanitizeString( classname);
                
                this.writer.write("class STORAGE_CLASS_INFO " + classname);
                if (this.type.isFault())
                    this.writer.write(" : public SoapFaultException");
                this.writer.write("\n{\n");
                writeAttributes();
                writeGetSetMethods();
                writeConstructors();
                writeDestructors();
                writeDeepCopyFlags();
                this.writer.write("};\n\n");
                
                writeFunctionPrototypes();
            }
            this.writer.write("\n");
            this.writer.write("#endif /* !defined(__" + classname.toUpperCase()
                    + "_" + getFileType().toUpperCase() + "_H__INCLUDED_)*/\n");
            writer.flush();
            writer.close();
            if (WSDL2Ws.c_verbose)
                System.out.println(getFilePath().getAbsolutePath() + " created.....");
        } 
        catch (IOException e)
        {
            throw new WrapperFault(e);
        }
    }

    /**
     * 
     */
    private void writeDeepCopyFlags() throws WrapperFault
    {
        if (type.isArray())
            return;
        
        if (attribs.length == 0)
            return;
        
        try
        {
            boolean foundDeepCopyType = false;
            for (int i = 0 ; i < attribs.length ; i++)
            {
                Type type = attribs[i].getType();
                boolean isPointerType = false;
                
                if (type.isSimpleType())
                    isPointerType = CUtils.isPointerType(CUtils.getSimpleType(type.getBaseType())); 
                else
                    isPointerType = CUtils.isPointerType(getCorrectParmNameConsideringArraysAndComplexTypes(attribs[i]));

                if ((attribs[i].isSimpleType() || attribs[i].getType().isSimpleType()) 
                        && !attribs[i].isArray() 
                        && (isElementNillable(i) 
                                || isElementOptional(i) 
                                || isPointerType 
                                || attribs[i].getChoiceElement() 
                                || attribs[i].getAllElement()))
                {
                    if (!foundDeepCopyType)
                    {
                        writer.write("\nprivate:\n");
                        foundDeepCopyType = true;
                    }
                    writer.write("\tbool __axis_deepcopy_" + attribs[i].getParamNameAsMember() + ";\n");
                }
            }
        }
        catch (IOException e)
        {
            throw new WrapperFault(e);
        }
    }

    protected void writeSimpleTypeWithRestrictions() throws WrapperFault
    {
        try
        {
            writer.write("#include <axis/AxisUserAPI.hpp>\n");
            writer.write("#include <axis/AxisUserAPIArrays.hpp>\n");
            
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
                writer.write( "#include \"" + langTypeName + ".hpp\"\n\n");
            }
            else
                langTypeName = baseTypeName;
            
            writer.write("AXIS_CPP_NAMESPACE_USE \n\n");

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
                    || "xsd__base64Binary".equals(baseTypeName) 
                    || "xsd__hexBinary".equals(baseTypeName))
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
            writer.write("public:\n");
            for (int i = 0; i < attribs.length; i++)
            {                
                // Following will set the correct type 
                String paramType = getCorrectParmNameConsideringArraysAndComplexTypes(attribs[i]);
                
                // Following will set param name - if anyType, we index param name
                String paramName = attribs[i].getParamNameAsMember();
                if(attribs[i].isAnyType())
                {
                    anyCounter += 1;
                    paramName  += Integer.toString(anyCounter);
                }

                // we pass arrays as pointers - ensure this
                if (attribs[i].isArray())
                {
                    // TODO - work on removing the following if-check, should not be needed if we
                    // let getCorrectParmNameConsideringArraysAndComplexTypes() perform check.
                    if (!paramType.endsWith("*"))
                        paramType += "*";
                    
                    if ((!attribs[i].isSimpleType() && attribs[i].getType().isSimpleType()) 
                            || attribs[i].getType().isRestriction())
                        writer.write("\t");
                    else
                        writer.write("\tclass ");                    
                }
                else
                    writer.write("\t");

                // Print out field.
                writer.write(paramType + " " + paramName + ";\n");
            }
            
            // Handle extension 
            if (extensionBaseAttrib != null &&
                getCorrectParmNameConsideringArraysAndComplexTypes(extensionBaseAttrib) != null)
            {
                writer.write("\t"
                             + getCorrectParmNameConsideringArraysAndComplexTypes(extensionBaseAttrib)
                             + " "
                             + extensionBaseAttrib.getParamNameAsMember() + ";\n");
            }
        } 
        catch (IOException e)
        {
            throw new WrapperFault(e);
        }
    }

    /**
     * Dushshantha: This method writes getters and setters of the attributes.
     */
    protected void writeGetSetMethods() throws WrapperFault
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
                
                // Set method name to use
                String methodName = attribs[i].getMethodName();
                
                //  If anyType, we index method name
                if(attribs[i].isAnyType())
                {
                    anyCounter += 1;
                    methodName += Integer.toString(anyCounter);
                }

                // we pass arrays as pointers - ensure this
                if (attribs[i].isArray() && !paramType.endsWith("*"))
                        paramType += "* ";  
                
                writer.write("\n");
                
                // Generate getter prototype
                writer.write("\t" + paramType + " get" + methodName + "();\n");
                
                // Generate setter prototype - need to consider deep copies
                writer.write("\t" + "void set" + methodName + "(" + paramType + " InValue");
                
                Type type = attribs[i].getType();
                boolean isPointerType;                
                if (type.isSimpleType())
                    isPointerType = CUtils.isPointerType(CUtils.getSimpleType(type.getBaseType())); 
                else
                    isPointerType = CUtils.isPointerType(paramType);
                
                if ((attribs[i].isSimpleType() || attribs[i].getType().isSimpleType()) 
                        && !attribs[i].isArray() 
                        && (isElementNillable(i) 
                                || isElementOptional(i) 
                                || isPointerType 
                                || attribs[i].getChoiceElement() 
                                || attribs[i].getAllElement()))                
                    writer.write(", bool deep=true, bool makeCopy=true");
                    
                writer.write(");\n");
            }
        } 
        catch (IOException e)
        {
            throw new WrapperFault(e);
        }
    }

    protected void writeConstructors() throws WrapperFault
    {
        try
        {
            writer.write("\n\t" + classname + "();\n");
            writer.write("\t" + classname + "(const " + classname + " & original);\n");
            writeReset();
        } 
        catch (IOException e)
        {
            throw new WrapperFault(e);
        }
    }
    protected void writeReset() throws WrapperFault
    {
        try
        {
            writer.write("\n\tvoid reset();\n");
        } 
        catch (IOException e)
        {
            throw new WrapperFault(e);
        }
    }

    protected void writeDestructors() throws WrapperFault
    {
        try
        {
            if (this.type.isFault())
                writer.write("\tvirtual ~" + classname + "() throw();\n");
            else
                writer.write("\tvirtual ~" + classname + "();\n");
        } 
        catch (IOException e)
        {
            throw new WrapperFault(e);
        }
    }

    protected void writeMethods() throws WrapperFault
    {
    }

    protected File getFilePath() throws WrapperFault
    {
        return this.getFilePath(false);
    }

    protected File getFilePath(boolean useServiceName) throws WrapperFault
    {
        String targetOutputLocation = this.wscontext.getWrapperInfo().getTargetOutputLocation();
        new File(targetOutputLocation).mkdirs();

        String fileName = targetOutputLocation + "/" + classname + CUtils.CPP_HEADER_SUFFIX;

        if (useServiceName)
        {
            fileName = targetOutputLocation + "/"
                    + this.wscontext.getServiceInfo().getServicename() + "_"
                    + classname + CUtils.CPP_HEADER_SUFFIX;
        }

        return new File(fileName);
    }


    protected void writeFunctionPrototypes() throws WrapperFault
    {
        try
        {
            if (type.isSimpleType() || type.isArray() || type.getName().equals(CUtils.anyTypeQname)
                    || (type.isAnonymous() && !type.isExternalized()))
                return;
            
            String typeName = classname;
            
            writer.write("\n");
            writer.write("/* ********************************************************************* */\n");
            writer.write("/* --- Functions to create/delete, serialize/deserialize custom type --- */\n");
            writer.write("/* ********************************************************************* */\n");
            writer.write("\n");  
            
            writer.write("extern int Axis_DeSerialize_" + typeName
                    + "(" + typeName + "* param, IWrapperSoapDeSerializer* pDZ);\n");
            writer.write("extern void* Axis_Create_" + typeName + "(int nSize=0);\n");
            writer.write("extern void Axis_Delete_" + typeName + "("
                    + typeName + "* param, int nSize=0);\n");
            writer.write("extern int Axis_Serialize_" + typeName + "("
                    + typeName + "* param, IWrapperSoapSerializer* pSZ, bool bArray = false);\n\n");

        }
        catch (IOException e)
        {
            throw new WrapperFault(e);
        }
    }
    
    /*
     * (non-Javadoc)
     * 
     * @see org.apache.axis.wsdl.wsdl2ws.cpp.BasicFileWriter#writePreprocssorStatements()
     */
    protected void writePreprocessorStatements() throws WrapperFault
    {
        try
        {
            writer.write("#include <axis/AxisUserAPI.hpp>\n");
            writer.write("#include <axis/AxisUserAPIArrays.hpp>\n");
            writer.write("#include <axis/IWrapperSoapDeSerializer.hpp>\n");
            writer.write("#include <axis/IWrapperSoapSerializer.hpp>\n");

            
            if (this.type.isFault())
            {
                writer.write("#include <axis/SoapFaultException.hpp>\n");
                writer.write("\n");
                writer.write("using namespace std;\n");
            }
            
            writer.write("AXIS_CPP_NAMESPACE_USE \n\n");
            HashSet typeSet = new HashSet();
            for (int i = 0; i < attribs.length; i++)
            {
                String basicType = attribs[i].getTypeName();
                Type theType = attribs[i].getType();
                
                if (theType.isRestriction() && !CUtils.isPrimitiveType(basicType))
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

                if (!CUtils.isPrimitiveType(extBaseType))
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
                    writer.write("#include \"" + includeFile + CUtils.CPP_HEADER_SUFFIX + "\"\n");
            }

            writer.write("\n");
            //Local name and the URI for the type
            writer.write("/*Local name and the URI for the type*/\n");
            writer.write("static const char Axis_URI_" + classname + "[] = \""
                    + type.getName().getNamespaceURI() + "\";\n");
            writer.write("static const char Axis_TypeName_" + classname
                    + "[] = \"" + type.getName().getLocalPart() + "\";\n\n");

            // Define class to avoid compilation issues (cycle in includes).
            // This is a must for complex wsdl files.
            typeSet = new HashSet();
            for (int i = 0; i < attribs.length; i++)
            {
                if (!attribs[i].isArray() && 
                        !(attribs[i].isSimpleType() || attribs[i].getType().isSimpleType())
                        && !attribs[i].isAnyType())
				{
                    typeSet.add(attribs[i].getTypeName());
                } 
            }
            
            itr = typeSet.iterator();
            while (itr.hasNext())
            {
                writer.write("class " + itr.next().toString() + ";\n");
            }

        } 
        catch (IOException e)
        {
            throw new WrapperFault(e);
        }
    }

    protected String getFileType()
    {
        return "Param";
    }
}