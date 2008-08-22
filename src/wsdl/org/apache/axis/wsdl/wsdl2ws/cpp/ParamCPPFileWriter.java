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
        super(wscontext, type, CUtils.getImplFileExtension());
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
            c_writer = new BufferedWriter(new FileWriter(getFilePath(false), false));
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
            
            c_writer.flush();
            c_writer.close();
            if (WSDL2Ws.c_verbose)
                System.out.println(getFilePath(false).getAbsolutePath() + " created.....");
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
        c_classname = CUtils.sanitizeString( c_classname);

        String targetOutputLocation = this.wscontext.getWrapperInfo().getTargetOutputLocation();
        new File(targetOutputLocation).mkdirs();
        String fileName = targetOutputLocation + "/" + this.c_classname + CUtils.getImplFileExtension();
        this.wscontext.addGeneratedFile(c_classname + CUtils.getImplFileExtension());
        return new File(fileName);
    }

    protected void writePreprocessorStatements() throws WrapperFault
    {
        try
        {
            c_writer.write("#include <axis/AxisException.hpp>\n");
            c_writer.write("#include <axis/ElementMissingException.hpp>\n");
            c_writer.write("#include <axis/RedundantElementException.hpp>\n");
            c_writer.write("#include <axis/UnknownElementException.hpp>\n");
            c_writer.write("#include <axis/AxisWrapperAPI.hpp>\n");
            c_writer.write("#include <axis/Axis.hpp>\n\n");
            c_writer.write("#include \"" + this.c_classname + CUtils.getHeaderFileExtension() + "\"\n");
        }
        catch (IOException e)
        {
            throw new WrapperFault(e);
        }
    }
}
