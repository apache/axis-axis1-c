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

import java.util.HashMap;
import java.util.Vector;

import org.apache.axismora.ServicePool;

import org.apache.axis.AxisFault;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
/**
 * Service pool services store their objects.
 * Only one object can be stored per one application-service/session-service.
 * <p>
 * Usage of this pool is to store wrappers of services. 
 * </p>
 * @author Dimuthu Leelarathne (muthulee@opensource.lk)
 * @author Srinath Perera(hemapani@opensource.lk)   
*/
public class SimpleServicePool implements ServicePool {
    protected static Log log = LogFactory.getLog(ServicePool.class.getName());

    private int appServObjects = 33;
    private int sesServObjects = 77;
    private HashMap appMap;
    private HashMap sessionMap;
    private Vector avalibleServices;

    /**
     * 
     *@param appServObjects is maximum no of application services (on average).
     *		It can go beyond this number but it would not be efficient
     *@param sesServObjects is maximum no of session services (on average). 
     *		It can go beyond this number but it would not be efficient
     */

    //TODO::Get the no of on-average-maximum-no-of-services for appMap and sessionMap
    public SimpleServicePool() {
        appMap = new HashMap(appServObjects);
        sessionMap = new HashMap(sesServObjects);
        avalibleServices = new Vector(201);
    }

    /**
     * 
     * Returns a object belonging to a specific service.
     * If service cannot be found it is null.
     * 
     * @param serviceName
     * @return
     */

    public Object getService(String serviceName) {
        Integer key;
        Object obj;
        key = new Integer(serviceName.hashCode() * 7);
        log.info("Getting the application object");
        obj = appMap.get((Object) key);
        if (obj == null)
            return null;
        else {
            while (true) {
                synchronized (this) {
                    //do this all or nothing when true it will break the loop
                    if (this.avalibleServices.contains(obj)) {
                        this.avalibleServices.remove(obj);
                        return obj;
                    }
                }
                //else wait
                try {
                    obj.wait();
                } catch (Exception e) {
                }
            }
        }
    }

    /**
     * Returns a object belonging to a specific service given serviceName and session
     * 
     * @param serviceName
     * @param session
     * @return the object if found else null.
     */

    public Object getService(String serviceName, String session) {
        Integer key;
        Object obj;
        key = new Integer((serviceName + session).hashCode() * 7);
        obj = sessionMap.get((Object) key);

        Thread thread = Thread.currentThread();
        int intPrority = thread.getPriority();
        thread.setPriority(Thread.NORM_PRIORITY);

        if (obj == null)
            return null;
        else {
            while (true) {
                synchronized (this) {
                    //do all or nothing 
                    if (this.avalibleServices.contains(obj)) {
                        this.avalibleServices.remove(obj);
                        thread.setPriority(intPrority);
                        return obj;
                    }
                }
                try {
                    obj.wait();
                } catch (Exception e) {
                }
            }
        }
    }

    /**
     * Used for putting the application object into the application Hash map.
     * Once you put an object into this hash map, you can'r remove it.
     */
    public void putService(Object obj, String serviceName) {
        try {
            Integer key;
            key = new Integer(serviceName.hashCode() * 7);
            synchronized (this) {
                appMap.put((Object) key, obj);
                this.avalibleServices.add(obj);
            }
            obj.notifyAll();
        } catch (java.lang.IllegalMonitorStateException e) {
            //no body may be waiting ..k..ignore
        }
    }

    /**
     * Used for putting the session specific object into the session Hash map.
     * Takes in session details as parameters.
     *  
     * @param obj is the object to stored in the hash map.
     * @param serviceName 
     * @param session
     */

    public void putService(Object obj, String serviceName, String session) {
        try {
            Integer key;
            key = new Integer((serviceName + session).hashCode() * 7);

            synchronized (this) {
                sessionMap.put((Object) key, obj);
                this.avalibleServices.add(obj);
            }
            obj.notifyAll();

        } catch (java.lang.IllegalMonitorStateException e) {
            //no body may be waiting ..k..ignore
        }
    }

    /**
     * After a session expires removet the object.
     * 
     * @param serviceName is the name of the service that object belongs to.
     * @param session is the name of the session that the object belongs to.
      */
    public void removeService(String serviceName, String session) throws AxisFault {
        Integer key;
        key = new Integer((serviceName + session).hashCode() * 7);
        //TODO there is a issue what would happen somebody remove the servcie while
        // somebody is waiting for it.  will one session send two requests once 
        //does this solution that based on the thread prority will do any help.
        if (!sessionMap.containsValue(key))
            throw new AxisFault("trying to remove non exists object");

        Thread thread = Thread.currentThread();
        int intPrority = thread.getPriority();
        thread.setPriority(Thread.MIN_PRIORITY);

        while (true) {
            synchronized (this) {
                if (this.avalibleServices.contains(key)) {
                    this.avalibleServices.remove(key);
                    sessionMap.remove((Object) key);
                    thread.setPriority(intPrority);
                    return;
                }
                try {
                    key.wait();
                } catch (Exception e) {
                }
            }
        }
    }

    public void returnService(Object service) {
        this.avalibleServices.add(service);
    }

}
