package org.apache.axismora.wsdl2ws.doclit;

import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Iterator;

import javax.xml.namespace.QName;

import org.apache.axismora.wsdl2ws.WrapperFault;
import org.apache.axismora.wsdl2ws.WrapperUtils;
import org.apache.axismora.wsdl2ws.info.MethodInfo;
import org.apache.axismora.wsdl2ws.info.ParameterInfo;
import org.apache.axismora.wsdl2ws.info.Type;
import org.apache.axismora.wsdl2ws.info.TypeMap;
import org.apache.axismora.wsdl2ws.info.WebServiceContext;

import org.apache.axismora.wsdl2ws.java.client.StubWriter;

/**
 * @author Dimuthu Leelaratne. 
 *
 * To change the template for this generated type comment go to
 * Window>Preferences>Java>Code Generation>Code and Comments
 */
public class DocLitStubWriter extends StubWriter {
	private WebServiceContext wscontext;
	private ArrayList methods;
	
	
	/**
	 * @param packagename
	 * @param classname
	 * @throws WrapperFault
	 */
	public DocLitStubWriter(WebServiceContext wscontext) throws WrapperFault {
		super(wscontext);
		this.wscontext = wscontext;
		this.methods = wscontext.getSerInfo().getMethods();
	}

	/* (non-Javadoc)
	 * @see org.apache.axismora.wsdl2ws.java.JavaClassWriter#writeAttributes()
	 */
	protected void writeAttributes() throws WrapperFault {
          super.writeAttributes();
	}

	/* (non-Javadoc)
	 * @see org.apache.axismora.wsdl2ws.java.JavaClassWriter#writeConstructors()
	 */
	protected void writeConstructors() throws WrapperFault {
          super.writeConstructors();
	}

	/* (non-Javadoc)
	 * @see org.apache.axismora.wsdl2ws.java.JavaClassWriter#writeMethods()
	 */
	protected void writeMethods() throws WrapperFault {
		MethodInfo minfo;
		QName paramQName;
		Type paramType;
		Object obj;
		try {
			for (int i = 0; i < methods.size(); i++) {
                minfo = (MethodInfo) this.methods.get(i);
                
                this.writeMethodSignature(minfo);
                
                // below code writes the method body.
                writer.write(
					"\n\t\tjavax.xml.namespace.QName methodName = new javax.xml.namespace.QName(\""
						+ minfo.getMethodname()
						+ "\");");
				String ops = "";
				writer.write(
					"\n\t\torg.apache.axismora.client.Call call = (org.apache.axismora.client.Call)service.createCall();");
				writer.write("\n\t\tcall.setOperationName(methodName);");
				writer.write("\n\t\tcall.setPortTypeName(SOAPAction);");
				writer.write("\n\t\tcall.setTargetEndpointAddress(this.enduri);");
				writer.write("\n\t\tcall.setStyle(\"document\");");
				writer.write("\n\t\tcall.setUse(org.apache.axis.enum.Use.LITERAL)");
				
				// add paramters to the call object .........
				Iterator params = minfo.getParameterTypes().iterator();
				if (params.hasNext()) {
					obj = params.next();
					paramType =
						wscontext.getTypemap().getType(
							((ParameterInfo) obj).getSchemaName());
					paramQName = ((ParameterInfo) obj).getSchemaName();
				
					if ((TypeMap.isSimpleType(paramQName)) || (paramType != null && paramType.isArray()) ) {
                	    throw new WrapperFault("Simple types and array types are not accepted by document literal services.");
                	}else {
						paramQName = ((ParameterInfo) obj).getSchemaName();
						writer.write(
							"\n\t\tcall.addParameter(\"param0\",new javax.xml.namespace.QName(\""
								+ paramQName.getNamespaceURI()
								+ "\",\""
								+ paramQName.getLocalPart()
								+ "\"),javax.xml.rpc.ParameterMode.IN);"); 
						ops = "param0";
					}
				}
				

				// adding return types to the call object.......
				ParameterInfo returnType = (ParameterInfo) minfo.getReturnType();
					if (returnType != null) {
					paramQName = returnType.getSchemaName();
					paramType =
						wscontext.getTypemap().getType(
							((ParameterInfo) minfo.getReturnType()).getSchemaName());
					
					writer.write(
						"\n\t\tcall.setReturnType(new javax.xml.namespace.QName(\""
							+ paramQName.getNamespaceURI()
							+ "\",\""
							+ paramQName.getLocalPart()
							+ "\"));");
					
					writer.write(
						"\n\t\torg.apache.axismora.MessageContext mx = (org.apache.axismora.MessageContext)call.invokeLowLevel(methodName,new org.apache.axismora.encoding.OutParameter[]{"
							+ ops 
							+ "});");
				
					if ( (TypeMap.isSimpleType(paramQName)) ||(paramType != null && paramType.isArray())) {
						throw new WrapperFault("Simple types and array types are not accepted by document literal services.");
    				} else {
						// Writing validation code for start tag.
							writer.write("\t\t//This is a docLit service.\n Therefore cursor of the pull parser is at body tag\n");
							writer.write("\t\tAxisPullParser aXpp = msgdata.getAxisPullParser();\n");
							writer.write("\t//The current state is the body tag. We move one step ahead using aXpp.next()\n");
							writer.write("\t\tint state=aXpp.next();\n");
							writer.write("\t\tif(state == XmlPullParser.START_TAG){\n");
							writer.write("\t\t//Validate the local name of the parameter\n");
							writer.write("\t\t\taXpp.getName().equals(\"Get the elementName of pinfo.get(0)\");\n");
							writer.write("\t\t}else{\n");
							writer.write("\t\t\tthrow new AxisFault(\"Empty Soap Body, or text node in the soap body.\");\n}\n");
							writer.write("\t// Validation of start tag is done.");
    					
						writer.write(
							"\n\t\t"
								+ paramType.getLanguageSpecificName()
								+ " res = ("
								+ paramType.getLanguageSpecificName()
								+ ")(new "
								+ paramType.getLanguageSpecificName()
								+ "()).desierialize(mx);");
						writer.write("\n\t\t return res;\n");
					}
					
					
				} else { // if return type is null
					writer.write(
						"\n\t\torg.apache.axismora.MessageContext mx = (org.apache.axismora.MessageContext)call.invokeLowLevel(methodName,new org.apache.axismora.encoding.OutParameter[]{"
							+ ops
							+ "});");
				}
				writer.write("\n\t\t}\n");
			}
		} catch (Exception e) {
			e.printStackTrace();
			throw new WrapperFault(e);
		}

	}


