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

package org.apache.axismora.engine;
import java.util.Random;

import junit.framework.TestCase;

import org.apache.axismora.Constants;
import org.apache.axismora.Handler;
import org.apache.axismora.HandlerChain;
import org.apache.axismora.deployment.wsdd.WSDDDeployment;
import org.apache.axismora.util.NOTSupportedException;
/**
 * This testcase simulate the handler pool and check is it get into
 * trouble. This class is not included in the <code>AllTests</code> as the 
 * output is different (random) and will make it hard to check wheather the
 * tests suceeded using the diff -u.  
 * @author Srinath Perera (hemapani@opensource.lk)
 */
public class BasicHandlerPoolTest extends TestCase {
    public BasicHandlerPoolTest() {
        super();
    }

    public BasicHandlerPoolTest(String arg0) {
        super(arg0);

    }

    public void testDynamicClassLoading() throws Exception {
        Class type = Class.forName("testData.SimpleGlobalRequestHandler");
        Handler handler = (Handler) type.newInstance();
        handler.invoke(null);
    }

    public void testHandlerPool() throws Exception {
        HandlerPool pool =
            BasicHandlerPool.getInstance(
                WSDDDeployment.getInstance(
                    "test\\lk\\opensource\\axis2\\engine\\Enginetest.wsdd"));
        pool.init();

        for (int i = 0; i < 10; i++) {
            (new HandlerConsumer(pool, i)).start();
        }
    }

    public class HandlerConsumer extends Thread {
        private HandlerPool pool;
        private int val;
        public HandlerConsumer(HandlerPool pool, int val) {
            this.pool = pool;
            this.val = val;
        }
        public void run() {
            Handler[] h = new Handler[4];
            try {
                for (int count = 0; count < 50; count++) {
                    h[0] = pool.getGlobelRequestFlowHandlers();
                    h[1] = pool.getTransportRequestFlowHandlers(Constants.HTTP);
                    h[2] = pool.getTransportResponseFlowHandlers(Constants.HTTP);
                    h[3] = pool.getGlobelResponseFlowHandlers();
                    System.out.println("get handlers " + count);
                    //for(int i =0;i<h.length;i++){
                    //	h[i].invoke(null);
                    //}
                    Thread.sleep(
                        (10 - val)
                            * 100
                            * (1 + (int) Math.abs((new Random()).nextGaussian())));

                    pool.returnGlobelRequestFlowHandlers((HandlerChain) h[0]);
                    pool.returnTransportRequestFlowHandlers(
                        Constants.HTTP,
                        (HandlerChain) h[1]);
                    pool.returnTransportResponseFlowHandlers(
                        Constants.HTTP,
                        (HandlerChain) h[2]);
                    pool.returnGlobelResponseFlowHandlers((HandlerChain) h[3]);
                    System.out.println("return handlers " + count);
                    Thread.sleep(
                        (10 - val)
                            * 100
                            * (1 + (int) Math.abs((new Random()).nextGaussian())));
                }
            } catch (ClassImplementationNotFoundException e) {
                e.printStackTrace();
            } catch (NOTSupportedException e) {
                e.printStackTrace();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }

        }
    }

    /* (non-Javadoc)
     * @see junit.framework.TestCase#setUp()
     */
    protected void setUp() throws Exception {

    }

    /* (non-Javadoc)
     * @see junit.framework.TestCase#tearDown()
     */
    protected void tearDown() throws Exception {
        super.tearDown();
    }
    public static void main(String[] args) throws Exception {
        BasicHandlerPoolTest bht = new BasicHandlerPoolTest();
        bht.testHandlerPool();
    }
}
