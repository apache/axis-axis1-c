/*
 *   Copyright 2003-2004 The Apache Software Foundation.
 *
 *   Licensed under the Apache License, Version 2.0 (the "License");
 *   you may not use this file except in compliance with the License.
 *   You may obtain a copy of the License at
 *
 *       http://www.apache.org/licenses/LICENSE-2.0
 *
 *   Unless required by applicable law or agreed to in writing, software
 *   distributed under the License is distributed on an "AS IS" BASIS,
 *   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *   See the License for the specific language governing permissions and
 *   limitations under the License.
 *
 * 
 * @author Sanjaya Singharage (sanjayas@opensource.lk)
 * @author Susantha Kumara (susantha@opensource.lk, skumara@virtusa.com)
 * @author Samisa Abeysinghe (sabeysinghe@virtusa.com)
 *
 */

/*
 * Revision 1.1  2004/05/31 samisa
 * Added setProxy
 */

/*
 * Revision 1.2  2005/01/06 Roshan
 * Added IHeaderBlock* Call::createHeaderBlock(AxisChar* pachLocalName, 
 *                                      AxisChar* pachUri, AxisChar* pachPrefix)
 */


#include <axis/client/Call.hpp>
#include <axis/AxisException.hpp>
#include "../../common/AxisConfig.h"
#include "ClientAxisEngine.h"
#include "../SOAPTransportFactory.h"
#include "../../transport/SOAPTransport.h"
#include "../../soap/SoapSerializer.h"
#include "../../soap/SoapDeSerializer.h"
#include "../../soap/HeaderBlock.h"

extern AXIS_CPP_NAMESPACE_PREFIX AxisConfig* g_pConfig;

extern "C" int initialize_module (int bServer);
extern "C" int uninitialize_module ();

extern bool g_bModuleInitialize;

AXIS_CPP_NAMESPACE_USE

bool CallBase::bInitialized = false;

Call::Call ()
:m_pcEndPointUri(NULL), m_strProxyHost(""), m_uiProxyPort(0), m_bUseProxy(false), m_bModuleInitialized(false)
{
    m_pAxisEngine = NULL;
    m_pIWSSZ = NULL;
    m_pIWSDZ = NULL;
    if (!g_bModuleInitialize)
    {
        initialize_module (0);
        m_bModuleInitialized = true;
    }
    
    m_pTransport = NULL;
    m_nTransportType = APTHTTP1_1;
    m_pTransport = SOAPTransportFactory::getTransportObject(m_nTransportType);
    m_nStatus = AXIS_SUCCESS;
    m_pchSessionID = NULL;
}

Call::~Call ()
{
	    SOAPTransportFactory::destroyTransportObject(m_pTransport);
		m_pTransport = NULL;
    if (m_bModuleInitialized)
        uninitialize_module();
    if (m_pcEndPointUri)
        delete [] m_pcEndPointUri;
}

int Call::setEndpointURI (const char* pchEndpointURI)
{
    if (m_pcEndPointUri)
        delete [] m_pcEndPointUri;
    m_pcEndPointUri = NULL;
    if (pchEndpointURI)
    {
        m_pcEndPointUri = new char[strlen(pchEndpointURI)+1];
        strcpy(m_pcEndPointUri, pchEndpointURI);
    }
    return AXIS_SUCCESS;
}

void Call::setOperation (const char* pchOperation, const char* pchNamespace)
{
    m_pIWSSZ->createSoapMethod (pchOperation, pchNamespace);
    m_pAxisEngine->getMessageData()->setOperationName(pchOperation);
}

void Call::addParameter (void* pValue, const char* pchName, XSDTYPE nType)
{
     m_nStatus = m_pIWSSZ->addOutputParam (pchName, pValue, nType);
}

/*
 * Method used to add arrays of basic types as parameters
 */
void Call::addBasicArrayParameter (Axis_Array* pArray, XSDTYPE nType,
    const AxisChar* pName)
{
    m_nStatus = m_pIWSSZ->addOutputBasicArrayParam (pArray, nType, pName);
}

void Call::addCmplxArrayParameter (Axis_Array* pArray, void* pSZFunct,
    void* pDelFunct, void* pSizeFunct, const AxisChar* pName, 
    const AxisChar* pNamespace)
{
     m_nStatus = m_pIWSSZ->addOutputCmplxArrayParam (pArray, pSZFunct, pDelFunct, pSizeFunct,
        pName, pNamespace);
}

