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

package org.apache.axismora.engine.scope;

import java.util.Random;

import junit.framework.TestCase;

import org.apache.axismora.ServicePool;
import org.apache.axismora.engine.SimpleServicePool;

/**
 * @author hemapani
 */
public class ServicePoolTest extends TestCase {
    private static int YET_TO_FINISHED = 10;
    /**
     * Constructor for ServicePoolTest.
     * @param arg0
     */
    public ServicePoolTest(String arg0) {
        super(arg0);
    }
    /**
     * if this test suceeded and all the request savred without deadlock the test end with
     * ###########Test Suceeded yet to finish = 0 printing
     * @throws Exception
     */

    public void testApplicationScope() throws Exception {
        String[][] vals = new String[][] { { "a", "ac" }, {
                "aav", "de" }, {
                "dre", "ctg" }, {
                "cfe", "ew" }, {
                "tere", "gsg" }, {
                "ceqw", "df" }
        };
        ServicePool pool = new SimpleServicePool();
        for (int i = 0; i < 10; i++) {
            (new ApplicationServiceConsumer(pool, vals, i)).start();
        }

    }

    /**
     * if this test suceeded and all the request savred without deadlock the test end with
     * ###########Test Suceeded yet to finish = 0 printing
     * @throws Exception
     */
    public void testSessionScope() throws Exception {
        String[][] vals = new String[][] { { "a", "ac" }, {
                "aav", "de" }, {
                "dre", "ctg" }, {
                "cfe", "ew" }, {
                "tere", "gsg" }, {
                "ceqw", "df" }
        };
        ServicePool pool = new SimpleServicePool();
        for (int i = 0; i < 10; i++) {
            (new SessionServiceConsumer(pool, vals, i)).start();
        }

    }

    public class ApplicationServiceConsumer extends Thread {
        private ServicePool pool;
        private String[][] keys;
        private int val;
        public ApplicationServiceConsumer(ServicePool pool, String[][] keys, int val) {
            this.pool = pool;
            this.keys = keys;
            this.val = val;
        }
        public void run() {
            try {
                for (int count = 0; count < 10; count++) {
                    System.out.println("get handlers " + count);

                    int val = keys[0].length;

                    int index = Math.abs((new Random()).nextInt() % val);

                    Object obj = pool.getService(keys[0][index]);

                    if (obj == null) {
                        obj = new Object();
                        pool.putService(obj, keys[0][index]);
                        obj = pool.getService(keys[0][index]);
                    }
                    System.out.println("consuming service " + index + obj);
                    Thread.sleep(
                        (10 - val)
                            * 100
                            * (1 + (int) Math.abs((new Random()).nextGaussian())));
                    pool.returnService(obj);
                    Thread.sleep(
                        (10 - val)
                            * 100
                            * (1 + (int) Math.abs((new Random()).nextGaussian())));

                }
                YET_TO_FINISHED--;
                System.out.println(
                    "###########Test Suceeded yet to finish = " + YET_TO_FINISHED);
            } catch (InterruptedException e) {
                // TODO Auto-generated catch block
                e.printStackTrace();
            }

        }
    }

    public class SessionServiceConsumer extends Thread {
        private ServicePool pool;
        private String[][] keys;
        private int val;
        public SessionServiceConsumer(ServicePool pool, String[][] keys, int val) {
            this.pool = pool;
            this.keys = keys;
            this.val = val;
        }
        public void run() {
            try {
                for (int count = 0; count < 10; count++) {
                    System.out.println("get handlers " + count);

                    int val = keys[0].length;

                    int index = Math.abs((new Random()).nextInt() % val);

                    Object obj = pool.getService(keys[0][index], keys[1][index]);

                    if (obj == null) {
                        obj = new Object();
                        pool.putService(obj, keys[0][index], keys[1][index]);
                        obj = pool.getService(keys[0][index], keys[1][index]);
                    }

                    System.out.println("consuming service " + index + obj);
                    Thread.sleep(
                        (10 - val)
                            * 100
                            * (1 + (int) Math.abs((new Random()).nextGaussian())));
                    pool.returnService(obj);
                    Thread.sleep(
                        (10 - val)
                            * 100
                            * (1 + (int) Math.abs((new Random()).nextGaussian())));
                }
                YET_TO_FINISHED--;
                System.out.println(
                    "###########Test Suceeded yet to finish = " + YET_TO_FINISHED);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }

        }
    }
    public static void main(String[] args) throws Exception {
        ServicePoolTest bht = new ServicePoolTest("");
        //bht.testApplicationScope();
        bht.testSessionScope();
    }
}
