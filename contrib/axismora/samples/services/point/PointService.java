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

package services.point;

import org.apache.axis.AxisFault;
import org.apache.axis.message.SOAPFault;
import org.apache.axismora.MessageContext;
import org.apache.axismora.handlers.BasicHandler;
import org.apache.axismora.wrappers.simpleType.DoubleParam;
import org.apache.axismora.wrappers.simpleType.IntParam;
import org.apache.axismora.wrappers.simpleType.StringParam;

/**
 * An <code>PointService</code> is the wrapper class for the service Point.
 * It Handles common mapping functionality by dealing with the
 * both message data and the service class.
 * This wrapper is created automatically and the design is under construction.
 * 
 *  @author Jeyakumaran {jkuamranc@opensource.lk}
 */
public class PointService extends BasicHandler {
    private Point p;

    public PointService() {
        this.p = new Point(0, 0);
    }

    //The only method which is known and invoked by the provider is invoke method.
    public void invoke(MessageContext md) {
        try {
            String method = md.getMethodName().getLocalPart();
            //Because to take only the method name,not the QName
            if (method.equals("addPoint")) {
                addPoint(md); //complex parsing complex return
            } else if (method.equals("distance")) {
                distance(md); //complex parsing simple return
            } else if (method.equals("operations")) {
                operations(md); //simple parsing complex return
            } else if (method.equals("add")) {
                add(md); //simple parsing simple return
            } else if (method.equals("getName")) {
                getName(md);
            }
        } catch (Exception e) {
            e.printStackTrace();
            md.setSoapFault(
                new SOAPFault(new AxisFault("Error at wrapper", e)));
            //set the soap fault
        }
    }

    public void onFalult(MessageContext msgdata) {
        //Still under construction
    }

    public void init() {
        //Do any initialization here.
    }

    public void cleanup() {
        //Do any finalization here.
    }

    public void addPoint(MessageContext md) {
        PointParam pw1 = new PointParam(md);
        PointParam pw2 = new PointParam(md);
        Point p1 = new Point(pw1.getPoint().getX(), pw1.getPoint().getY());
        Point p2 = new Point(pw2.getPoint().getX(), pw2.getPoint().getY());
        try {
            PointParam pw = new PointParam(p.addPoint(p1, p2));
            md.setSoapBodyContent(pw);
        } catch (Exception e) {
            e.printStackTrace();
            md.setSoapFault(
                new SOAPFault(new AxisFault("Error at wrapper", e)));
            //set the soap fault
        }
    }

    public void distance(MessageContext md) {
        PointParam pw1 = new PointParam(md);
        PointParam pw2 = new PointParam(md);

        Point p1 = pw1.getPoint();
        Point p2 = pw2.getPoint();

        try {
            DoubleParam pw = new DoubleParam(p.distance(p1, p2));
            md.setSoapBodyContent(pw);
        } catch (Exception e) {
            md.setSoapFault(
                new SOAPFault(new AxisFault("Error at wrapper", e)));
            //set the soap fault
            //set the soap fault
        }
    }

    public void operations(MessageContext md) {
        try {
            IntParam num = new IntParam(Integer.parseInt(md.getValue()));
            IntParam x = new IntParam(Integer.parseInt(md.getValue()));
            IntParam y = new IntParam(Integer.parseInt(md.getValue()));

            PointParam pw =
                new PointParam(
                    p.operations(num.getParam(), x.getParam(), y.getParam()));
            md.setSoapBodyContent(pw);
        } catch (Exception e) {
            md.setSoapFault(
                new SOAPFault(new AxisFault("Error at wrapper", e)));
            //set the soap fault
        }
    }

    public void add(MessageContext md) {

        try {
            IntParam a = new IntParam(Integer.parseInt(md.getValue()));
            IntParam b = new IntParam(Integer.parseInt(md.getValue()));

            IntParam pw = new IntParam(p.add(a.getParam(), b.getParam()));
            md.setSoapBodyContent(pw);
        } catch (Exception e) {
            md.setSoapFault(
                new SOAPFault(new AxisFault("Error at wrapper", e)));
            //set the soap fault
        }
    }

    public void getName(MessageContext md) {
        try {
            StringParam str1 = new StringParam(md.getValue());
            StringParam str2 = new StringParam(md.getValue());

            StringParam pw =
                new StringParam(p.getName(str1.getParam(), str2.getParam()));
            md.setSoapBodyContent(pw);
        } catch (Exception e) {
            md.setSoapFault(
                new SOAPFault(new AxisFault("Error at wrapper", e)));
            //set the soap fault
        }
    }

}