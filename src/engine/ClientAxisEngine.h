// ClientAxisEngine.h: interface for the ClientAxisEngine class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CLIENTAXISENGINE_H__4DA1EBC5_C7D8_4747_8069_C3E8B6A2E929__INCLUDED_)
#define AFX_CLIENTAXISENGINE_H__4DA1EBC5_C7D8_4747_8069_C3E8B6A2E929__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "AxisEngine.h"

class ClientAxisEngine : public AxisEngine  
{
public:
	MessageData* GetMessageData();
	ClientAxisEngine();
	virtual ~ClientAxisEngine();
	virtual int Process(Ax_soapstream* pSoap);
protected:
	virtual int Invoke(MessageData* pMsg);
	virtual void OnFault(MessageData* pMsg);
private:
	Ax_soapstream* m_pSoap;
};

#endif // !defined(AFX_CLIENTAXISENGINE_H__4DA1EBC5_C7D8_4747_8069_C3E8B6A2E929__INCLUDED_)
