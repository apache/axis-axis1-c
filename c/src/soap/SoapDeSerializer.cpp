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

// SoapDeSerializer.cpp: implementation of the SoapDeSerializer class.
//
//////////////////////////////////////////////////////////////////////
#include <axis/soap/SoapDeSerializer.h>
#include <axis/soap/SoapEnvelope.h>
#include <axis/soap/SoapKeywordMapping.h>
#include <axis/soap/URIMapping.h>
#include <axis/soap/SoapHeader.h>
#include <axis/soap/SoapMethod.h>
#include <axis/soap/SoapBody.h>
#include <axis/soap/SoapFault.h>
#include <axis/common/GDefine.h>
#include <axis/common/Packet.h>

#include <axis/common/AxisTrace.h>

#define INITIAL_ARRAY_SIZE 4

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IWrapperSoapDeSerializerFunctions SoapDeSerializer::ms_VFtable;

SoapDeSerializer::SoapDeSerializer()
{
	__vfptr = &ms_VFtable;
	m_pParser = new SoapParserExpat();
	m_pEnv = NULL;
	m_pHeader = NULL;
}

SoapDeSerializer::~SoapDeSerializer()
{
	m_pParser->Init();
    if (m_pParser) delete m_pParser;
}

int SoapDeSerializer::SetInputStream(const Ax_soapstream* pInputStream)
{
	if ((NULL == pInputStream->transport.pGetFunct) ||
		(NULL == pInputStream->transport.pRelBufFunct))
		return AXIS_FAIL;
	return m_pParser->SetInputStream(pInputStream);
}

SoapEnvelope* SoapDeSerializer::GetEnvelope()
{
	Attribute *pAttr = NULL;
    AXISTRACE1("SoapDeSerializer::GetEnvelope");
	if (!m_pNode) m_pNode = m_pParser->Next();
	if (!m_pNode || (START_ELEMENT != m_pNode->m_type)) return NULL;
	if (0 == strcmp(m_pNode->m_pchNameOrValue, SoapKeywordMapping::Map(SOAP_VER_1_2).pchWords[SKW_ENVELOPE]))
	{
		SoapEnvelope* m_pEnv = new SoapEnvelope();
		//set all attributes of SoapEnvelope
		pAttr = new Attribute();

		pAttr->setValue(m_pNode->m_pchNamespace);
		m_pEnv->addNamespaceDecl(pAttr);

		if (0 == strcmp(m_pNode->m_pchNamespace, SoapKeywordMapping::Map(SOAP_VER_1_1).pchNamespaceUri))
		{
			m_nSoapVersion = SOAP_VER_1_1;
		}
		else if (0 == strcmp(m_pNode->m_pchNamespace, SoapKeywordMapping::Map(SOAP_VER_1_2).pchNamespaceUri))
		{
			m_nSoapVersion = SOAP_VER_1_2;
		}
		else
		{
			m_nSoapVersion = VERSION_LAST;
		}

		//Set Attributes
		for (int i = 0; m_pNode->m_pchAttributes[i]; i += 3) 
		{
			pAttr = new Attribute();
			pAttr->setLocalName(m_pNode->m_pchAttributes[i]);
			pAttr->setUri(m_pNode->m_pchAttributes[i+1]);
			pAttr->setValue(m_pNode->m_pchAttributes[i+2]);
			m_pEnv->addAttribute(pAttr);
		}
		m_pNode = NULL; /*This is to indicate that node is identified and used */
		return m_pEnv;
	}
	return NULL;
}

/**
 * Header block parsing should be done differently for different SOAP versions.
 * Since the Header blocks may be requested in a different order than it is in the SOAP stream
 * there must be a mechanism to manage the situation. Possibly to re-parse the stream part
 * which has unused header blocks.
 */
IHeaderBlock* SoapDeSerializer::GetHeaderBlock(const AxisChar* pName, const AxisChar* pNamespace)
{
	if (!m_pHeader) return NULL; /* there has been no <Header> element so there can be no Header blocks */
	/*TODO*/
	return NULL;
}
											   
ISoapHeader* SoapDeSerializer::GetHeader()
{
	if (m_pHeader) return m_pHeader;
	m_pNode = m_pParser->Next();
	if (!m_pNode) {
		m_nStatus = AXIS_FAIL;
		return NULL;
	}
	if ((START_ELEMENT != m_pNode->m_type) && (0 == strcmp(m_pNode->m_pchNameOrValue, SoapKeywordMapping::Map(m_nSoapVersion).pchWords[SKW_HEADER])))
	{
		m_pHeader = new SoapHeader();
		/* Set any attributes/namspaces to the SoapHeader object */
		m_pNode = NULL; /*This is to indicate that node is identified and used */
		return m_pHeader;
	}
	return NULL;
}

int SoapDeSerializer::GetBody()
{
    AXISTRACE1("SoapDeSerializer::GetBody");
	while (true)
	{
		if (!m_pNode) m_pNode = m_pParser->Next(); /* previous header searching may have left a node unidentified */
		if (!m_pNode) {
			m_nStatus = AXIS_FAIL;
			return AXIS_FAIL;
		}
		if ((START_ELEMENT == m_pNode->m_type) && (0 == strcmp(m_pNode->m_pchNameOrValue, SoapKeywordMapping::Map(m_nSoapVersion).pchWords[SKW_BODY])))
		{
			/* Set any attributes/namspaces to the SoapBody object */
			m_pNode = NULL; /*This is to indicate that node is identified and used */
			return AXIS_SUCCESS;
		}
		else /* probably there are un-processed soap headers. So check for "mustUnderstand" attribute in those headers */
		{
			/*TODO: parse until <Body> tag is found. If a "mustUnderstand" attribute found
			{
				m_nStatus = AXIS_MUSTUNDERSTAND_IGNORED;
				return NULL;
			}
			else
			{
				leave the <Body> element un-identified state
			}
			*/
			m_pNode = NULL;
		}
	}
	return AXIS_FAIL;
}

int SoapDeSerializer::CheckMessageBody(const AxisChar* pName, const AxisChar* pNamespace)
{
	/* check and skip the soap body tag */
	if (AXIS_SUCCESS != GetBody()) return AXIS_FAIL;
    AXISTRACE1("SoapDeSerializer::CheckMessageBody");
	if (!m_pNode) m_pNode = m_pParser->Next();
	if (!m_pNode || (START_ELEMENT != m_pNode->m_type)) return AXIS_FAIL;
	if (0 != strcmp(m_pNode->m_pchNameOrValue, pName)) return AXIS_FAIL;
	/* we can check the namespace uri too here. Should we ?*/
	m_pNode = NULL; /*This is to indicate that node is identified and used */
	return AXIS_SUCCESS;
}

SoapFault* SoapDeSerializer::GetFault()
{
	/* TODO : */
	return NULL;
}

int SoapDeSerializer::Init()
{
	m_pNode = 0;
	m_nStatus = m_pParser->Init();
	if (m_pEnv) 
	{
		delete m_pEnv;
		m_pEnv = NULL;
	}
	if (m_pHeader)
	{
		delete m_pHeader;
		m_pHeader = NULL;
	}
	m_nSoapVersion = VERSION_LAST;
	return m_nStatus;
}

int SoapDeSerializer::GetVersion()
{
	if (VERSION_LAST == m_nSoapVersion)
	{
		GetEnvelope();
	}
	return m_nSoapVersion;	
}

/**
 * In rpc/encoded style the stream is as follows,
 * <abc:ArrayOfPoints xmlns:abc="http://www.opensource.lk/Points"
 *	xmlns:enc="http://www.w3.org/2001/06/soap-encoding"
 *	enc:arrayType="xsd:Point[2]">
 *	<abc:Point><x>5</x><y>6</y></abc:Point>
 *	<abc:Point><x>7</x><y>8</y></abc:Point>
 * </abc:ArrayOfPoints>
 * But in doc/literal style it is,
 *	<points><x>5</x><y>6</y></points>
 *	<points><x>7</x><y>8</y></points>
 *
 */
Axis_Array SoapDeSerializer::GetCmplxArray(void* pDZFunct, void* pCreFunct, void* pDelFunct, void* pSizeFunct, const AxisChar* pName, const AxisChar* pNamespace)
{
	Axis_Array Array = {NULL, 0};
	int nIndex = 0;
	void* pItem;
	int itemsize;
	unsigned long ptrval;
	if (AXIS_SUCCESS != m_nStatus) return Array; /* if anything has gone wrong earlier just do nothing */
	if (RPC_ENCODED == m_nStyle)
	{
		m_pNode = m_pParser->Next(); /* just skip wrapper node with type info  Ex: <tns:QuoteInfoTypeArray xmlns:tns="http://www.getquote.org/test">*/ 
		Array.m_Size = GetArraySize(m_pNode);
		if (Array.m_Size > 0)
		{
			Array.m_Array = ((AXIS_OBJECT_CREATE_FUNCT)pCreFunct)(Array.m_Array, true, Array.m_Size);
			if (!Array.m_Array)
			{
				Array.m_Size = 0;
				m_nStatus = AXIS_FAIL;
				return Array;
			}
			itemsize = ((AXIS_OBJECT_SIZE_FUNCT)pSizeFunct)();
			ptrval = reinterpret_cast<unsigned long>(Array.m_Array);
			for (; nIndex < Array.m_Size; nIndex++)
			{
				m_pNode = m_pParser->Next(); /* wrapper node without type info  Ex: <item>*/
				pItem = reinterpret_cast<void*>(ptrval+nIndex*itemsize);
				((AXIS_DESERIALIZE_FUNCT)pDZFunct)(pItem, this);
				m_pNode = m_pParser->Next(); /* skip end element node too */
			}
			return Array;
		}
	}
	else
	{
		Array.m_Array = ((AXIS_OBJECT_CREATE_FUNCT)pCreFunct)(Array.m_Array, true, INITIAL_ARRAY_SIZE);
		if (!Array.m_Array) return Array;
		Array.m_Size = INITIAL_ARRAY_SIZE;
		itemsize = ((AXIS_OBJECT_SIZE_FUNCT)pSizeFunct)();
		while(true)
		{
			ptrval = reinterpret_cast<unsigned long>(Array.m_Array);
			for (; nIndex < Array.m_Size; nIndex++)
			{
				if (!m_pNode) /* if there is an unprocessed node that may be one left from last array deserialization */ 
					m_pNode = m_pParser->Next(); /* wrapper node without type info  Ex: <phonenumbers>*/
				if (0 == strcmp(pName, m_pNode->m_pchNameOrValue))
				{
					pItem = reinterpret_cast<void*>(ptrval+nIndex*itemsize);
					if (AXIS_SUCCESS == ((AXIS_DESERIALIZE_FUNCT)pDZFunct)(pItem, this))
						continue;
				}
				else
				{
					if (nIndex > 0)
					{
						Array.m_Size = nIndex; /* put the actual deserialized item size */
						/* note we do not make m_pNode = NULL because this node doesnot belong to this array */
						return Array;
					}
					/* error : no elements deserialized */
				}
				/* if we come here it is an error situation */
				m_nStatus = AXIS_FAIL;
				m_pNode = NULL;
				((AXIS_OBJECT_DELETE_FUNCT)pDelFunct)(Array.m_Array, true, Array.m_Size);
				Array.m_Array = 0;
				Array.m_Size = 0;
				return Array;
			}
			/* if we come here that means the array allocated is not enough. So double it */
			Array.m_Array = ((AXIS_OBJECT_CREATE_FUNCT)pCreFunct)(Array.m_Array, true, Array.m_Size*2);
			if (!Array.m_Array) 
			{
				Array.m_Size = 0;
				return Array;
			}
			Array.m_Size *= 2;
		}
	}
	m_nStatus = AXIS_FAIL;
	m_pNode = NULL;
	return Array;
}

