/*
 * This is the Service Class genarated by the tool WSDL2Ws
 * pt1.hpp: interface for the pt1class.
 *
 */
#if !defined(__PT1_SERVERSKELETON_H__INCLUDED_)
#define __PT1_SERVERSKELETON_H__INCLUDED_

#include <axis/AxisUserAPI.hpp>
#include "AxisServiceException.hpp" 
#include <axis/ISoapAttachment.hpp>

class pt1 
{
	public:
		pt1();
	public:
		virtual ~pt1();
	public: 
		void onFault();
		void init();
		void fini();
	    ISoapAttachment* EchoAttachment(ISoapAttachment* objSoapAttach);
		//xsd__base64Binary EchoAttachment(xsd__base64Binary Value0);
};


#endif /* !defined(__PT1_SERVERSKELETON_H__INCLUDED_)*/
