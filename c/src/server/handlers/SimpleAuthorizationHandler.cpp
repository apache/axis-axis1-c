//////////////////////////////////////////////////////////////////////

#include "SimpleAuthorizationHandler.h"
#include "../soap/SoapDeSerializer.h"
#include "../soap/SoapSerializer.h"
#include <string.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

SimpleAuthorizationHandler::SimpleAuthorizationHandler()
{

}

SimpleAuthorizationHandler::~SimpleAuthorizationHandler()
{

}
// Implementation of BasicHandler interface.
int SimpleAuthorizationHandler::Invoke(MessageData* md)
{
  string sValue = GetOption("allowByDefault");
  int intIsAllowed =   atoi(sValue.c_str());
  if(0 == intIsAllowed)
  {
    md->SetIsServiceAllowed(0);
    return SUCCESS;
  }
  m_sAuthUser = md->GetUserName();
  if(m_sAuthUser.empty())
  {
    WSDDService* m_Service =  md->GetService();
    if(m_Service)
    {
      string sServiceName = m_Service->GetServiceName();
      m_AllowedRoles =  m_Service->GetAllowedRoles();
      m_itCurrentRole = m_AllowedRoles.begin();
	    while (m_itCurrentRole != m_AllowedRoles.end())
	    {
        if(strcmp(m_sAuthUser.c_str(),(*m_itCurrentRole).c_str()) == 0)
        {
          return SUCCESS;
        }
			  m_itCurrentRole++;
      }
     }
     else
     {
      return FAIL;
     }
  }
  else
  {
    return FAIL;
  }
}

void SimpleAuthorizationHandler::OnFault(MessageData* mc)
{

}


