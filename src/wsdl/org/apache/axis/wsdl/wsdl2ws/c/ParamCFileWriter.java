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

import org.apache.axis.wsdl.wsdl2ws.CUtils;
import org.apache.axis.wsdl.wsdl2ws.ParamWriter;
import org.apache.axis.wsdl.wsdl2ws.WSDL2Ws;
import org.apache.axis.wsdl.wsdl2ws.WrapperFault;
import org.apache.axis.wsdl.wsdl2ws.info.Type;
import org.apache.axis.wsdl.wsdl2ws.info.WebServiceContext;

public abstract class ParamCFileWriter extends ParamWriter
{
    /**
     * @param wscontext
     * @param type
     * @throws WrapperFault
     */
    public ParamCFileWriter(WebServiceContext wscontext, Type type) throws WrapperFault
    {
        super(wscontext, type, CUtils.getImplFileExtension());
    }

    /**
     * @throws WrapperFault
     */
    protected abstract void writeRestrictionCheckerFunction() throws WrapperFault;

    /* (non-Javadoc)
     * @see org.apache.axis.wsdl.wsdl2ws.SourceWriter#writeSource()
     */
    public void writeSource() throws WrapperFault
    {
        // TODO Makes no sense to write out restriction checking function that is incomplete
        //      AND that we do not use.  So for now, do not write  out it out. 
        if (type.isSimpleType())
            return;
        
        try
        {
            c_writer = new BufferedWriter(new FileWriter(getFilePath(false), false));
            writeClassComment();
            writePreprocessorStatements();
            if (type.isSimpleType())
                writeRestrictionCheckerFunction();
            else
            {
                writeGlobalCodes();
                writeAttributes();
                writeMethods();
            }
            //cleanup
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
    {}

    /**
     * @throws WrapperFault
     */
    protected abstract void writeGlobalCodes() throws WrapperFault;

    /* (non-Javadoc)
     * @see org.apache.axis.wsdl.wsdl2ws.BasicFileWriter#getFilePath()
     */
    protected File getFilePath() throws WrapperFault
    {
        String targetOutputLocation = this.wscontext.getWrapperInfo().getTargetOutputLocation();
        new File(targetOutputLocation).mkdirs();
        String fileName = targetOutputLocation + "/" + this.c_classname + CUtils.getImplFileExtension();
        this.wscontext.addGeneratedFile(c_classname + CUtils.getImplFileExtension());
        return new File(fileName);
    }

    /* (non-Javadoc)
     * @see org.apache.axis.wsdl.wsdl2ws.BasicFileWriter#writePreprocessorStatements()
     */
    protected void writePreprocessorStatements() throws WrapperFault
    {
        try
        {
            c_writer.write("#include <stdlib.h>\n");
            c_writer.write("#include <string.h>\n");
            c_writer.write("\n");
            
            c_writer.write("#include \"" + CUtils.resolveWSDL2LanguageNameClashes(this.c_classname) + CUtils.getHeaderFileExtension() + "\"\n");
            c_writer.write("\n");

            c_writer.write("#include <axis/client/Stub.h>\n");
            c_writer.write("#include <axis/client/Call.h>\n");
            c_writer.write("#include <axis/AxisWrapperAPI.h>\n");
            c_writer.write("#include <axis/IWrapperSoapSerializer.h>\n");
            c_writer.write("#include <axis/IWrapperSoapDeSerializer.h>\n");
            c_writer.write("\n");
        }
        catch (IOException e)
        {
            throw new WrapperFault(e);
        }
    }
}