void Call::addCmplxParameter (void* pObject, void* pSZFunct, void* pDelFunct,
    const AxisChar* pName, const AxisChar* pNamespace)
{
     m_nStatus = m_pIWSSZ->addOutputCmplxParam (pObject, pSZFunct, pDelFunct, pName,
        pNamespace);
}

int Call::invoke ()
{
        m_nStatus =  m_pAxisEngine->process(m_pTransport);

    return m_nStatus;
}

class HandlerProperty
{
public:
	HandlerProperty(AxisChar *n, void *v, int l) {name=n; value=v; len=l;}

	// The storage pointed at by name and value is not owned by HandlerProperty
	AxisChar *name;
	void *value;
	int len;
};

int Call::initialize(PROVIDERTYPE nStyle)
/* Does this mean that the stub that uses this Call object as well as all 
 * client side handlers have the same PROVIDERTYPE ? 
 */
{
    /* Initialize re-usable objects of this instance (objects may have been 
     * populated by the previous call.)
     */
    try
    {
        m_nStatus = AXIS_SUCCESS;
        // remove_headers(&m_Soap);
        if (AXIS_SUCCESS != openConnection ()) {
        	m_nStatus = AXIS_FAIL;
            return AXIS_FAIL;
        }
        if (m_pAxisEngine)
            delete m_pAxisEngine;
        m_pAxisEngine = new ClientAxisEngine ();
        if (!m_pAxisEngine) {
        	m_nStatus = AXIS_FAIL;
            return AXIS_FAIL;
        }
        if (AXIS_SUCCESS == m_pAxisEngine->initialize ())
        {
            MessageData *msgData = m_pAxisEngine->getMessageData ();
            if (msgData)
            {
				list<void*>::iterator it = m_handlerProperties.begin();
				while (it != m_handlerProperties.end())
				{
					HandlerProperty *pHp = (HandlerProperty*)(*it);
					msgData->setProperty(pHp->name, pHp->value, pHp->len);
					delete pHp;
					it++;
				}
				m_handlerProperties.clear();

                msgData->getSoapSerializer ((IWrapperSoapSerializer**) 
                    (&m_pIWSSZ));
                msgData->getSoapDeSerializer ((IWrapperSoapDeSerializer**) 
                    (&m_pIWSDZ));
                if (m_pIWSSZ && m_pIWSDZ)
                {
                    m_pIWSSZ->setCurrentProviderType (nStyle);
                    m_pIWSDZ->setCurrentProviderType (nStyle);
                    switch (nStyle)
                    {
                        case C_RPC_PROVIDER:
                        case CPP_RPC_PROVIDER:
                            m_pIWSSZ->setStyle (RPC_ENCODED);
                            m_pIWSDZ->setStyle (RPC_ENCODED);
                            break;
                        case C_DOC_PROVIDER:
                        case CPP_DOC_PROVIDER:
                            m_pIWSSZ->setStyle (DOC_LITERAL);
                            m_pIWSDZ->setStyle (DOC_LITERAL);
                            break;
                        case COM_PROVIDER:
                            // TODO: ??
                            break;
                        default:;
                                //TODO: ??
                    }
                    if(m_pchSessionID)
                    {
                        msgData->setProperty("sessionid", m_pchSessionID);
                    }
                    return AXIS_SUCCESS;
                }
            }
            m_nStatus = AXIS_FAIL;
            return AXIS_FAIL;
        }
        m_nStatus = AXIS_FAIL;        
        return AXIS_FAIL;
    }
    catch (AxisException& e)
    {
        e = e;
        /* printf(e.GetErr().c_str()); */
        m_nStatus = AXIS_FAIL;
        throw;
    }
    catch (...)
    {
        /* printf("Unknown exception occured in the client"); */
        m_nStatus = AXIS_FAIL;        
        throw;
    }
}

