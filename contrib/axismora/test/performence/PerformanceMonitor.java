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

package performence;

import java.io.FileWriter;
import java.util.Random;

import org.apache.axis.client.Call;

public class PerformanceMonitor {
    FileWriter w;
    public PerformanceMonitor() throws Exception {
        w = new FileWriter("testdata.txt", true);
    }
    private final int LOAD_REPEAT = 5;
    private final int TEST_REPEAT = 1000;
    public void measure(Call axisCall, Object[] obj1, Call axis2Call, Object[] obj2)
        throws Exception {
        for (int i = 0; i < LOAD_REPEAT; i++) {
            axisCall.invoke(obj1);
            axis2Call.invoke(obj2);
        }

        long[] axis = new long[TEST_REPEAT];
        long[] axis2 = new long[TEST_REPEAT];

        long start, end;

        for (int i = 0; i < TEST_REPEAT; i++) {
            start = System.currentTimeMillis();
            axisCall.invoke();
            end = System.currentTimeMillis();
            axis[i] = end - start;
            System.out.println("1= " + i);

            start = System.currentTimeMillis();
            axis2Call.invoke();
            end = System.currentTimeMillis();
            axis2[i] = end - start;
            System.out.println("2 = " + i);
        }

        long axismeanTot = 0;
        long axis2meanTot = 0;
        for (int i = 0; i < TEST_REPEAT; i++) {
            axismeanTot = axismeanTot + axis[i];
            axis2meanTot = axis2meanTot + axis2[i];
        }

        float axismean = axismeanTot / TEST_REPEAT;
        float axis2mean = axis2meanTot / TEST_REPEAT;

        float axissdvTot = 0;
        float axis2sdvTot = 0;
        for (int i = 0; i < TEST_REPEAT; i++) {
            axissdvTot = axissdvTot + (axis[i] - axismean) * (axis[i] - axismean);
            axis2sdvTot = axis2sdvTot + (axis2[i] - axis2mean) * (axis2[i] - axis2mean);
        }

        System.out.println("********************* Result ************************");
        System.out.println("Axis 1.1 ");
        System.out.println("Totel time   : " + axismeanTot + " milliseconds");
        System.out.println("Average      : " + axismean + " miliseconds per request");
        System.out.println(
            "Stdev        : " + axissdvTot / TEST_REPEAT + " miliseconds per request\n");

        System.out.println("Axis2.0");
        System.out.println("Totel time   : " + axis2meanTot + " milliseconds");
        System.out.println("Average      : " + axis2mean + " per request");
        System.out.println(
            "Stdev        : " + axis2sdvTot / TEST_REPEAT + " miliseconds per request\n");

        w.write("********************* Result ************************\n");
        w.write("Axis 1.1\n ");
        w.write("Totel time   : " + axismeanTot + " milliseconds\n");
        w.write("Average      : " + axismean + " miliseconds per request\n");
        w.write(
            "Stdev        : "
                + axissdvTot / TEST_REPEAT
                + " miliseconds per request\n\n");

        w.write("Axis2.0\n");
        w.write("Totel time   : " + axis2meanTot + " milliseconds\n");
        w.write("Average      : " + axis2mean + " per request\n");
        w.write(
            "Stdev        : "
                + axis2sdvTot / TEST_REPEAT
                + " miliseconds per request\n\n");
        w.flush();
    }

    public void stasitcallymeasure(
        Call[] axisCall,
        Object[][] obj1,
        Call[] axis2Call,
        Object[][] obj2)
        throws Exception {
        for (int i = 0; i < LOAD_REPEAT; i++) {
            for (int j = 0; j < axisCall.length; j++) {
                axisCall[j].invoke(obj1);
                axis2Call[j].invoke(obj2);
            }
        }

        long[] axis = new long[TEST_REPEAT];
        long[] axis2 = new long[TEST_REPEAT];

        long start, end;
        Random r = new Random();

        for (int i = 0; i < TEST_REPEAT; i++) {
            int randservice = (int) Math.round(Math.random() * axisCall.length);

            start = System.currentTimeMillis();
            axisCall[randservice].invoke();
            end = System.currentTimeMillis();
            axis[i] = end - start;
            System.out.println("1 = " + randservice + " try " + i);

            start = System.currentTimeMillis();
            axis2Call[randservice].invoke();
            end = System.currentTimeMillis();
            axis2[i] = end - start;
            System.out.println("2 = " + randservice + " try " + i);
        }

        long axismeanTot = 0;
        long axis2meanTot = 0;
        for (int i = 0; i < TEST_REPEAT; i++) {
            axismeanTot = axismeanTot + axis[i];
            axis2meanTot = axis2meanTot + axis2[i];
        }

        float axismean = axismeanTot / TEST_REPEAT;
        float axis2mean = axis2meanTot / TEST_REPEAT;

        float axissdvTot = 0;
        float axis2sdvTot = 0;
        for (int i = 0; i < TEST_REPEAT; i++) {
            axissdvTot = axissdvTot + (axis[i] - axismean) * (axis[i] - axismean);
            axis2sdvTot = axis2sdvTot + (axis2[i] - axis2mean) * (axis2[i] - axis2mean);
        }

        System.out.println("********************* Result ************************");
        System.out.println("Axis 1.1 ");
        System.out.println("Totel time   : " + axismeanTot + " milliseconds");
        System.out.println("Average      : " + axismean + " miliseconds per request");
        System.out.println(
            "Stdev        : " + axissdvTot / TEST_REPEAT + " miliseconds per request\n");

        System.out.println("Axis2.0");
        System.out.println("Totel time   : " + axis2meanTot + " milliseconds");
        System.out.println("Average      : " + axis2mean + " per request");
        System.out.println(
            "Stdev        : " + axis2sdvTot / TEST_REPEAT + " miliseconds per request\n");

        w.write("********************* Result ************************\n");
        w.write("Axis 1.1\n ");
        w.write("Totel time   : " + axismeanTot + " milliseconds\n");
        w.write("Average      : " + axismean + " miliseconds per request\n");
        w.write(
            "Stdev        : "
                + axissdvTot / TEST_REPEAT
                + " miliseconds per request\n\n");

        w.write("Axis2.0\n");
        w.write("Totel time   : " + axis2meanTot + " milliseconds\n");
        w.write("Average      : " + axis2mean + " per request\n");
        w.write(
            "Stdev        : "
                + axis2sdvTot / TEST_REPEAT
                + " miliseconds per request\n\n");
        w.flush();

    }
}
