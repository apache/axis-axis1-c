// AttachmentHelper.h: interface for the AttachmentHelper class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ATTACHMENTHELPER_H__F133843A_6A8F_4443_9DCC_850C7DEEFB7E__INCLUDED_)
#define AFX_ATTACHMENTHELPER_H__F133843A_6A8F_4443_9DCC_850C7DEEFB7E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifdef strtoul
#undef strtoul
#endif
#define strtoul strtoul

#pragma warning( disable : 4786 )

#include <string>
#include <map>
#include <axis/ISoapAttachment.hpp>
#include "../../soap/SoapAttachment.hpp"

using namespace std;
AXIS_CPP_NAMESPACE_USE

/*
struct ltstr
{
         //bool operator()(const string* s1, const string* s2) const
		 bool operator()(const char* s1, const char* s2) const
         {
          //return strcmp(s1->c_str() , s2->c_str()) < 0;
		  return strcmp(s1 , s2) < 0;
         }
};
*/

class AttachmentHelper  
{
private:
	map<const string, ISoapAttachment*> mymap;
	char* pMime;
public:
	char* getIncomingSOAPMimeHeaders();
	ISoapAttachment* getAttachment (const char* pcAttchId);
	void extract_info(string header,const char* label,SoapAttachment* pSoapAttachment);
	void extract_SOAPMimeHeaders(char* pBuffer);
	void extract_Soap (char* pBuffer);
	void extract_Attachment (char* pBuffer);
	AttachmentHelper();
	virtual ~AttachmentHelper();
};

#endif // !defined(AFX_ATTACHMENTHELPER_H__F133843A_6A8F_4443_9DCC_850C7DEEFB7E__INCLUDED_)