/**
 * Get Size of the single dimension array from arrayType attribute
 * Ex : enc:arrayType="xs:string[6]"
 */
int SoapDeSerializer::GetArraySize(const AnyElement* pElement)
{
	int nSize = 0;
	/* first check whether this is a start element node */
	if (START_ELEMENT != pElement->m_type) return nSize;
	for (int i=0; pElement->m_pchAttributes[i]; i+=3)
	{
		if (URI_ENC == URIMapping::Map(pElement->m_pchAttributes[i+1]) &&
			(0 == strcmp(pElement->m_pchAttributes[i], SoapKeywordMapping::Map(m_nSoapVersion).pchWords[SKW_ARRAYTYPE])))
		{
			QName qn;
			qn.SplitQNameString(pElement->m_pchAttributes[i+2], '[');
			nSize = strtol(qn.localname, &m_pEndptr, 10);
			qn.MergeQNameString('[');
			return nSize;
		}
	}
	return nSize;
}

/**
 * In rpc/encoded style the stream is as follows,
 * <abc:ArrayOfPhoneNumbers xmlns:abc="http://example.org/2001/06/numbers"
 *	xmlns:enc="http://www.w3.org/2001/06/soap-encoding"
 *	enc:arrayType="xsd:string[2]">
 *	<item>+94-112-500500</item>
 *	<item>+94-112-500500</item>
 * </abc:ArrayOfPhoneNumbers>
 * But in doc/literal style it is,
 *	<phonenumbers>+94-112-500500</phonenumbers>
 *	<phonenumbers>+94-112-500500</phonenumbers> 
 *
 *
 */

/* Following macros are used just to shorten the coding */
#define CONV_STRTOL(str) strtol(str, &m_pEndptr, 10)
#define CONV_STRTOUL(str) strtoul(str, &m_pEndptr, 10)
#define CONV_STRTOD(str) strtod(str,  &m_pEndptr)
#define CONV_STRTODATETIME(str) AxisTime::Deserialize(str, nType)
#define CONV_STRTODURATION(str) AxisTime::DeserializeDuration(str, nType)
#define CONV_STRDUP(str) strdup(str)
#define CONV_STRTOBASE64BINARY(str) DecodeFromBase64Binary(str)
#define CONV_STRTOHEXBINARY(str) DecodeFromHexBinary(str)

#define DESERIALIZE_ENCODED_ARRAY_BLOCK(cpp_type, conv_func) \
			Array.m_Array = malloc(sizeof(cpp_type)*Array.m_Size);\
			if (!Array.m_Array)\
			{\
				Array.m_Size = 0;\
				m_nStatus = AXIS_FAIL;\
				return Array;\
			}\
			for (; nIndex < Array.m_Size; nIndex++)\
			{\
				m_pNode = m_pParser->Next(); /* wrapper node without type info  Ex: <item>*/\
				m_pNode = m_pParser->Next(); /* charactor node */\
				if (m_pNode && (CHARACTER_ELEMENT == m_pNode->m_type))\
				{\
					((cpp_type*)Array.m_Array)[nIndex] = conv_func(m_pNode->m_pchNameOrValue);\
					m_pNode = m_pParser->Next(); /* skip end element node too */\
					continue;\
				}\
				/* error : unexpected element type or end of stream */\
				m_nStatus = AXIS_FAIL;\
				free(Array.m_Array);\
				Array.m_Array = 0;\
				Array.m_Size = 0;\
				return Array;\
			}\
			return Array;

#define DESERIALIZE_LITERAL_ARRAY_BLOCK(cpp_type, conv_func) \
			Array.m_Array = malloc(sizeof(cpp_type)*INITIAL_ARRAY_SIZE);\
			if (!Array.m_Array) return Array;\
			Array.m_Size = INITIAL_ARRAY_SIZE;\
			while(true)\
			{\
				for (; nIndex < Array.m_Size; nIndex++)\
				{\
					if (!m_pNode) /* if there is an unprocessed node that may be one left from last array deserialization */ \
						m_pNode = m_pParser->Next(); /* wrapper node without type info  Ex: <phonenumbers>*/\
					if (0 == strcmp(pName, m_pNode->m_pchNameOrValue))\
					{\
						m_pNode = m_pParser->Next(); /* charactor node */\
						if (m_pNode && (CHARACTER_ELEMENT == m_pNode->m_type))\
						{\
							((cpp_type*)Array.m_Array)[nIndex] = conv_func(m_pNode->m_pchNameOrValue);\
							m_pNode = m_pParser->Next(); /* skip end element node too */\
							m_pNode = NULL; /* this is important in doc/lit style when deserializing arrays */\
							continue;\
						}\
						/* error : unexpected element type or end of the stream */\
					}\
					else\
					{\
						if (nIndex > 0)\
						{\
							Array.m_Size = nIndex; /* put the actual deserialized item size */\
							/* note we do not make m_pNode = NULL because this node doesnot belong to this array */\
							return Array;\
						}\
						/* error : no elements deserialized */\
					}\
					/* if we come here it is an error situation */\
					m_nStatus = AXIS_FAIL;\
					m_pNode = NULL;\
					free(Array.m_Array);\
					Array.m_Array = 0;\
					Array.m_Size = 0;\
					return Array;\
				}\
				/* if we come here that means the array allocated is not enough. So double it */\
				Array.m_Array = realloc(Array.m_Array, sizeof(cpp_type)*(Array.m_Size*2));\
				if (!Array.m_Array) \
				{\
					Array.m_Size = 0;\
					return Array;\
				}\
				Array.m_Size *= 2;\
			}\
			break;

