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
 *        Apache Software Foundation (http://www.apache.org/)."
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

package services.calculator;

import java.util.Vector;

import org.apache.axismora.MessageContext;
import org.apache.axismora.handlers.BasicHandler;
import org.apache.axismora.wrappers.simpleType.FloatParam;
import org.apache.axismora.wrappers.simpleType.IntParam;

import org.apache.axis.AxisFault;
import org.apache.axis.message.SOAPFault;

/**
 * @author {jkuamranc@opensource.lk}
 */

public class CalculatorService extends BasicHandler {
    private Calculator cal;

    public CalculatorService() {
        this.cal = new Calculator();
    }

    public void invoke(MessageContext md) {

        try {
            String method = md.getMethodName().getLocalPart();
            if (method.equals("add")) {
                add(md);
            } else if (method.equals("sub")) {
                sub(md);
            } else if (method.equals("mul")) {
                mul(md);
            } else if (method.equals("div")) {
                div(md);
            }
        } catch (Exception e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }

    }

    public void add(MessageContext md) {
        try {
            Vector obj = new Vector();
            int i = 0;
            String val = md.getValue("someuri", "add");
            while (val != null) {
                obj.add(new IntParam(Integer.parseInt(val)));
                val = md.getValue("someuri", "add");
                i++;
            }
            if (i == 2) {
                IntParam a = (IntParam) obj.get(0);
                IntParam b = (IntParam) obj.get(1);
                IntParam pw = new IntParam(cal.add(a.getParam(), b.getParam()));
                md.setSoapBodyContent(pw);
            } else if (i == 3) {
                IntParam a = (IntParam) obj.get(0);
                IntParam b = (IntParam) obj.get(1);
                IntParam c = (IntParam) obj.get(2);
                IntParam pw =
                    new IntParam(cal.add(a.getParam(), b.getParam(), c.getParam()));
                md.setSoapBodyContent(pw);
            } else
                throw new AxisFault("method sinature not found");
        } catch (Exception e) {
            e.printStackTrace();
            md.setSoapFault(new SOAPFault(new AxisFault("Error at wrapper", e)));
            //set the soap fault
        }
    }

    public void sub(MessageContext md) {
        try {
            IntParam a = new IntParam(Integer.parseInt(md.getValue()));
            IntParam b = new IntParam(Integer.parseInt(md.getValue()));
            IntParam pw = new IntParam(cal.sub(a.getParam(), b.getParam()));
            md.setSoapBodyContent(pw);
        } catch (Exception e) {
            e.printStackTrace();
            md.setSoapFault(new SOAPFault(new AxisFault("Error at wrapper", e)));
            //set the soap fault
        }
    }

    public void mul(MessageContext md) {
        try {
            IntParam a = new IntParam(Integer.parseInt(md.getValue()));
            IntParam b = new IntParam(Integer.parseInt(md.getValue()));
            IntParam pw = new IntParam(cal.mul(a.getParam(), b.getParam()));
            md.setSoapBodyContent(pw);
        } catch (Exception e) {
            e.printStackTrace();
            md.setSoapFault(new SOAPFault(new AxisFault("Error at wrapper", e)));
            //set the soap fault
        }
    }

    public void div(MessageContext md) {
        try {
            FloatParam a = new FloatParam(Float.parseFloat(md.getValue()));
            FloatParam b = new FloatParam(Float.parseFloat(md.getValue()));
            FloatParam pw = new FloatParam(cal.div(a.getParam(), b.getParam()));
            md.setSoapBodyContent(pw);
        } catch (Exception e) {
            e.printStackTrace();
            md.setSoapFault(new SOAPFault(new AxisFault("Error at wrapper", e)));
            //set the soap fault
        }
    }

}
