/* -*- C++ -*- */

/*
 * The Apache Software License, Version 1.1
 *
 *
 * Copyright (c) 2002 The Apache Software Foundation.  All rights
 * reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * 3. The end-user documentation included with the redistribution,
 *    if any, must include the following acknowledgment:
 *       "This product includes software developed by the
 *        Apache Software Foundation (http://www.apache.org/)."
 *    Alternately, this acknowledgment may appear in the software itself,
 *    if and wherever such third-party acknowledgments normally appear.
 *
 * 4. The names "SOAP" and "Apache Software Foundation" must
 *    not be used to endorse or promote products derived from this
 *    software without prior written permission. For written
 *    permission, please contact apache@apache.org.
 *
 * 5. Products derived from this software may not be called "Apache",
 *    nor may "Apache" appear in their name, without prior written
 *    permission of the Apache Software Foundation.
 *
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESSED OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED.  IN NO EVENT SHALL THE APACHE SOFTWARE FOUNDATION OR
 * ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
 * USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 * ====================================================================
 *
 * This software consists of voluntary contributions made by many
 * individuals on behalf of the Apache Software Foundation.  For more
 * information on the Apache Software Foundation, please see
 * <http://www.apache.org/>.
 *
 *
 *
 *
 * @author Susantha Kumara (skumara@virtusa.com)
 *
 */

#pragma warning (disable : 4010)

#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "../common/Packet.h"

extern int process_request(Ax_soapstream *str);

//soap request with headers
//char* ip = "<?xml version=\"1.0\" encoding=\"UTF-8\"?><soapenv:Envelope \
			xmlns:soapenv=\"http://schemas.xmlsoap.org/soap/envelope/\" \
			xmlns:xsd=\"http://www.w3.org/2001/XMLSchema\" \
			xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"> \
			<soapenv:Header><t:Transaction xmlns:t=\"http://example.org/2001/06/tx\" \
			soapenv:mustUnderstand=\"true\" >Hello Req Header Val</t:Transaction></soapenv:Header> \
			<soapenv:Body><add soapenv:encodingStyle=\"http://schemas.xmlsoap.org/soap/encoding/\"><op1 xsi:type=\"xsd:int\">3</op1><op2 xsi:type=\"xsd:int\">4</op2></add></soapenv:Body></soapenv:Envelope>";

char* ip = "<?xml version=\"1.0\" encoding=\"UTF-8\"?><soapenv:Envelope xmlns:soapenv=\"http://schemas.xmlsoap.org/soap/envelope/\" xmlns:xsd=\"http://www.w3.org/2001/XMLSchema\" xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"><soapenv:Body><add soapenv:encodingStyle=\"http://schemas.xmlsoap.org/soap/encoding/\"><op1 xsi:type=\"xsd:int\">3</op1><op2 xsi:type=\"xsd:int\">4</op2></add></soapenv:Body></soapenv:Envelope>";

//	char* ip = "<?xml version=\"1.0\" encoding=\"UTF-8\"?><soapenv:Envelope xmlns:soapenv=\"http://schemas.xmlsoap.org/soap/envelope/\" xmlns:xsd=\"http://www.w3.org/2001/XMLSchema\" xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"><soapenv:Body><echo soapenv:encodingStyle=\"http://schemas.xmlsoap.org/soap/encoding/\"><op1 xsi:type=\"xsd:string\">Hello World!</op1></echo></soapenv:Body></soapenv:Envelope>";

	
	//user type that contains an array of another user type
	//char* ip = "<?xml version=\"1.0\" encoding=\"UTF-8\"?><soapenv:Envelope xmlns:soapenv=\"\
		http://schemas.xmlsoap.org/soap/envelope/\" xmlns:xsd=\"http://www.w3.org/2001/XMLSchema\"\
		xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"><soapenv:Body><Store \
		soapenv:encodingStyle=\"http://schemas.xmlsoap.org/soap/encoding/\"><def:Person xmlns:def=\"\
		http://example.org/2001/06/numbers\" xmlns:enc=\"http://www.w3.org/2001/06/soap-encoding\"\
		> <name>John Hancock</name> <phoneNumbers enc:arrayType=\"def:phoneNumber[2]\"> \
		<phoneNumber>206-555-1212</phoneNumber> <phoneNumber>1-888-123-4567</phoneNumber> \
		</phoneNumbers> </def:Person></Store></soapenv:Body></soapenv:Envelope>";

	//Array of user types