Axis_Array SoapDeSerializer::GetBasicArray(XSDTYPE nType, const AxisChar* pName, const AxisChar* pNamespace)
{
	Axis_Array Array = {NULL, 0};
	int nIndex = 0;
	if (AXIS_SUCCESS != m_nStatus) return Array; /* if anything has gone wrong earlier just do nothing */
	if (RPC_ENCODED == m_nStyle)
	{
		m_pNode = m_pParser->Next(); /* just skip wrapper node with type info  Ex: <tns:ArrayOfPhoneNumbers xmlns:tns="http://www.getquote.org/test">*/ 
		Array.m_Size = GetArraySize(m_pNode);
		if (Array.m_Size > 0)
		{
			switch(nType)
			{
			case XSD_INT:
				Array.m_Array = malloc(sizeof(int)*Array.m_Size);
				if (!Array.m_Array)
				{
					Array.m_Size = 0;
					m_nStatus = AXIS_FAIL;
					return Array;
				}
				for (; nIndex < Array.m_Size; nIndex++)
				{
					m_pNode = m_pParser->Next(); /* wrapper node without type info  Ex: <item>*/
					m_pNode = m_pParser->Next(); /* charactor node */
					if (m_pNode && (CHARACTER_ELEMENT == m_pNode->m_type))
					{
						((int*)Array.m_Array)[nIndex] = strtol(m_pNode->m_pchNameOrValue, &m_pEndptr, 10);
						m_pNode = m_pParser->Next(); /* skip end element node too */
						continue;
					}
					/* error : unexpected element type or end of stream */
					m_nStatus = AXIS_FAIL;
					free(Array.m_Array);
					Array.m_Array = 0;
					Array.m_Size = 0;
					return Array;
				}
				return Array;
			case XSD_UNSIGNEDINT:
				DESERIALIZE_ENCODED_ARRAY_BLOCK(unsigned int, CONV_STRTOUL)
			case XSD_SHORT:
				DESERIALIZE_ENCODED_ARRAY_BLOCK(short, CONV_STRTOL)
			case XSD_UNSIGNEDSHORT:
				DESERIALIZE_ENCODED_ARRAY_BLOCK(unsigned short, CONV_STRTOUL)
			case XSD_BYTE:
				DESERIALIZE_ENCODED_ARRAY_BLOCK(char, CONV_STRTOL)
			case XSD_UNSIGNEDBYTE:
				DESERIALIZE_ENCODED_ARRAY_BLOCK(unsigned char, CONV_STRTOUL)
			case XSD_LONG:
			case XSD_INTEGER:
				DESERIALIZE_ENCODED_ARRAY_BLOCK(long, CONV_STRTOL)
			case XSD_UNSIGNEDLONG:
				DESERIALIZE_ENCODED_ARRAY_BLOCK(unsigned long, CONV_STRTOUL)
			case XSD_FLOAT:
				DESERIALIZE_ENCODED_ARRAY_BLOCK(float, CONV_STRTOD)
			case XSD_DOUBLE:
			case XSD_DECIMAL:
				DESERIALIZE_ENCODED_ARRAY_BLOCK(double, CONV_STRTOD)
			case XSD_STRING:
			case XSD_HEXBINARY:
			case XSD_BASE64BINARY:
			case XSD_ANYURI:
			case XSD_QNAME:
			case XSD_NOTATION:			
				DESERIALIZE_ENCODED_ARRAY_BLOCK(char*, CONV_STRDUP)
			case XSD_DATETIME:
			case XSD_DATE:
			case XSD_TIME:
				DESERIALIZE_ENCODED_ARRAY_BLOCK(struct tm, CONV_STRTODATETIME)     
			case XSD_DURATION:
				DESERIALIZE_ENCODED_ARRAY_BLOCK(long, CONV_STRTODURATION)
			}
		}
	}
	else
	{
		switch(nType)
		{
		case XSD_INT:
			Array.m_Array = malloc(sizeof(int)*INITIAL_ARRAY_SIZE);
			if (!Array.m_Array) return Array;
			Array.m_Size = INITIAL_ARRAY_SIZE;
			while(true)
			{
				for (; nIndex < Array.m_Size; nIndex++)
				{
					if (!m_pNode) /* if there is an unprocessed node that may be one left from last array deserialization */ 
						m_pNode = m_pParser->Next(); /* wrapper node without type info  Ex: <phonenumbers>*/
					if (0 == strcmp(pName, m_pNode->m_pchNameOrValue))
					{
						m_pNode = m_pParser->Next(); /* charactor node */
						if (m_pNode && (CHARACTER_ELEMENT == m_pNode->m_type))
						{
							((int*)Array.m_Array)[nIndex] = strtol(m_pNode->m_pchNameOrValue, &m_pEndptr, 10);
							m_pNode = m_pParser->Next(); /* skip end element node too */
							m_pNode = NULL; /* this is important in doc/lit style when deserializing arrays */
							continue;
						}
						/* error : unexpected element type or end of the stream */
					}
					else
					{
						if (nIndex > 0)
						{
							Array.m_Size = nIndex; /* put the actual deserialized item size */
							/* note we do not make m_pNode = NULL because this node doesnot belong to this array */
							return Array;
						}
						/* error : no elements deserialized */
					}
					/* if we come here it is an error situation */
					m_nStatus = AXIS_FAIL;
					m_pNode = NULL;
					free(Array.m_Array);
					Array.m_Array = 0;
					Array.m_Size = 0;
					return Array;
				}
				/* if we come here that means the array allocated is not enough. So double it */
				Array.m_Array = realloc(Array.m_Array, sizeof(int)*(Array.m_Size*2));
				if (!Array.m_Array) 
				{
					Array.m_Size = 0;
					return Array;
				}
				Array.m_Size *= 2;
			}
			break;
		case XSD_UNSIGNEDINT:
			DESERIALIZE_LITERAL_ARRAY_BLOCK(unsigned int, CONV_STRTOUL)
		case XSD_SHORT:
			DESERIALIZE_LITERAL_ARRAY_BLOCK(short, CONV_STRTOL)
		case XSD_UNSIGNEDSHORT:
			DESERIALIZE_LITERAL_ARRAY_BLOCK(unsigned short, CONV_STRTOUL)
		case XSD_BYTE:
			DESERIALIZE_LITERAL_ARRAY_BLOCK(char, CONV_STRTOL)
		case XSD_UNSIGNEDBYTE:
			DESERIALIZE_LITERAL_ARRAY_BLOCK(unsigned char, CONV_STRTOUL)
		case XSD_LONG:
		case XSD_INTEGER:
			DESERIALIZE_LITERAL_ARRAY_BLOCK(long, CONV_STRTOL)
		case XSD_UNSIGNEDLONG:
			DESERIALIZE_LITERAL_ARRAY_BLOCK(unsigned long, CONV_STRTOUL)
		case XSD_FLOAT:
			DESERIALIZE_LITERAL_ARRAY_BLOCK(float, CONV_STRTOD)
		case XSD_DOUBLE:
		case XSD_DECIMAL:
			DESERIALIZE_LITERAL_ARRAY_BLOCK(double, CONV_STRTOD)
		case XSD_STRING:
		case XSD_HEXBINARY:
		case XSD_BASE64BINARY:
		case XSD_ANYURI:
		case XSD_QNAME:
		case XSD_NOTATION:			
			DESERIALIZE_LITERAL_ARRAY_BLOCK(char*, CONV_STRDUP)
		case XSD_DATETIME:
		case XSD_DATE:
		case XSD_TIME:
			DESERIALIZE_LITERAL_ARRAY_BLOCK(struct tm, CONV_STRTODATETIME)     
	    case XSD_DURATION:
			DESERIALIZE_LITERAL_ARRAY_BLOCK(long, CONV_STRTODURATION)
		}
	}
	m_nStatus = AXIS_FAIL;
	m_pNode = NULL;
	return Array;
}

/**
 * In doc/lit style pName is the name of the type instance "result"
 *  <result>
 *		<name>Widgets Inc.</name> 
 *		<symbol>WID</symbol> 
 *		<public>true</public> 
 *  </result>
 * But in rpc/encoded style pName is the name of the type "QuoteInfoType"
 *  <tns:QuoteInfoType xmlns:tns="http://www.getquote.org/test">
 *		<name xsi:type="xsd:string">Widgets Inc.</name> 
 *		<symbol xsi:type="xsd:string">WID</symbol> 
 *		<public xsi:type="xsd:boolean">true</public> 
 *  </tns:QuoteInfoType>
 *
 */
void* SoapDeSerializer::GetCmplxObject(void* pDZFunct, void* pCreFunct, void* pDelFunct, const AxisChar* pName, const AxisChar* pNamespace)
{
	if (AXIS_SUCCESS != m_nStatus) return NULL; /* if anything has gone wrong earlier just do nothing */
	if (RPC_ENCODED == m_nStyle)
	{
		m_pNode = m_pParser->Next(); /* just skip wrapper node with type info  Ex: <tns:QuoteInfoType xmlns:tns="http://www.getquote.org/test">*/ 
		/* type  can be checked here */
		void* pObject = ((AXIS_OBJECT_CREATE_FUNCT)pCreFunct)(NULL, false, 0);
		if (pObject)
		{
			if (pDZFunct && (AXIS_SUCCESS == ((AXIS_DESERIALIZE_FUNCT)pDZFunct)(pObject, this)))
			{
				m_pParser->Next(); /* skip end node too */
				return pObject;
			}
			else
			{
				((AXIS_OBJECT_DELETE_FUNCT)pDelFunct)(pObject, false, 0);
			}
		}
	}
	else
	{
		if (!m_pNode) /* if there is an unprocessed node that may be one left from last array deserialization */ 
			m_pNode = m_pParser->Next(); /* wrapper node without type info  Ex: <result>*/
		if (0 == strcmp(pName, m_pNode->m_pchNameOrValue))
		{
			void* pObject = ((AXIS_OBJECT_CREATE_FUNCT)pCreFunct)(NULL, false, 0);
			if (pObject)
			{
				if (pDZFunct && (AXIS_SUCCESS == ((AXIS_DESERIALIZE_FUNCT)pDZFunct)(pObject, this)))
				{
					m_pParser->Next(); /* skip end node too */
					return pObject;
				}
			}
			else
			{
				((AXIS_OBJECT_DELETE_FUNCT)pDelFunct)(pObject, false, 0);
			}
		}
		else
		{
			/* error: unexpected element */
		}
	}
	m_nStatus = AXIS_FAIL; /* unexpected SOAP stream */
	return NULL;
}

int SoapDeSerializer::GetElementForAttributes(const AxisChar* pName, const AxisChar* pNamespace)
{
	if (!m_pNode)
	{
		m_pNode = m_pParser->Next();
		m_pCurrNode = m_pParser->Next();
	}
	else /* previous node not processed. So consider it */
	{
		m_pCurrNode = m_pNode;
	}
	if (0 == strcmp(pName, m_pNode->m_pchNameOrValue))
	{
		m_pNode = NULL;
	}
	else /* error : current element is not the expected one */
	{
		m_nStatus = AXIS_FAIL;
		m_pCurrNode = NULL;
	}
	return m_nStatus;
}

#define DESERIALIZE_GET_ATTRIBUTE_AS(cpp_type, conv_func) \
	cpp_type ret;\
	if(!m_pCurrNode) \
	{\
		m_nStatus = AXIS_FAIL;\
		return ret;\
	}\
	if (START_ELEMENT == m_pNode->m_type)\
	{\
		for (int i=0; m_pCurrNode->m_pchAttributes[i]; i+=3)\
		{\
			if (0 == strcmp(m_pCurrNode->m_pchAttributes[i], pName))\
			{\
				ret = conv_func(m_pCurrNode->m_pchAttributes[i]);\
				return ret;\
			}\
		}\
	}\
	else\
	{\
		m_nStatus = AXIS_FAIL;\
		return ret;\
	}\
	return ret;

/**
 * Before calling any of GetAttributeAs... API functions the user should move current Element
 * to the right Element by calling GetElementForAttributes(..)
 */
int SoapDeSerializer::GetAttributeAsInt(const AxisChar* pName, const AxisChar* pNamespace)
{
	int ret = 0;
	if(!m_pCurrNode) 
	{
		m_nStatus = AXIS_FAIL;
		return ret;
	}
	if (START_ELEMENT == m_pNode->m_type)
	{
		for (int i=0; m_pCurrNode->m_pchAttributes[i]; i+=3) 
			/* browse through the attributes list */
		{
			if (0 == strcmp(m_pCurrNode->m_pchAttributes[i], pName))
			{
				ret = strtol(m_pCurrNode->m_pchAttributes[i], &m_pEndptr, 10);
				return ret;
			}
		}	
	}
	else
	{
		m_nStatus = AXIS_FAIL;
	}
	return ret;		
}

