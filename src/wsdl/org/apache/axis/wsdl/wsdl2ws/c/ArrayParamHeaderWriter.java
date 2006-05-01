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

import javax.xml.namespace.QName;

import org.apache.axis.wsdl.wsdl2ws.CUtils;
import org.apache.axis.wsdl.wsdl2ws.ParamWriter;
import org.apache.axis.wsdl.wsdl2ws.WSDL2Ws;
import org.apache.axis.wsdl.wsdl2ws.WrapperFault;
import org.apache.axis.wsdl.wsdl2ws.WrapperUtils;
import org.apache.axis.wsdl.wsdl2ws.info.Type;
import org.apache.axis.wsdl.wsdl2ws.info.WebServiceContext;

public class ArrayParamHeaderWriter extends ParamWriter
{
    public ArrayParamHeaderWriter(WebServiceContext wscontext, Type type)
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

            this.writer.write("#if !defined(__"  + classname.toUpperCase() + "_H__INCLUDED_)\n");
            this.writer.write("#define __" + classname.toUpperCase() + "_H__INCLUDED_\n\n");
                        
            if (attribs.length != 1)
            {
                System.out.println("Array " + classname + " contains unexpected no of variables");
                throw new WrapperFault("Array type " + classname + " contain unexpected no of types");
            }
                      
            writer.write("#include <axis/Axis.h>\n");
            writer.write("#include <axis/AxisUserAPI.h>\n\n");

            this.writer.write("#ifdef __cplusplus\n extern \"C\" {\n#endif\n\n");
            
            writeArrayClassDefinition();
            
            this.writer.write("\n#ifdef __cplusplus\n }\n#endif\n\n");
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

    public boolean isSimpleTypeArray() throws WrapperFault
    {
        QName qname = WrapperUtils.getArrayType(type).getName();
        return CUtils.isSimpleType(qname);
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

        String fileName = targetOutputLocation + "/" + classname + CUtils.C_HEADER_SUFFIX;

        if (useServiceName)
        {
            fileName =  targetOutputLocation + "/"
                    + this.wscontext.getSerInfo().getServicename()
                    + "_" + classname + CUtils.C_HEADER_SUFFIX;
        }

        return new File(fileName);
    }

    protected void writeArrayClassDefinition() throws WrapperFault
    {
        try
        {
            writer.write("typedef struct " + classname + "Tag {\n");
            writer.write("\tstruct " + attribs[0].getTypeName()
                        + "Tag ** m_Array;\n\tint m_Size;\n\tAXISC_XSDTYPE m_Type;\n} "
                        + classname + ";\n");   
            writer.write("\n");
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
            this.writer.write("extern void* Axis_Create_" + classname + "(void);\n");
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
            this.writer.write("extern void Axis_Delete_" + classname 
                    + "(" + classname + "* param);\n");
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