//	char* ip = "<?xml version=\"1.0\" encoding=\"UTF-8\"?><soapenv:Envelope xmlns:soapenv=\"\
		http://schemas.xmlsoap.org/soap/envelope/\" xmlns:xsd=\"http://www.w3.org/2001/XMLSchema\"\
		xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"><soapenv:Body><Store \
		soapenv:encodingStyle=\"http://schemas.xmlsoap.org/soap/encoding/\"><def:phoneNumbers xmlns:def=\"\
		http://example.org/2001/06/numbers\" xmlns:enc=\"http://www.w3.org/2001/06/soap-encoding\"\
		enc:arrayType=\"def:phoneNumber[2]\"> \
		<phoneNumber>206-555-1212</phoneNumber> <phoneNumber>1-888-123-4567</phoneNumber> \
		</def:phoneNumbers> </Store></soapenv:Body></soapenv:Envelope>";

	//Array of int
//	char* ip = "<?xml version=\"1.0\" encoding=\"UTF-8\"?><soapenv:Envelope xmlns:soapenv=\"\
		http://schemas.xmlsoap.org/soap/envelope/\" xmlns:xsd=\"http://www.w3.org/2001/XMLSchema\"\
		 xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"><soapenv:Body><Store \
		soapenv:encodingStyle=\"http://schemas.xmlsoap.org/soap/encoding/\"><def:Numbers xmlns:def=\"\
		http://example.org/2001/06/numbers\" xmlns:enc=\"http://www.w3.org/2001/06/soap-encoding\"\
		enc:arrayType=\"xsd:int[2]\"> \
		<Number>3242</Number> <Number>5243</Number> \
		</def:Numbers> </Store></soapenv:Body></soapenv:Envelope>";

		//EchoIntArray
//	char* ip = "<?xml version=\"1.0\" encoding=\"UTF-8\"?><soapenv:Envelope xmlns:soapenv=\"\
		http://schemas.xmlsoap.org/soap/envelope/\" xmlns:xsd=\"http://www.w3.org/2001/XMLSchema\"\
		 xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"><soapenv:Body><EchoIntArray \
		soapenv:encodingStyle=\"http://schemas.xmlsoap.org/soap/encoding/\"><def:Numbers xmlns:def=\"\
		http://example.org/2001/06/numbers\" xmlns:enc=\"http://www.w3.org/2001/06/soap-encoding\"\
		enc:arrayType=\"xsd:int[2]\"> \
		<Number>3242</Number> <Number>5243</Number> \
		</def:Numbers> </EchoIntArray></soapenv:Body></soapenv:Envelope>";

	//Multiref
//	char* ip = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\
		<soapenv:Envelope xmlns:soapenv=\"http://schemas.xmlsoap.org/soap/envelope/\" xmlns:xsd=\"http://www.w3.org/2001/XMLSchema\" xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\">\
		<soapenv:Body>\
		<ns1:Add soapenv:encodingStyle=\"http://schemas.xmlsoap.org/soap/encoding/\" xmlns:ns1=\"http://localhost:8080/axis/services/MyMathService\">\
		<in0 href=\"#id0\"/>\
		<in1 href=\"#id1\"/>\
		</ns1:Add>\
		<multiRef id=\"id0\" soapenc:root=\"0\" soapenv:encodingStyle=\"http://schemas.xmlsoap.org/soap/encoding/\" xsi:type=\"ns2:Point\" xmlns:soapenc=\"http://schemas.xmlsoap.org/soap/encoding/\" xmlns:ns2=\"urn:BeanService\">\
		<x xsi:type=\"xsd:int\">23</x>\
		<y xsi:type=\"xsd:int\">77</y>\
		</multiRef>\
		<multiRef id=\"id1\" soapenc:root=\"0\" soapenv:encodingStyle=\"http://schemas.xmlsoap.org/soap/encoding/\" xsi:type=\"ns3:Point\" xmlns:ns3=\"urn:BeanService\" xmlns:soapenc=\"http://schemas.xmlsoap.org/soap/encoding/\">\
		<x xsi:type=\"xsd:int\">77</x>\
		<y xsi:type=\"xsd:int\">23</y>\
		</multiRef>\
		</soapenv:Body>\
		</soapenv:Envelope>";

	//Add two Points
