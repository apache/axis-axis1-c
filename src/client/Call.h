// Call.h: interface for the Call class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CALL_H__D13E5626_0A9B_43EA_B606_364B98CEDAA8__INCLUDED_)
#define AFX_CALL_H__D13E5626_0A9B_43EA_B606_364B98CEDAA8__INCLUDED_

#include "../common/IParam.h"
#include "../engine/ClientAxisEngine.h"

/* A separate call class object should be used by each thread */
class Call  
{
public:
	void SetSOAPVersion(SOAP_VERSION version);
	int SetHeader(char * key, char* value);
	int SetProtocol(AXIS_PROTOCOL_TYPE protocol);
	int UnInitialize();
	int Initialize();
	uParamValue GetResult();
	int Invoke();
	void SetReturnType(void* pObject, void* pDZFunct, void* pDelFunct, const char * theType, const char * uri);
	void SetReturnType(XSDTYPE nType);

	void AddParameter(void* pObject, void* pSZFunct, void* pDelFunct, const char* pchName);
	void AddParameter(IArrayBean* pArrayBean, const char* pchName);

	void AddParameter(int nValue,const char* pchName);
	void AddParameter(unsigned int unValue,const char* pchName);
	void AddParameter(short sValue,const char* pchName);
	void AddParameter(unsigned short usValue,const char* pchName);
	void AddParameter(long lValue,const char* pchName);
	void AddParameter(unsigned long ulValue,const char* pchName);
	void AddParameter(char cValue,const char* pchName);
	void AddParameter(unsigned char ucValue,const char* pchName);
	void AddParameter(float fValue,const char* pchName);
	void AddParameter(double dValue,const char* pchName);
	void AddParameter(struct tm tValue,const char* pchName);
	void AddParameter(const AxisChar* pStrValue,const char* pchName);

	void SetOperation(const char* pchOperation, const char* pchNamespace);
	void SetOperation(const char* pchOperation, const char* pchNamespace,const char* pchName);
	int SetEndpointURI(const char* pchEndpointURI);
	Call();
	virtual ~Call();
private:
	int OpenConnection();
	void CloseConnection();
private:
	ClientAxisEngine* m_pAxisEngine;
	uParamValue m_uReturnValue;
	MessageData* m_pMsgData;
	IWrapperSoapSerializer* m_pIWSSZ;
	IWrapperSoapDeSerializer* m_pIWSDZ;
	XSDTYPE m_nReturnType;
	ComplexObjectHandler m_ReturnCplxObj;
	Ax_soapstream m_Soap;
};

#endif // !defined(AFX_CALL_H__D13E5626_0A9B_43EA_B606_364B98CEDAA8__INCLUDED_)
