
package org.apache.axismora.wsdl2ws.doclit;

import java.util.Iterator;

import org.apache.axismora.wsdl2ws.WrapperConstants;
import org.apache.axismora.wsdl2ws.WrapperFault;
import org.apache.axismora.wsdl2ws.info.Type;
import org.apache.axismora.wsdl2ws.info.TypeMap;
import org.apache.axismora.wsdl2ws.info.WebServiceContext;

/**
 * Geberates all parmeter classes for document literal web service.
 * This is what the BP says;
 * 
 * R2201 A document-literal binding in a DESCRIPTION MUST, 
 * in each of its soapbind:body element(s), 
 * have at most one part listed in the parts attribute, 
 * if the parts attribute is specified. 
 * I am a bit confused about R2201 ????
 * 
 * R2204 A document-literal binding in a DESCRIPTION MUST refer, 
 * in each of its soapbind:body element(s), 
 * only to wsdl:part element(s) 
 * that have been defined using the element attribute. 
 * 
 * R2210 If a document-literal binding in a DESCRIPTION 
 * does not specify the parts attribute on a soapbind:body element, 
 * the corresponding abstract wsdl:message MUST define zero or one wsdl:parts. 
 * 
 * @author Dimuthu Leelaratne. muthulee@yahoo.com
 *
 */
public class AllDocLitParamWriter {
/*	TODO :: Check for R2201 compliance.
 *  NO support for arrays of enums ?????
 *  Arrays can exist only inside beans ..... and how is the problem
 */

	private WebServiceContext wscontext;

		public AllDocLitParamWriter(WebServiceContext wscontext) {
			this.wscontext = wscontext;
		}

		/**
		 * Calls the DocLit BeanParam writer for all parameters.
		 * According to BP only elements should travel on wire.
		 * 
		 * @throws WrapperFault if simple types or arrays.
		 * @see org.apache.axismora.wsdl2ws.SourceWriter#writeSource()
		 */
		public void writeSource() throws WrapperFault {
			Iterator allTypes = wscontext.getTypemap().getTypes().iterator();
			String generator = wscontext.getWrapInfo().getImplStyle();
			Type type;
        
			while (allTypes.hasNext()) {
				try {
					type = (Type) allTypes.next();
					
					if(TypeMap.isSimpleType(type.getName()))
						System.out.println(" +++++++++++++ simple type met ");
						//throw new WrapperFault("Simple types not allowed. Only elements are allowed.\n Refer R2204 of BP.");
					    //TODO :: Check whether to put break;
					
					// change the things
					if (wscontext.getWrapInfo().getImplStyle().equals(WrapperConstants.IMPL_STYLE_STRUCT)) {
						if(type.getEnumerationdata() != null){
                             System.out.println("Enumeration not supported yet ... in docLit");                   
						}else if (type.isArray()) {
	 						 TypeMap.regestorArrayTypeToCreate(type);
						} else {
							System.out.println("DocLitBeanWriter is called ......");
							(new DocLitBeanWriter(wscontext, type)).writeSource();
						}
				    
				    }
				} catch (Exception e) {
					System.out.println(
						"Error occured yet we continue to genarate other classes ... you should check the error");
					e.printStackTrace();
				}
			}
        
		  Iterator arrayTypes = TypeMap.getUnregisterdArrayTypes();
			while(arrayTypes.hasNext()){
				System.out.println("Array writer called ......");
				(new DocLitArrayWriter(wscontext, (Type)arrayTypes.next())).writeSource();
			}
		}



}
