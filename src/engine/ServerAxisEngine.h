// ServerAxisEngine.h: interface for the ServerAxisEngine class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SERVERAXISENGINE_H__8E421346_17A9_47EF_9003_6DC9C6F7787A__INCLUDED_)
#define AFX_SERVERAXISENGINE_H__8E421346_17A9_47EF_9003_6DC9C6F7787A__INCLUDED_

#include "AxisEngine.h"

class ServerAxisEngine : public AxisEngine  
{
private:
		BasicHandler* m_pWebService;
public:
	ServerAxisEngine();
	virtual ~ServerAxisEngine();
public:
	int Process(Ax_soapstream* soap);
protected:
	virtual int Invoke(MessageData* pMsg);
	virtual void OnFault(MessageData* pMsg);
};

#endif // !defined(AFX_SERVERAXISENGINE_H__8E421346_17A9_47EF_9003_6DC9C6F7787A__INCLUDED_)
