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
        
        try
        {
            writer.write("void " + classname + "::" + "set(" + attribs[0].getTypeName() + "** array, const int size)\n");
            writer.write("{\n");
            writer.write("\tAxis_Array::set((void**)array, size, USER_TYPE);\n");
            writer.write("}\n\n");
            writer.write("const " + attribs[0].getTypeName() + "** " + classname + "::" + "get(int & size) const\n");
            writer.write("{\n");
            writer.write("\tXSDTYPE type;\n");
            writer.write("\treturn (const " + attribs[0].getTypeName() + "**) Axis_Array::get(size, type);\n");
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
            writer.write("}\n\n");
            writer.write(classname + "::" + classname + "(" + classname + " & original)\n");
            writer.write("{\n");
            writer.write("\tclone(original);\n");
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
