package org.apache.geronimo.ews.ws4j2ee.toWs.wrapperWs;

import java.util.ArrayList;
import java.util.Iterator;

import org.apache.axis.components.logger.LogFactory;
import org.apache.commons.logging.Log;
import org.apache.geronimo.ews.ws4j2ee.context.J2EEWebServiceContext;
import org.apache.geronimo.ews.ws4j2ee.context.SEIOperation;
import org.apache.geronimo.ews.ws4j2ee.toWs.GenerationFault;
import org.apache.geronimo.ews.ws4j2ee.toWs.JavaClassWriter;

/**
 * This class genarate the wrapper Webservice.
 * @author Srinath Perera(hemapani@opensource.lk)
 */
public class WrapperClassWriter extends JavaClassWriter{
	protected static Log log =
						LogFactory.getLog(WrapperWsGenarator.class.getName());
	/**
	 * @param j2eewscontext
	 * @param qulifiedName
	 * @throws GenerationFault
	 */
	public WrapperClassWriter(J2EEWebServiceContext j2eewscontext)
		throws GenerationFault {
		super(j2eewscontext, j2eewscontext.getMiscInfo().getJaxrpcSEI() +"BindingImpl");
	}

	protected String getimplementsPart() {
		return " implements "+ j2eewscontext.getMiscInfo().getJaxrpcSEI();
	}

	protected void writeAttributes() throws GenerationFault {
		out.write("private "+j2eewscontext.getMiscInfo().getEjbsei()+" ejb = null;\n");
	}

	protected void writeConstructors() throws GenerationFault {
		out.write("\tpublic "+classname+"(){}\n");
	}

	protected void writeMethods() throws GenerationFault {
		writeGetRemoteRef(classname);
		
		String parmlistStr = null;
		 ArrayList operations = j2eewscontext.getMiscInfo().getSEIOperations();
		 for(int i =0;i<operations.size();i++){
			parmlistStr = "";
			 SEIOperation op = (SEIOperation)operations.get(i);
			 String returnType = op.getReturnType();
			 if(returnType == null)
				returnType = "void";
			 out.write("\tpublic "+returnType+" "+op.getMethodName()+"(");
				
			 Iterator pas = op.getParameterNames().iterator();
			 boolean first = true;
			 while(pas.hasNext()){
				 String name = (String)pas.next();
				 String type = op.getParameterType(name);
				 if(first){ 
					 first = false;
					 out.write(type + " " +name);
					 parmlistStr = parmlistStr + name;
				 }else{
					 out.write(","+type + " " +name);
					 parmlistStr = parmlistStr + ","+name;
				 }
						
			 }
				
			 out.write(") throws java.rmi.RemoteException");
			 ArrayList faults = op.getFaults();
			 for(int j = 0;j<faults.size();j++){
				 out.write(","+(String)faults.get(i));
			 }
			 out.write("{\n");
			 out.write("\t\tif(ejb ==  null)\n");
			 out.write("\t\t\tejb = getRemoteRef();\n");

			 if(!"void".equals(returnType))
				 out.write("\t\treturn "+op.getMethodName()+"("+parmlistStr+");\n");
			 else
				 out.write("\t\tejb."+op.getMethodName()+"("+parmlistStr+");\n");	
				
			 out.write("\t}\n");
		 }
		 //out.write("}\n");	

	}

	public String getFileName() {
		String filename = j2eewscontext.getMiscInfo().getOutPutPath()+"/jaxrpc/"+
				j2eewscontext.getMiscInfo().getJaxrpcSEI().replace('.','/')+"BindingImpl.java";
		log.info(filename + " generating.....................");
		return filename;
	}
	private void writeGetRemoteRef(String classname){
	   out.write("\tpublic "+j2eewscontext.getMiscInfo().getEjbsei()+" getRemoteRef()throws org.apache.axis.AxisFault{\n");
	   out.write("\t\ttry{\n");
	   out.write("\t\t\tjava.util.Properties env = new java.util.Properties();\n");
	   out.write("\t\t\tenv.put(javax.naming.Context.INITIAL_CONTEXT_FACTORY,\"org.jnp.interfaces.NamingContextFactory\");\n");
	   out.write("\t\t\tenv.put(javax.naming.Context.PROVIDER_URL, \"127.0.0.1:1099\");\n");
		
	   out.write("\t\t\tjavax.naming.Context initial = new javax.naming.InitialContext(env);\n");		
	   out.write("\t\t\tObject objref = initial.lookup(\""+j2eewscontext.getMiscInfo().getEjbName()+"\");\n");
	   String ejbhome = j2eewscontext.getMiscInfo().getEjbhome();
	   out.write("\t\t\t"+ejbhome+" home = \n\t\t\t\t("+ejbhome
		   +")javax.rmi.PortableRemoteObject.narrow(objref,"+ejbhome+".class);\n");
	   out.write("\t\t\treturn home.create();\n");
	   out.write("\t\t}catch (Exception e) {\n");
	   out.write("\t\t    throw org.apache.axis.AxisFault.makeFault(e);\n");
	   out.write("\t\t}\n");
	   out.write("\t}\n");
	}

}
