/*
 * The Apache Software License, Version 1.1
 *
 *
 * Copyright (c) 2001 The Apache Software Foundation.  All rights
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
 * 4. The names "SOAP" and "Apache Software Foundation" must
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
 * individuals on behalf of the Apache Software Foundation and was
 * originally based on software copyright (c) 2001, International
 * Business Machines, Inc., http://www.apache.org.  For more
 * information on the Apache Software Foundation, please see
 * <http://www.apache.org/>.
 */

package org.apache.axis.components.bridge;

import java.util.Hashtable;
import java.util.Vector;

/**
 * Class COMBridge
 *
 * @author James Snell <jmsnell@apache.org>
 * @author Davanum Srinivas <dims@yahoo.com>
 */
public class COMBridge {

    /** Field vp           */
    private byte[] vp = null;

    /** Field progid           */
    private String progid = null;

    /** Field threadingModel           */
    private String threadingModel = null;

    /** Field dllLoadException           */
    static Throwable dllLoadException =
            null;                                       // Can hold an exception on from the loading of the c++ dll.

    /** Field libName           */
    static final String libName = "COMBridge";    // C++ dll name.

    /** Field sizeOfVariant           */
    private static final int sizeOfVariant = 16;

    static {
        try {
            System.loadLibrary(libName);
        } catch (java.lang.SecurityException e) {
            dllLoadException = e;
        } catch (java.lang.UnsatisfiedLinkError e) {
            dllLoadException = e;
        }
    }

    /**
     * Method execute
     *
     * @param methodName
     * @param parms
     * @param props
     *
     * @return
     *
     * @throws Throwable
     */
    public Object execute(String methodName, Vector parms, Hashtable props)
            throws Throwable {

        if (null != dllLoadException) {
            throw dllLoadException;
        }
        int noParms = 0;
        if (parms != null) {
            vp = new byte[sizeOfVariant * parms.size()];
            noParms = parms.size();
        }
        for (int i = 0; i < noParms; ++i) {
            // Yes. Parameters are reversed here.
            objectToVariant((parms.elementAt(noParms - i - 1)), vp,
                    i * sizeOfVariant);
        }
        progid = (String) props.get("progid");
        threadingModel = (String) props.get("threadmodel");
        if (null == threadingModel) {
            threadingModel = "MULTITHREADED";
        }
        return invoke(threadingModel, progid, methodName, vp);
    }    

    /**
     * Method logit
     *
     * @param level
     * @param msg
     */
    protected void logit(int level, String msg)     // Called by CPP
    {
        System.out.println("CPP:" + msg);
    }

    /**
     * Method invoke
     *
     * @param threadingModel
     * @param progId
     * @param methodName
     * @param parms
     *
     * @return
     *
     * @throws Exception
     */
    private native Object invoke(
            String threadingModel, String progId, String methodName, byte[] parms)
            throws Exception;

    /**
     * Method nativeConvertToBString
     *
     * @param o
     *
     * @return
     */
    private static native byte[] nativeConvertToBString(String o);

