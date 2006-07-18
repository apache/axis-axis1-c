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

package org.apache.axis.wsdl.wsdl2ws.cpp;
import java.util.Iterator;

import javax.xml.namespace.QName;

import org.apache.axis.wsdl.wsdl2ws.CUtils;
import org.apache.axis.wsdl.wsdl2ws.SourceWriter;
import org.apache.axis.wsdl.wsdl2ws.WSDL2Ws;
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
        Iterator types = wscontext.getTypemap().getTypes().iterator();
        Type type = null;
        while (types.hasNext())
        {
            try
            {
                type = (Type) types.next();
                if (type.isArray())
                {
                    QName qname = type.getName();
                    
                    String elementType = type.getElementType();
                    if (elementType != null)
                    {
                        if (WSDL2Ws.verbose)
                            System.out.println("Array element type: " + elementType);
                        elementType = elementType.replace('>', '_');
                        QName elementQname = new QName(qname.getNamespaceURI(), elementType);
                        
                        Type currentType = wscontext.getTypemap().getType(elementQname);
                        if (currentType != null)
                            if ( currentType.isSimpleType())
                            {
                                if (WSDL2Ws.verbose)
                                    System.out.println("Array writer not called - element type is simple");

                                continue;
                            }
                    }
                                            
                    if (CUtils.isSimpleType(qname) && !CUtils.isDefinedSimpleType(qname))
                    {
                        throw new WrapperFault(
                            "No need to create an Array for simple type " + qname + "\n"
                                + "It seems that some thing wrong with symbolTable population");
                    }
                    
                    ArrayParamHeaderWriter writer = (new ArrayParamHeaderWriter(wscontext, type));
                    if (!writer.isSimpleTypeArray())
                    {
                        if (WSDL2Ws.verbose)
                            System.out.println("Array writer called for......" + type.getName());
                        
                        writer.writeSource();
                        (new ArrayParamWriter(wscontext, type)).writeSource();
                    }
                }
                else if (type.isAnonymous() && !type.isExternalized())
                {
                    if(WSDL2Ws.verbose)
                        System.out.println("ignoring anonymous type " + type.getLanguageSpecificName() + "\n");
                }
                else
                {
                    if (WSDL2Ws.verbose)
                        System.out.println("struct writer called for......" + type.getName());

                    (new BeanParamWriter(wscontext, type)).writeSource();
                    (new ParmHeaderFileWriter(wscontext, type)).writeSource();
                }
            }
            catch (Exception e)
            {
                System.out.println(
                    "Error occurred generating code for " + type.getLanguageSpecificName()
                            + ". Other classes will continue to be generated.");                
                e.printStackTrace();
            }
        }
    }
}
