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
            {
                writeSimpleTypeWithEnumerations();
            }
            else
            {
                classname = CUtils.sanitiseClassName( classname);

                // vvv FJP - 17667
                // Check that type is not a restriction
                if( type.isRestriction())
                {
                    String	baseType = type.getRestrictionBase();

                    baseType = baseType.substring( baseType.indexOf( ":") + 1);

                    writer.write( "#include \"" + baseType + ".hpp\"\n\n");
                    writer.write( "// " + classname + " is a restricted type (base=" + baseType + ").\n// The following restrictions need to be applied:-\n");

                    Vector vre = type.getRestrictionEnumeration();
                    Vector vrp = type.getRestrictionPattern();

                    if( vre != null)
                    {
                        writer.write("//\t Enumeration:\n");
                        
                        for( int j = 0; j < vre.size(); j++)
                        {
                            writer.write("//\t\t " + vre.get( j) + "\n");
                        }
                    }
                    
                    if( vrp != null)
                    {
                        writer.write("//\t Pattern:\n");
                        
                        for( int j = 0; j < vrp.size(); j++)
                        {
                            writer.write("//\t\t " + vrp.get( j) + "\n");
                        }
                    }
                    
                    writer.write( "\ntypedef " + baseType + " " + classname + ";\n\n");
                }
                // ^^^ FJP - 17667
                else
                {
	                writePreprocessorStatements();
	
	                this.writer.write("class STORAGE_CLASS_INFO " + classname);
	                
	                if (this.type.isFault())
	                {
	                    this.writer.write(" : public SoapFaultException");
	                }
	                
	                this.writer.write("\n{\n");
	                
	                writeAttributes();
	
	                /**
	                 * Dushshantha: Call writeGetSetMethods() method.
	                 */
	
	                writeGetSetMethods();
	                //..................................
	                writeConstructors();
	                writeDestructors();
	                writeDeepCopyFlags();
	                
	                this.writer.write("};\n\n");
                }
            }
            
            this.writer.write("#endif /* !defined(__" + classname.toUpperCase()
                    + "_" + getFileType().toUpperCase() + "_H__INCLUDED_)*/\n");
            writer.flush();
            writer.close();
            
            if (WSDL2Ws.verbose)
            {
                System.out.println(getFilePath().getAbsolutePath()
                        + " created.....");
            }
        }
        catch (IOException e)
        {
            e.printStackTrace();
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
                    isPointerType = CUtils.isPointerType(CUtils.getclass4qname(type.getBaseType())); 
				else if( type.isRestriction()) // vvv FJP - 17667
			    {
			        // Find base type of the restricted type.
			        type = CUtils.findBaseTypeOfRestriction( type, wscontext);
			        String restBaseClass = CUtils.getBaseTypeOfRestrictionAsString( type);

			        if( type == null)
			            System.out.println( "Warning - Could not find root base class of " + type.getName().getLocalPart());
			        else if( restBaseClass != null)
				        isPointerType = CUtils.isPointerType( restBaseClass);
			    } // ^^^ FJP - 17667
			    else
			    {
				    isPointerType = CUtils.isPointerType(getCorrectParmNameConsideringArraysAndComplexTypes(attribs[i]));
			    }
				
        	    if ((attribs[i].isSimpleType() || type.isSimpleType())
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
                    writer.write("\tbool __axis_deepcopy_" + attribs[i].getParamNameWithoutSymbols() + ";\n");
                }
            }
        }
        catch (IOException e)
        {
            throw new WrapperFault(e);
        }
    }

    protected void writeSimpleTypeWithEnumerations() throws WrapperFault
    {
        try
        {
            writer.write("#include <axis/AxisUserAPI.hpp>\n");
            writer.write("#include <axis/AxisUserAPIArrays.hpp>\n");
            writer.write("AXIS_CPP_NAMESPACE_USE \n\n");

            Vector restrictionData = type.getEnumerationdata();
            if (restrictionData == null)
                return;

            TypeEntry baseEType = (TypeEntry) restrictionData.firstElement();
            QName baseType = baseEType.getQName();
            if (!CUtils.isSimpleType(baseType))
                return;

            writer.write("\n");
            writer.write("/* ********************************************************************* */\n");
            writer.write("/* --- Simple types and enumerations                                 --- */\n");
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
            
            String langTypeName = CUtils.getclass4qname(baseType);
            writer.write("typedef ");
            if (CUtils.isPointerType(CUtils.getclass4qname(baseType)) 
                    || "xsd__base64Binary".equals(CUtils.getclass4qname(baseType)) 
                    || "xsd__hexBinary".equals(CUtils.getclass4qname(baseType)))
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
                attribs[i].setParamName( CUtils.sanitiseAttributeName( classname, attribs[i].getParamName()));
                
                if (isElementNillable(i) 
                        || attribs[i].isArray() 
                        || isElementOptional(i) 
                        && !attribs[i].getAllElement())
                {
                    if(attribs[i].isAnyType())
                    {
                        anyCounter += 1;
                        writer.write("\t"
                                + getCorrectParmNameConsideringArraysAndComplexTypes(attribs[i])
                                + " * " + attribs[i].getParamName()
                                + Integer.toString(anyCounter)
                                + ";\n");
                    }
                    else if( attribs[i].isArray())
                    {
                        String paramName = getCorrectParmNameConsideringArraysAndComplexTypes(attribs[i]);
                        if (!paramName.endsWith("*"))
                            paramName += " *";
                        
                        if (!attribs[i].isSimpleType() && attribs[i].getType().isSimpleType())
                            writer.write("\t");
                        else
                            writer.write("\tclass ");

                        writer.write(paramName + " " + attribs[i].getParamName() + ";\n");
                    }
                    else if(attribs[i].getChoiceElement() && !isElementNillable(i))
                        writer.write("\t"
                             + getCorrectParmNameConsideringArraysAndComplexTypes(attribs[i])
                             + " " + attribs[i].getParamName()
                             + ";\n");
                    else
                        writer.write("\t"
                                 + getCorrectParmNameConsideringArraysAndComplexTypes(attribs[i])
                                 + " * " + attribs[i].getParamName()
                                 + ";\n");
                } 
                else if(attribs[i].getAllElement() || attribs[i].getChoiceElement() )
                {
                    writer.write("\t"
                             + getCorrectParmNameConsideringArraysAndComplexTypes(attribs[i])
                             + " " + attribs[i].getParamName()
                             + ";\n");
                }
                else if(attribs[i].isAnyType())
                {
                    anyCounter += 1;
                    writer.write("\t"
                            + getCorrectParmNameConsideringArraysAndComplexTypes(attribs[i])
                            + " " + attribs[i].getParamName()
                            + Integer.toString(anyCounter)
                            + ";\n");
                }
				else
				{
			        // vvv FJP - 17667
					if( attribs[i].getType().isRestriction())
					{
					    String  typeName = getCorrectParmNameConsideringArraysAndComplexTypes(attribs[i]);
					    Type    baseType = CUtils.findBaseTypeOfRestriction( attribs[i].getType(), wscontext);
					    boolean	isPointer = CUtils.isPointerType( CUtils.getBaseTypeOfRestrictionAsString( baseType));
					  
					    if( isPointer)
					    {
					        int	pointerPos = typeName.indexOf( "*");
					        
					        if( pointerPos > 0)
					        {
					            typeName = typeName.substring( 0, pointerPos);
					        }
					    }
					    
					    writer.write( "\t" + typeName + " " + attribs[i].getParamNameWithoutSymbols() + ";\n");
					}
			        // ^^^ FJP - 17667
					else
					{
					    writer.write( "\t" +
					                  getCorrectParmNameConsideringArraysAndComplexTypes(attribs[i]) +
					                  " " + attribs[i].getParamNameWithoutSymbols() + ";\n");
					}
				}								
            }
            
            if (extensionBaseAttrib != null &&
                getCorrectParmNameConsideringArraysAndComplexTypes(extensionBaseAttrib) != null)
            {
                writer.write("\t"
                             + getCorrectParmNameConsideringArraysAndComplexTypes(extensionBaseAttrib)
                             + " "
                             + extensionBaseAttrib.getParamNameWithoutSymbols() + ";\n");
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
                String methodName = attribs[i].getParamNameWithoutSymbols();
                
                if( methodName.endsWith( "_"))
                {
                    String localMethodName = methodName.substring( 0, methodName.length() - 1);
                    
                    if( localMethodName.equals( classname))
                        methodName = localMethodName; 
                }
                
                if (isElementNillable(i)  || attribs[i].isArray() || isElementOptional(i))
                {
                    if ( attribs[i].isAnyType())
                    {
                        anyCounter += 1;
                        writer.write("\t"
                                    + getCorrectParmNameConsideringArraysAndComplexTypes(attribs[i])
                                    + " * get"
                                    + methodName + Integer.toString(anyCounter) + "();\n");

                        writer.write("\t"
                                    + "void set" + methodName
                                    + Integer.toString(anyCounter)
                                    + "("
                                    + getCorrectParmNameConsideringArraysAndComplexTypes(attribs[i])
                                    + " * pInValue);\n\n");
                    }
                    else 
                    {
                        if(attribs[i].getAllElement() || attribs[i].getChoiceElement())
                        {
                            String paramName = getCorrectParmNameConsideringArraysAndComplexTypes(attribs[i]);
                            if (!paramName.endsWith("*"))
                                paramName += " *";

                            if (attribs[i].isArray())
                            {
                                writer.write( "\n\t" + paramName + " get" + methodName + "();\n");

                                writer.write( "\t" + "void set" + methodName + "(" + paramName + " pInValue");
                            }
                            else if (isElementNillable(i))
                            {
                                writer.write( "\n\t"
                                  + getCorrectParmNameConsideringArraysAndComplexTypes(attribs[i])
                                  + " * get" + methodName + "();\n");

                                writer.write( "\t"
                                  + "void set" + methodName + "("
                                  + getCorrectParmNameConsideringArraysAndComplexTypes(attribs[i])
                                  + " * pInValue");
                            }
                            else
                            {
                                writer.write( "\n\t"
                                          + getCorrectParmNameConsideringArraysAndComplexTypes(attribs[i])
                                          + " get" + methodName + "();\n");

                                writer.write( "\t"
                                          + "void set" + methodName + "("
                                          + getCorrectParmNameConsideringArraysAndComplexTypes(attribs[i])
                                          + " pInValue");
                            }
                        }
                        else
                        {
                            writer.write( "\n\t"
                                      + getCorrectParmNameConsideringArraysAndComplexTypes(attribs[i])
                                      + " * get" + methodName + "();\n");
    
                            writer.write( "\t"
                                      + "void set" + methodName + "("
                                      + getCorrectParmNameConsideringArraysAndComplexTypes(attribs[i])
                                      + " * pInValue");
                        }
                        
                        if ((isElementNillable(i) || isElementOptional(i) 
                                || attribs[i].getAllElement() || attribs[i].getChoiceElement() ) 
                             && !attribs[i].isArray())
                            writer.write(", bool deep = true");
                        
                        writer.write(");\n");
                    }
                }
                else if ( attribs[i].isAnyType())
                {
                    anyCounter += 1;
                    writer.write("\t"
                                + getCorrectParmNameConsideringArraysAndComplexTypes(attribs[i])
                                + " get" + methodName + Integer.toString(anyCounter) + "();\n");

                    writer.write("\t"
                                + "void set" + methodName + Integer.toString(anyCounter) + "("
                                + getCorrectParmNameConsideringArraysAndComplexTypes(attribs[i])
                                + "  InValue);\n\n");
                }
                else 
                {
                    // vvv FJP - 17667
                    Type type = attribs[i].getType();
                    boolean isPointerType = false;
                    String	typeName = getCorrectParmNameConsideringArraysAndComplexTypes( attribs[i]);
                    
                    // Check for restriction.  If found, then find base type.
                    if( type.isRestriction())
                    {
                        type = CUtils.findBaseTypeOfRestriction( type, wscontext);
                    }
                    
                    if (type.isSimpleType())
                        isPointerType = CUtils.isPointerType(CUtils.getclass4qname(type.getBaseType())); 
                    else
                        isPointerType = CUtils.isPointerType(getCorrectParmNameConsideringArraysAndComplexTypes(attribs[i]));

                    if( type.isRestriction() && isPointerType)
                    {
                        int pointerLocation = typeName.indexOf( "*");
                        
                        if( pointerLocation > 0)
                        {
                            typeName = typeName.substring( 0, pointerLocation);
                        }
                    }
                    // ^^^ FJP - 17667

                    
                    writer.write("\n\t"
                            + typeName
                            + " get" + methodName + "();\n");

                    writer.write("\t"
                            + "void set" + methodName + "("
                            + typeName
                            + " InValue");
                

                    if ( (attribs[i].getAllElement() || attribs[i].getChoiceElement() || isPointerType) 
                         && (attribs[i].isSimpleType() || type.isSimpleType()))
                        writer.write(", bool deep = true");
                    
                    writer.write(");\n");
                }
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
        String targetOutputLocation = this.wscontext.getWrapInfo().getTargetOutputLocation();
        if (targetOutputLocation.endsWith("/"))
            targetOutputLocation = targetOutputLocation.substring(0,targetOutputLocation.length() - 1);

        new File(targetOutputLocation).mkdirs();

        String fileName = targetOutputLocation + "/" + classname + CUtils.CPP_HEADER_SUFFIX;

        if (useServiceName)
        {
            fileName = targetOutputLocation + "/"
                    + this.wscontext.getSerInfo().getServicename() + "_"
                    + classname + CUtils.CPP_HEADER_SUFFIX;
        }

        return new File(fileName);
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
            
            if (this.type.isFault())
            {
                writer.write("#include <axis/SoapFaultException.hpp>\n");
                writer.write("using namespace std;\n");
            }
            
            writer.write("AXIS_CPP_NAMESPACE_USE \n\n");
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
				    !(attribs[i].isSimpleType() || attribs[i].getType().isSimpleType()) &&
					!attribs[i].isAnyType() &&
					!attribs[i].getType().isRestriction())
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