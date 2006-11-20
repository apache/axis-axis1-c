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
            else if( type.isRestriction())    // vvv FJP - 17667
            {
                writer.write( "\n// Type consists of purely 'restriction' information.\n// Currently no code has been written, but some may be required to check the restriction.\n\n");
            } // ^^^ FJP - 17667              
            else
            {
                writeGlobalCodes();
                writeAttributes();
                writeConstructors();
                writeDestructors();
                writeMethods();
            }
            
            writer.flush();
            writer.close();
            if (WSDL2Ws.verbose)
                System.out.println(getFilePath().getAbsolutePath() + " created.....");
        }
        catch (IOException e)
        {
            e.printStackTrace();
            throw new WrapperFault(e);
        }
    }

    protected void writeMethods() throws WrapperFault
    {}
    protected abstract void writeGlobalCodes() throws WrapperFault;
    protected File getFilePath() throws WrapperFault
    {
        classname = CUtils.sanitiseClassName( classname);

        String targetOutputLocation = this.wscontext.getWrapInfo().getTargetOutputLocation();
        if (targetOutputLocation.endsWith("/"))
            targetOutputLocation = targetOutputLocation.substring(0,targetOutputLocation.length() - 1);
        new File(targetOutputLocation).mkdirs();
        String fileName = targetOutputLocation + "/" + this.classname + CUtils.CPP_CLASS_SUFFIX;
        this.wscontext.addGeneratedFile(classname + CUtils.CPP_CLASS_SUFFIX);
        return new File(fileName);
    }

    protected void writePreprocessorStatements() throws WrapperFault
    {
        try
        {
            writer.write("#include <axis/AxisWrapperAPI.hpp>\n");
            writer.write("#include <axis/Axis.hpp>\n\n");
            writer.write("#include \"" + this.classname + CUtils.CPP_HEADER_SUFFIX + "\"\n");
        }
        catch (IOException e)
        {
            e.printStackTrace();
            throw new WrapperFault(e);
        }
    }
}