//	char* ip = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\
		<soapenv:Envelope xmlns:soapenv=\"http://schemas.xmlsoap.org/soap/envelope/\" xmlns:xsd=\"http://www.w3.org/2001/XMLSchema\" xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\">\
		<soapenv:Body>\
		<AddPoint soapenv:encodingStyle=\"http://schemas.xmlsoap.org/soap/encoding/\">\
		<Point1 xsi:type=\"ns1:Point\" xmlns:ns1=\"http://www.opensource.lk/Axis/\">\
		<x xsi:type=\"xsd:int\">23</x>\
		<y xsi:type=\"xsd:int\">77</y>\
		</Point1>\
		<Point2 xsi:type=\"ns2:Point\" xmlns:ns2=\"http://www.opensource.lk/Axis/\">\
		<x xsi:type=\"xsd:int\">77</x>\
		<y xsi:type=\"xsd:int\">23</y>\
		</Point2>\
		</AddPoint>\
		</soapenv:Body>\
		</soapenv:Envelope>";

	//Array of Point
	//char* ip = "<?xml version=\"1.0\" encoding=\"UTF-8\"?><soapenv:Envelope xmlns:soapenv=\"\
		http://schemas.xmlsoap.org/soap/envelope/\" xmlns:xsd=\"http://www.w3.org/2001/XMLSchema\"\
		xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"><soapenv:Body><EchoPointArray \
		soapenv:encodingStyle=\"http://schemas.xmlsoap.org/soap/encoding/\"><enc:Array xmlns:def=\"\
		http://www.opensource.lk/Axis/\" xmlns:enc=\"http://www.w3.org/2001/06/soap-encoding\"\
		enc:arrayType=\"def:Point[3]\"> \
		<Point>\
		<x xsi:type=\"xsd:int\">11</x>\
		<y xsi:type=\"xsd:int\">22</y>\
		</Point>\
		<Point>\
		<x xsi:type=\"xsd:int\">33</x>\
		<y xsi:type=\"xsd:int\">44</y>\
		</Point>\
		<Point>\
		<x xsi:type=\"xsd:int\">55</x>\
		<y xsi:type=\"xsd:int\">66</y>\
		</Point>\
		</enc:Array> </EchoPointArray></soapenv:Body></soapenv:Envelope>";

int main() 
{		
	int xx;
	Ax_soapstream* str = (Ax_soapstream*)malloc(sizeof(Ax_soapstream));
	str->trtype = APTHTTP;
	str->sessionid = "somesessionid";
	str->so.http.ip_method = AXIS_HTTP_POST;

	str->so.http.ip_headers = (Ax_header*)malloc(sizeof(Ax_header));
	str->so.http.ip_headers->headername = SOAPACTIONHEADER;
	str->so.http.ip_headers->headervalue = "\"Calculator\"";	
	str->so.http.ip_headercount = 1;

	printf("soap request :\n %s\n", ip);

	initialize_module();
	for (xx =0; xx < 100 ; xx++)
		process_request(str);	

	return 0;
}

int send_response_bytes(char * res, void* pOutputStream) {

//	printf("sending SOAP response : \n%s\n", res);
	return 0;
}

int get_request_bytes(char * req, int reqsize, int* retsize) {

	req[0]= '\0';
	strcat(req, ip);
//	printf("strlen(ip)%d", strlen(ip));
	*retsize= strlen(ip);
	return 0;
}

int send_transport_information(Ax_soapstream* sSoapstream) {

	return 0;
}