    /**
     * Method objectToVariant
     *
     * @param o
     * @param bo
     * @param os
     *
     * @return
     *
     * @throws Exception
     */
    private final byte[] objectToVariant(Object o, byte[] bo, int os)
            throws Exception {
        byte[] v = bo;

        if (null == v) {
            v = new byte[sizeOfVariant];    // Size of a variant
            os = 0;
        }
        if (null == o) {                              // to be safe.
            v[os + 0] = 1;                            // VT_NULL
            v[os + 1] = 0;
        } else if (o instanceof java.lang.Boolean)    // VT_R8
        {
            v[os + 0] = 11;                           // VT_BOOL
            v[os + 1] = 0;
            byte x = (byte) ((((Boolean) o).booleanValue())
                    ? 0xff
                    : 0);

            v[os + 8] = x;
            v[os + 9] = x;
            v[os + 10] = x;
            v[os + 11] = x;
        } else if (o instanceof java.lang.Integer)    // VT_R8
        {
            v[os + 0] = 3;                            // VT_I4
            v[os + 1] = 0;
            int x = ((Integer) o).intValue();

            v[os + 8] = (byte) x;
            v[os + 9] = (byte) ((x >>> 8) & 0xff);
            v[os + 10] = (byte) ((x >>> 16) & 0xff);
            v[os + 11] = (byte) ((x >>> 24) & 0xff);
        } else if (o instanceof java.lang.String) {
            v[os + 0] = 8;                            // VT_BSTR
            v[os + 1] = 0;
            byte[] pbs = nativeConvertToBString((String) o);

            v[os + 8] = pbs[0];
            v[os + 9] = pbs[1];
            v[os + 10] = pbs[2];
            v[os + 11] = pbs[3];
        } else if (o instanceof java.lang.Long)       // VT_R8
        {    // COM has no long type so promote it to double which can contain it.
            v[os + 0] = 5;                            // VT_R8
            v[os + 1] = 0;
            long x = Double.doubleToLongBits((double) (((Long) o).longValue()));

            v[os + 8] = (byte) x;
            v[os + 9] = (byte) ((x >>> 8) & 0xff);
            v[os + 10] = (byte) ((x >>> 16) & 0xff);
            v[os + 11] = (byte) ((x >>> 24) & 0xff);
            v[os + 12] = (byte) ((x >>> 32) & 0xff);
            v[os + 13] = (byte) ((x >>> 40) & 0xff);
            v[os + 14] = (byte) ((x >>> 48) & 0xff);
            v[os + 15] = (byte) ((x >>> 56) & 0xff);
        } else if (o instanceof java.lang.Short) {
            v[os + 0] = 2;                            // VT_I2
            v[os + 1] = 0;
            int x = ((Short) o).intValue();

            v[os + 8] = (byte) x;
            v[os + 9] = (byte) ((x >>> 8) & 0xff);
            v[os + 10] = (byte) ((x >>> 16) & 0xff);
            v[os + 11] = (byte) ((x >>> 24) & 0xff);
        } else if (o instanceof java.lang.Float) {
            v[os + 0] = 4;                            // VT_R4
            v[os + 1] = 0;
            int x = Float.floatToIntBits(((Float) o).floatValue());

            v[os + 8] = (byte) x;
            v[os + 9] = (byte) ((x >>> 8) & 0xff);
            v[os + 10] = (byte) ((x >>> 16) & 0xff);
            v[os + 11] = (byte) ((x >>> 24) & 0xff);
        } else if (o instanceof java.lang.Double)     // VT_R8
        {
            v[os + 0] = 5;                            // VT_R8
            v[os + 1] = 0;
            long x = Double.doubleToLongBits(((Double) o).doubleValue());

            v[os + 8] = (byte) x;
            v[os + 9] = (byte) ((x >>> 8) & 0xff);
            v[os + 10] = (byte) ((x >>> 16) & 0xff);
            v[os + 11] = (byte) ((x >>> 24) & 0xff);
            v[os + 12] = (byte) ((x >>> 32) & 0xff);
            v[os + 13] = (byte) ((x >>> 40) & 0xff);
            v[os + 14] = (byte) ((x >>> 48) & 0xff);
            v[os + 15] = (byte) ((x >>> 56) & 0xff);
        } else if (o instanceof java.lang.Byte) {
            v[os + 0] = 17;                           // VT_UI1
            v[os + 1] = 0;
            byte x = ((Byte) o).byteValue();

            v[os + 8] = x;
        } else if (o instanceof java.lang.Character) {
            v[os + 0] = 17;                           // VT_UI1
            v[os + 1] = 0;
            byte x = (byte) ((Character) o).charValue();

            v[os + 8] = x;
        } else if (o instanceof java.lang.Void) {
            v[os + 0] = 1;                            // VT_NULL
            v[os + 1] = 0;
        } else if (o.getClass().isArray()) {

            // ArrayInfo ai= new ArrayInfo(o);
            // v= ai.toVariant();
            throw new Exception(
                    "Currently arrays are unsupported,  type received:"
                    + o.getClass().getName());
        } else {
            throw new Exception("Currently unsupported data type received:"
                    + o.getClass().getName());
        }
        return v;
    }

    public static void main(String[] args) throws Throwable {
        org.apache.axis.components.bridge.COMBridge bridge = new org.apache.axis.components.bridge.COMBridge();
        Hashtable props = new Hashtable();
        props.put("progid", "Apacheadder.adder");

        String  methodName2 = "add";
        Vector  params2 = new Vector();
        params2.add(new Short("6"));
        params2.add(new Short("5"));
        Object ret2 = bridge.execute(methodName2, params2, props);
        System.out.println("return:" + ret2);
    }
}