xsd__boolean SoapDeSerializer::GetAttributeAsBoolean(const AxisChar* pName, const AxisChar* pNamespace)
{
	xsd__boolean ret = false_;
	if(!m_pCurrNode) 
	{
		m_nStatus = AXIS_FAIL;
		return ret;
	}
	if (START_ELEMENT == m_pNode->m_type)
	{
		for (int i=0; m_pCurrNode->m_pchAttributes[i]; i+=3) 
			/* browse through the attributes list */
		{
			if (0 == strcmp(m_pCurrNode->m_pchAttributes[i], pName))
			{
				ret = (0 == strcmp(m_pCurrNode->m_pchAttributes[i], "true")) ? true_: false_;
				return ret;
			}
		}	
	}
	else
	{
		m_nStatus = AXIS_FAIL;
	}
	return ret;		
}

unsigned int SoapDeSerializer::GetAttributeAsUnsignedInt(const AxisChar* pName, const AxisChar* pNamespace)
{
	DESERIALIZE_GET_ATTRIBUTE_AS(unsigned int,CONV_STRTOUL)
}
short SoapDeSerializer::GetAttributeAsShort(const AxisChar* pName, const AxisChar* pNamespace)
{
	DESERIALIZE_GET_ATTRIBUTE_AS(short,CONV_STRTOL)
}
unsigned short SoapDeSerializer::GetAttributeAsUnsignedShort(const AxisChar* pName, const AxisChar* pNamespace)
{
	DESERIALIZE_GET_ATTRIBUTE_AS(unsigned short,CONV_STRTOUL)
}
char SoapDeSerializer::GetAttributeAsByte(const AxisChar* pName, const AxisChar* pNamespace)
{
	DESERIALIZE_GET_ATTRIBUTE_AS(char,CONV_STRTOL)
}
unsigned char SoapDeSerializer::GetAttributeAsUnsignedByte(const AxisChar* pName, const AxisChar* pNamespace)
{
	DESERIALIZE_GET_ATTRIBUTE_AS(unsigned char,CONV_STRTOUL)
}
long SoapDeSerializer::GetAttributeAsLong(const AxisChar* pName, const AxisChar* pNamespace)
{
	DESERIALIZE_GET_ATTRIBUTE_AS(long,CONV_STRTOL)
}
long SoapDeSerializer::GetAttributeAsInteger(const AxisChar* pName, const AxisChar* pNamespace)
{
	DESERIALIZE_GET_ATTRIBUTE_AS(long,CONV_STRTOL)
}
unsigned long SoapDeSerializer::GetAttributeAsUnsignedLong(const AxisChar* pName, const AxisChar* pNamespace)
{
	DESERIALIZE_GET_ATTRIBUTE_AS(unsigned long,CONV_STRTOUL)
}
float SoapDeSerializer::GetAttributeAsFloat(const AxisChar* pName, const AxisChar* pNamespace)
{
	DESERIALIZE_GET_ATTRIBUTE_AS(float,CONV_STRTOD)
}
double SoapDeSerializer::GetAttributeAsDouble(const AxisChar* pName, const AxisChar* pNamespace)
{
	DESERIALIZE_GET_ATTRIBUTE_AS(double,CONV_STRTOD)
}
double SoapDeSerializer::GetAttributeAsDecimal(const AxisChar* pName, const AxisChar* pNamespace)
{
	DESERIALIZE_GET_ATTRIBUTE_AS(double,CONV_STRTOD)
}
AxisChar* SoapDeSerializer::GetAttributeAsString(const AxisChar* pName, const AxisChar* pNamespace)
{
	DESERIALIZE_GET_ATTRIBUTE_AS(AxisChar*,CONV_STRDUP)
}
AxisChar* SoapDeSerializer::GetAttributeAsAnyURI(const AxisChar* pName, const AxisChar* pNamespace)
{
	DESERIALIZE_GET_ATTRIBUTE_AS(AxisChar*,CONV_STRDUP)
}
AxisChar* SoapDeSerializer::GetAttributeAsQName(const AxisChar* pName, const AxisChar* pNamespace)
{
	DESERIALIZE_GET_ATTRIBUTE_AS(AxisChar*,CONV_STRDUP)
}
xsd__hexBinary SoapDeSerializer::GetAttributeAsHexBinary(const AxisChar* pName, const AxisChar* pNamespace)
{
	DESERIALIZE_GET_ATTRIBUTE_AS(xsd__hexBinary,CONV_STRTOHEXBINARY)
}
xsd__base64Binary SoapDeSerializer::GetAttributeAsBase64Binary(const AxisChar* pName, const AxisChar* pNamespace)
{
	DESERIALIZE_GET_ATTRIBUTE_AS(xsd__base64Binary,CONV_STRTOBASE64BINARY)
}
struct tm SoapDeSerializer::GetAttributeAsDateTime(const AxisChar* pName, const AxisChar* pNamespace)
{
	XSDTYPE nType = XSD_DATETIME;
	DESERIALIZE_GET_ATTRIBUTE_AS(struct tm, CONV_STRTODATETIME)
}
struct tm SoapDeSerializer::GetAttributeAsDate(const AxisChar* pName, const AxisChar* pNamespace)
{
	XSDTYPE nType = XSD_DATE;
	DESERIALIZE_GET_ATTRIBUTE_AS(struct tm, CONV_STRTODATETIME)
}
struct tm SoapDeSerializer::GetAttributeAsTime(const AxisChar* pName, const AxisChar* pNamespace)
{
	XSDTYPE nType = XSD_DATE;
	DESERIALIZE_GET_ATTRIBUTE_AS(struct tm, CONV_STRTODATETIME)
}
long SoapDeSerializer::GetAttributeAsDuration(const AxisChar* pName, const AxisChar* pNamespace)
{
	XSDTYPE nType = XSD_DURATION;
	DESERIALIZE_GET_ATTRIBUTE_AS(long, CONV_STRTODURATION)
}

/**
 * Deserializing Elements as values directly.
 * 
 */
xsd__boolean SoapDeSerializer::GetElementAsBoolean(const AxisChar* pName, const AxisChar* pNamespace)
{
	xsd__boolean ret = false_;
	if (AXIS_SUCCESS != m_nStatus) return ret;
	if (RPC_ENCODED == m_nStyle)
	{
		m_pNode = m_pParser->Next(); /* wrapper node with type info  Ex: <i xsi:type="xsd:int">*/ 
		if (XSD_INT == GetXSDType(m_pNode))
		{
			m_pNode = m_pParser->Next(); /* charactor node */
			if (m_pNode && (CHARACTER_ELEMENT == m_pNode->m_type))
			{
				ret = (0 == strcmp(m_pNode->m_pchNameOrValue, "true")) ? true_: false_;
				m_pNode = m_pParser->Next(); /* skip end element node too */
				return ret;
			}
		}
		else
		{
			/* it is an error if type is different or not present */
		}
	}
	else
	{
		if (!m_pNode) /* if there is an unprocessed node that may be one left from last array deserialization */ 
			m_pNode = m_pParser->Next(); /* wrapper node without type info  Ex: <i>*/
		if (0 == strcmp(pName, m_pNode->m_pchNameOrValue))
		{
			m_pNode = m_pParser->Next(); /* charactor node */
			if (m_pNode && (CHARACTER_ELEMENT == m_pNode->m_type))
			{
				ret = (0 == strcmp(m_pNode->m_pchNameOrValue, "true")) ? true_: false_;
				m_pNode = m_pParser->Next(); /* skip end element node too */
				m_pNode = NULL; /* this is important in doc/lit style when deserializing arrays */
				return ret;
			}			
		}
		else
		{
			/* error: unexpected element */
		}
	}
	m_nStatus = AXIS_FAIL; /* unexpected SOAP stream */
	return ret;
}

int SoapDeSerializer::GetElementAsInt(const AxisChar* pName, const AxisChar* pNamespace)
{
	int ret = 0;
	if (AXIS_SUCCESS != m_nStatus) return ret;
	if (RPC_ENCODED == m_nStyle)
	{
		m_pNode = m_pParser->Next(); /* wrapper node with type info  Ex: <i xsi:type="xsd:int">*/ 
		if (XSD_INT == GetXSDType(m_pNode))
		{
			m_pNode = m_pParser->Next(); /* charactor node */
			if (m_pNode && (CHARACTER_ELEMENT == m_pNode->m_type))
			{
				ret = strtol(m_pNode->m_pchNameOrValue, &m_pEndptr, 10);
				m_pNode = m_pParser->Next(); /* skip end element node too */
				return ret;
			}
		}
		else
		{
			/* it is an error if type is different or not present */
		}
	}
	else
	{
		if (!m_pNode) /* if there is an unprocessed node that may be one left from last array deserialization */ 
			m_pNode = m_pParser->Next(); /* wrapper node without type info  Ex: <i>*/
		if (0 == strcmp(pName, m_pNode->m_pchNameOrValue))
		{
			m_pNode = m_pParser->Next(); /* charactor node */
			if (m_pNode && (CHARACTER_ELEMENT == m_pNode->m_type))
			{
				ret = strtol(m_pNode->m_pchNameOrValue, &m_pEndptr, 10);
				m_pNode = m_pParser->Next(); /* skip end element node too */
				m_pNode = NULL; /* this is important in doc/lit style when deserializing arrays */
				return ret;
			}			
		}
		else
		{
			/* error: unexpected element */
		}
	}
	m_nStatus = AXIS_FAIL; /* unexpected SOAP stream */
	return ret;
}

