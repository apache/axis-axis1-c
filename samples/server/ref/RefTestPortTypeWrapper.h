/*
 * This file was auto-generated by the Axis C++ Web Service Generator (WSDL2Ws)
 * This file contains Web Service Wrapper declarations
 */

#if !defined(__REFTESTPORTTYPEWRAPPER_SERVERWRAPPER_H__INCLUDED_)
#define __REFTESTPORTTYPEWRAPPER_SERVERWRAPPER_H__INCLUDED_

#include "RefTestPortType.h"
#include <axis/server/WrapperClassHandler.h>
#include <axis/server/IMessageData.h>
#include <axis/server/GDefine.h>
#include <axis/server/AxisWrapperAPI.h>
#include "AxisServiceException.h" 
AXIS_CPP_NAMESPACE_USE 

class RefTestPortTypeWrapper : public WrapperClassHandler
{
private:/* Actual web service object*/
	RefTestPortType *pWs;
public:
	RefTestPortTypeWrapper();
public:
	virtual ~RefTestPortTypeWrapper();
public:/*implementation of WrapperClassHandler interface*/
	int AXISCALL invoke(void* pMsg);
	void AXISCALL onFault(void* pMsg);
	int AXISCALL init();
	int AXISCALL fini();
	AXIS_BINDING_STYLE AXISCALL getBindingStyle(){return RPC_ENCODED;};
private:/*Methods corresponding to the web service methods*/
	int echoInt(void* pMsg);
};

#endif /* !defined(__REFTESTPORTTYPEWRAPPER_SERVERWRAPPER_H__INCLUDED_)*/