/*
 *   Copyright 2003-2004 The Apache Software Foundation.
 *
 *   Licensed under the Apache License, Version 2.0 (the "License");
 *   you may not use this file except in compliance with the License.
 *   You may obtain a copy of the License at
 *
 *       http://www.apache.org/licenses/LICENSE-2.0
 *
 *   Unless required by applicable law or agreed to in writing, software
 *   distributed under the License is distributed on an "AS IS" BASIS,
 *   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *   See the License for the specific language governing permissions and
 *   limitations under the License.
 */

package org.apache.axis.wsdl.wsdl2ws;

/**
 *  Most of the Constants are taken from the Axis constants class ... Here are few adittional ones 
 * @author Srianth Perera (hemapani@opensource.lk)
 */
public class Constants {
    /* This constants are regarding scope */
    public static final String PARAMETER_SCOPE = "scope";
    public static final String SCOPE_REQUEST = "request";
    public static final String SCOPE_SESSION = "session";
    public static final String SCOPE_APPLICATION = "application";

    public static int HTTP = 0;
    public static String DEFAULT_SIMPLETYPE_ENCODING_URI = "http://www.w3.org/2001/XMLSchema";
	
	/* Constants for the wrapper */
    public static final String WRAPPER_NAME_APPENDER = "Service";
    public static final String PARAM_NAME_APPENDER = "Param";
    public static final String PATH_TO_WRAPPERS = "lk.opensource.service.wrappers.";
    public static final String ADMIN_SERVICE_URI = "AdminService";
	public static final String NODE_NAME_PARAMETER = "nodename";
	public static final String SERVER_ROLE = "http://www.w3.org/2002/12/soap-envelope/role/server";
	public static final String CLIENT_ROLE = "http://www.w3.org/2002/12/soap-envelope/role/client";
	public static final String PROVIDER_ROLE = "http://www.w3.org/2002/12/soap-envelope/role/provider";
}