int Call::unInitialize ()
{
    if (m_pAxisEngine)
    {
		/* Initialization,serialization, invokation or check message success */
		if ( m_nStatus == AXIS_SUCCESS &&  m_pIWSDZ != NULL ) 
		{
			/* Test if deserialization failed */
			m_nStatus = m_pIWSDZ->getStatus();
		}
		MessageData *msgData = m_pAxisEngine->getMessageData();	
        AxisChar * pachTemp = (AxisChar *)msgData->getProperty("sessionid");
        int len = strlen(pachTemp);
        if ( len > 0 ) // Samisa: check if there is a session key
        {
            if (m_pchSessionID) // Samisa: deallocate before allocation
            {
                delete [] m_pchSessionID;
                m_pchSessionID = NULL;
            }
            m_pchSessionID = new char[len + 1];  // Samisa: should have space for terminating char
            strcpy(m_pchSessionID, pachTemp);
        }
        else //Samisa: there is no session key
        {
            if (m_pchSessionID) 
                delete [] m_pchSessionID;
            m_pchSessionID = NULL;
        }
        m_pAxisEngine->unInitialize ();
        delete m_pAxisEngine;
        m_pAxisEngine = NULL;
    }
    closeConnection ();
    return AXIS_SUCCESS;
}

int Call::setProtocol (AXIS_PROTOCOL_TYPE protocol)
{
    m_nTransportType = protocol;
    if (m_pTransport)
        m_pTransport->setProtocol(m_nTransportType);
    return AXIS_SUCCESS;
}

AXIS_PROTOCOL_TYPE Call::getProtocol ()
{
	return m_nTransportType;
}

int Call::setTransportProperty (AXIS_TRANSPORT_INFORMATION_TYPE type,
    const char* value)
{
    // Samisa - if SOAPAction is being set add extra "" to value
    if (type == SOAPACTION_HEADER)
    {
        char* tempvalue = new char[strlen(value) + 3];
        sprintf( tempvalue, "\"%s\"", value);
        m_pTransport->setTransportProperty(type, tempvalue);
        delete [] tempvalue;
    }
    else
        m_pTransport->setTransportProperty(type, value);
    return AXIS_SUCCESS;
}

int Call::setHandlerProperty(AxisChar* name, void* value, int len)
{
	// Unfortunately we have to cache the handler properties here
	// in the Call object since the m_pMsgData is not set up
	// until Call::initialize which doesn't happen until the actual
	// web service is invoked.
	m_handlerProperties.push_back(new HandlerProperty(name,value,len));
	return AXIS_SUCCESS;
}

/*
 * This method takes a look at the m_Soap structure and open 
 * transport layer connection to the server. Then this adds the 
 * relevant function pointers and streams to the m_Soap structure, 
 * which is given to the AxisEngine. AxisEngine can use those 
 * functions with those streams at any time it wants to send/receive
 * bytes to/from the server.
 */
int Call::openConnection()
{
    try
    {
        if( !m_pTransport)
		{
            m_pTransport = SOAPTransportFactory::getTransportObject(m_nTransportType);

			if( !m_pTransport)
			{
				return AXIS_FAIL;
			}
		}

        char * pcChannelHTTPLibraryPath = g_pConfig->getAxisConfProperty( AXCONF_CHANNEL_HTTP);
        char * pcChannelHTTPSSLLibraryPath = g_pConfig->getAxisConfProperty( AXCONF_SSLCHANNEL_HTTP);
        char * pcSSLChannelInfo = g_pConfig->getAxisConfProperty( AXCONF_SECUREINFO);

        if( pcChannelHTTPLibraryPath)
		{
			m_pTransport->setTransportProperty( CHANNEL_HTTP_DLL_NAME, pcChannelHTTPLibraryPath);
		}

        if( pcChannelHTTPSSLLibraryPath)
		{
			m_pTransport->setTransportProperty( CHANNEL_HTTP_SSL_DLL_NAME, pcChannelHTTPSSLLibraryPath);
		}

        m_pTransport->setEndpointUri( m_pcEndPointUri);

		if( pcSSLChannelInfo && strlen( pcSSLChannelInfo) > 0)
		{
			char *	pszArgPtr = NULL;
			int		iArgIndex = 0;
			string	sArguments[8];

			pszArgPtr = strtok( pcSSLChannelInfo, ",");

			while( pszArgPtr != NULL && iArgIndex < 8)
			{
				sArguments[iArgIndex] = pszArgPtr;

				iArgIndex++;

				pszArgPtr = strtok( NULL, ",");

				while( pszArgPtr != NULL && *pszArgPtr == ' ' && *pszArgPtr != '\0')
				{
					pszArgPtr++;
				}
			}

			m_pTransport->setTransportProperty( SECURE_PROPERTIES, (const char *) &sArguments);
		}

        //if use proxy then set proxy
        if( m_bUseProxy)
		{
    	    m_pTransport->setProxy(m_strProxyHost.c_str(), m_uiProxyPort);
		}

        m_nStatus = m_pTransport->openConnection();
    }
    catch(AxisException& e)
    {
        e = e;

        throw;
    }
    catch(...)
    {
        throw;
    }

    return m_nStatus;
}

