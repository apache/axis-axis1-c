// Copyright 2003-2004 The Apache Software Foundation.
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

// AttachmentHelper.cpp: implementation of the AttachmentHelper class.
//
//////////////////////////////////////////////////////////////////////

#include "AttachmentHelper.h"
#include "../../common/AxisUtils.h"
#include <string>

using namespace std;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

AXIS_CPP_NAMESPACE_USE

AttachmentHelper::
AttachmentHelper()
{
}

AttachmentHelper::
~AttachmentHelper()
{
}

void AttachmentHelper::
extract_Attachment(char *pBuffer)
{        
    string Soap_Message = pBuffer;
    int boundary1 = Soap_Message.find("</soapenv:Envelope>");
    int boundary2 = boundary1 + strlen("</soapenv:Envelope>") + 2;
    int boundary3 = Soap_Message.find("Content-Type:", boundary2);
    int length = (boundary3-2) - boundary2;
    string boundary = Soap_Message.substr(boundary2, length);
    bool blnContinue = true;
    bool blnFirstTime = true;
    int end = 0;
    int x =0;

    while (blnContinue)
    {
        unsigned int start = 0;

        if (blnFirstTime) 
        {
            start = Soap_Message.find("Content-Type", boundary3);
            blnFirstTime = false;                 
         } 
         else 
            start = Soap_Message.find("Content-Type", end);

        if (start == string::npos)
            break;      
              
        SoapAttachment* pSoapAttachment= new SoapAttachment();
              
        int start2 = Soap_Message.find(">", start+strlen("Content-Type"));
        int headerLength = (start2+1)  - start;
        string header = Soap_Message.substr (start, headerLength);
        end = Soap_Message.find(boundary, start);
        int length2 = (end- 4) - (start2+5) ;
        
        string attachment = Soap_Message.substr(start2+5, length2);
        const char* attach = attachment.c_str ();

        int iEncodingType= -1;
                  
        const char * strContentType1 ="Content-Type";
        extract_info(header,strContentType1,pSoapAttachment, iEncodingType);
        const char * strContentType2 ="Content-Transfer-Encoding";
        extract_info(header,strContentType2,pSoapAttachment, iEncodingType);
        const char * strContentType3 ="Content-Id";
        extract_info(header,strContentType3,pSoapAttachment, iEncodingType);        

        /*Extracting and adding the attch body*/

        if (iEncodingType==AXIS_BASE64) 
        {
            xsd__base64Binary*  base64_attachment = AxisUtils::decodeFromBase64Binary(attach);        
            pSoapAttachment->addBody(base64_attachment);
        } 
        else if (iEncodingType==AXIS_BINARY) 
            pSoapAttachment->addBody((char*)attachment.c_str());

        x++;
    }
}

void AttachmentHelper::
extract_Soap(char *pBuffer)
{   
   string  s = pBuffer;
   int i = s.find("<soapenv");
   int z = s.find("</soapenv:Envelope>");
   int length_soap = strlen("</soapenv:Envelope>");
   int length = (z - i) + length_soap;
   string extracted_message = s.substr(i,length);    
   strcpy(pBuffer, extracted_message.c_str());        
}

void AttachmentHelper::
extract_SOAPMimeHeaders(char *pBuffer)
{
    string Soap_Message = pBuffer;
    int mime_Boundary = Soap_Message.find("Content", 0);
    int mime_Headers = Soap_Message.find (">", mime_Boundary);
    int mime_Length = (mime_Headers +1) - mime_Boundary;
    string mime_Part = Soap_Message.substr(mime_Boundary, mime_Length);
    pMime = (char*)malloc(mime_Part.size());
    strcpy(pMime, mime_Part.c_str ());
}

void AttachmentHelper::
extract_info(string header, const char *label, SoapAttachment *pSoapAttachment, int& iEncodingType)
{
    int ContentTypeLabel = header.find(label);    
    int startValue = ContentTypeLabel+strlen(label);
    if (strcmp(label,"Content-Id")==0) 
    {
        int endValue = header.find (">" , startValue);
        int lengthId = (endValue) - (startValue + 3);
        string ContentValue = header.substr (startValue+3, lengthId);
        pSoapAttachment->addHeader(label,ContentValue.c_str());
        mymap[ContentValue.c_str()] = pSoapAttachment;
    }
    else 
    {
        int endValue = header.find ("Content-", startValue);
        int length = endValue - (startValue + 2);
        string ContentValue = header.substr (startValue + 2, length-2);

        if (strcmp(label, "Content-Transfer-Encoding") ==0) 
        {
            if(strcmp (ContentValue.c_str(), "base64")==0) 
                iEncodingType = AXIS_BASE64;
            else if(strcmp (ContentValue.c_str(), "binary")==0) 
                iEncodingType = AXIS_BINARY;
        }

        pSoapAttachment->addHeader(label,ContentValue.c_str());
    }
}

ISoapAttachment* AttachmentHelper::
getAttachment(const char *pcAttchId)
{
    if (mymap.find(pcAttchId) == mymap.end())
        return NULL;
    else
        return mymap[pcAttchId];    
}

char* AttachmentHelper::
getIncomingSOAPMimeHeaders()
{
    return pMime;
}

ISoapAttachment** AttachmentHelper::
getAllAttachments(int *pAttchArraySize)
{ 
    ISoapAttachment** attachArray = (ISoapAttachment**)new SoapAttachment*[mymap.size()];
    
    map<string, ISoapAttachment*>::iterator itCurrMap= mymap.begin();

    int i = 0;
    while(itCurrMap != mymap.end())
    {               
        attachArray[i] = (*itCurrMap).second;

        itCurrMap++; 
        i++;
    }      

    *pAttchArraySize = i;

    return attachArray;   
}
