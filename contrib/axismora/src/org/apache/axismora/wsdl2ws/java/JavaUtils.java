/*
 * The Apache Software License, Version 1.1
 *
 *
 * Copyright (c) 2001-2003 The Apache Software Foundation.  All rights
 * reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * 3. The end-user documentation included with the redistribution,
 *    if any, must include the following acknowledgment:
 *       "This product includes software developed by the
 *    Apache Software Foundation (http://www.apache.org/)."
 *    Alternately, this acknowledgment may appear in the software itself,
 *    if and wherever such third-party acknowledgments normally appear.
 *
 * 4. The names "Axis" and "Apache Software Foundation" must
 *    not be used to endorse or promote products derived from this
 *    software without prior written permission. For written
 *    permission, please contact apache@apache.org.
 *
 * 5. Products derived from this software may not be called "Apache",
 *    nor may "Apache" appear in their name, without prior written
 *    permission of the Apache Software Foundation.
 *
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESSED OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED.  IN NO EVENT SHALL THE APACHE SOFTWARE FOUNDATION OR
 * ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
 * USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 * ====================================================================
 *
 * This software consists of voluntary contributions made by many
 * individuals on behalf of the Apache Software Foundation.  For more
 * information on the Apache Software Foundation, please see
 * <http://www.apache.org/>.
 */

package org.apache.axismora.wsdl2ws.java;

import org.apache.axismora.wsdl2ws.WrapperFault;
import org.apache.axismora.wsdl2ws.WrapperUtils;
import org.apache.axismora.wsdl2ws.info.ParameterInfo;
import org.apache.axismora.wsdl2ws.info.Type;
import org.apache.axismora.wsdl2ws.info.TypeMap;
import org.apache.axismora.wsdl2ws.info.WebServiceContext;

/**
 * @author hemapani
 */
public class JavaUtils {

    private static String[] unwrappedSimpleTypes =
        new String[] {
            "org.apache.axismora.wrappers.simpleType.Base64ByteArrayParam",
            "org.apache.axismora.wrappers.simpleType.HexBinaryParam" };

    public static boolean isUnwrapperdSimpleType(String type) {
        for (int i = 0; i < unwrappedSimpleTypes.length; i++) {
            if (unwrappedSimpleTypes[i].equals(type))
                return true;
        }
        return false;
    }

    public static boolean isJavaSimpleType(String type) {
        if ("int".equals(type)
            || "long".equals(type)
            || "float".equals(type)
            || "double".equals(type)
            || "short".equals(type)
            || "byte".equals(type)
            || "char".equals(type)
            || "boolean".equals(type))
            return true;
        return false;
    }

    public static String getSimpleTypeParameterCreationCode(
        ParameterInfo inparam,
        WebServiceContext wscontext,
        int i)
        throws WrapperFault {
        String paramUsualName = inparam.getLangName();
        String paraTypeName =
            WrapperUtils.getWrapperName4FullyQualifiedName(paramUsualName);
        StringBuffer code = new StringBuffer();

        Type type;
        if ((TypeMap.isSimpleType(inparam.getLangName()))) {
            if (isUnwrapperdSimpleType(paramUsualName))
                code.append(
                    "\t\t" + paramUsualName + " paramIn" + i 
                    + " =  new  "+ paraTypeName + "(msgdata);");
            else
                //if it is unwrapped simple type we should not print ".getParam() 
                code.append(
                    "\t\t" + paramUsualName + " paramIn" + i
                        + " =  (new  " + paraTypeName  + "(msgdata)).getParam();\n");
        } else if (
            (type = wscontext.getTypemap().getType(inparam.getSchemaName()))
                != null
                && type.isArray()) {
            String ContentparaTypeName =
                WrapperUtils.getClassNameFromParamInfoConsideringArrays(
                    inparam,
                    wscontext);
            code.append(
                "\t\t" + paraTypeName + " temp" + i
                    + " =  new  " + paraTypeName + "();\n");
            code.append("\t\ttemp" + i + ".desierialize(msgdata);\n");
            code.append(
                "\t\t" + ContentparaTypeName + " paramIn"
                + i + "= temp" + i + ".getParam();\n");
        } else {
            code.append(
                "\t\t"
                    + paraTypeName  + " paramIn"  + i
                    + " =  new  " + paraTypeName + "();\n");
            code.append("\t\tparamIn" + i + ".desierialize(msgdata);\n");
        }
        return code.toString();
    }
}
