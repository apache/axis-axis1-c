/*
 *   Copyright 2003-2004 The Apache Software Foundation.
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

import org.apache.axis.wsdl.wsdl2ws.BasicFileWriter;
import org.apache.axis.wsdl.wsdl2ws.WSDL2Ws;
import org.apache.axis.wsdl.wsdl2ws.WrapperFault;
import org.apache.axis.wsdl.wsdl2ws.info.WebServiceContext;

public abstract class CFileWriter extends BasicFileWriter
{
    protected WebServiceContext wscontext;

    /**
     * @param classname
     * @throws WrapperFault
     */
    public CFileWriter(String classname) throws WrapperFault
    {
        super(classname);
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
            writePreprocessorStatements();
            writeGlobalCodes();
            // this.writer.write("public class "+servicename+getExtendsPart()+"{\n");
            writeAttributes();
            writeMethods();
            //this.writer.write("}\n");
            //cleanup
            writer.flush();
            writer.close();
            if (WSDL2Ws.verbose)
                System.out.println(
                    getFilePath().getAbsolutePath() + " created.....");
        }
        catch (IOException e)
        {
            e.printStackTrace();
            throw new WrapperFault(e);
        }

    }

    /**
     * @throws WrapperFault
     */
    protected void writeGlobalCodes() throws WrapperFault
    {}

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

        String fileName = targetOutputLocation + "/" + classname + ".c";

        if (useServiceName)
        {
            String serviceName = this.wscontext.getSerInfo().getServicename();
            fileName =
                targetOutputLocation
                    + "/"
                    + serviceName
                    + "_"
                    + classname
                    + ".c";
            this.wscontext.addGeneratedFile(
                serviceName + "_" + classname + ".c");
        }
        else
        {
            this.wscontext.addGeneratedFile(classname + ".c");
        }

        return new File(fileName);
    }
}
