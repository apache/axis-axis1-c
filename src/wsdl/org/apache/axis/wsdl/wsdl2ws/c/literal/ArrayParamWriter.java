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

import java.io.IOException;

import org.apache.axis.wsdl.wsdl2ws.WrapperFault;
import org.apache.axis.wsdl.wsdl2ws.info.Type;
import org.apache.axis.wsdl.wsdl2ws.info.WebServiceContext;

public class ArrayParamWriter
    extends org.apache.axis.wsdl.wsdl2ws.c.ArrayParamWriter
{
    /**
     * @param wscontext
     * @param type
     * @throws WrapperFault
     */
    public ArrayParamWriter(WebServiceContext wscontext, Type type)
        throws WrapperFault
    {
        super(wscontext, type);
    }

    /* (non-Javadoc)
     * @see org.apache.axis.wsdl.wsdl2ws.c.ArrayParamWriter#writeArrayStruct()
     */
    protected void writeArrayStruct() throws WrapperFault
    {
        try
        {
            writer.write("typedef struct " + classname + "Tag\n{\n");
            /*
             * Needed for self referenced  array else compilation failed.
             * <xsd:complexType name="Type1">
             *	<xsd:sequence>
             *		<xsd:element name="followings" maxOccurs="unbounded" minOccurs="0" type="tns:Type1" />
             *		<xsd:element name="kind" type="xsd:string" />
             *		<xsd:element name="index" type="xsd:int" />
             *	</xsd:sequence>
             *	<xsd:attribute name="att_kind" type="tns:Kind" />
             * </xsd:complexType>
             */
            //writer.write("\t"+attribs[0].getTypeName()+"* m_Array;\n\tint m_Size;\n} "+classname+";\n\n");
            writer.write(
                "\tstruct "
                    + attribs[0].getTypeName()
                    + "Tag * m_Array;\n\tint m_Size;\n} "
                    + classname
                    + ";\n\n");
        }
        catch (IOException e)
        {
            throw new WrapperFault(e);
        }
    }
}
