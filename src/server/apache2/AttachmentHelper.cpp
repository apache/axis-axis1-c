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

		//int startPosContentId = Soap_Message.find ("<",start+strlen("Content-Id:"))+1;
     
		int start2 = Soap_Message.find(">", start+strlen("Content-Type"));
		

		int headerLength = (start2+1)  - start;
		
		string header = Soap_Message.substr (start, headerLength);
		
 
		//string strContentId = Soap_Message.substr(startPosContentId,attachLength);

		//cout <<"attach Ids:" << strContentId <<"\n";
		//Soap_Message = "abcde------=_Part_0_6349096.1105418692309--";
		//boundary = "------=_Part_0_6349096.1105418692309--";
		//start = 100;
		end = Soap_Message.find(boundary, start);

		int length2 = (end- 4) - (start2+5) ;
		
		xsd__base64Binary*  base64_attachment = new xsd__base64Binary();

		string attachment = Soap_Message.substr(start2+5, length2);

		
		const char* attach = attachment.c_str ();

		//base64_attachment = &(TestUtils::decodeFromBase64Binary(attach));
		base64_attachment = AxisUtils::decodeFromBase64Binary(attach);

		//base64_attachment->__ptr = (unsigned char*)attachment.c_str();
		//base64_attachment->__size = attachment.length();

		pSoapAttachment->addBody(base64_attachment);

        const char * strContentType1 ="Content-Type";
		extract_info(header,strContentType1,pSoapAttachment);
		const char * strContentType2 ="Content-Transfer-Encoding";
		extract_info(header,strContentType2,pSoapAttachment);

		const char * strContentType3 ="Content-Id";
		extract_info(header,strContentType3,pSoapAttachment);

  
		//strcpy(pAttachBuffer, attachment.c_str());

	//  char* pchTmp= (char*)malloc(1);
	//	_itoa(x, pchTmp, 10);
	//	char* pchKey = (char*) malloc(strlen("key")+strlen(pchTmp)+1);
	//	strcpy(pchKey, "key"); 
	//	mymap[new string(strcat(pchKey, pchTmp))] = new string(pAttachBuffer);
	
  
		//mymap[new string(header)] = new string(pAttachBuffer);

		x++;
	}
	
}

void AttachmentHelper::extract_Soap(char *pBuffer)
{
	
   //pBuffer = "406322D3F><soapenv:Envelope xmlns:soapenv=\"http://schemas.xmlsoap.org/soap/envelope/\" xmlns:xsd=\"http://www.w3.org/2001/XMLSchema\" xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"><soapenv:Body><echo xmlns=\"\"><source href=\"cid:43C5072344351B661A3742EB758A90F6\" xmlns=\"\"/></echo></soapenv:Body></soapenv:Envelope>------=_Part_0_14301726";

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
	//pMime = "\0";	

	string Soap_Message = pBuffer;

	int mime_Boundary = Soap_Message.find("Content", 0);

	int mime_Headers = Soap_Message.find (">", mime_Boundary);

	int mime_Length = (mime_Headers +1) - mime_Boundary;

	string mime_Part = Soap_Message.substr(mime_Boundary, mime_Length);


	//pMime = new char(mime_Part.size());
	pMime = (char*)malloc(mime_Part.size());

	strcpy(pMime, mime_Part.c_str ());

    
	
}

void AttachmentHelper::extract_info(string header, const char *label, SoapAttachment *pSoapAttachment)
{
	
  int ContentTypeLabel = header.find(label);    
  
  int startValue = ContentTypeLabel+strlen(label);

  if (label =="Content-Id") 
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
  
  /*
  if (label =="Content-Id:") 
  {

   mymap[ContentValue.c_str()] = pSoapAttachment;

  }
*/
 	

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
