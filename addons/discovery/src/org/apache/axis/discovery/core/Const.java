/*
 * The Apache Software License, Version 1.1
 *
 *
 * Copyright (c) 2003 The Apache Software Foundation.  All rights
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

package org.apache.axis.discovery.core;

/**
 * This is where build time constants go
 * @author Steve Loughran
 */
public class Const {

    /**
     * We are using the IANA SLP address, listening on a
     * different port
     * @todo maybe get a real address from IANA
     */

    //IANA
    public static final String MBONE_ADDRESS = "239.255.255.253";

    /**
     * port to listen to (20649). we dont use 5049 as
     * endpoints may be using http on that port
     */
    public static final int MBONE_PORT = 0x50A9;

    /**
     * do we list ourself
     */
    public static final boolean AUTO_REGISTER_SELF = true;

    /**
     * what is our own uri; SLP style.
     */
    public static final String DISCOVERY_SERVICE_URI = "service:axis-discovery";

    /**
     * spin delay on the server; longer means slower shutdown time
     */

    public static final int SERVER_TIMEOUT = 1000;

    /**
     * default TTL for queries sent out. IANA say 255 for
     * SLP, leaving it to the routers to sort it out. But I
     * dont trust the routers to be so well configured.
     */

    public static final int DEFAULT_TTL = 4;

    /**
     * frequency of resync to axis state
     */
    public static final long AXIS_BINDER_RESYNC_INTERVAL = 1000;

    /**
     * time for client apps to wait for a response; recommended
     */
    public static final int CLIENT_TIMEOUT = 2000;

    /**
     * what is the charset of the xml messages
     */
    public static final String MESSAGE_CHARSET = "UTF-8";

    /**
     * how big can a datagram be
     */
    public static final int DATAGRAM_SIZE = 8192;

    /**
     * how big can a datagram be for warnings
     */
    public static final int DATAGRAM_WARN_SIZE = 1500;

    /**
     * default scope for registering stuff
     */
    public static final String DEFAULT_SCOPE = "*";
}
