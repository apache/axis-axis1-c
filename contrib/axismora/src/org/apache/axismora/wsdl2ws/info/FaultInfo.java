package org.apache.axismora.wsdl2ws.info;

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
