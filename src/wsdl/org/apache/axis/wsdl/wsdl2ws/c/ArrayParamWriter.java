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

import javax.xml.namespace.QName;

import org.apache.axis.wsdl.wsdl2ws.CUtils;
import org.apache.axis.wsdl.wsdl2ws.ParamWriter;
import org.apache.axis.wsdl.wsdl2ws.WSDL2Ws;
import org.apache.axis.wsdl.wsdl2ws.WrapperFault;
import org.apache.axis.wsdl.wsdl2ws.info.Type;
import org.apache.axis.wsdl.wsdl2ws.info.WebServiceContext;

public class ArrayParamWriter extends ParamWriter
{
    /**
     * @param wscontext
     * @param type
     * @throws WrapperFault
     */
    public ArrayParamWriter(WebServiceContext wscontext, Type type)
        throws WrapperFault
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
            c_writer = new BufferedWriter(new FileWriter(getFilePath(), false));
            
            // Write prolog
            writeClassComment(); 

            // include system header files
            c_writer.write("#include <stdlib.h>\n");
            c_writer.write("#include <stdio.h>\n");
            c_writer.write("#include <string.h>\n");
            c_writer.write("\n");
            
            // include header file for datatype
            c_writer.write("#include \"" + c_classname + ".h\"\n");
            
            // include header file for the contained type
            QName qname = CUtils.getArrayType(type).getName();
            if (!CUtils.isSimpleType(qname))
                c_writer.write("#include \"" + attribs[0].getTypeName() + CUtils.getHeaderFileExtension() + "\"\n");
            c_writer.write("\n");
            
            c_writer.write("\n");
            c_writer.write("#include <axis/AxisWrapperAPI.h>\n");
            c_writer.write("#include <axis/IWrapperSoapSerializer.h>\n");
            c_writer.write("#include <axis/IWrapperSoapDeSerializer.h>\n");
            c_writer.write("#include <axis/client/Stub.h>\n");
            c_writer.write("#include <axis/client/Call.h>\n");
            c_writer.write("\n");
            
            this.writeMethods();
            
            c_writer.flush();
            c_writer.close();
            if (WSDL2Ws.c_verbose)
                System.out.println(getFilePath().getAbsolutePath() + " created.....");
        }
        catch (IOException e)
        {
            throw new WrapperFault(e);
        }
    }
    /* (non-Javadoc)
     * @see org.apache.axis.wsdl.wsdl2ws.BasicFileWriter#writeMethods()
     */
    protected void writeMethods() throws WrapperFault
    {
        this.writeConstructors();
        this.writeDestructors();
        this.writeSetMethod();
        this.writeGetMethod();
        this.writeCloneMethod();
        this.writeClearMethod();
    }

    /**
     * @throws WrapperFault
     * 
     */
    protected void writeClearMethod() throws WrapperFault
    {}
    
    /**
     * @throws IOException
     */
    protected void writeCloneMethod() throws WrapperFault
    { }
    
    /**
     * @throws IOException
     */
    protected void writeGetMethod() throws WrapperFault
    {}
    
    /**
     * @throws IOException
     */
    protected void writeSetMethod() throws WrapperFault
    {}
    
    protected void writeConstructors() throws WrapperFault
    {
        try
        {
            CUtils.printMethodComment(c_writer, "Function used to create objects of type " 
                    + c_classname + ".");
            
            c_writer.write("extern void* Axis_Create_" + c_classname + "(int nSize)\n");
            c_writer.write("{\n");
            
            // Begin function body

            c_writer.write("\t/* Create array data type */\n");
            c_writer.write("\t" + c_classname + " *pArray = (" + c_classname + "*)axiscAxisNew(XSDC_ARRAY, 0);\n");
            c_writer.write("\tpArray->m_Type = C_USER_TYPE;\n");
            c_writer.write("\n");

            c_writer.write("\treturn pArray;\n");
            
            // End function body

            c_writer.write("}\n");
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
            CUtils.printMethodComment(c_writer, "Function used to delete objects of type " 
                    + c_classname + ".");
            
            c_writer.write("extern void Axis_Delete_" + c_classname 
                    + "(" + c_classname + "* param, int nSize)\n");
            c_writer.write("{\n");
            
            // Begin function body
            
            c_writer.write("\t/* If null, simply return */\n");
            c_writer.write("\tif (param == NULL)\n");
            c_writer.write("\t\treturn;\n");
            c_writer.write("\n");
            
            c_writer.write("\t/* Reclaim memory resources of array elements, if it exists */\n");
            c_writer.write("\tif (param->m_Array && param->m_Size > 0)\n");
            c_writer.write("\t{\n");            
            c_writer.write("\t\tAxis_Delete_" +  attribs[0].getTypeName() 
                    + "((" + attribs[0].getTypeName() + " *)param->m_Array, param->m_Size);\n");
            c_writer.write("\t\tparam->m_Array = NULL;\n");            
            c_writer.write("\t}\n");                     
            c_writer.write("\n");
            
            c_writer.write("\t/* Reclaim array data type memory resources */\n");
            c_writer.write("\taxiscAxisDelete(param, XSDC_ARRAY);\n");
            
            // End function body            
            
            c_writer.write("}\n");
        }
        catch (IOException e)
        {
            throw new WrapperFault(e);
        }
    }

    /* (non-Javadoc)
     * @see org.apache.axis.wsdl.wsdl2ws.BasicFileWriter#getFilePath(boolean)
     */
    protected File getFilePath(boolean useServiceName) throws WrapperFault
    {
        String targetOutputLocation = this.wscontext.getWrapperInfo().getTargetOutputLocation();
        new File(targetOutputLocation).mkdirs();

        String fileName = targetOutputLocation + "/" + c_classname + CUtils.getImplFileExtension();

        return new File(fileName);
    }
}
