// Call.h: interface for the Call class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CALL_H__D13E5626_0A9B_43EA_B606_364B98CEDAA8__INCLUDED_)
#define AFX_CALL_H__D13E5626_0A9B_43EA_B606_364B98CEDAA8__INCLUDED_

#include "../common/IParam.h"
#include "../engine/ClientAxisEngine.h"

class Call  
{
public:
	int UnInitialize();
	int Initialize();
	const uParamValue& GetResult();
	int Invoke();
	void SetReturnType(void* pObject, void* pDZFunct, void* pDelFunct);
	void SetReturnType(XSDTYPE nType);
	void AddParameter(void* pObject, void* pSZFunct, void* pDelFunct, const char* pchName);
	void AddParameter(IArrayBean* pArrayBean, const char* pchName);
	void AddParameter(XSDTYPE nType, uParamValue Value, const char* pchName);
	void SetOperation(const char* pchOperation, const char* pchNamespace);
	int SetEndpointURI(const char* pchEndpointURI);
	Call();
	virtual ~Call();
private:
	ClientAxisEngine* m_pAxisEngine;
	uParamValue m_uReturnValue;
	MessageData* m_pMsgData;
	IWrapperSoapSerializer* m_pIWSSZ;
	IWrapperSoapDeSerializer* m_pIWSDZ;
	XSDTYPE m_nReturnType;
	ComplexObjectHandler m_ReturnCplxObj;
	Ax_soapstream m_Soap;
	Param m_Param;
};

#endif // !defined(AFX_CALL_H__D13E5626_0A9B_43EA_B606_364B98CEDAA8__INCLUDED_)
