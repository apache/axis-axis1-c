/*
 * This is the Service Class genarated by the tool WSDL2Ws
 * RefTestPortType.h: interface for the RefTestPortTypeclass.
 *
 */
#if !defined(__REFTESTPORTTYPE_SERVERSKELETON_H__INCLUDED_)
#define __REFTESTPORTTYPE_SERVERSKELETON_H__INCLUDED_

#include <axis/AxisUserAPI.hpp>
#include "AxisServiceException.h" 

#include "intType.h"

class RefTestPortType 
{
	public:
		RefTestPortType();
	public:
		virtual ~RefTestPortType();
	public: 
		void onFault();
		void init();
		void fini();
		intType* echoInt(intType* Value0);
};

#endif /* !defined(__REFTESTPORTTYPE_SERVERSKELETON_H__INCLUDED_)*/