/*
 * This method closes the connection of this object to the server
 */
void Call::closeConnection()
{
	if (m_pTransport) {
        m_pTransport->closeConnection();
	//    SOAPTransportFactory::destroyTransportObject(m_pTransport);
	//	m_pTransport = NULL;
	}
}

void Call::setSOAPVersion (SOAP_VERSION version)
{
    m_pIWSSZ->setSoapVersion (version);
}

Axis_Array Call::getBasicArray (XSDTYPE nType, const AxisChar* pName,
    const AxisChar* pNamespace)
{
    return m_pIWSDZ->getBasicArray (nType, pName, pNamespace);
}

Axis_Array Call::getCmplxArray (void* pDZFunct, void* pCreFunct, 
    void* pDelFunct, void* pSizeFunct, const AxisChar* pName, 
    const AxisChar* pNamespace)
{
    return m_pIWSDZ->getCmplxArray (pDZFunct, pCreFunct, pDelFunct, pSizeFunct,
        pName, pNamespace);
}

int Call::getElementAsInt (const AxisChar* pName, const AxisChar* pNamespace)
{
    return m_pIWSDZ->getElementAsInt (pName, pNamespace);
}

int Call::getFaultDetail(char** ppcDetail)
{
    return m_pIWSDZ->getFaultDetail(ppcDetail);
}

xsd__boolean Call::getElementAsBoolean (const AxisChar* pName, 
    const AxisChar* pNamespace)
{
    return m_pIWSDZ->getElementAsBoolean (pName, pNamespace);
}

unsigned int Call::getElementAsUnsignedInt (const AxisChar* pName,
    const AxisChar* pNamespace)
{
    return m_pIWSDZ->getElementAsUnsignedInt (pName, pNamespace);
}

short Call::getElementAsShort (const AxisChar* pName, 
    const AxisChar* pNamespace)
{
    return m_pIWSDZ->getElementAsShort (pName, pNamespace);
}

unsigned short Call::getElementAsUnsignedShort (const AxisChar* pName,
    const AxisChar* pNamespace)
{
    return m_pIWSDZ->getElementAsUnsignedShort (pName, pNamespace);
}

char Call::getElementAsByte (const AxisChar* pName, const AxisChar* pNamespace)
{
    return m_pIWSDZ->getElementAsByte (pName, pNamespace);
}
unsigned char Call::getElementAsUnsignedByte (const AxisChar* pName,
    const AxisChar * pNamespace)
{
    return m_pIWSDZ->getElementAsUnsignedByte (pName, pNamespace);
}

LONGLONG Call::getElementAsLong (const AxisChar* pName, const AxisChar* pNamespace)
{
    return m_pIWSDZ->getElementAsLong (pName, pNamespace);
}

long Call::getElementAsInteger (const AxisChar* pName, 
    const AxisChar* pNamespace)
{
    return m_pIWSDZ->getElementAsInteger (pName, pNamespace);
}

unsigned long Call::getElementAsUnsignedLong (const AxisChar* pName,
    const AxisChar* pNamespace)
{
    return m_pIWSDZ->getElementAsUnsignedLong (pName, pNamespace);
}

float Call::getElementAsFloat (const AxisChar* pName, 
    const AxisChar* pNamespace)
{
    return m_pIWSDZ->getElementAsFloat (pName, pNamespace);
}

double Call::getElementAsDouble (const AxisChar* pName, 
    const AxisChar* pNamespace)
{
    return m_pIWSDZ->getElementAsDouble (pName, pNamespace);
}