    private void writeMethodSignature(MethodInfo minfo) throws WrapperFault, IOException{
		writer.write("\n\tpublic ");
		ParameterInfo returnType = minfo.getReturnType();
						if (returnType == null
							|| returnType.getLangName() == null
							|| returnType.getLangName() == "void")
							writer.write("void ");
						else
							writer.write(
								WrapperUtils.getClassNameFromParamInfoConsideringArrays(
									minfo.getReturnType(),
									wscontext));
		
		// writing the method Name
		writer.write(minfo.getMethodname() + "(");

		//write parameter - only one parameter is writen. 
		Iterator params = minfo.getParameterTypes().iterator();
							
		if (params.hasNext())
						writer.write(
							WrapperUtils.getClassNameFromParamInfoConsideringArrays(
								(ParameterInfo) params.next(),
								wscontext)
								+ " param"
								+ 0);
				
		writer.write(")throws java.rmi.RemoteException{");								
									
    }

	/* (non-Javadoc)
	 * @see org.apache.axismora.wsdl2ws.java.JavaClassWriter#getJavaFilePath()
	 */
	protected File getJavaFilePath() throws WrapperFault {
	       return super.getJavaFilePath();
	}
	/* (non-Javadoc)
	* @see org.apache.axismora.wsdl2ws.java.JavaClassWriter#getExtendsPart()
	*/
	protected String getExtendsPart() {
		return super.getExtendsPart();
	}

	/* (non-Javadoc)
	 * @see org.apache.axismora.wsdl2ws.java.JavaClassWriter#getimplementsPart()
	 */
	protected String getimplementsPart() {
		return "implements " + wscontext.getSerInfo().getQualifiedServiceName();
	}

	/* (non-Javadoc)
	 * @see org.apache.axismora.wsdl2ws.java.JavaClassWriter#writeClassComment()
	 */
	protected void writeClassComment() throws WrapperFault {
		try {
			writer.write("/*This class is automatically generated by \n");
			writer.write("*axis_lsf client stub generator\n");
			writer.write("*The client side stub of the document literal web service. \n");
			writer.write("*/\n\n");
		} catch (IOException e) {
			e.printStackTrace();
			throw new WrapperFault(e);
		}
	}
}

