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
package org.apache.axis.wsdl.wsdl2ws.cpp;

import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

import org.apache.axis.wsdl.wsdl2ws.CUtils;
import org.apache.axis.wsdl.wsdl2ws.ParamWriter;
import org.apache.axis.wsdl.wsdl2ws.WSDL2Ws;
import org.apache.axis.wsdl.wsdl2ws.WrapperFault;
import org.apache.axis.wsdl.wsdl2ws.info.Type;
import org.apache.axis.wsdl.wsdl2ws.info.WebServiceContext;

/**
 * @author dicka.new
 *
 * TODO To change the template for this generated type comment go to
 * Window - Preferences - Java - Code Style - Code Templates
 */
public class ArrayParamWriter extends ParamWriter
{
    

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
            this.writer =
                new BufferedWriter(new FileWriter(getFilePath(), false));
            writeClassComment();
            
            writer.write("#include \"" + classname + ".hpp\"\n\n");
            this.writeMethods();
            writer.flush();
            writer.close();
            if (WSDL2Ws.verbose)
            {
                System.out.println(
                    getFilePath().getAbsolutePath() + " created.....");
            }
        }
        catch (IOException e)
        {
            e.printStackTrace();
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
    {
        try
        {
            writer.write("void " + classname + "::clear()\n");
            writer.write("{\n");
            writer.write("\tif (m_Array != NULL)\n");
            writer.write("\t{\n");
            writer.write("\t\tif (m_Size > 0)\n");
            writer.write("\t\t{\n");
            writer.write("\t\t\tfor (int count = 0 ; count < m_Size ; count++)\n");
            writer.write("\t\t\t{\n");
            writer.write("\t\t\t\tif (m_Array[count] != NULL)\n");
            writer.write("\t\t\t\t{\n");
            writer.write("\t\t\t\t\tdelete ((" + attribs[0].getTypeName() + "**) m_Array)[count];\n");
            writer.write("\t\t\t\t\tm_Array[count] = NULL;\n");
            writer.write("\t\t\t\t}\n");
            writer.write("\t\t\t}\n");
            writer.write("\t\t}\n");
            writer.write("\t\tif (m_belongsToAxisEngine == false)\n");
            writer.write("\t\t{\n");
            writer.write("\t\t\tdelete [] m_Array;\n");
            writer.write("\t\t\tm_Array = NULL;\n");
            writer.write("\t\t\tm_Size = 0;\n");
            writer.write("\t\t}\n");
            writer.write("\t\telse\n");
            writer.write("\t\t{\n");
            writer.write("\t\t\t// Allow the engine to clear up it's memory\n");
            writer.write("\t\t\tAxis_Array::clear();\n");
            writer.write("\t\t}\n");
            writer.write("\t\tm_belongsToAxisEngine = false;\n");
            writer.write("\t}\n");
            writer.write("}\n\n");
        }
        catch (IOException e)
        {
            throw new WrapperFault(e);
        }        
    }
    /**
     * @throws IOException
     */
    protected void writeCloneMethod() throws WrapperFault
    {
        // Write clone method
        try
        {
            writer.write("void " + classname + "::clone(" + classname + " & original)\n");
            writer.write("{\n");
            writer.write("\tset((" + attribs[0].getTypeName() + "**) original.m_Array, original.m_Size);\n");
            writer.write("}\n\n");
        }
        catch (IOException e)
        {
            throw new WrapperFault(e);
        }
    }
    /**
     * @throws IOException
     */
    protected void writeGetMethod() throws WrapperFault
    {
        try
        {
            writer.write(attribs[0].getTypeName() + "** " + classname + "::" + "get(int & size) const\n");
            writer.write("{\n");
            writer.write("\tXSDTYPE type;\n");
            writer.write("\treturn (" + attribs[0].getTypeName() + "**) Axis_Array::get(size, type);\n");
            writer.write("}\n\n");
        }
        catch (IOException e)
        {
            throw new WrapperFault(e);
        }
    }
    /**
     * @throws IOException
     */
    protected void writeSetMethod() throws WrapperFault
    {
        try
        {
            writer.write("void " + classname + "::" + "set(" + attribs[0].getTypeName() + "** array, const int size)\n");
            writer.write("{\n");
            writer.write("\tclear();\n");
            writer.write("\tm_Size = size;\n");
            writer.write("\tm_Type = USER_TYPE;\n\n");
            writer.write("\tif (m_Size == 0)\n");
            writer.write("\t{\n");
            writer.write("\t\tm_Array = NULL;\n");
            writer.write("\t}\n");
            writer.write("\telse\n");
            writer.write("\t{\n");
            writer.write("\t\tm_Array = new void*[m_Size];\n");
            writer.write("\t\tfor (int count = 0 ; count < m_Size ; count++ )\n");
            writer.write("\t\t{\n");
            writer.write("\t\t\tif (array[count] == NULL)\n");
            writer.write("\t\t\t{\n");
            writer.write("\t\t\t\tm_Array[count] = NULL;\n");
            writer.write("\t\t\t}\n");
            writer.write("\t\t\telse\n");
            writer.write("\t\t\t{\n");
            writer.write("\t\t\t\t((" + attribs[0].getTypeName() + "**) m_Array)[count] =\n");
            writer.write("\t\t\t\t\tnew " + attribs[0].getTypeName() + "(*((" + attribs[0].getTypeName() + "**) array)[count]);\n");
            writer.write("\t\t\t}\n");
            writer.write("\t\t}\n");
            writer.write("\t}\n");
            writer.write("}\n\n");
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
            writer.write(classname + "::" + classname + "()\n");
            writer.write("{\n");
            writer.write("\tm_Type = USER_TYPE;\n");
            writer.write("\tm_belongsToAxisEngine = false;\n");
            writer.write("}\n\n");
            writer.write(classname + "::" + classname + "(" + classname + " & original)\n");
            writer.write("{\n");
            writer.write("\tm_Type = USER_TYPE;\n");
            writer.write("\tm_belongsToAxisEngine = false;\n");
            writer.write("\tclone(original);\n");
            writer.write("}\n\n");
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
            writer.write(classname + "::~" + classname + "()\n");
            writer.write("{\n");
            writer.write("\tclear();\n");
            writer.write("}\n\n");
        }
        catch (IOException e)
        {
            throw new WrapperFault(e);
        }
    }
    
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
        String targetOutputLocation =
            this.wscontext.getWrapInfo().getTargetOutputLocation();
        if (targetOutputLocation.endsWith("/"))
        {
            targetOutputLocation =
                targetOutputLocation.substring(
                    0,
                    targetOutputLocation.length() - 1);
        }
        new File(targetOutputLocation).mkdirs();

        String fileName =
            targetOutputLocation + "/" + classname + CUtils.CPP_CLASS_SUFFIX;

        if (useServiceName)
        {
            fileName =
                targetOutputLocation
                    + "/"
                    + this.wscontext.getSerInfo().getServicename()
                    + "_"
                    + classname
                    + CUtils.CPP_HEADER_SUFFIX;
        }

        return new File(fileName);
    }

}