double Call::getElementAsDecimal (const AxisChar* pName, 
    const AxisChar* pNamespace)
{
    return m_pIWSDZ->getElementAsDecimal (pName, pNamespace);
}

AxisChar* Call::getElementAsString (const AxisChar* pName, 
    const AxisChar* pNamespace)
{
    return m_pIWSDZ->getElementAsString (pName, pNamespace);
}

AxisChar* Call::getElementAsAnyURI (const AxisChar* pName, 
    const AxisChar* pNamespace)
{
    return m_pIWSDZ->getElementAsAnyURI (pName, pNamespace);
}

AxisChar* Call::getElementAsQName (const AxisChar* pName, 
    const AxisChar* pNamespace)
{
    return m_pIWSDZ->getElementAsQName (pName, pNamespace);
}

xsd__hexBinary Call::getElementAsHexBinary (const AxisChar* pName, 
    const AxisChar * pNamespace)
{
    return m_pIWSDZ->getElementAsHexBinary (pName, pNamespace);
}

xsd__base64Binary Call::getElementAsBase64Binary (const AxisChar* pName,
    const AxisChar* pNamespace)
{
    return m_pIWSDZ->getElementAsBase64Binary (pName, pNamespace);
}

struct tm Call::getElementAsDateTime (const AxisChar* pName,
    const AxisChar* pNamespace)
{
    return m_pIWSDZ->getElementAsDateTime (pName, pNamespace);
}

struct tm Call::getElementAsDate (const AxisChar* pName, 
    const AxisChar* pNamespace)
{
    return m_pIWSDZ->getElementAsDate (pName, pNamespace);
}

struct tm Call::getElementAsTime (const AxisChar* pName, 
    const AxisChar* pNamespace)
{
    return m_pIWSDZ->getElementAsTime (pName, pNamespace);
}

long Call::getElementAsDuration (const AxisChar* pName, 
    const AxisChar* pNamespace)
{
    return m_pIWSDZ->getElementAsDuration (pName, pNamespace);
}

int Call::getAttributeAsInt (const AxisChar* pName, const AxisChar* pNamespace)
{
    return m_pIWSDZ->getAttributeAsInt (pName, pNamespace);
}

xsd__boolean Call::getAttributeAsBoolean (const AxisChar* pName,
    const AxisChar* pNamespace)
{
    return m_pIWSDZ->getAttributeAsBoolean (pName, pNamespace);
}
unsigned int Call::getAttributeAsUnsignedInt (const AxisChar* pName,
    const AxisChar* pNamespace)
{
    return m_pIWSDZ->getAttributeAsUnsignedInt (pName, pNamespace);
}

short Call::getAttributeAsShort (const AxisChar* pName, 
    const AxisChar* pNamespace)
{
    return m_pIWSDZ->getAttributeAsShort (pName, pNamespace);
}

unsigned short Call::getAttributeAsUnsignedShort (const AxisChar* pName,
    const AxisChar* pNamespace)
{
    return m_pIWSDZ->getAttributeAsUnsignedShort (pName, pNamespace);
}

char Call::getAttributeAsByte (const AxisChar* pName, 
    const AxisChar* pNamespace)
{
    return m_pIWSDZ->getAttributeAsByte (pName, pNamespace);
}
unsigned char Call::getAttributeAsUnsignedByte (const AxisChar* pName,
    const AxisChar* pNamespace)
{
    return m_pIWSDZ->getAttributeAsUnsignedByte (pName, pNamespace);
}

long Call::getAttributeAsLong (const AxisChar* pName, 
    const AxisChar* pNamespace)
{
    return m_pIWSDZ->getAttributeAsLong (pName, pNamespace);
}

long Call::getAttributeAsInteger (const AxisChar* pName,
    const AxisChar * pNamespace)
{
    return m_pIWSDZ->getAttributeAsInteger (pName, pNamespace);
}
unsigned long Call::getAttributeAsUnsignedLong (const AxisChar* pName,
    const AxisChar* pNamespace)
{
    return m_pIWSDZ->getAttributeAsUnsignedLong (pName, pNamespace);
}

float Call::getAttributeAsFloat (const AxisChar* pName,
    const AxisChar* pNamespace)
{
    return m_pIWSDZ->getAttributeAsFloat (pName, pNamespace);
}

