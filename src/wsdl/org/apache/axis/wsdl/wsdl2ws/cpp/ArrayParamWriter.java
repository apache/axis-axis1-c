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
        super(wscontext, type, CUtils.getImplFileExtension());
    }
    
    /* (non-Javadoc)
     * @see org.apache.axis.wsdl.wsdl2ws.SourceWriter#writeSource()
     */
    public void writeSource() throws WrapperFault
    {
        try
        {
            c_writer = new BufferedWriter(new FileWriter(getFilePath(false), false));
            
            writeClassComment();            
            c_writer.write("#include \"" + c_classname + ".hpp\"\n\n");
            this.writeMethods();
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
            CUtils.printMethodComment(c_writer, "Method to delete allocated resources.");
            
            c_writer.write("void " + c_classname + "::\nclear()\n");
            c_writer.write("{\n");
            c_writer.write("\tif (m_Array != NULL)\n");
            c_writer.write("\t{\n");
            c_writer.write("\t\tif (m_Size > 0)\n");
            c_writer.write("\t\t{\n");
            c_writer.write("\t\t\tfor (int count = 0 ; count < m_Size ; count++)\n");
            c_writer.write("\t\t\t{\n");
            c_writer.write("\t\t\t\tif (m_Array[count] != NULL)\n");
            c_writer.write("\t\t\t\t{\n");
            c_writer.write("\t\t\t\t\tdelete ((" + attribs[0].getTypeName() + "**) m_Array)[count];\n");
            c_writer.write("\t\t\t\t\tm_Array[count] = NULL;\n");
            c_writer.write("\t\t\t\t}\n");
            c_writer.write("\t\t\t}\n");
            c_writer.write("\t\t}\n");
            c_writer.write("\t\tif (m_belongsToAxisEngine == false)\n");
            c_writer.write("\t\t{\n");
            c_writer.write("\t\t\tdelete [] m_Array;\n");
            c_writer.write("\t\t\tm_Array = NULL;\n");
            c_writer.write("\t\t\tm_Size = 0;\n");
            c_writer.write("\t\t}\n");
            c_writer.write("\t\telse\n");
            c_writer.write("\t\t{\n");
            c_writer.write("\t\t\t// Allow the engine to clear up it's memory\n");
            c_writer.write("\t\t\tAxis_Array::clear();\n");
            c_writer.write("\t\t}\n");
            c_writer.write("\t\tm_belongsToAxisEngine = false;\n");
            c_writer.write("\t}\n");
            c_writer.write("}\n");
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
            CUtils.printMethodComment(c_writer, "Method to initialize object from another object of type " + c_classname + ".");
            
            c_writer.write("void " + c_classname + "::\nclone(const " + c_classname + " & original)\n");
            c_writer.write("{\n");
            c_writer.write("\tset((" + attribs[0].getTypeName() + "**) original.m_Array, original.m_Size);\n");
            c_writer.write("}\n\n");

            CUtils.printMethodComment(c_writer, "Method to clone objects of type " + c_classname + ".");
            
            c_writer.write("Axis_Array * " + c_classname + "::\nclone() const\n");
            c_writer.write("{\n");
            c_writer.write("\treturn new " + c_classname + "(*this);\n");
            c_writer.write("}\n");
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
            CUtils.printMethodComment(c_writer, "Getter method for class member field m_Array.");
            
            c_writer.write(attribs[0].getTypeName() + "** " + c_classname + "::\n" + "get(int & size) const\n");
            c_writer.write("{\n");
            c_writer.write("\tXSDTYPE type;\n");
            c_writer.write("\treturn (" + attribs[0].getTypeName() + "**) Axis_Array::get(size, type);\n");
            c_writer.write("}\n");
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
            CUtils.printMethodComment(c_writer, "Setter method for class member field m_Array.");
            
            c_writer.write("void " + c_classname + "::\n" + "set(" + attribs[0].getTypeName() + "** array, const int size)\n");
            c_writer.write("{\n");
            c_writer.write("\tclear();\n");
            c_writer.write("\tm_Size = size;\n");
            c_writer.write("\tm_Type = USER_TYPE;\n\n");
            c_writer.write("\tif (m_Size == 0)\n");
            c_writer.write("\t{\n");
            c_writer.write("\t\tm_Array = NULL;\n");
            c_writer.write("\t}\n");
            c_writer.write("\telse\n");
            c_writer.write("\t{\n");
            c_writer.write("\t\tm_Array = new void*[m_Size];\n");
            c_writer.write("\t\tfor (int count = 0 ; count < m_Size ; count++ )\n");
            c_writer.write("\t\t{\n");
            c_writer.write("\t\t\tif (array[count] == NULL)\n");
            c_writer.write("\t\t\t{\n");
            c_writer.write("\t\t\t\tm_Array[count] = NULL;\n");
            c_writer.write("\t\t\t}\n");
            c_writer.write("\t\t\telse\n");
            c_writer.write("\t\t\t{\n");
            c_writer.write("\t\t\t\t((" + attribs[0].getTypeName() + "**) m_Array)[count] =\n");
            c_writer.write("\t\t\t\t\tnew " + attribs[0].getTypeName() + "(*((" + attribs[0].getTypeName() + "**) array)[count]);\n");
            c_writer.write("\t\t\t}\n");
            c_writer.write("\t\t}\n");
            c_writer.write("\t}\n");
            c_writer.write("}\n");
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
            CUtils.printMethodComment(c_writer, "Constructor for class " + c_classname + ".");
            
            c_writer.write(c_classname + "::\n" + c_classname + "()\n");
            c_writer.write("{\n");
            c_writer.write("\tm_Type = USER_TYPE;\n");
            c_writer.write("\tm_belongsToAxisEngine = false;\n");
            c_writer.write("}\n");
            
            CUtils.printMethodComment(c_writer, "Copy constructor for class " + c_classname + ".");
            
            c_writer.write(c_classname + "::\n" + c_classname + "(const " + c_classname + " & original)\n");
            c_writer.write("{\n");
            c_writer.write("\tm_Type = USER_TYPE;\n");
            c_writer.write("\tm_belongsToAxisEngine = false;\n");
            c_writer.write("\tclone(original);\n");
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
            CUtils.printMethodComment(c_writer, "Destructor for class " + c_classname + ".");
            
            c_writer.write(c_classname + "::\n~" + c_classname + "()\n");
            c_writer.write("{\n");
            c_writer.write("\tclear();\n");
            c_writer.write("}\n");
        }
        catch (IOException e)
        {
            throw new WrapperFault(e);
        }
    }
}
