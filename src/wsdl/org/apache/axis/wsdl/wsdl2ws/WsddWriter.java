/*
 * Created on Mar 19, 2004
 *
 */
package org.apache.axis.wsdl.wsdl2ws;

import java.io.File;
import java.util.ArrayList;
import java.util.Vector;

import org.apache.axis.wsdl.wsdl2ws.info.MethodInfo;
import org.apache.axis.wsdl.wsdl2ws.info.WebServiceContext;

/**
 * @author Susantha Kumara
 *
 */
public class WsddWriter implements SourceWriter {
	protected String servicename = null;
	protected String providerLang = null;
	protected String providerStyle = null;
	protected String description = null;
	protected Vector allowedmethods = new Vector();
	WebServiceContext wscontext = null;
	public WsddWriter(WebServiceContext wscontext) throws WrapperFault {
		this.wscontext = wscontext;
		servicename = wscontext.getSerInfo().getServicename();
		String language = wscontext.getWrapInfo().getWrapperLanguage();
		providerStyle = ("rpc".equals(wscontext.getWrapInfo().getWrapperStyle()))? "RPC" : "DOCUMENT";
		providerLang = ("c".equalsIgnoreCase(language)) ? "C" : "CPP";
		description = "Axis C++ web service";
		ArrayList methods = wscontext.getSerInfo().getMethods();
		MethodInfo minfo;
		for (int i = 0; i < methods.size(); i++) {
			minfo = (MethodInfo)methods.get(i);
			allowedmethods.add(minfo.getMethodname());
		}

	}
	public void writeSource()throws WrapperFault{
		
	}
	protected File getFilePath(WebServiceContext wscontext, String filename) throws WrapperFault {
		String targetOutputLocation = wscontext.getWrapInfo().getTargetOutputLocation();
		if(targetOutputLocation.endsWith("/"))
			targetOutputLocation = targetOutputLocation.substring(0, targetOutputLocation.length() - 1);
		new File(targetOutputLocation).mkdirs();
		String fileName = targetOutputLocation + "/" + filename + ".wsdd";
		return new File(fileName);
	}
}
