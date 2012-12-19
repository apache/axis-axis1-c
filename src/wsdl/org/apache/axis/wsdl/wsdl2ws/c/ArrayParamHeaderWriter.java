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

import javax.xml.namespace.QName;

import org.apache.axis.wsdl.wsdl2ws.CUtils;
import org.apache.axis.wsdl.wsdl2ws.ParamWriter;
import org.apache.axis.wsdl.wsdl2ws.WSDL2Ws;
import org.apache.axis.wsdl.wsdl2ws.WrapperFault;
import org.apache.axis.wsdl.wsdl2ws.info.Type;
import org.apache.axis.wsdl.wsdl2ws.info.WebServiceContext;

public class ArrayParamHeaderWriter extends ParamWriter
{
    public ArrayParamHeaderWriter(WebServiceContext wscontext, Type type)
        throws WrapperFault
    {
        super(wscontext, type, CUtils.getHeaderFileExtension());
    }

    public void writeSource() throws WrapperFault
    {
        try
        {
            c_writer = new BufferedWriter(new FileWriter(getFilePath(false), false));
            writeClassComment();

            c_writer.write("#if !defined(__"  + c_classname.toUpperCase() + "_H__INCLUDED_)\n");
            c_writer.write("#define __" + c_classname.toUpperCase() + "_H__INCLUDED_\n\n");
                        
            if (attribs.length != 1)
            {
                System.out.println("Array " + c_classname + " contains unexpected no of variables");
                throw new WrapperFault("Array type " + c_classname + " contain unexpected no of types");
            }
                      
            c_writer.write("#include <axis/Axis.h>\n");
            c_writer.write("#include <axis/AxisUserAPI.h>\n\n");

            c_writer.write("#ifdef __cplusplus\n extern \"C\" {\n#endif\n\n");
            
            writeArrayClassDefinition();
            
            c_writer.write("\n#ifdef __cplusplus\n }\n#endif\n\n");
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

    public boolean isSimpleTypeArray() throws WrapperFault
    {
        QName qname = CUtils.getArrayType(type).getName();
        return CUtils.isSimpleType(qname);
    }

    protected void writeArrayClassDefinition() throws WrapperFault
    {
        try
        {
            c_writer.write("\n");
            c_writer.write("/* ********************************************************************* */\n");
            c_writer.write("/* --- Array type                                                    --- */\n");
            c_writer.write("/* ********************************************************************* */\n");
            c_writer.write("\n");                
            
            c_writer.write("typedef struct " + c_classname + "Tag {\n"
                       + "\tstruct " + attribs[0].getTypeName() + "Tag **   m_Array;\n"
                       + "\tint   m_Size;\n"
                       + "\tAXISC_XSDTYPE   m_Type;\n"
                       + "} " + CUtils.resolveWSDL2LanguageNameClashes(c_classname) + ";\n"); 
            
            c_writer.write("\n");
            c_writer.write("/* ********************************************************************* */\n");
            c_writer.write("/* --- Functions to create/delete array type                         --- */\n");
            c_writer.write("/* ********************************************************************* */\n");
            c_writer.write("\n");                

            this.writeConstructors();
            this.writeDestructors();
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
            c_writer.write("extern void* Axis_Create_" + c_classname + "(int nSize);\n");
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
            c_writer.write("extern void Axis_Delete_" + c_classname 
                    + "(" + c_classname + "* param, int nSize);\n");
        }
        catch (IOException e)
        {
            throw new WrapperFault(e);
        }        
    }

    protected void writeMethods() throws WrapperFault
    {
    }

    protected String getFileType()
    {
        return "Array";
    }
}
