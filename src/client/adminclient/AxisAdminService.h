/*
 * This is the Client Stub Class genarated by the tool WSDL2Ws
 * AxisAdminService.h: interface for the AxisAdminServiceclass.
 *
 */
#if !defined(__AXISADMINSERVICE_CLIENTSTUB_H__INCLUDED_)
#define __AXISADMINSERVICE_CLIENTSTUB_H__INCLUDED_

#include <axis/client/Call.h>

class AxisAdminService 
{
private:
	Call* m_pCall;
public:
	AxisAdminService(const char* pchUri);
public:
	virtual ~AxisAdminService();
public: 
	xsd__boolean updateWSDD(xsd__base64Binary Value0);
};

#endif /* !defined(__AXISADMINSERVICE_CLIENTSTUB_H__INCLUDED_)*/
