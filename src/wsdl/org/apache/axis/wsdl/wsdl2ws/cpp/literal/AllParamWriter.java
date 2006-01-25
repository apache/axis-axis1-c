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
 * Parameter genarator.. genarate all necessary param classes
 * @author Srinath Perera(hemapani@openource.lk)
 * @author Susantha Kumara(susantha@opensource.lk, skumara@virtusa.com)
 * @author Samisa Abeysinghe (sabeysinghe@virtusa.com)
 */

package org.apache.axis.wsdl.wsdl2ws.cpp.literal;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Iterator;

import javax.xml.namespace.QName;

import org.apache.axis.wsdl.wsdl2ws.CUtils;
import org.apache.axis.wsdl.wsdl2ws.SourceWriter;
import org.apache.axis.wsdl.wsdl2ws.WSDL2Ws;
import org.apache.axis.wsdl.wsdl2ws.WrapperFault;
import org.apache.axis.wsdl.wsdl2ws.cpp.ArrayParamHeaderWriter;
import org.apache.axis.wsdl.wsdl2ws.cpp.ArrayParamWriter;
import org.apache.axis.wsdl.wsdl2ws.info.Type;
import org.apache.axis.wsdl.wsdl2ws.info.WebServiceContext;

public class AllParamWriter implements SourceWriter
{
    private WebServiceContext wscontext;

    public AllParamWriter(WebServiceContext wscontext)
    {
        this.wscontext = wscontext;
    }

    private File getFilePath(String filename) throws WrapperFault
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
            targetOutputLocation + "/" + filename + CUtils.CPP_HEADER_SUFFIX;
        return new File(fileName);
    }

    /**
     * genarate all the wrappets for custom complex types.
     * @see org.apache.axis.wsdl.wsdl2ws.SourceWriter#writeSource()
     */
    public void writeSource() throws WrapperFault
    {
        Iterator enu = wscontext.getTypemap().getTypes().iterator();
        Type type = null;
        while (enu.hasNext())
        {
            try
            {
                type = (Type) enu.next();
                    if (type.isArray())
                    {
                        if (WSDL2Ws.verbose)
                        {
                            System.out.println("Array writer called ......");
                        }
                        QName qname = type.getName();

                        
                        String elementType = type.getElementType();
                        elementType = elementType.replace('>', '_');
                        QName elementQname = new QName(qname.getNamespaceURI(), elementType);
                        Type currentType = wscontext.getTypemap().getType(elementQname);
                        if (currentType != null)
                        {
	                        if ( currentType.isSimpleType())
	                        {
	                            continue;
	                        }
                        }
                        
                        if (CUtils.isSimpleType(qname)
                            && !CUtils.isDefinedSimpleType(qname))
                        {
                            throw new WrapperFault(
                                "No need to create an Array for simple type "
                                    + qname
                                    + "\n"
                                    + "It seems that some thing wrong with symbolTable population - Susantha");
                        }
                        ArrayParamHeaderWriter writer =
                            (new ArrayParamHeaderWriter(wscontext, type));
                        if (!writer.isSimpleTypeArray())
                        {
                            writer.writeSource();
                            (new ArrayParamWriter(wscontext, type)).writeSource();
                        }
                    }
                    else
                    {
                        /* TODO check whether this type is referenced or not. Synthesize only if  reference
                         * But of cause that depends on the commandline option too  */
                        if (type.getLanguageSpecificName().startsWith(">"))
                        {
                            /* TODO do some processing to this type before synthesizing to remove ">" charactors.
                             * And then it should also be synthesized if commandline option says to */
                            if(WSDL2Ws.verbose)
                            {
                                System.out.println(
                                "ignoring anonymous type "
                                    + type.getLanguageSpecificName()
                                    + "\n");
                            }
                        }
                        else
                        {
                            if (WSDL2Ws.verbose)
                            {
                                System.out.println(
                                    "struct writer called ......");
                            }
                            (new BeanParamWriter(wscontext, type))
                                .writeSource();
                            (new ParmHeaderFileWriter(wscontext, type))
                                .writeSource();
                        }
                    }
            }
            catch (Exception e)
            {
                System.out.println(
                    "Error occurred generating code for "
                        + type.getLanguageSpecificName()
                            + ". Other classes will continue to be generated.");                
                e.printStackTrace();
            }
        }
    }
}
