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

package org.apache.axis.wsdl.wsdl2ws.info;

import java.util.ArrayList;

/**
 * @author Srinath Perera (hemapani@opensource.lk)
 */
public class FaultInfo {
	private String name;
	private ArrayList params = new ArrayList();
	
	public FaultInfo(String name){
		this.name = name; 	
	}
	
	public void addParam(ParameterInfo paraminfo){
		params.add(paraminfo);
	}
	
	public ArrayList getParams(){
		return params;
	}

}
