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
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

import org.apache.axis.wsdl.wsdl2ws.CUtils;
import org.apache.axis.wsdl.wsdl2ws.WrapperFault;
import org.apache.axis.wsdl.wsdl2ws.ParamWriter;
import org.apache.axis.wsdl.wsdl2ws.info.Type;
import org.apache.axis.wsdl.wsdl2ws.info.WebServiceContext;
import org.apache.axis.wsdl.wsdl2ws.WSDL2Ws;

public abstract class ParamCPPFileWriter extends ParamWriter
{
    public ParamCPPFileWriter(WebServiceContext wscontext, Type type)
        throws WrapperFault
    {
        super(wscontext, type);
    }

    protected void writeConstructors() throws WrapperFault
    {}
    protected void writeDestructors() throws WrapperFault
    {}
    protected abstract void writeRestrictionCheckerFunction()
        throws WrapperFault;

    public void writeSource() throws WrapperFault
    {
        try
        {
            this.writer = new BufferedWriter(new FileWriter(getFilePath(), false));
            writeClassComment();
            writePreprocessorStatements();
            
            if (type.isSimpleType())
                writeRestrictionCheckerFunction();
            else
            {
                writeAttributes();
                writeConstructors();
                writeDestructors();
                writeMethods();                
                writeGlobalCodes();
            }
            
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

    protected void writeMethods() throws WrapperFault
    {}
    protected abstract void writeGlobalCodes() throws WrapperFault;
    protected File getFilePath() throws WrapperFault
    {
        classname = CUtils.sanitizeString( classname);

        String targetOutputLocation = this.wscontext.getWrapperInfo().getTargetOutputLocation();
        new File(targetOutputLocation).mkdirs();
        String fileName = targetOutputLocation + "/" + this.classname + CUtils.getImplFileExtension();
        this.wscontext.addGeneratedFile(classname + CUtils.getImplFileExtension());
        return new File(fileName);
    }

    protected void writePreprocessorStatements() throws WrapperFault
    {
        try
        {
            writer.write("#include <axis/AxisException.hpp>\n");
            writer.write("#include <axis/ElementMissingException.hpp>\n");
            writer.write("#include <axis/RedundantElementException.hpp>\n");
            writer.write("#include <axis/UnknownElementException.hpp>\n");
            writer.write("#include <axis/AxisWrapperAPI.hpp>\n");
            writer.write("#include <axis/Axis.hpp>\n\n");
            writer.write("#include \"" + this.classname + CUtils.getHeaderFileExtension() + "\"\n");
        }
        catch (IOException e)
        {
            throw new WrapperFault(e);
        }
    }
}