unsigned int SoapDeSerializer::GetElementAsUnsignedInt(const AxisChar* pName, const AxisChar* pNamespace)
{
	unsigned int ret = 0;
	if (AXIS_SUCCESS != m_nStatus) return ret;
	if (RPC_ENCODED == m_nStyle)
	{
		m_pNode = m_pParser->Next(); /* wrapper node with type info  Ex: <i xsi:type="xsd:int">*/ 
		if (XSD_UNSIGNEDINT == GetXSDType(m_pNode))
		{
			m_pNode = m_pParser->Next(); /* charactor node */
			if (m_pNode && (CHARACTER_ELEMENT == m_pNode->m_type))
			{
				ret = strtoul(m_pNode->m_pchNameOrValue, &m_pEndptr, 10);
				m_pNode = m_pParser->Next(); /* skip end element node too */
				return ret;
			}
		}
		else
		{
			/* it is an error if type is different or not present */
		}
	}
	else
	{
		if (!m_pNode) /* if there is an unprocessed node that may be one left from last array deserialization */ 
			m_pNode = m_pParser->Next(); /* wrapper node without type info  Ex: <i>*/
		if (0 == strcmp(pName, m_pNode->m_pchNameOrValue))
		{
			m_pNode = m_pParser->Next(); /* charactor node */
			if (m_pNode && (CHARACTER_ELEMENT == m_pNode->m_type))
			{
				ret = strtoul(m_pNode->m_pchNameOrValue, &m_pEndptr, 10);
				m_pNode = m_pParser->Next(); /* skip end element node too */
				m_pNode = NULL; /* this is important in doc/lit style when deserializing arrays */
				return ret;
			}			
		}
		else
		{
			/* error: unexpected element */
		}
	}
	m_nStatus = AXIS_FAIL; /* unexpected SOAP stream */
	return ret;
}

short SoapDeSerializer::GetElementAsShort(const AxisChar* pName, const AxisChar* pNamespace)
{
	short ret = 0;
	if (AXIS_SUCCESS != m_nStatus) return ret;
	if (RPC_ENCODED == m_nStyle)
	{
		m_pNode = m_pParser->Next(); /* wrapper node with type info  Ex: <i xsi:type="xsd:int">*/ 
		if (XSD_SHORT == GetXSDType(m_pNode))
		{
			m_pNode = m_pParser->Next(); /* charactor node */
			if (m_pNode && (CHARACTER_ELEMENT == m_pNode->m_type))
			{
				ret = strtol(m_pNode->m_pchNameOrValue, &m_pEndptr, 10);
				m_pNode = m_pParser->Next(); /* skip end element node too */
				return ret;
			}
		}
		else
		{
			/* it is an error if type is different or not present */
		}
	}
	else
	{
		if (!m_pNode) /* if there is an unprocessed node that may be one left from last array deserialization */ 
			m_pNode = m_pParser->Next(); /* wrapper node without type info  Ex: <i>*/
		if (0 == strcmp(pName, m_pNode->m_pchNameOrValue))
		{
			m_pNode = m_pParser->Next(); /* charactor node */
			if (m_pNode && (CHARACTER_ELEMENT == m_pNode->m_type))
			{
				ret = strtol(m_pNode->m_pchNameOrValue, &m_pEndptr, 10);
				m_pNode = m_pParser->Next(); /* skip end element node too */
				m_pNode = NULL; /* this is important in doc/lit style when deserializing arrays */
				return ret;
			}			
		}
		else
		{
			/* error: unexpected element */
		}
	}
	m_nStatus = AXIS_FAIL; /* unexpected SOAP stream */
	return ret;
}

unsigned short SoapDeSerializer::GetElementAsUnsignedShort(const AxisChar* pName, const AxisChar* pNamespace)
{
	unsigned short ret = 0;
	if (AXIS_SUCCESS != m_nStatus) return ret;
	if (RPC_ENCODED == m_nStyle)
	{
		m_pNode = m_pParser->Next(); /* wrapper node with type info  Ex: <i xsi:type="xsd:int">*/ 
		if (XSD_UNSIGNEDSHORT == GetXSDType(m_pNode))
		{
			m_pNode = m_pParser->Next(); /* charactor node */
			if (m_pNode && (CHARACTER_ELEMENT == m_pNode->m_type))
			{
				ret = strtoul(m_pNode->m_pchNameOrValue, &m_pEndptr, 10);
				m_pNode = m_pParser->Next(); /* skip end element node too */
				return ret;
			}
		}
		else
		{
			/* it is an error if type is different or not present */
		}
	}
	else
	{
		if (!m_pNode) /* if there is an unprocessed node that may be one left from last array deserialization */ 
			m_pNode = m_pParser->Next(); /* wrapper node without type info  Ex: <i>*/
		if (0 == strcmp(pName, m_pNode->m_pchNameOrValue))
		{
			m_pNode = m_pParser->Next(); /* charactor node */
			if (m_pNode && (CHARACTER_ELEMENT == m_pNode->m_type))
			{
				ret = strtoul(m_pNode->m_pchNameOrValue, &m_pEndptr, 10);
				m_pNode = m_pParser->Next(); /* skip end element node too */
				m_pNode = NULL; /* this is important in doc/lit style when deserializing arrays */
				return ret;
			}			
		}
		else
		{
			/* error: unexpected element */
		}
	}
	m_nStatus = AXIS_FAIL; /* unexpected SOAP stream */
	return ret;
}

char SoapDeSerializer::GetElementAsByte(const AxisChar* pName, const AxisChar* pNamespace)
{
	char ret = 0;
	if (AXIS_SUCCESS != m_nStatus) return ret;
	if (RPC_ENCODED == m_nStyle)
	{
		m_pNode = m_pParser->Next(); /* wrapper node with type info  Ex: <i xsi:type="xsd:int">*/ 
		if (XSD_BYTE == GetXSDType(m_pNode))
		{
			m_pNode = m_pParser->Next(); /* charactor node */
			if (m_pNode && (CHARACTER_ELEMENT == m_pNode->m_type))
			{
				ret = strtol(m_pNode->m_pchNameOrValue, &m_pEndptr, 10);
				m_pNode = m_pParser->Next(); /* skip end element node too */
				return ret;
			}
		}
		else
		{
			/* it is an error if type is different or not present */
		}
	}
	else
	{
		if (!m_pNode) /* if there is an unprocessed node that may be one left from last array deserialization */ 
			m_pNode = m_pParser->Next(); /* wrapper node without type info  Ex: <i>*/
		if (0 == strcmp(pName, m_pNode->m_pchNameOrValue))
		{
			m_pNode = m_pParser->Next(); /* charactor node */
			if (m_pNode && (CHARACTER_ELEMENT == m_pNode->m_type))
			{
				ret = strtol(m_pNode->m_pchNameOrValue, &m_pEndptr, 10);
				m_pNode = m_pParser->Next(); /* skip end element node too */
				m_pNode = NULL; /* this is important in doc/lit style when deserializing arrays */
				return ret;
			}			
		}
		else
		{
			/* error: unexpected element */
		}
	}
	m_nStatus = AXIS_FAIL; /* unexpected SOAP stream */
	return ret;
}

unsigned char SoapDeSerializer::GetElementAsUnsignedByte(const AxisChar* pName, const AxisChar* pNamespace)
{
	unsigned char ret = 0;
	if (AXIS_SUCCESS != m_nStatus) return ret;
	if (RPC_ENCODED == m_nStyle)
	{
		m_pNode = m_pParser->Next(); /* wrapper node with type info  Ex: <i xsi:type="xsd:int">*/ 
		if (XSD_UNSIGNEDBYTE == GetXSDType(m_pNode))
		{
			m_pNode = m_pParser->Next(); /* charactor node */
			if (m_pNode && (CHARACTER_ELEMENT == m_pNode->m_type))
			{
				ret = strtoul(m_pNode->m_pchNameOrValue, &m_pEndptr, 10);
				m_pNode = m_pParser->Next(); /* skip end element node too */
				return ret;
			}
		}
		else
		{
			/* it is an error if type is different or not present */
		}
	}
	else
	{
		if (!m_pNode) /* if there is an unprocessed node that may be one left from last array deserialization */ 
			m_pNode = m_pParser->Next(); /* wrapper node without type info  Ex: <i>*/
		if (0 == strcmp(pName, m_pNode->m_pchNameOrValue))
		{
			m_pNode = m_pParser->Next(); /* charactor node */
			if (m_pNode && (CHARACTER_ELEMENT == m_pNode->m_type))
			{
				ret = strtoul(m_pNode->m_pchNameOrValue, &m_pEndptr, 10);
				m_pNode = m_pParser->Next(); /* skip end element node too */
				m_pNode = NULL; /* this is important in doc/lit style when deserializing arrays */
				return ret;
			}			
		}
		else
		{
			/* error: unexpected element */
		}
	}
	m_nStatus = AXIS_FAIL; /* unexpected SOAP stream */
	return ret;
}

long SoapDeSerializer::GetElementAsLong(const AxisChar* pName, const AxisChar* pNamespace)
{
	long ret = 0;
	if (AXIS_SUCCESS != m_nStatus) return ret;
	if (RPC_ENCODED == m_nStyle)
	{
		m_pNode = m_pParser->Next(); /* wrapper node with type info  Ex: <i xsi:type="xsd:int">*/ 
		if (XSD_LONG == GetXSDType(m_pNode))
		{
			m_pNode = m_pParser->Next(); /* charactor node */
			if (m_pNode && (CHARACTER_ELEMENT == m_pNode->m_type))
			{
				ret = strtol(m_pNode->m_pchNameOrValue, &m_pEndptr, 10);
				m_pNode = m_pParser->Next(); /* skip end element node too */
				return ret;
			}
		}
		else
		{
			/* it is an error if type is different or not present */
		}
	}
	else
	{
		if (!m_pNode) /* if there is an unprocessed node that may be one left from last array deserialization */ 
			m_pNode = m_pParser->Next(); /* wrapper node without type info  Ex: <i>*/
		if (0 == strcmp(pName, m_pNode->m_pchNameOrValue))
		{
			m_pNode = m_pParser->Next(); /* charactor node */
			if (m_pNode && (CHARACTER_ELEMENT == m_pNode->m_type))
			{
				ret = strtol(m_pNode->m_pchNameOrValue, &m_pEndptr, 10);
				m_pNode = m_pParser->Next(); /* skip end element node too */
				m_pNode = NULL; /* this is important in doc/lit style when deserializing arrays */
				return ret;
			}			
		}
		else
		{
			/* error: unexpected element */
		}
	}
	m_nStatus = AXIS_FAIL; /* unexpected SOAP stream */
	return ret;
}

