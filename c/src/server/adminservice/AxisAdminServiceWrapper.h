/*
 * This is the Service Class genarated by the tool WSDL2Ws
 *		AxisAdminServiceWrapper.h: interface for the AxisAdminServiceWrapperclass.
 *
 */
#if !defined(__AXISADMINSERVICEWRAPPER_SERVERWRAPPER_H__INCLUDED_)
#define __AXISADMINSERVICEWRAPPER_SERVERWRAPPER_H__INCLUDED_

#include "AxisAdminService.h"
#include <axis/server/WrapperClassHandler.h>
#include <axis/server/IMessageData.h>
#include <axis/server/GDefine.h>
#include <axis/server/AxisWrapperAPI.h>

class AxisAdminServiceWrapper : public WrapperClassHandler
{
private:/* Actual web service object*/
	AxisAdminService *pWs;
public:
	AxisAdminServiceWrapper();
public:
	virtual ~AxisAdminServiceWrapper();
public:/*implementation of WrapperClassHandler interface*/
	int AXISCALL Invoke(IMessageData* mc);
	void AXISCALL OnFault(IMessageData* pMsg);
	int AXISCALL Init();
	int AXISCALL Fini();
	AXIS_BINDING_STYLE AXISCALL GetBindingStyle(){return DOC_LITERAL;};
private:/*Methods corresponding to the web service methods*/
	int deploy(IMessageData* mc);
	int undeploy(IMessageData* mc);
};

#endif /* !defined(__AXISADMINSERVICEWRAPPER_SERVERWRAPPER_H__INCLUDED_)*/
