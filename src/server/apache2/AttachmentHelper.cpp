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

AttachmentHelper::AttachmentHelper()
{
}

AttachmentHelper::~AttachmentHelper()
{
}

void AttachmentHelper::extract_Attachment(char *pBuffer)
{	
	SoapAttachment* pSoapAttachment= new SoapAttachment();
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
		int start =0;

	if (blnFirstTime) {
			start = Soap_Message.find("Content-Type", boundary3);
			blnFirstTime = false;                 

 		} else {
			start = Soap_Message.find("Content-Type", end);
		}

		if (start == string::npos)
			break;		
		int start2 = Soap_Message.find(">", start+strlen("Content-Type"));
		int headerLength = (start2+1)  - start;
		string header = Soap_Message.substr (start, headerLength);
		end = Soap_Message.find(boundary, start);
		int length2 = (end- 4) - (start2+5) ;
		xsd__base64Binary*  base64_attachment = new xsd__base64Binary();
		string attachment = Soap_Message.substr(start2+5, length2);
		const char* attach = attachment.c_str ();		
		base64_attachment = AxisUtils::decodeFromBase64Binary(attach);		
		pSoapAttachment->addBody(base64_attachment);
        const char * strContentType1 ="Content-Type";
		extract_info(header,strContentType1,pSoapAttachment);
		const char * strContentType2 ="Content-Transfer-Encoding";
		extract_info(header,strContentType2,pSoapAttachment);
		const char * strContentType3 ="Content-Id";
		extract_info(header,strContentType3,pSoapAttachment);		
		x++;
	}
}

void AttachmentHelper::extract_Soap(char *pBuffer)
{   
   string  s = pBuffer;
   int i = s.find("<soapenv");
   int z = s.find("</soapenv:Envelope>");
   int length_soap = strlen("</soapenv:Envelope>");
   int length = (z - i) + length_soap;
   string extracted_message = s.substr(i,length);	
   strcpy(pBuffer, extracted_message.c_str());		
}

void AttachmentHelper::extract_SOAPMimeHeaders(char *pBuffer)
{
	string Soap_Message = pBuffer;
	int mime_Boundary = Soap_Message.find("Content", 0);
	int mime_Headers = Soap_Message.find (">", mime_Boundary);
	int mime_Length = (mime_Headers +1) - mime_Boundary;
	string mime_Part = Soap_Message.substr(mime_Boundary, mime_Length);
	pMime = (char*)malloc(mime_Part.size());
	strcpy(pMime, mime_Part.c_str ());
}

void AttachmentHelper::extract_info(string header, const char *label, SoapAttachment *pSoapAttachment)
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
  pSoapAttachment->addHeader(label,ContentValue.c_str());
    }
}

ISoapAttachment* AttachmentHelper::getAttachment(const char *pcAttchId)
{
	if (mymap.find(pcAttchId) == mymap.end())
		return NULL;
	else
	    return mymap[pcAttchId];	
}

char* AttachmentHelper::getIncomingSOAPMimeHeaders()
{
	return pMime;
}