long SoapDeSerializer::GetElementAsInteger(const AxisChar* pName, const AxisChar* pNamespace)
{
	long ret = 0;
	if (AXIS_SUCCESS != m_nStatus) return ret;
	if (RPC_ENCODED == m_nStyle)
	{
		m_pNode = m_pParser->Next(); /* wrapper node with type info  Ex: <i xsi:type="xsd:int">*/ 
		if (XSD_INTEGER == GetXSDType(m_pNode))
		{
			m_pNode = m_pParser->Next(); /* charactor node */
			if (m_pNode && (CHARACTER_ELEMENT == m_pNode->m_type))
			{
				ret = strtol(m_pNode->m_pchNameOrValue, &m_pEndptr, 10);
				m_pNode = m_pParser->Next(); /* skip end element node too */
				return ret;
			}
		}
		else
		{
			/* it is an error if type is different or not present */
		}
	}
	else
	{
		if (!m_pNode) /* if there is an unprocessed node that may be one left from last array deserialization */ 
			m_pNode = m_pParser->Next(); /* wrapper node without type info  Ex: <i>*/
		if (0 == strcmp(pName, m_pNode->m_pchNameOrValue))
		{
			m_pNode = m_pParser->Next(); /* charactor node */
			if (m_pNode && (CHARACTER_ELEMENT == m_pNode->m_type))
			{
				ret = strtol(m_pNode->m_pchNameOrValue, &m_pEndptr, 10);
				m_pNode = m_pParser->Next(); /* skip end element node too */
				m_pNode = NULL; /* this is important in doc/lit style when deserializing arrays */
				return ret;
			}			
		}
		else
		{
			/* error: unexpected element */
		}
	}
	m_nStatus = AXIS_FAIL; /* unexpected SOAP stream */
	return ret;
}

unsigned long SoapDeSerializer::GetElementAsUnsignedLong(const AxisChar* pName, const AxisChar* pNamespace)
{
	unsigned long ret = 0;
	if (AXIS_SUCCESS != m_nStatus) return ret;
	if (RPC_ENCODED == m_nStyle)
	{
		m_pNode = m_pParser->Next(); /* wrapper node with type info  Ex: <i xsi:type="xsd:int">*/ 
		if (XSD_UNSIGNEDLONG == GetXSDType(m_pNode))
		{
			m_pNode = m_pParser->Next(); /* charactor node */
			if (m_pNode && (CHARACTER_ELEMENT == m_pNode->m_type))
			{
				ret = strtoul(m_pNode->m_pchNameOrValue, &m_pEndptr, 10);
				m_pNode = m_pParser->Next(); /* skip end element node too */
				return ret;
			}
		}
		else
		{
			/* it is an error if type is different or not present */
		}
	}
	else
	{
		if (!m_pNode) /* if there is an unprocessed node that may be one left from last array deserialization */ 
			m_pNode = m_pParser->Next(); /* wrapper node without type info  Ex: <i>*/
		if (0 == strcmp(pName, m_pNode->m_pchNameOrValue))
		{
			m_pNode = m_pParser->Next(); /* charactor node */
			if (m_pNode && (CHARACTER_ELEMENT == m_pNode->m_type))
			{
				ret = strtoul(m_pNode->m_pchNameOrValue, &m_pEndptr, 10);
				m_pNode = m_pParser->Next(); /* skip end element node too */
				m_pNode = NULL; /* this is important in doc/lit style when deserializing arrays */
				return ret;
			}			
		}
		else
		{
			/* error: unexpected element */
		}
	}
	m_nStatus = AXIS_FAIL; /* unexpected SOAP stream */
	return ret;
}

float SoapDeSerializer::GetElementAsFloat(const AxisChar* pName, const AxisChar* pNamespace)
{
	float ret = 0;
	if (AXIS_SUCCESS != m_nStatus) return ret;
	if (RPC_ENCODED == m_nStyle)
	{
		m_pNode = m_pParser->Next(); /* wrapper node with type info  Ex: <i xsi:type="xsd:int">*/ 
		if (XSD_FLOAT == GetXSDType(m_pNode))
		{
			m_pNode = m_pParser->Next(); /* charactor node */
			if (m_pNode && (CHARACTER_ELEMENT == m_pNode->m_type))
			{
				ret = strtod(m_pNode->m_pchNameOrValue, &m_pEndptr);
				m_pNode = m_pParser->Next(); /* skip end element node too */
				return ret;
			}
		}
		else
		{
			/* it is an error if type is different or not present */
		}
	}
	else
	{
		if (!m_pNode) /* if there is an unprocessed node that may be one left from last array deserialization */ 
			m_pNode = m_pParser->Next(); /* wrapper node without type info  Ex: <i>*/
		if (0 == strcmp(pName, m_pNode->m_pchNameOrValue))
		{
			m_pNode = m_pParser->Next(); /* charactor node */
			if (m_pNode && (CHARACTER_ELEMENT == m_pNode->m_type))
			{
				ret = strtod(m_pNode->m_pchNameOrValue, &m_pEndptr);
				m_pNode = m_pParser->Next(); /* skip end element node too */
				m_pNode = NULL; /* this is important in doc/lit style when deserializing arrays */
				return ret;
			}			
		}
		else
		{
			/* error: unexpected element */
		}
	}
	m_nStatus = AXIS_FAIL; /* unexpected SOAP stream */
	return ret;
}

double SoapDeSerializer::GetElementAsDouble(const AxisChar* pName, const AxisChar* pNamespace)
{
	double ret = 0;
	if (AXIS_SUCCESS != m_nStatus) return ret;
	if (RPC_ENCODED == m_nStyle)
	{
		m_pNode = m_pParser->Next(); /* wrapper node with type info  Ex: <i xsi:type="xsd:int">*/ 
		if (XSD_DOUBLE == GetXSDType(m_pNode))
		{
			m_pNode = m_pParser->Next(); /* charactor node */
			if (m_pNode && (CHARACTER_ELEMENT == m_pNode->m_type))
			{
				ret = strtod(m_pNode->m_pchNameOrValue, &m_pEndptr);
				m_pNode = m_pParser->Next(); /* skip end element node too */
				return ret;
			}
		}
		else
		{
			/* it is an error if type is different or not present */
		}
	}
	else
	{
		if (!m_pNode) /* if there is an unprocessed node that may be one left from last array deserialization */ 
			m_pNode = m_pParser->Next(); /* wrapper node without type info  Ex: <i>*/
		if (0 == strcmp(pName, m_pNode->m_pchNameOrValue))
		{
			m_pNode = m_pParser->Next(); /* charactor node */
			if (m_pNode && (CHARACTER_ELEMENT == m_pNode->m_type))
			{
				ret = strtod(m_pNode->m_pchNameOrValue, &m_pEndptr);
				m_pNode = m_pParser->Next(); /* skip end element node too */
				m_pNode = NULL; /* this is important in doc/lit style when deserializing arrays */
				return ret;
			}			
		}
		else
		{
			/* error: unexpected element */
		}
	}
	m_nStatus = AXIS_FAIL; /* unexpected SOAP stream */
	return ret;
}

double SoapDeSerializer::GetElementAsDecimal(const AxisChar* pName, const AxisChar* pNamespace)
{
	double ret = 0;
	if (AXIS_SUCCESS != m_nStatus) return ret;
	if (RPC_ENCODED == m_nStyle)
	{
		m_pNode = m_pParser->Next(); /* wrapper node with type info  Ex: <i xsi:type="xsd:int">*/ 
		if (XSD_DECIMAL == GetXSDType(m_pNode))
		{
			m_pNode = m_pParser->Next(); /* charactor node */
			if (m_pNode && (CHARACTER_ELEMENT == m_pNode->m_type))
			{
				ret = strtod(m_pNode->m_pchNameOrValue, &m_pEndptr);
				m_pNode = m_pParser->Next(); /* skip end element node too */
				return ret;
			}
		}
		else
		{
			/* it is an error if type is different or not present */
		}
	}
	else
	{
		if (!m_pNode) /* if there is an unprocessed node that may be one left from last array deserialization */ 
			m_pNode = m_pParser->Next(); /* wrapper node without type info  Ex: <i>*/
		if (0 == strcmp(pName, m_pNode->m_pchNameOrValue))
		{
			m_pNode = m_pParser->Next(); /* charactor node */
			if (m_pNode && (CHARACTER_ELEMENT == m_pNode->m_type))
			{
				ret = strtod(m_pNode->m_pchNameOrValue, &m_pEndptr);
				m_pNode = m_pParser->Next(); /* skip end element node too */
				m_pNode = NULL; /* this is important in doc/lit style when deserializing arrays */
				return ret;
			}			
		}
		else
		{
			/* error: unexpected element */
		}
	}
	m_nStatus = AXIS_FAIL; /* unexpected SOAP stream */
	return ret;
}

