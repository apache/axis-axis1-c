// Copyright 2003-2004 The Apache Software Foundation.
// (c) Copyright IBM Corp. 2004, 2005 All Rights Reserved
// 
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// 
//        http://www.apache.org/licenses/LICENSE-2.0
// 
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

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

#ifdef WIN32
#pragma warning( disable : 4786 ) 	// identifier was truncated to 'number' characters 
#endif // WIN32

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
	map<string, ISoapAttachment*> mymap;
	char* pMime;
public:
	char* getIncomingSOAPMimeHeaders();
	ISoapAttachment* getAttachment (const char* pcAttchId);
    ISoapAttachment** getAllAttachments(int *pAttchArraySize);
	void extract_info(string header,const char* label,SoapAttachment* pSoapAttachment, int& iEncodingType);
	void extract_SOAPMimeHeaders(char* pBuffer);
	void extract_Soap (char* pBuffer);
	void extract_Attachment (char* pBuffer);
	AttachmentHelper();
	virtual ~AttachmentHelper();
};

#endif // !defined(AFX_ATTACHMENTHELPER_H__F133843A_6A8F_4443_9DCC_850C7DEEFB7E__INCLUDED_)
