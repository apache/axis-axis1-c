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
package org.apache.axis.deployment.wsdd;

import org.apache.axis.ConfigurationException;
import org.apache.axis.EngineConfiguration;
import org.apache.axis.Handler;
import org.apache.axis.components.logger.LogFactory;
import org.apache.axis.encoding.SerializationContext;
import org.apache.axis.providers.java.JavaProvider;
import org.apache.axis.utils.ClassUtils;
import org.apache.axis.utils.JavaUtils;
import org.apache.axis.utils.LockableHashtable;
import org.apache.axis.utils.XMLUtils;
import org.apache.commons.logging.Log;
import org.w3c.dom.Element;
import org.xml.sax.helpers.AttributesImpl;

import javax.xml.namespace.QName;
import java.io.IOException;
import java.util.Hashtable;
import java.util.Iterator;
import java.util.Map;
import java.util.Set;


/**
 * WSDD DeployableItem complexType
 *
 */
public abstract class WSDDDeployableItem
    extends WSDDElement
{
    public static final int SCOPE_PER_ACCESS = 0;
    public static final int SCOPE_PER_REQUEST = 1;
    public static final int SCOPE_SINGLETON = 2;
    public static String [] scopeStrings = { "per-access",
                                             "per-request",
                                             "singleton" };
    
    protected static Log log =
        LogFactory.getLog(WSDDDeployableItem.class.getName());

    /** Our parameters */
    protected LockableHashtable parameters;

    /** Our name */
    protected QName qname;
    
    /** Our type */
    protected QName type;
    
    /** Scope for this item (default is singleton) */
    protected int scope = SCOPE_SINGLETON;
    
    /** Placeholder for hanging on to singleton object */
    protected Handler singletonInstance = null;

    /**
     * Default constructor
     */ 
    public WSDDDeployableItem()
    {
    }
    
    /**
     *
     * @param e (Element) XXX
     * @throws WSDDException XXX
     */
    public WSDDDeployableItem(Element e)
        throws WSDDException
    {
        super(e);
        
        String name = e.getAttribute(ATTR_NAME);
        if (name != null && !name.equals("")) {
//            qname = XMLUtils.getQNameFromString(name, e);
            qname = new QName("", name);
        }
        
        String typeStr = e.getAttribute(ATTR_TYPE);
        if (typeStr != null && !typeStr.equals("")) {
            type = XMLUtils.getQNameFromString(typeStr, e);
        }

        // Figure out our scope - right now if a non-recognized scope
        // attribute appears, we will ignore it and use the default
        // scope.  Is this right, or should we throw an error?
        String scopeStr = e.getAttribute(JavaProvider.OPTION_SCOPE);
        if (scopeStr != null) {
            for (int i = 0; i < scopeStrings.length; i++) {
                if (scopeStr.equals(scopeStrings[i])) {
                    scope = i;
                    break;
                }
            }
        }

        parameters = new LockableHashtable();
        
        // Load up our params
        Element [] paramElements = getChildElements(e, ELEM_WSDD_PARAM);
        for (int i = 0; i < paramElements.length; i++) {
            Element param = paramElements[i];
            String pname = param.getAttribute(ATTR_NAME);
            String value = param.getAttribute(ATTR_VALUE);
            String locked = param.getAttribute(ATTR_LOCKED);
            parameters.put(pname, value, JavaUtils.isTrueExplicitly(locked));
        }
    }

    /**
     *
     * @param name XXX
     */
    public void setName(String name)
    {
        qname = new QName(null, name);
    }
    
    public void setQName(QName qname)
    {
        this.qname = qname;
    }

    /**
     *
     * @return XXX
     */
    public QName getQName()
    {
        return qname;
    }

    /**
     *
     * @return XXX
     */
    public QName getType()
    {
        return type;
    }

    /**
     *
     * @param type XXX
     */
    public void setType(QName type)
    {
        this.type = type;
    }

    /**
     * Set a parameter
     */ 
    public void setParameter(String name, String value)
    {
        if (parameters == null)
            parameters = new LockableHashtable();
        parameters.put(name, value);
    }
    
    /**
     * Get the value of one of our parameters
     */ 
    public String getParameter(String name)
    {
        if (name == null)
            return null;
        
        return (String)parameters.get(name);
    }
    
    /**
     * Returns the config parameters as a hashtable (lockable)
     * @return XXX
     */
    public LockableHashtable getParametersTable()
    {
        return parameters;
    }
    
    /**
     * Convenience method for using old deployment XML with WSDD.
     * This allows us to set the options directly after the Admin class
     * has parsed them out of the old format.
     */ 
    public void setOptionsHashtable(Hashtable hashtable)
    {
        if (hashtable == null)
            return;
        
        parameters = new LockableHashtable(hashtable);
    }
    
    public void writeParamsToContext(SerializationContext context)
        throws IOException
    {
        if (parameters == null)
            return;

        Set entries = parameters.entrySet();
        Iterator i = entries.iterator();
        while (i.hasNext()) {
            Map.Entry entry = (Map.Entry) i.next();
            String name = (String) entry.getKey();
            AttributesImpl attrs = new AttributesImpl();
            
            attrs.addAttribute("", ATTR_NAME, ATTR_NAME, "CDATA", name);
            attrs.addAttribute("", ATTR_VALUE, ATTR_VALUE, "CDATA", 
                                   entry.getValue().toString());
            if (parameters.isKeyLocked(name)) {
                attrs.addAttribute("", ATTR_LOCKED, ATTR_LOCKED, "CDATA", "true");
            }

            context.startElement(QNAME_PARAM, attrs);
            context.endElement();
        }
    }

    /**
     *
     * @param name XXX
     */
    public void removeParameter(String name)
    {
        parameters.remove(name);
    }

    /**
     *
     * @param registry XXX
     * @return XXX
     * @throws ConfigurationException XXX
     */
    public final Handler getInstance(EngineConfiguration registry)
        throws ConfigurationException
    {
        if (scope == SCOPE_SINGLETON) {
             synchronized (this) {
                if (singletonInstance == null)
                    singletonInstance = getNewInstance(registry);
            }
            return singletonInstance;
        }
        
        return getNewInstance(registry);
    }

    private Handler getNewInstance(EngineConfiguration registry)
        throws ConfigurationException
    {
        QName type = getType();
        if (type == null ||
            WSDDConstants.URI_WSDD_JAVA.equals(type.getNamespaceURI())) {
            return makeNewInstance(registry);
        } else {
            return registry.getHandler(type);
        }
    }

    /**
     * Creates a new instance of this deployable.  if the
     * java class is not found, the registry is queried to
     * find a suitable item
     * @param registry XXX
     * @return XXX
     * @throws ConfigurationException XXX
     */
    protected Handler makeNewInstance(EngineConfiguration registry)
        throws ConfigurationException
    {
        Class   c = null;
        Handler h = null;

        try {
            c = getJavaClass();
        } catch (ClassNotFoundException e) {
            throw new ConfigurationException(e);
        }

        if (c != null) {
            try {
                h = (Handler)createInstance(c);
            } catch (Exception e) {
                throw new ConfigurationException(e);
            }

            if (h != null) {
                if ( qname != null )
                  h.setName(qname.getLocalPart()); 
                h.setOptions(getParametersTable());
                try{
                  h.init();
                }catch(Exception e){
                    String msg=e + JavaUtils.LS + JavaUtils.stackToString(e);
                    log.debug(msg);
                    throw new ConfigurationException(e);
                }catch(Error e){
                    String msg=e + JavaUtils.LS + JavaUtils.stackToString(e);
                    log.debug(msg);
                    throw new ConfigurationException(msg);
                }
            }
        } else {
            // !!! Should never get here!
            h = registry.getHandler(getType());
        }
        
        return h;
    }

    /**
     *
     * @param _class XXX
     * @return XXX
     */
    Object createInstance(Class _class)
        throws InstantiationException, IllegalAccessException
    {
        return _class.newInstance();
    }

    /**
     *
     * @return XXX
     * @throws ClassNotFoundException XXX
     */
    public Class getJavaClass()
        throws ClassNotFoundException
    {
        QName type = getType();
        if (type != null &&
                URI_WSDD_JAVA.equals(type.getNamespaceURI())) {
            return ClassUtils.forName(type.getLocalPart());
        }
        return null;
    }
}
