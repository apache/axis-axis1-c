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

import org.apache.axis.wsdl.wsdl2ws.info.WebServiceContext;
import org.apache.axis.wsdl.wsdl2ws.rpc.RPCWebServiceGenarator;
import org.apache.axis.wsdl.wsdl2ws.doclit.DocLitWebServiceGenarator;
/**
 * Create the concreate WebService Genarator depends on the options.
 * @author Srinath Perera (hemapani@opensource.lk)
 * @author Dimuthu Leelarathne (muthulee@opensource.lk)
 */
public class WebServiceGenaratorFactory {
	public static WebServiceGenarator createWebServiceGenarator(WebServiceContext wscontext){
		if(wscontext.getWrapInfo().getWrapperStyle() == WrapperConstants.STYLE_RPC)
			return new 	RPCWebServiceGenarator(wscontext);	
		else if(wscontext.getWrapInfo().getWrapperStyle() == WrapperConstants.STYLE_DOCUMENT)										
			return new 	DocLitWebServiceGenarator(wscontext);
		else	
			return null;
	}
}
