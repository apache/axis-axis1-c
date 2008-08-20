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

import org.apache.axis.wsdl.wsdl2ws.BasicFileWriter;
import org.apache.axis.wsdl.wsdl2ws.WSDL2Ws;
import org.apache.axis.wsdl.wsdl2ws.WrapperFault;
import org.apache.axis.wsdl.wsdl2ws.info.WebServiceContext;

public abstract class HeaderFileWriter extends BasicFileWriter
{
    protected WebServiceContext wscontext;

    /**
     * @param classname
     * @throws WrapperFault
     */
    public HeaderFileWriter(String classname) throws WrapperFault
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
            this.writer = new BufferedWriter(new FileWriter(getFilePath(), false));
            
            writeClassComment();
            
            // if this headerfile not defined define it 
            this.writer.write("#if !defined(__" + classname.toUpperCase() + "_H__INCLUDED_)\n");
            this.writer.write("#define __" + classname.toUpperCase() + "_H__INCLUDED_\n\n");
            
            //includes
            writePreprocessorStatements();
            
            this.writer.write("\n#ifdef __cplusplus\n extern \"C\" {\n#endif\n\n");

            //class
            writeAttributes();
            writeMethods();
            
            this.writer.write("\n");
            this.writer.write("#ifdef __cplusplus\n }\n#endif\n\n");
            this.writer.write("#endif /* !defined(__" + classname.toUpperCase() + "_H__INCLUDED_) */\n");
            
            //cleanup
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
        String targetOutputLocation = this.wscontext.getWrapperInfo().getTargetOutputLocation();
        new File(targetOutputLocation).mkdirs();

        String fileName = targetOutputLocation + "/" + classname + ".h";

        if (useServiceName)
            fileName = targetOutputLocation + "/" + this.getServiceName() + "_" + classname + ".h";

        return new File(fileName);
    }
    protected String getServiceName() throws WrapperFault
    {
        return wscontext.getServiceInfo().getServicename();
    }
}
