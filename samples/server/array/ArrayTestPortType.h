/*
 * This is the Service Class genarated by the tool WSDL2Ws
 * ArrayTestPortType.h: interface for the ArrayTestPortTypeclass.
 *
 */
#if !defined(__ARRAYTESTPORTTYPE_SERVERSKELETON_H__INCLUDED_)
#define __ARRAYTESTPORTTYPE_SERVERSKELETON_H__INCLUDED_

#include <axis/server/AxisUserAPI.hpp>
#include "AxisServiceException.h" 

#include "intArrayType.h"

class ArrayTestPortType 
{
	public:
		ArrayTestPortType();
	public:
		virtual ~ArrayTestPortType();
	public: 
		void onFault();
		void init();
		void fini();
		intArrayType* echoIntArray(intArrayType* Value0);
};

#endif /* !defined(__ARRAYTESTPORTTYPE_SERVERSKELETON_H__INCLUDED_)*/