AxisChar* SoapDeSerializer::GetElementAsString(const AxisChar* pName, const AxisChar* pNamespace)
{
	AxisChar* ret = 0;
	if (AXIS_SUCCESS != m_nStatus) return ret;
	if (RPC_ENCODED == m_nStyle)
	{
		m_pNode = m_pParser->Next(); /* wrapper node with type info  Ex: <i xsi:type="xsd:int">*/ 
		if (XSD_STRING == GetXSDType(m_pNode))
		{
			m_pNode = m_pParser->Next(); /* charactor node */
			if (m_pNode && (CHARACTER_ELEMENT == m_pNode->m_type))
			{
				ret = strdup(m_pNode->m_pchNameOrValue); /* this is because the string may not be available later */
				m_pNode = m_pParser->Next(); /* skip end element node too */
				return ret;
			}
		}
		else
		{
			/* it is an error if type is different or not present */
		}
	}
	else
	{
		if (!m_pNode) /* if there is an unprocessed node that may be one left from last array deserialization */ 
			m_pNode = m_pParser->Next(); /* wrapper node without type info  Ex: <i>*/
		if (0 == strcmp(pName, m_pNode->m_pchNameOrValue))
		{
			m_pNode = m_pParser->Next(); /* charactor node */
			if (m_pNode && (CHARACTER_ELEMENT == m_pNode->m_type))
			{
				ret = strdup(m_pNode->m_pchNameOrValue); /* this is because the string may not be available later */
				m_pNode = m_pParser->Next(); /* skip end element node too */
				m_pNode = NULL; /* this is important in doc/lit style when deserializing arrays */
				return ret;
			}			
		}
		else
		{
			/* error: unexpected element */
		}
	}
	m_nStatus = AXIS_FAIL; /* unexpected SOAP stream */
	return ret;
}

AxisChar* SoapDeSerializer::GetElementAsAnyURI(const AxisChar* pName, const AxisChar* pNamespace)
{
	AxisChar* ret = 0;
	if (AXIS_SUCCESS != m_nStatus) return ret;
	if (RPC_ENCODED == m_nStyle)
	{
		m_pNode = m_pParser->Next(); /* wrapper node with type info  Ex: <i xsi:type="xsd:int">*/ 
		if (XSD_ANYURI == GetXSDType(m_pNode))
		{
			m_pNode = m_pParser->Next(); /* charactor node */
			if (m_pNode && (CHARACTER_ELEMENT == m_pNode->m_type))
			{
				ret = strdup(m_pNode->m_pchNameOrValue); /* this is because the string may not be available later */
				m_pNode = m_pParser->Next(); /* skip end element node too */
				return ret;
			}
		}
		else
		{
			/* it is an error if type is different or not present */
		}
	}
	else
	{
		if (!m_pNode) /* if there is an unprocessed node that may be one left from last array deserialization */ 
			m_pNode = m_pParser->Next(); /* wrapper node without type info  Ex: <i>*/
		if (0 == strcmp(pName, m_pNode->m_pchNameOrValue))
		{
			m_pNode = m_pParser->Next(); /* charactor node */
			if (m_pNode && (CHARACTER_ELEMENT == m_pNode->m_type))
			{
				ret = strdup(m_pNode->m_pchNameOrValue); /* this is because the string may not be available later */
				m_pNode = m_pParser->Next(); /* skip end element node too */
				m_pNode = NULL; /* this is important in doc/lit style when deserializing arrays */
				return ret;
			}			
		}
		else
		{
			/* error: unexpected element */
		}
	}
	m_nStatus = AXIS_FAIL; /* unexpected SOAP stream */
	return ret;
}

AxisChar* SoapDeSerializer::GetElementAsQName(const AxisChar* pName, const AxisChar* pNamespace)
{
	AxisChar* ret = 0;
	if (AXIS_SUCCESS != m_nStatus) return ret;
	if (RPC_ENCODED == m_nStyle)
	{
		m_pNode = m_pParser->Next(); /* wrapper node with type info  Ex: <i xsi:type="xsd:int">*/ 
		if (XSD_QNAME == GetXSDType(m_pNode))
		{
			m_pNode = m_pParser->Next(); /* charactor node */
			if (m_pNode && (CHARACTER_ELEMENT == m_pNode->m_type))
			{
				ret = strdup(m_pNode->m_pchNameOrValue); /* this is because the string may not be available later */
				m_pNode = m_pParser->Next(); /* skip end element node too */
				return ret;
			}
		}
		else
		{
			/* it is an error if type is different or not present */
		}
	}
	else
	{
		if (!m_pNode) /* if there is an unprocessed node that may be one left from last array deserialization */ 
			m_pNode = m_pParser->Next(); /* wrapper node without type info  Ex: <i>*/
		if (0 == strcmp(pName, m_pNode->m_pchNameOrValue))
		{
			m_pNode = m_pParser->Next(); /* charactor node */
			if (m_pNode && (CHARACTER_ELEMENT == m_pNode->m_type))
			{
				ret = strdup(m_pNode->m_pchNameOrValue); /* this is because the string may not be available later */
				m_pNode = m_pParser->Next(); /* skip end element node too */
				m_pNode = NULL; /* this is important in doc/lit style when deserializing arrays */
				return ret;
			}			
		}
		else
		{
			/* error: unexpected element */
		}
	}
	m_nStatus = AXIS_FAIL; /* unexpected SOAP stream */
	return ret;
}

xsd__hexBinary SoapDeSerializer::GetElementAsHexBinary(const AxisChar* pName, const AxisChar* pNamespace)
{
	xsd__hexBinary ret = {0,0};
	if (AXIS_SUCCESS != m_nStatus) return ret;
	if (RPC_ENCODED == m_nStyle)
	{
		m_pNode = m_pParser->Next(); /* wrapper node with type info  Ex: <i xsi:type="xsd:int">*/ 
		if (XSD_HEXBINARY == GetXSDType(m_pNode))
		{
			m_pNode = m_pParser->Next(); /* charactor node */
			if (m_pNode && (CHARACTER_ELEMENT == m_pNode->m_type))
			{
				ret = DecodeFromHexBinary(m_pNode->m_pchNameOrValue); /* this is because the string may not be available later */
				m_pNode = m_pParser->Next(); /* skip end element node too */
				return ret;
			}
		}
		else
		{
			/* it is an error if type is different or not present */
		}
	}
	else
	{
		if (!m_pNode) /* if there is an unprocessed node that may be one left from last array deserialization */ 
			m_pNode = m_pParser->Next(); /* wrapper node without type info  Ex: <i>*/
		if (0 == strcmp(pName, m_pNode->m_pchNameOrValue))
		{
			m_pNode = m_pParser->Next(); /* charactor node */
			if (m_pNode && (CHARACTER_ELEMENT == m_pNode->m_type))
			{
				ret = DecodeFromHexBinary(m_pNode->m_pchNameOrValue); /* this is because the string may not be available later */
				m_pNode = m_pParser->Next(); /* skip end element node too */
				m_pNode = NULL; /* this is important in doc/lit style when deserializing arrays */
				return ret;
			}			
		}
		else
		{
			/* error: unexpected element */
		}
	}
	m_nStatus = AXIS_FAIL; /* unexpected SOAP stream */
	return ret;
}

xsd__base64Binary SoapDeSerializer::DecodeFromBase64Binary(const AxisChar* pValue)
{
	xsd__base64Binary value;
	value.__ptr = NULL; /*TODO : allocate memory and decode value and put size */
	value.__size = 0;
	return value;
}

xsd__hexBinary SoapDeSerializer::DecodeFromHexBinary(const AxisChar* pValue)
{
	xsd__hexBinary value;
	value.__ptr = NULL; /*TODO : allocate memory and decode value and put size */
	value.__size = 0;
	return value;
}

xsd__base64Binary SoapDeSerializer::GetElementAsBase64Binary(const AxisChar* pName, const AxisChar* pNamespace)
{
	xsd__base64Binary ret = {0,0};
	if (AXIS_SUCCESS != m_nStatus) return ret;
	if (RPC_ENCODED == m_nStyle)
	{
		m_pNode = m_pParser->Next(); /* wrapper node with type info  Ex: <i xsi:type="xsd:int">*/ 
		if (XSD_BASE64BINARY == GetXSDType(m_pNode))
		{
			m_pNode = m_pParser->Next(); /* charactor node */
			if (m_pNode && (CHARACTER_ELEMENT == m_pNode->m_type))
			{
				ret = DecodeFromBase64Binary(m_pNode->m_pchNameOrValue); /* this is because the string may not be available later */
				m_pNode = m_pParser->Next(); /* skip end element node too */
				return ret;
			}
		}
		else
		{
			/* it is an error if type is different or not present */
		}
	}
	else
	{
		if (!m_pNode) /* if there is an unprocessed node that may be one left from last array deserialization */ 
			m_pNode = m_pParser->Next(); /* wrapper node without type info  Ex: <i>*/
		if (0 == strcmp(pName, m_pNode->m_pchNameOrValue))
		{
			m_pNode = m_pParser->Next(); /* charactor node */
			if (m_pNode && (CHARACTER_ELEMENT == m_pNode->m_type))
			{
				ret = DecodeFromBase64Binary(m_pNode->m_pchNameOrValue); /* this is because the string may not be available later */
				m_pNode = m_pParser->Next(); /* skip end element node too */
				m_pNode = NULL; /* this is important in doc/lit style when deserializing arrays */
				return ret;
			}			
		}
		else
		{
			/* error: unexpected element */
		}
	}
	m_nStatus = AXIS_FAIL; /* unexpected SOAP stream */
	return ret;
}

struct tm SoapDeSerializer::GetElementAsDateTime(const AxisChar* pName, const AxisChar* pNamespace)
{
	struct tm ret;
	if (AXIS_SUCCESS != m_nStatus) return ret;
	if (RPC_ENCODED == m_nStyle)
	{
		m_pNode = m_pParser->Next(); /* wrapper node with type info  Ex: <i xsi:type="xsd:int">*/ 
		if (XSD_DATETIME == GetXSDType(m_pNode))
		{
			m_pNode = m_pParser->Next(); /* charactor node */
			if (m_pNode && (CHARACTER_ELEMENT == m_pNode->m_type))
			{
				ret = AxisTime::Deserialize(m_pNode->m_pchNameOrValue, XSD_DATETIME);
				m_pNode = m_pParser->Next(); /* skip end element node too */
				return ret;
			}
		}
		else
		{
			/* it is an error if type is different or not present */
		}
	}
	else
	{
		if (!m_pNode) /* if there is an unprocessed node that may be one left from last array deserialization */ 
			m_pNode = m_pParser->Next(); /* wrapper node without type info  Ex: <i>*/
		if (0 == strcmp(pName, m_pNode->m_pchNameOrValue))
		{
			m_pNode = m_pParser->Next(); /* charactor node */
			if (m_pNode && (CHARACTER_ELEMENT == m_pNode->m_type))
			{
				ret = AxisTime::Deserialize(m_pNode->m_pchNameOrValue, XSD_DATETIME);
				m_pNode = m_pParser->Next(); /* skip end element node too */
				m_pNode = NULL; /* this is important in doc/lit style when deserializing arrays */
				return ret;
			}			
		}
		else
		{
			/* error: unexpected element */
		}
	}
	m_nStatus = AXIS_FAIL; /* unexpected SOAP stream */
	return ret;
}

