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

package org.apache.axis.wsdl.wsdl2ws.c.literal;

import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;

import org.apache.axis.wsdl.wsdl2ws.WSDL2Ws;
import org.apache.axis.wsdl.wsdl2ws.WrapperFault;
import org.apache.axis.wsdl.wsdl2ws.info.Type;
import org.apache.axis.wsdl.wsdl2ws.info.WebServiceContext;

public abstract class ParamCFileWriter
    extends org.apache.axis.wsdl.wsdl2ws.c.ParamCFileWriter
{
    /**
     * @param wscontext
     * @param type
     * @throws WrapperFault
     */
    public ParamCFileWriter(WebServiceContext wscontext, Type type)
        throws WrapperFault
    {
        super(wscontext, type);
    }

    /**
     * @throws WrapperFault
     */
    protected abstract void writeRestrictionCheckerFunction()
        throws WrapperFault;

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
            if (type.isSimpleType())
            {
                writeRestrictionCheckerFunction();
            }
            else
            {
                writeGlobalCodes();
                writeAttributes();
                writeMethods();
            }
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

    /* (non-Javadoc)
     * @see org.apache.axis.wsdl.wsdl2ws.BasicFileWriter#writePreprocessorStatements()
     */
    protected void writePreprocessorStatements() throws WrapperFault
    {
        try
        {
            writer.write("#include <malloc.h>\n");
            writer.write("#include <memory.h>\n");
            writer.write("#include <axis/server/AxisWrapperAPI.h>\n\n");
            writer.write("#include \"" + this.classname + ".h\"\n");
        }
        catch (IOException e)
        {
            e.printStackTrace();
            throw new WrapperFault(e);
        }
    }
}
