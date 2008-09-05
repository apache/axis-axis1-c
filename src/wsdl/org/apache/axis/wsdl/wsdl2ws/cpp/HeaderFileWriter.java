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
import java.io.FileWriter;
import java.io.IOException;

import org.apache.axis.wsdl.wsdl2ws.CUtils;
import org.apache.axis.wsdl.wsdl2ws.WrapperFault;
import org.apache.axis.wsdl.wsdl2ws.BasicFileWriter;
import org.apache.axis.wsdl.wsdl2ws.WSDL2Ws;

public abstract class HeaderFileWriter extends BasicFileWriter
{
    public HeaderFileWriter(String classname) throws WrapperFault
    {
        super(classname, CUtils.getHeaderFileExtension());
    }
    public void writeSource() throws WrapperFault
    {
        try
        {
            String filename = getFilePath(false).getName();

            c_writer =
                new BufferedWriter(
                    new FileWriter(
                        getFilePath(filename.startsWith("AxisClientException")),
                        false));

            writeClassComment();
            // if this headerfile not defined define it 
            c_writer.write(
                "#if !defined(__"
                    + c_classname.toUpperCase()
                    + "_"
                    + getFileType().toUpperCase()
                    + "_H__INCLUDED_)\n");
            c_writer.write(
                "#define __"
                    + c_classname.toUpperCase()
                    + "_"
                    + getFileType().toUpperCase()
                    + "_H__INCLUDED_\n\n");
            //includes
            writePreprocessorStatements();
            //class

            if ("AxisClientException".equals(c_classname))
            {
                c_writer.write(
                    "class "
                        + getServiceName()
                        + "_"
                        + c_classname
                        + getExtendsPart()
                        + "\n{\n");
            }
            else
            {
                c_writer.write(
                    "class " + c_classname + getExtendsPart() + "\n{\n");
            }
            writeAttributes();
            writeConstructors();
            writeDestructors();
            writeMethods();
            c_writer.write("};\n\n");
            c_writer.write(
                "#endif /* !defined(__"
                    + c_classname.toUpperCase()
                    + "_"
                    + getFileType().toUpperCase()
                    + "_H__INCLUDED_)*/\n");
            //cleanup
            c_writer.flush();
            c_writer.close();
            if (WSDL2Ws.c_veryVerbose)
                System.out.println(
                    getFilePath(false).getAbsolutePath() + " created.....");

        }
        catch (IOException e)
        {
            throw new WrapperFault(e);
        }

    }
    protected abstract String getExtendsPart(); //{return " ";}
    protected abstract String getFileType();

    protected String getServiceName() throws WrapperFault
    {
        return wscontext.getServiceInfo().getServicename();
    }
}
