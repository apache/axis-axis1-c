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
 * Parameter genarator.. genarate all necessary param classes
 * @author Srinath Perera(hemapani@openource.lk)
 * @author Susantha Kumara(susantha@opensource.lk, skumara@virtusa.com)
 * @author Samisa Abeysinghe (sabeysinghe@virtusa.com)
 */

package org.apache.axis.wsdl.wsdl2ws.cpp;
import java.util.Iterator;

import javax.xml.namespace.QName;

import org.apache.axis.wsdl.wsdl2ws.CUtils;
import org.apache.axis.wsdl.wsdl2ws.SourceWriter;
import org.apache.axis.wsdl.wsdl2ws.WSDL2Ws;
import org.apache.axis.wsdl.wsdl2ws.WrapperConstants;
import org.apache.axis.wsdl.wsdl2ws.WrapperFault;
import org.apache.axis.wsdl.wsdl2ws.info.Type;
import org.apache.axis.wsdl.wsdl2ws.info.WebServiceContext;

public class AllParamWriter implements SourceWriter
{
    private WebServiceContext wscontext;

    public AllParamWriter(WebServiceContext wscontext)
    {
        this.wscontext = wscontext;
    }

    /**
     * generate all the wrappets for custom complex types.
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
                if (wscontext
                    .getWrapInfo()
                    .getImplStyle()
                    .equals(WrapperConstants.IMPL_STYLE_STRUCT))
                {
                    if (type.isArray())
                    {
                        if (WSDL2Ws.verbose)
                        {
                            System.out.println("Array writer called ......");
                        }
                        QName qname = type.getName();
                        if (CUtils.isSimpleType(qname)
                            && !CUtils.isDefinedSimpleType(qname))
                        {
                            throw new WrapperFault(
                                "No need to create an Array for simple type "
                                    + qname
                                    + "\n"
                                    + "It seems that some thing wrong with symbolTable population - Susantha");
                        }
                        ArrayParamWriter writer =
                            (new ArrayParamWriter(wscontext, type));
                        if (!writer.isSimpleTypeArray())
                        {
                            writer.writeSource();
                        }
                    }
                    else
                    {
                        /* TODO check whether this type is referenced or not. Synthesize only if  reference
                         * But of cause that depends on the command line option too  */
                        if (type.getLanguageSpecificName().startsWith(">"))
                        {
                            /* TODO do some processing to this type before synthesizing to remove ">" charactors.
                             * And then it should also be synthesized if command line option says to */
                            System.out.println(
                                "ignoring anonymous type "
                                    + type.getLanguageSpecificName()
                                    + "\n");
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
            }
            catch (Exception e)
            {
                System.out.println(
                    "Error occured generating code for "
                        + type.getLanguageSpecificName()
                        + ". Yet we continue to genarate other classes ... You should check the error");
                e.printStackTrace();
            }
        }
    }
}