double Call::getAttributeAsDouble (const AxisChar* pName,
    const AxisChar* pNamespace)
{
    return m_pIWSDZ->getAttributeAsDouble (pName, pNamespace);
}

double Call::getAttributeAsDecimal (const AxisChar* pName,
    const AxisChar* pNamespace)
{
    return m_pIWSDZ->getAttributeAsDecimal (pName, pNamespace);
}

AxisChar* Call::getAttributeAsString (const AxisChar* pName,
    const AxisChar* pNamespace)
{
    return m_pIWSDZ->getAttributeAsString (pName, pNamespace);
}

AxisChar* Call::getAttributeAsAnyURI (const AxisChar* pName,
    const AxisChar* pNamespace)
{
    return m_pIWSDZ->getAttributeAsAnyURI (pName, pNamespace);
}

AxisChar* Call::getAttributeAsQName (const AxisChar* pName,
    const AxisChar* pNamespace)
{
    return m_pIWSDZ->getAttributeAsQName (pName, pNamespace);
}

xsd__hexBinary Call::getAttributeAsHexBinary (const AxisChar* pName,
    const AxisChar* pNamespace)
{
    return m_pIWSDZ->getAttributeAsHexBinary (pName, pNamespace);
}

xsd__base64Binary Call::getAttributeAsBase64Binary (const AxisChar* pName,
    const AxisChar * pNamespace)
{
    return m_pIWSDZ->getAttributeAsBase64Binary (pName, pNamespace);
}
struct tm Call::getAttributeAsDateTime (const AxisChar* pName,
    const AxisChar * pNamespace)
{
    return m_pIWSDZ->getAttributeAsDateTime (pName, pNamespace);
}
struct tm Call::getAttributeAsDate (const AxisChar* pName, 
    const AxisChar* pNamespace)
{
    return m_pIWSDZ->getAttributeAsDate (pName, pNamespace);
}
struct tm Call::getAttributeAsTime (const AxisChar* pName, 
    const AxisChar* pNamespace)
{
    return m_pIWSDZ->getAttributeAsTime (pName, pNamespace);
}

long Call::getAttributeAsDuration (const AxisChar* pName,
    const AxisChar* pNamespace)
{
    return m_pIWSDZ->getAttributeAsDuration (pName, pNamespace);
}

int Call::checkMessage (const AxisChar* pName, const AxisChar* pNamespace)
{
	 m_nStatus = m_pIWSDZ->checkMessageBody (pName, pNamespace);
    return m_nStatus;
}

void* Call::checkFault (const AxisChar* pName, const AxisChar* pNamespace)
{
	 return m_pIWSDZ->checkForFault (pName, pNamespace);
}

void* Call::getCmplxObject (void* pDZFunct, void* pCreFunct, void* pDelFunct,
    const AxisChar* pName, const AxisChar* pNamespace)
{
    return m_pIWSDZ->getCmplxObject (pDZFunct, pCreFunct, pDelFunct, pName,
        pNamespace);
}

IHeaderBlock* Call::createHeaderBlock ()
{
    return (m_pIWSSZ->createHeaderBlock ());
}

IHeaderBlock* Call::createHeaderBlock(AxisChar* pachLocalName, 
                                       AxisChar* pachUri)
{
 	return new HeaderBlock(pachLocalName, pachUri);
}

IHeaderBlock* Call::createHeaderBlock(AxisChar* pachLocalName, 
                                       AxisChar* pachUri, AxisChar* pachPrefix)
{
 	return new HeaderBlock(pachLocalName, pachUri, pachPrefix);
}

int Call::getStatus() 
{
	return m_nStatus;
}

void Call::setProxy(const char* pcProxyHost, unsigned int uiProxyPort)
{
    m_strProxyHost = pcProxyHost;
    m_uiProxyPort = uiProxyPort;
    m_bUseProxy = true;    
}

AnyType* Call::getAnyObject()
{
	return m_pIWSDZ->getAnyObject();
}

int Call::addAnyObject(AnyType* pAnyObject)
{
	return m_pIWSSZ->addOutputAnyObject(pAnyObject);
}

const AxisChar* Call::getNamespacePrefix(const AxisChar* pNamespace)
{
    return m_pIWSSZ->getNamespacePrefix(pNamespace);
}

