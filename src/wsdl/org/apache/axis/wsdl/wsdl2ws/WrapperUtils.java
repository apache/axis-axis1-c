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
 * Utility Classes
 * @author Srinath Perera(hemapani@openource.lk)
 */
package org.apache.axis.wsdl.wsdl2ws;

import java.util.Iterator;
import java.util.Stack;
import java.util.StringTokenizer;

import javax.xml.namespace.QName;

import org.apache.axis.wsdl.wsdl2ws.info.ParameterInfo;
import org.apache.axis.wsdl.wsdl2ws.info.Type;
import org.apache.axis.wsdl.wsdl2ws.info.TypeMap;
import org.apache.axis.wsdl.wsdl2ws.info.WebServiceContext;

public class WrapperUtils
{
    private static int nscount = 0;
    /**
     * translation fullyqualifiedname -> packagename
     */
    public static String getPackegeName4QualifiedName(String fullyQualifiedName)
    {
        int index = fullyQualifiedName.indexOf('.');
        int lastIndex = 0;
        while (index != -1)
        {
            lastIndex = index;
            index = fullyQualifiedName.indexOf('.', lastIndex + 1);
        }
        if (lastIndex == 0)
        {
            return fullyQualifiedName;
        }

        return fullyQualifiedName.substring(0, lastIndex);

    }

    /**
     * take care of the conversion from basic type name to parameter names. e.g. int -> Int
     * the param will not intParam but IntParm !!!
     * @param packagename
     * @param classname
     * @return fully quallified name for the param class.   
     */

    /**
     * extract the parameter name from the fully qualified name
     * @param fullyQualifiedName
     * @return only the class name 
     */
    public static String getClassNameFromFullyQualifiedName(String fullyQualifiedName)
    {
        int index = fullyQualifiedName.indexOf('.');
        int lastIndex = 0;
        while (index != -1)
        {
            lastIndex = index;
            index = fullyQualifiedName.indexOf('.', lastIndex + 1);
        }
        if (lastIndex == 0)
        {
            return fullyQualifiedName;
        }

        return fullyQualifiedName.substring(lastIndex + 1);
    }

    /**
     *  get classpart of the class and if name happen to be a Simple type return 
     *  the Wrapper Class name(service.0 wrapper class name) eg int -> Int ect
     *  
     */
    public static String getLanguageTypeName4Type(Type type)
        throws WrapperFault
    {
        if (type.isArray())
        {
            QName qname = getArrayType(type).getName();
            //this can never be a simple type
            return CUtils.getCmplxArrayNameforType(qname);
        }
        else
        {
            String fullyQualifiedName = type.getLanguageSpecificName();
            return getClassNameFromFullyQualifiedName(fullyQualifiedName);
        }
    }

    /**
     * Capitalize the first Character of a given String. 
     * @param value String 
     * @return changed String 
     */
    public static String capitalizeFirstCaractor(String value)
    {
        char[] chars = value.toCharArray();
        chars[0] = Character.toUpperCase(value.charAt(0));
        return new String(chars);
    }

    /* This return the String of type xsi:type ="typename"*/
    public static String getParamTypeString(QName name)
    {
        nscount++;
        return " xsi:type=\\\"ns"
            + nscount
            + ":"
            + name.getLocalPart()
            + "\\\"  xmlns:ns"
            + nscount
            + " = \\\""
            + name.getNamespaceURI()
            + "\\\"";
    }

    public static String firstCharacterToLowercase(String value)
    {
        char[] chars = value.toCharArray();
        chars[0] = Character.toLowerCase(value.charAt(0));
        return new String(chars);
    }
    public static String nsURI2packageName(String nsuri)
    {

        //gard agien if nsuri is urn | http and nothing return		
        if (("urn".equals(nsuri) || "http".equals(nsuri)))
        {
            return nsuri;
        }

        StringTokenizer tokenizer = new StringTokenizer(nsuri, ":/.", false);
        String token;
        Stack stack = new Stack();

        //first ine may be urn: or http: remove it
        if (tokenizer.hasMoreTokens())
        {
            token = tokenizer.nextToken();
            if (!("urn".equals(token) || "http".equals(token)))
            {
                stack.push(token);
            }
        }

        while (tokenizer.hasMoreTokens())
        {
            token = tokenizer.nextToken();
            if (!(token == null || "".equals(token)))
            {
                stack.push(token);
            }
        }

        // create the String from the stack
        StringBuffer buff = new StringBuffer(150);
        if (!stack.isEmpty())
        {
            buff.append((String) stack.pop());
        }
        while (!stack.isEmpty())
        {
            buff.append('.');
            buff.append((String) stack.pop());

        }

        String changednsuri = buff.toString();
        //remove any unexpected charactors		
        changednsuri = changednsuri.replaceAll("[^(a-zA-z0-9|.|_)]", "_");
        return changednsuri;
    }

    public static String getClassNameFromParamInfoConsideringArrays(
        ParameterInfo param,
        WebServiceContext wscontext)
        throws WrapperFault
    {
        if (param.getType().getName().equals(CUtils.anyTypeQname))
        { //anyType
            return "AnyType*";
        }
        Type type = wscontext.getTypemap().getType(param.getSchemaName());
        if (type.isSimpleType())
        {
            return param.getLangName();
        }
        else
        {
            if (!TypeMap.isSimpleType(param.getSchemaName()))
            { //array or complex types
                if (type.isArray())
                {
                    String arrayName =
                        CUtils.getCmplxArrayNameforType(
                            getArrayType(type).getName());
                    if (null == arrayName)
                    { //simple type array
                        /* Does the program flow ever come to this place ? if so in which situation ? - Susantha 20/10/2004 */
                        arrayName =
                            CUtils.getBasicArrayNameforType(
                                CUtils.getclass4qname(
                                    getArrayType(type).getName()));
                    }
                    return arrayName;
                }
                else
                {
                    return param.getLangName() + "*";
                    //All complex types will be pointers	
                }
            }
            else
            {
                if (param.isArray())
                {
                    /* This enables having simple type array declarations in the wrapping element
                     * <s:element name="GetProjectNamesResponse">
                    	<s:complexType>
                    		<s:sequence>
                    			<s:element minOccurs="0" maxOccurs="unbounded" form="unqualified" name="return" type="s:string" />
                    		</s:sequence>
                    	</s:complexType>
                    </s:element>
                     */
                    return CUtils.getBasicArrayNameforType(
                        CUtils.getclass4qname(type.getName()));
                }
                else
                {
                    return param.getLangName();
                }
            }
        }
    }

    public static Type getArrayType(Type type) throws WrapperFault
    {
        if (!type.isArray())
        {
            return null;
        }
        Iterator elements = type.getElementnames();
        if (elements.hasNext())
        {
            return type
                .getElementForElementName((String) elements.next())
                .getType();
        }
        throw new WrapperFault("Array type do not have any attibutes");
    }

}