struct tm SoapDeSerializer::GetElementAsDate(const AxisChar* pName, const AxisChar* pNamespace)
{
	struct tm ret;
	if (AXIS_SUCCESS != m_nStatus) return ret;
	if (RPC_ENCODED == m_nStyle)
	{
		m_pNode = m_pParser->Next(); /* wrapper node with type info  Ex: <i xsi:type="xsd:int">*/ 
		if (XSD_DATE == GetXSDType(m_pNode))
		{
			m_pNode = m_pParser->Next(); /* charactor node */
			if (m_pNode && (CHARACTER_ELEMENT == m_pNode->m_type))
			{
				ret = AxisTime::Deserialize(m_pNode->m_pchNameOrValue, XSD_DATE);
				m_pNode = m_pParser->Next(); /* skip end element node too */
				return ret;
			}
		}
		else
		{
			/* it is an error if type is different or not present */
		}
	}
	else
	{
		if (!m_pNode) /* if there is an unprocessed node that may be one left from last array deserialization */ 
			m_pNode = m_pParser->Next(); /* wrapper node without type info  Ex: <i>*/
		if (0 == strcmp(pName, m_pNode->m_pchNameOrValue))
		{
			m_pNode = m_pParser->Next(); /* charactor node */
			if (m_pNode && (CHARACTER_ELEMENT == m_pNode->m_type))
			{
				ret = AxisTime::Deserialize(m_pNode->m_pchNameOrValue, XSD_DATE);
				m_pNode = m_pParser->Next(); /* skip end element node too */
				m_pNode = NULL; /* this is important in doc/lit style when deserializing arrays */
				return ret;
			}			
		}
		else
		{
			/* error: unexpected element */
		}
	}
	m_nStatus = AXIS_FAIL; /* unexpected SOAP stream */
	return ret;
}

struct tm SoapDeSerializer::GetElementAsTime(const AxisChar* pName, const AxisChar* pNamespace)
{
	struct tm ret;
	if (AXIS_SUCCESS != m_nStatus) return ret;
	if (RPC_ENCODED == m_nStyle)
	{
		m_pNode = m_pParser->Next(); /* wrapper node with type info  Ex: <i xsi:type="xsd:int">*/ 
		if (XSD_TIME == GetXSDType(m_pNode))
		{
			m_pNode = m_pParser->Next(); /* charactor node */
			if (m_pNode && (CHARACTER_ELEMENT == m_pNode->m_type))
			{
				ret = AxisTime::Deserialize(m_pNode->m_pchNameOrValue, XSD_TIME);
				m_pNode = m_pParser->Next(); /* skip end element node too */
				return ret;
			}
		}
		else
		{
			/* it is an error if type is different or not present */
		}
	}
	else
	{
		if (!m_pNode) /* if there is an unprocessed node that may be one left from last array deserialization */ 
			m_pNode = m_pParser->Next(); /* wrapper node without type info  Ex: <i>*/
		if (0 == strcmp(pName, m_pNode->m_pchNameOrValue))
		{
			m_pNode = m_pParser->Next(); /* charactor node */
			if (m_pNode && (CHARACTER_ELEMENT == m_pNode->m_type))
			{
				ret = AxisTime::Deserialize(m_pNode->m_pchNameOrValue, XSD_TIME);
				m_pNode = m_pParser->Next(); /* skip end element node too */
				m_pNode = NULL; /* this is important in doc/lit style when deserializing arrays */
				return ret;
			}			
		}
		else
		{
			/* error: unexpected element */
		}
	}
	m_nStatus = AXIS_FAIL; /* unexpected SOAP stream */
	return ret;
}

long SoapDeSerializer::GetElementAsDuration(const AxisChar* pName, const AxisChar* pNamespace)
{
	long ret = 0;
	if (AXIS_SUCCESS != m_nStatus) return ret;
	if (RPC_ENCODED == m_nStyle)
	{
		m_pNode = m_pParser->Next(); /* wrapper node with type info  Ex: <i xsi:type="xsd:int">*/ 
		if (XSD_DURATION == GetXSDType(m_pNode))
		{
			m_pNode = m_pParser->Next(); /* charactor node */
			if (m_pNode && (CHARACTER_ELEMENT == m_pNode->m_type))
			{
				ret = AxisTime::DeserializeDuration(m_pNode->m_pchNameOrValue, XSD_DURATION);
				m_pNode = m_pParser->Next(); /* skip end element node too */
				return ret;
			}
		}
		else
		{
			/* it is an error if type is different or not present */
		}
	}
	else
	{
		if (!m_pNode) /* if there is an unprocessed node that may be one left from last array deserialization */ 
			m_pNode = m_pParser->Next(); /* wrapper node without type info  Ex: <i>*/
		if (0 == strcmp(pName, m_pNode->m_pchNameOrValue))
		{
			m_pNode = m_pParser->Next(); /* charactor node */
			if (m_pNode && (CHARACTER_ELEMENT == m_pNode->m_type))
			{
				ret = AxisTime::DeserializeDuration(m_pNode->m_pchNameOrValue, XSD_DURATION);
				m_pNode = m_pParser->Next(); /* skip end element node too */
				m_pNode = NULL; /* this is important in doc/lit style when deserializing arrays */
				return ret;
			}			
		}
		else
		{
			/* error: unexpected element */
		}
	}
	m_nStatus = AXIS_FAIL; /* unexpected SOAP stream */
	return ret;
}

/**
 * This method checks the attribute list of pElement node for the xsi:type attribute.
 * if it is found then finds what the type is. Otherwise returns XSD_UNKNOWN.
 */
XSDTYPE SoapDeSerializer::GetXSDType(const AnyElement* pElement)
{
	/* first check whether this is a start element node */
	if (START_ELEMENT != pElement->m_type) return XSD_UNKNOWN;
	for (int i=0; pElement->m_pchAttributes[i]; i+=3)
	{
		if (URI_XSI == URIMapping::Map(pElement->m_pchAttributes[i+1]))
		{
			QName qn;
			XSDTYPE type = XSD_UNKNOWN;
			qn.SplitQNameString(pElement->m_pchAttributes[i+2], ':');
			const char* pNS = m_pParser->GetNS4Prefix(qn.uri);
			if (pNS)
			{
				if (URI_XSD == URIMapping::Map(pNS))
				{
					type = TypeMapping::Map(qn.localname);
				}
			}
			qn.MergeQNameString(':');
			return type;
		}
	}
	return XSD_UNKNOWN;
}

void* SoapDeSerializer::CreateArray(XSDTYPE nType, int nSize)
{
	switch (nType)
	{
	case XSD_INT:
	case XSD_UNSIGNEDINT:
	case XSD_BOOLEAN:
		return new xsd__boolean[nSize];
	case XSD_FLOAT:
		return new float[nSize];
	case XSD_STRING:
	case XSD_HEXBINARY:
	case XSD_BASE64BINARY:
	case XSD_ANYURI:
	case XSD_QNAME:
	case XSD_NOTATION:
		return new AxisString[nSize];
	case XSD_LONG:
	case XSD_UNSIGNEDLONG:
	case XSD_INTEGER:
	case XSD_DURATION:
		return new long[nSize];
	case XSD_SHORT:
	case XSD_UNSIGNEDSHORT:
		return new short[nSize];
	case XSD_BYTE:
	case XSD_UNSIGNEDBYTE:
		return new char[nSize];
	case XSD_DOUBLE:
	case XSD_DECIMAL:
		return new double[nSize];
	case XSD_DATETIME:
	case XSD_TIME:
	case XSD_DATE:
	case XSD_YEARMONTH:
	case XSD_YEAR:
	case XSD_MONTHDAY:
	case XSD_DAY:
	case XSD_MONTH:
		return new tm[nSize];
	default:
		return NULL;
	}
}

void SoapDeSerializer::DeleteArray(Axis_Array* pArray , XSDTYPE nType)
{
	switch (nType)
	{
	case XSD_INT:
	case XSD_UNSIGNEDINT:
	case XSD_BOOLEAN:
		delete [] ((int*)pArray->m_Array); break;
	case XSD_FLOAT:
		delete [] ((float*)pArray->m_Array); break;
	case XSD_STRING:
	case XSD_HEXBINARY:
	case XSD_BASE64BINARY:
	case XSD_ANYURI:
	case XSD_QNAME:
	case XSD_NOTATION:
		delete [] ((AxisString*)pArray->m_Array); break;
	case XSD_LONG:
	case XSD_UNSIGNEDLONG:
	case XSD_INTEGER:
	case XSD_DURATION:
		delete [] ((long*)pArray->m_Array); break;
	case XSD_SHORT:
	case XSD_UNSIGNEDSHORT:
		delete [] ((short*)pArray->m_Array); break;
	case XSD_BYTE:
	case XSD_UNSIGNEDBYTE:
		delete [] ((char*)pArray->m_Array); break;
	case XSD_DOUBLE:
	case XSD_DECIMAL:
		delete [] ((double*)pArray->m_Array); break;
	case XSD_DATETIME:
	case XSD_TIME:
	case XSD_DATE:
	case XSD_YEARMONTH:
	case XSD_YEAR:
	case XSD_MONTHDAY:
	case XSD_DAY:
	case XSD_MONTH:
		delete [] ((tm*)pArray->m_Array); break;
	default:
		break;
	}
	pArray->m_Array = NULL;
	pArray->m_Size = 0;
}
