/*
 *   Copyright 2003-2004 The Apache Software Foundation.
// (c) Copyright IBM Corp. 2004, 2005 All Rights Reserved
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
 */

/*
 * @author Roshan Weerasuriya (roshan@opensource.lk, roshanw@jkcsworld.com)
 * @author Susantha Kumara (susantha@opensource.lk, skumara@virtusa.com)
 * @author Damitha Kumarage (damitha@opensource.lk, damitha@jkcsworld.com)
 *
 */

// !!! This include file must be first thing in file !!!
#include "../platforms/PlatformAutoSense.hpp"

#include <stdio.h>
#include <stdarg.h>

#include <axis/GDefine.hpp>

#include "SoapEnvelope.h"
#include "SoapSerializer.h"
#include "HeaderBlock.h"
#include "SoapKeywordMapping.h"
#include "SoapAttachmentReference.hpp"
#include "AxisSoapException.h"
#include "../common/ArrayBean.h"
#include "../common/BasicTypeSerializer.h"
#include "../common/AxisConfig.h"

#include "../common/AxisTrace.h"


extern AXIS_CPP_NAMESPACE_PREFIX AxisConfig* g_pConfig;
#define MIMEBOUNDARY    "------=MIME_BOUNDARY"

AXIS_CPP_NAMESPACE_START

SoapSerializer::
SoapSerializer()
{
    logEntryEngine("SoapSerializer::SoapSerializer")

    m_pSoapEnvelope = NULL;
    m_iSoapVersion = SOAP_VER_1_1;
    m_pOutputStream = NULL;
    m_pNamespace = NULL;
    m_pContentIdSet = NULL;
    
    logExit()
}

SoapSerializer::
~SoapSerializer()
{
    logEntryEngine("SoapSerializer::~SoapSerializer")

    delete m_pSoapEnvelope;

    /* Cleaning the memory allocated to the SoapAttachments */       
    map<AxisXMLString, ISoapAttachment*>::iterator itCurrAttach= m_SoapAttachments.begin();
    while( itCurrAttach != m_SoapAttachments.end())
    {        
        delete( (SoapAttachment*)((*itCurrAttach).second));        
        itCurrAttach++;
    }
    m_SoapAttachments.clear();

    list<SoapAttachmentReference*>::iterator itAttRef= m_attachmentRefs.begin();
    while(itAttRef != m_attachmentRefs.end())
    {        
        delete *itAttRef;
        itAttRef++;
    }
    m_attachmentRefs.clear();
    
    logExit()
}

int SoapSerializer::
setSoapEnvelope( SoapEnvelope * pSoapEnvelope)
{
    logEntryEngine("SoapSerializer::setSoapEnvelope")

    m_pSoapEnvelope = pSoapEnvelope;

    logExitWithReturnCode(AXIS_SUCCESS)

    return AXIS_SUCCESS;
}

int SoapSerializer::
setSoapHeader( SoapHeader * pSoapHeader)
{
    logEntryEngine("SoapSerializer::setSoapHeader")

    int intStatus = AXIS_FAIL;

    if( m_pSoapEnvelope)
    {
        /* no need to create a SOAP Header, it already exists */
        if( (m_pSoapEnvelope) && (m_pSoapEnvelope->m_pSoapHeader))
            intStatus = AXIS_OBJECT_ALREADY_EXISTS;
        else
        {
            m_pSoapEnvelope->setSoapHeader( pSoapHeader);
            intStatus= AXIS_SUCCESS;
        }
    }
    
    logExitWithReturnCode(intStatus)

    return intStatus;
}

int SoapSerializer::
setSoapBody( SoapBody * pSoapBody)
{
    logEntryEngine("SoapSerializer::setSoapBody")

    int intStatus = AXIS_FAIL;

    if(m_pSoapEnvelope)
    {
        m_pSoapEnvelope->setSoapBody( pSoapBody);
        intStatus = AXIS_SUCCESS;
    }

    logExitWithReturnCode(intStatus)

    return intStatus;
}

int SoapSerializer::
setSoapMethod( SoapMethod *pSoapMethod)
{
    logEntryEngine("SoapSerializer::setSoapMethod")

    int intStatus = AXIS_FAIL;

    if( m_pSoapEnvelope && (m_pSoapEnvelope->m_pSoapBody))
    {
        if( !(m_pSoapEnvelope->m_pSoapBody->m_pSoapMethod))
            m_pSoapEnvelope->m_pSoapBody->m_pSoapMethod = pSoapMethod;
            
        intStatus = AXIS_SUCCESS;
    }

    logExitWithReturnCode(intStatus)

    return intStatus;
}

int SoapSerializer::
addOutputBasicArrayParam( const Axis_Array * pArray, XSDTYPE nType, const AxisChar * pName)
{
    logEntryEngine("SoapSerializer::addOutputBasicArrayParam")

    int    iSuccess = AXIS_SUCCESS;

    Axis_Array * pLocalArray       = (Axis_Array *)NULL;
    ArrayBean  * pAb               = (ArrayBean *)NULL;
    
    // We need to handle NULL array passed in which means serialize empty array.
    if (pArray)
    {
        pLocalArray = pArray->clone();
        pAb = makeArrayBean( nType, pLocalArray->m_Array );
        pAb->SetDimension(pLocalArray->m_Size);
        
        // We're now finished with the local array object, so it can be deleted
        // However, we need to de-couple from the internal array, which is now owned
        // by the ArrayBean.
        pLocalArray->m_Array = NULL;
        pLocalArray->m_Size = 0;
        delete pLocalArray;
    }
    else
    {
        pAb = makeArrayBean( nType, (void **)NULL );
        pAb->SetDimension(0);
    }

    Param* pParam = new Param();

    pAb->SetItemName(pName);
    if( RPC_ENCODED == m_nStyle)
        pParam->setName(pName);
    else
        pParam->setName("array");

    pParam->m_Value.pArray = pAb;
    pParam->m_Type = XSD_ARRAY;

    if( m_pSoapEnvelope && (m_pSoapEnvelope->m_pSoapBody) && 
        (m_pSoapEnvelope->m_pSoapBody->m_pSoapMethod)) 
        m_pSoapEnvelope->m_pSoapBody->m_pSoapMethod->addOutputParam( pParam);

    logExitWithReturnCode(iSuccess)

    return iSuccess;  
}

int SoapSerializer::
addOutputCmplxArrayParam( const Axis_Array * pArray, 
                          void * pSZFunct, void * pDelFunct,
                          const AxisChar * pName, const AxisChar * pNamespace)
{
    logEntryEngine("SoapSerializer::addOutputCmplxArrayParam")

    int    iSuccess = AXIS_SUCCESS;

    Axis_Array * pLocalArray       = (Axis_Array *)NULL;
    ArrayBean  * pAb               = (ArrayBean *)NULL;
    
    // We need to handle NULL array passed in which means serialize empty array.
    if (pArray)
    {
        pLocalArray = pArray->clone();
        pAb = makeArrayBean( pLocalArray->m_Array, pSZFunct, pDelFunct);
        pAb->SetDimension( pLocalArray->m_Size);
        
        // We're now finished with the local array object, so it can be deleted
        // However, we need to de-couple from the internal array, which is now owned
        // by the ArrayBean.
        pLocalArray->m_Array = NULL;
        pLocalArray->m_Size = 0;
        delete pLocalArray;
    }
    else
    {
        pAb = makeArrayBean( (void **)NULL, pSZFunct, pDelFunct);
        pAb->SetDimension(0);
    }
    
    Param * pParam = new Param();

    pAb->SetItemName( pName);
    if( RPC_ENCODED == m_nStyle)
    {
        pAb->SetTypeName( pName);
        pAb->SetUri( pNamespace);
        pParam->setName( pName);
    }
    else
    {
        if( NULL != pNamespace)
            pParam->setURI( pNamespace);

        pParam->setName( "array");        
    }

    pParam->m_Value.pArray = pAb;
    pParam->m_Type = XSD_ARRAY;

    if( m_pSoapEnvelope &&
        (m_pSoapEnvelope->m_pSoapBody) &&
        (m_pSoapEnvelope->m_pSoapBody->m_pSoapMethod)) 
        m_pSoapEnvelope->m_pSoapBody->m_pSoapMethod->addOutputParam( pParam);

    pParam->setName( pName);

    logExitWithReturnCode(iSuccess)
    
    return iSuccess;  
}

int SoapSerializer::
addOutputCmplxParam( void * pObject,
                     void * pSZFunct, void * pDelFunct,
                     const AxisChar * pName, const AxisChar * pNamespace)
{ 
    logEntryEngine("SoapSerializer::addOutputCmplxParam")

    int    iSuccess = AXIS_SUCCESS;

    Param * pParam = new Param();

    pParam->m_Value.pCplxObj = new ComplexObjectHandler;
    pParam->m_Value.pCplxObj->pObject = pObject;
    pParam->m_Value.pCplxObj->pSZFunct = (AXIS_SERIALIZE_FUNCT) pSZFunct;
    pParam->m_Value.pCplxObj->pDelFunct = (AXIS_OBJECT_DELETE_FUNCT) pDelFunct;
    if( m_pSoapEnvelope &&
        (m_pSoapEnvelope->m_pSoapBody) &&
        (m_pSoapEnvelope->m_pSoapBody->m_pSoapMethod)) 
        m_pSoapEnvelope->m_pSoapBody->m_pSoapMethod->addOutputParam( pParam);

    pParam->setName( pName);
    
    logExitWithReturnCode(iSuccess)
    
    return iSuccess;  
}

int SoapSerializer::
addFaultDetail( void * pObject,
                void * pSZFunct, void * pDelFunct,
                const AxisChar * pName, const AxisChar * pNamespace)
{ 
    logEntryEngine("SoapSerializer::addFaultDetail")

    int    iSuccess = AXIS_SUCCESS;
    Param * pParam = new Param();

    pParam->m_Value.pCplxObj = new ComplexObjectHandler;
    pParam->m_Value.pCplxObj->pObject = pObject;
    pParam->m_Value.pCplxObj->pSZFunct = (AXIS_SERIALIZE_FUNCT) pSZFunct;
    pParam->m_Value.pCplxObj->pDelFunct = (AXIS_OBJECT_DELETE_FUNCT) pDelFunct;

    if( m_pSoapEnvelope &&
        (m_pSoapEnvelope->m_pSoapBody) &&
        (m_pSoapEnvelope->m_pSoapBody->m_pSoapFault)) 
        iSuccess = m_pSoapEnvelope->m_pSoapBody->m_pSoapFault->setFaultDetail(pParam);

    pParam->setName( pName);

    logExitWithReturnCode(iSuccess)
    
    return iSuccess;
}

int SoapSerializer::
addFaultDetail( const AxisChar * pDetail)
{
    logEntryEngine("SoapSerializer::addFaultDetail")

    int iStatus = AXIS_FAIL;
    if( m_pSoapEnvelope &&
        (m_pSoapEnvelope->m_pSoapBody) && (m_pSoapEnvelope->m_pSoapBody->m_pSoapFault))
    {
        iStatus = m_pSoapEnvelope->m_pSoapBody->m_pSoapFault->setFaultDetail(pDetail);
    }

    logExitWithReturnCode(iStatus)
    
    return iStatus;
}

int SoapSerializer::
setSoapFault( SoapFault * pSoapFault)
{
    logEntryEngine("SoapSerializer::setSoapFault")

    int intStatus = AXIS_FAIL;

    if( m_pSoapEnvelope && (m_pSoapEnvelope->m_pSoapBody))
    {
        delete m_pSoapEnvelope->m_pSoapBody->m_pSoapFault;

        m_pSoapEnvelope->m_pSoapBody->m_pSoapFault = pSoapFault;
        intStatus = AXIS_SUCCESS;
    }

    logExitWithReturnCode(intStatus)
    
    return intStatus;
}

int SoapSerializer::
setOutputStream( SOAPTransport * pStream)
{
    logEntryEngine("SoapSerializer::setOutputStream")

    int    iStatus = AXIS_SUCCESS;

    m_pOutputStream = pStream;

    try
    {
        if( m_pSoapEnvelope)
        {
            if( checkAttachmentAvailability())
            {
                char *pszSOAPMimeHeaders = pStream->getIncomingSOAPMimeHeaders();
                if (NULL != pszSOAPMimeHeaders) 
                {    // Server code
                    string asSOAPMimeHeaders = pszSOAPMimeHeaders;
                    int        start            = asSOAPMimeHeaders.find( AXIS_CONTENT_TYPE);
                    int        startPosIdValue = asSOAPMimeHeaders.find( "<", start + strlen( AXIS_CONTENT_ID ":")) + 1;
                    int        endPosIdValue   = asSOAPMimeHeaders.find( ">", start + strlen( AXIS_CONTENT_TYPE));
                    int        length          = endPosIdValue - startPosIdValue ;    

                    string asStartID = asSOAPMimeHeaders.substr (startPosIdValue,length); 

                    string asContentType( "multipart/related; type=\"text/xml\"; start=\"<");

                    asContentType = asContentType + asStartID + ">\"";
                    asContentType = asContentType + ";  boundary=\"" MIMEBOUNDARY "\"";

                    pStream->setTransportProperty( CONTENT_TYPE, asContentType.c_str()); 

                    serialize( "\r\n" MIMEBOUNDARY "\r\n", NULL);
                    serialize( pStream->getIncomingSOAPMimeHeaders(), "\r\n\r\n", NULL);
                }
                else
                {    // Client code
                    const char *id = m_pContentIdSet->generateId();
                    string ctype = "multipart/related; type=\"text/xml\"; boundary=\"";
                    ctype += MIMEBOUNDARY;
                    ctype += "\"; start=\"<";
                    ctype += id;
                    ctype += ">\"";
                    pStream->deleteTransportProperty(AXIS_CONTENT_TYPE); // Never want 2 Content-Type HTTP headers
                    pStream->setTransportProperty(AXIS_CONTENT_TYPE, ctype.c_str());

                    serialize("\r\n--" MIMEBOUNDARY "\r\n", NULL);
                    serialize(AXIS_CONTENT_TYPE ": text/xml; charset=UTF-8\r\n", NULL);
                    serialize(AXIS_CONTENT_TRANSFER_ENCODING ": binary\r\n", NULL);

                    string cid = AXIS_CONTENT_ID;
                    cid += ": <";
                    cid += id;
                    cid += ">\r\n\r\n";        // Extra \r\n terminates headers
                    serialize(cid.c_str(), NULL);
                }
            }

            serialize( "<?xml version='1.0' encoding='utf-8' ?>", NULL);

            if( (iStatus = m_pSoapEnvelope->serialize( *this, (SOAP_VERSION) m_iSoapVersion)) == AXIS_FAIL)
            {
                logThrowExceptionWithData("AxisSoapException - CLIENT_SOAP_MESSAGE_INCOMPLETE", "The SOAP serializer has detected errors in the header or envelope. Transmission has been aborted.")
                
                throw AxisSoapException( CLIENT_SOAP_MESSAGE_INCOMPLETE, "The SOAP serializer has detected errors in the header or envelope. Transmission has been aborted.");
            }

            if( checkAttachmentAvailability())
                serializeAttachments( *this);
        }
    }
    catch( AxisSoapException& e)
    {
        e = e;
        
        logRethrowException()

        throw;
    }
    catch( AxisException& e)
    {
        e = e;
        
        logRethrowException()

        throw;
    }
    catch( ...)
    {
        logRethrowException()

        throw;
    }

    logExitWithReturnCode(iStatus)

    return iStatus;
}

/*
 * Some client side transport layer may wait until the end of buffers is 
 * acknowladged. Use this function to do that.
 */
void SoapSerializer::
markEndOfStream()
{
    logEntryEngine("SoapSerializer::markEndOfStream")

    m_pOutputStream->flushOutput();
    
    logExit()
}

/*
 * Initializing the members of the class. This is needed since
 * the same object instance of this class, may be used to server
 * several SOAP requests.
 */
int SoapSerializer::
init()
{
    logEntryEngine("SoapSerializer::init")

    m_nStatus = AXIS_SUCCESS;

    delete m_pSoapEnvelope;
    m_pSoapEnvelope= NULL;

    /* Adding SoapEnvelop and SoapBody to Serializer */
    m_pSoapEnvelope = new SoapEnvelope();
    m_pSoapEnvelope->setSoapBody( new SoapBody());
    
    m_nCounter=0;
    m_NsStack.clear();

    logExitWithReturnCode(m_nStatus)

    return m_nStatus;
}

int SoapSerializer::
setSoapVersion( SOAP_VERSION nSoapVersion)
{
    logEntryEngine("SoapSerializer::setSoapVersion")

    m_iSoapVersion = nSoapVersion;

    m_pSoapEnvelope->clearStandardNamespaceDecl(); // Samisa : AXISCPP-368

    /* here the default namespaces of the SoapEnvelop should be added and 
     * intialized as well. 
     */
    m_pSoapEnvelope->addStandardNamespaceDecl( SoapKeywordMapping::map(nSoapVersion).pEnv);
    m_pSoapEnvelope->addStandardNamespaceDecl( SoapKeywordMapping::map(nSoapVersion).pXsd);
    m_pSoapEnvelope->addStandardNamespaceDecl( SoapKeywordMapping::map(nSoapVersion).pXsi);

    /* Adding the standard SOAP namespace to the namespace stack */
    m_NsStack[SoapKeywordMapping::map(nSoapVersion).pchNamespaceUri] = 
        SoapKeywordMapping::map(nSoapVersion).pchPrefix;

    logExitWithReturnCode(AXIS_SUCCESS)

    return AXIS_SUCCESS;
}
void SoapSerializer::
removeNamespacePrefix( const AxisChar * pNamespace)
{
    logEntryEngine("SoapSerializer::removeNamespacePrefix")

    if( m_NsStack.find( pNamespace) != m_NsStack.end())
        m_NsStack.erase( pNamespace);
    
    logExit()
}

const AxisChar * SoapSerializer::
getNamespacePrefix( const AxisChar * pNamespace)
{
    bool blnIsNewPrefix;
    return getNamespacePrefix(pNamespace, blnIsNewPrefix);
}

const AxisChar * SoapSerializer::
getNamespacePrefix( const AxisChar * pNamespace, bool & blnIsNewPrefix)
{
    blnIsNewPrefix = false;
    
    // We will not map null or null string namespaces...MUST return null string
    // since the namespace is sometimes assigned to object of type string class.
    if (pNamespace == (const AxisChar *)NULL || pNamespace[0] == '\0')    
        return (const AxisChar *)"";
    
    if( m_NsStack.find( pNamespace) == m_NsStack.end())
    {
        m_nCounter++;
        AxisSprintf(m_Buf, 8, "ns%d", m_nCounter);
        m_NsStack[pNamespace] = m_Buf;
        blnIsNewPrefix = true;
    }

    return m_NsStack[pNamespace].c_str();
}

IWrapperSoapSerializer& SoapSerializer::
operator << (const AxisChar * cSerialized)
{
    logSetFunctionNameEngine("SoapSerializer::operator <<")

    // some thing has gone wrong. So do nothing 
    if( AXIS_SUCCESS != m_nStatus) 
        return *this;

    try
    {
      // send everything to transport layer, it should handle bufferization itself 
      m_pOutputStream->sendBytes( cSerialized, 0);
    }
    catch(AxisSoapException& e)
    {
        e = e;
        
        logRethrowException()

        throw;
    }
    catch(AxisException& e)
    {
        e = e;
        
        logRethrowException()

        throw;
    }
    catch(...)
    {
        logRethrowException()

        throw;
    }
    
    return *this;
}

int SoapSerializer::
createSoapMethod( const AxisChar * sLocalName, const AxisChar * sURI)
{
    logEntryEngine("SoapSerializer::createSoapMethod")

    if (NULL == m_pSoapEnvelope || NULL == m_pSoapEnvelope->m_pSoapBody)
        return AXIS_FAIL;
        
    SoapMethod * pMethod = m_pSoapEnvelope->m_pSoapBody->m_pSoapMethod;
    if (pMethod == NULL)
    {
        pMethod = new SoapMethod();
        setSoapMethod( pMethod);
    }
    
    // Ensure everything is cleared out if using existing method object.
    pMethod->reset();

    pMethod->setLocalName( sLocalName);
    pMethod->setPrefix( getNamespacePrefix( sURI));
    pMethod->setURI( sURI);

    logExitWithReturnCode(AXIS_SUCCESS)

    return AXIS_SUCCESS;
}

int SoapSerializer::
createSoapFault( const AxisChar * sLocalName, 
                 const AxisChar * sURI,
                 const AxisChar * sFaultCode,
                 const AxisChar * sFaultString)
{
    logEntryEngine("SoapSerializer::createSoapFault")

    SoapFault * pSoapFault = new SoapFault();

    setSoapFault( pSoapFault);

    pSoapFault->setLocalName( sLocalName);
    pSoapFault->setPrefix( getNamespacePrefix( sURI));
    pSoapFault->setURI( sURI);
    pSoapFault->setFaultcode( sFaultCode);
    pSoapFault->setFaultstring( sFaultString);

    char* pcNodeName = g_pConfig->getAxisConfProperty( AXCONF_NODENAME);
    char* pcPort = g_pConfig->getAxisConfProperty(AXCONF_LISTENPORT);
    string strUrl = pcNodeName;
    strUrl += ":";
    strUrl += string( pcPort);
    pSoapFault->setFaultactor( strUrl.c_str());
    
    logExitWithReturnCode(AXIS_SUCCESS)

    return AXIS_SUCCESS;  
}

/*
 * Used to create an ArrayBean when the return type of a method is an array
 * of basic types
 */
ArrayBean * SoapSerializer::
makeArrayBean( XSDTYPE nType, void ** pArray)
{
    logEntryEngine("SoapSerializer::makeArrayBean")

    ArrayBean* pAb = new ArrayBean();

    pAb->m_type = nType;
    pAb->m_value.sta = pArray;

    logExitWithPointer(pAb)

    return pAb;
}

/*
 * Used to create an ArrayBean when the return type of a method is an array
 * of complex types
 */
ArrayBean * SoapSerializer::
makeArrayBean(void ** pObject, void * pSZFunct, void * pDelFunct)
{
    logEntryEngine("SoapSerializer::makeArrayBean")

    ArrayBean* pAb = new ArrayBean();

    pAb->m_type = USER_TYPE;
    pAb->m_value.cta = new ComplexObjectHandler;
    pAb->m_value.cta->pSZFunct = (AXIS_SERIALIZE_FUNCT) pSZFunct;
    pAb->m_value.cta->pDelFunct = (AXIS_OBJECT_DELETE_FUNCT) pDelFunct;
    pAb->m_value.cta->pObject = pObject;

    logExitWithPointer(pAb)

    return pAb;
}

IHeaderBlock * SoapSerializer::
createHeaderBlock()
{
    logEntryEngine("SoapSerializer::createHeaderBlock")

    HeaderBlock * pHeaderBlock= new HeaderBlock();

    setHeaderBlock( pHeaderBlock);

    logExitWithPointer(pHeaderBlock)

    return pHeaderBlock;
}

int SoapSerializer::
setHeaderBlock( HeaderBlock * pHeaderBlock)
{
    logEntryEngine("SoapSerializer::setHeaderBlock")

    int intStatus = AXIS_FAIL;

    if( (m_pSoapEnvelope) && (m_pSoapEnvelope->m_pSoapHeader))
    {
        /* no need to create a SOAP Header, it already exists */
    }
    else
    {
        SoapHeader * pSoapHeader = new SoapHeader();
        setSoapHeader( pSoapHeader);
    }

    m_pSoapEnvelope->m_pSoapHeader->addHeaderBlock( pHeaderBlock);
    intStatus = AXIS_SUCCESS;

    logExitWithReturnCode(intStatus)

    return intStatus;
}

/*
 * This method not only removes the existing SoapHeader, but also removes
 * all the existing HeaderBlocks which are associated with this SoapHeader.
 * Therefore the caller of this method has to be exactly sure whether he wants
 * to do this.
 */
int SoapSerializer::
removeSoapHeader()
{
    logEntryEngine("SoapSerializer::removeSoapHeader")

    delete m_pSoapEnvelope->m_pSoapHeader;
    m_pSoapEnvelope->m_pSoapHeader= NULL;

    logExitWithReturnCode(AXIS_SUCCESS)

    return AXIS_SUCCESS;  
}

/*
 * Used to Serialize an array of complex types inside a complex type. Called 
 * from within the Serialize wrapper method of the complex type.
 */
int SoapSerializer::
serializeCmplxArray( const Axis_Array * pArray, 
                     void * pSZFunct, void * pDelFunct, 
                     const AxisChar * pName, const AxisChar * pNamespace)
{
    logEntryEngine("SoapSerializer::serializeCmplxArray")

    ArrayBean  * pAb = (ArrayBean *)NULL;
    
    // We need to handle NULL array passed in which means serialize empty array.
    if (pArray)
    {
        pAb = (ArrayBean*) makeArrayBean( pArray->m_Array, pSZFunct, pDelFunct);
        pAb->SetDimension( pArray->m_Size);
    }    
    else
    {
        pAb = (ArrayBean*) makeArrayBean( (void **)NULL, pSZFunct, pDelFunct);
        pAb->SetDimension(0);
    }

    Param * pParam = new Param();

    pAb->SetItemName( pName);
    if( RPC_ENCODED == m_nStyle)
    {
        pAb->SetTypeName( pName);
        pAb->SetUri( pNamespace);
        pParam->setName( pName);
    }
    else
        pParam->setName( "array");        

    pParam->m_Value.pArray = pAb;
    pParam->m_Type = XSD_ARRAY;

    if( pNamespace != NULL)
    {
        bool blnIsNewNamespacePrefix = false;
        const AxisChar* np = getNamespacePrefix( pNamespace, blnIsNewNamespacePrefix);
        const AxisChar* originalNamespace = getNamespace(); // Store original namespace

        pParam->setPrefix( np);

        if( blnIsNewNamespacePrefix)
            removeNamespacePrefix( pNamespace);

        setNamespace( pNamespace);
        pParam->serialize( *this);
        setNamespace( originalNamespace); // Revert back original namespace
    }
    else
        pParam->serialize( *this);

    /* Remove pointer to the array from the ArrayBean to avoid deleting the 
     * array when ArrayBean is deleted. Array will be deleted when the complex
     * type that contains this array is deleted */
    pAb->RemoveArrayPointer();
    delete pParam;

    logExitWithReturnCode(AXIS_SUCCESS)

    return AXIS_SUCCESS;  
}

/*
 * Used to Serialize an array of basic types inside a complex type. Called from
 * within the Serialize wrapper method of the complex type.
 */
int SoapSerializer::
serializeBasicArray( const Axis_Array * pArray, XSDTYPE nType, const AxisChar * pName)
{
    return serializeBasicArray( pArray, NULL, nType, pName);
}

/*
 * Used to Serialize an array of basic types inside a complex type. Contains 
 * the namespace so that it can be serialized. Called from within the Serialize
 * wrapper method of the complex type.
 */
int SoapSerializer::
serializeBasicArray(const Axis_Array* pArray, 
                    const AxisChar* pNamespace, XSDTYPE nType, const AxisChar* pName)
{
    logEntryEngine("SoapSerializer::serializeBasicArray")

    ArrayBean  * pAb = (ArrayBean *)NULL;
    
    // We need to handle NULL array passed in which means serialize empty array.
    if (pArray)
    {
        pAb = (ArrayBean*) makeArrayBean( nType, pArray->m_Array);
        pAb->SetDimension( pArray->m_Size);
    }    
    else
    {
        pAb = (ArrayBean*) makeArrayBean( nType, (void **)NULL);
        pAb->SetDimension(0);
    }

    Param * pParam = new Param();

    pAb->SetItemName( pName);
    if( RPC_ENCODED == m_nStyle)
        pParam->setName( pName);
    else
        pParam->setName( "array");        

    pParam->m_Value.pArray = pAb;
    pParam->m_Type = XSD_ARRAY;
    
    if( pNamespace != NULL)
    {
        bool blnIsNewNamespacePrefix = false;
        const AxisChar * np = getNamespacePrefix( pNamespace, blnIsNewNamespacePrefix);
        const AxisChar * originalNamespace = getNamespace(); // Store original namespace

        pParam->setPrefix( np);

        if( blnIsNewNamespacePrefix)
            removeNamespacePrefix( pNamespace);

        setNamespace( pNamespace);
        pParam->serialize( *this);
        setNamespace( originalNamespace); // Revert back original namespace
    }
    else
        pParam->serialize( *this);

    /* Remove pointer to the array from the ArrayBean to avoid deleting the
     * array when ArrayBean is deleted. Array will be deleted when the complex
     * type that contains this array is deleted
     */
    pAb->RemoveArrayPointer();
    delete pParam;

    logExitWithReturnCode(AXIS_SUCCESS)

    return AXIS_SUCCESS;  
}

#ifdef UNIT_TESTING_ON
int SoapSerializer::setOutputStreamForTesting(SOAPTransport* pStream)
{
    m_pOutputStream = pStream;

    return AXIS_SUCCESS;
}
#endif

/*
 * Basic output parameter going to be serialized as an Element later
 */
int SoapSerializer::
addOutputParam( const AxisChar * pchName, void * pValue, XSDTYPE type)
{
    logEntryEngine("SoapSerializer::addOutputParam")

    IAnySimpleType* xsdValue = AxisUtils::createSimpleTypeObject(pValue, type);
    
    Param * pParam = new Param();

    int iStatus = AXIS_FAIL;
    
    if( pParam)
    {
        pParam->m_Type = type;
        pParam->m_sName = pchName;
        pParam->setValue(type, xsdValue);
        
        if( m_pSoapEnvelope &&
            (m_pSoapEnvelope->m_pSoapBody) &&
            (m_pSoapEnvelope->m_pSoapBody->m_pSoapMethod)) 
        {
            m_pSoapEnvelope->m_pSoapBody->m_pSoapMethod->addOutputParam( pParam);
            iStatus = AXIS_SUCCESS;
        }
        else
            delete pParam;
    }

    logExitWithReturnCode(iStatus)

    return iStatus;  
}

int SoapSerializer::serializeAsElement( const AxisChar * pName,
                                        void * pValue, 
                                        XSDTYPE type)
{
  return serializeAsElement( pName, NULL, pValue, type);
}

int SoapSerializer::serializeAsElement( const AxisChar * pName, 
                                        const AxisChar * pNamespace,
                                        void * pValue, 
                                        XSDTYPE type) 
{
    IAnySimpleType* pSimpleType = AxisUtils::createSimpleTypeObject(pValue, type);
    int ret;
    ret = serializeAsElement(pName, pNamespace, pSimpleType);
    delete pSimpleType;

    return ret;
}
int SoapSerializer::serializeAsElement( const AxisChar * pName,
                                        IAnySimpleType * pSimpleType)
{
    return serializeAsElement( pName, NULL, pSimpleType);
}

int SoapSerializer::
serializeAsElement( const AxisChar * pName, 
                    const AxisChar * pNamespace,
                    IAnySimpleType * pSimpleType) 
{
    logEntryEngine("SoapSerializer::serializeAsElement")

    int iStatus = AXIS_FAIL;

    const AxisChar* pPrefix = NULL;
    bool blnIsNewPrefix = false;

    if( pNamespace)
        pPrefix = getNamespacePrefix( pNamespace, blnIsNewPrefix);
    
    const AxisChar * pSerialized = NULL;

    if( blnIsNewPrefix)
    {
        pSerialized = m_BTSZ.serializeAsElement( pName, pPrefix, pNamespace, pSimpleType);
        removeNamespacePrefix( pNamespace);
    }
    else
        pSerialized = m_BTSZ.serializeAsElement( pName, pPrefix, pSimpleType);

    if( pSerialized)
    {
        *this << pSerialized;
        iStatus = AXIS_SUCCESS;  
    }

    logExitWithReturnCode(iStatus)

    return iStatus;
} 

int SoapSerializer::serializeAsAttribute( const AxisChar * pName,
                                          const AxisChar * pNamespace,
                                          void * pValue,
                                          XSDTYPE type)
{
    IAnySimpleType* pSimpleType = AxisUtils::createSimpleTypeObject(pValue, type);
    
    int status = serializeAsAttribute(pName, pNamespace, pSimpleType);
    delete pSimpleType;
    
    return status;
}

int SoapSerializer::
serializeAsAttribute( const AxisChar * pName, 
                      const AxisChar * pNamespace, 
                      IAnySimpleType* pSimpleType)
{
    logEntryEngine("SoapSerializer::serializeAsAttribute")

    int iStatus = AXIS_FAIL;

    const AxisChar * pPrefix = NULL;

    if( pNamespace)
        pPrefix = getNamespacePrefix( pNamespace);

    const AxisChar * pSerialized = m_BTSZ.serializeAsAttribute(pName, pPrefix, pSimpleType);

    if( pSerialized)
    {
        *this << pSerialized;
        iStatus = AXIS_SUCCESS;   
    }

    logExitWithReturnCode(iStatus)

    return iStatus; 
}

void SoapSerializer::
serializeVargs( const char * pFirst, va_list vList)
{
    logEntryEngine("SoapSerializer::serializeVargs")

    const char * pArg;
    
    if( pFirst)
        *this << pFirst;

    do
    {
        pArg = va_arg( vList, const char*);

        if( pArg)
            *this << pArg;
    } 
    while( pArg != NULL);
    
    logExit()
}

void SoapSerializer::
serialize( const char * pFirst, ...)
{
    logEntryEngine("SoapSerializer::serialize")

    va_list vList;

    va_start( vList, pFirst );   
    serializeVargs(pFirst, vList);
    va_end( vList);  
    
    logExit()
}

/*
 * Used probably by a handler to add a header block to the Serializer. 
 */
int SoapSerializer::
addHeaderBlock( IHeaderBlock * pBlk)
{
    logEntryEngine("SoapSerializer::addHeaderBlock")

    int iStatus = AXIS_FAIL;
    
    if( m_pSoapEnvelope)
    {
        if( !m_pSoapEnvelope->m_pSoapHeader)
            m_pSoapEnvelope->m_pSoapHeader = new SoapHeader();
        
        m_pSoapEnvelope->m_pSoapHeader->addHeaderBlock( (HeaderBlock *) pBlk);
        iStatus = AXIS_SUCCESS;
    }

    logExitWithReturnCode(iStatus)

    return iStatus;  
}

int SoapSerializer::setBodyAsHexBinary( xsd__hexBinary body)
{
    /* TODO */
    return AXIS_SUCCESS;
}

int SoapSerializer::setBodyAsBase64Binary( xsd__base64Binary body)
{
    /* TODO */    
    return AXIS_SUCCESS;
}

const AxisChar* SoapSerializer::getBodyAsString()
{
    /* TODO */    
    return NULL;
}

/* following two functions are needed by serializer functions of complex types
 * for RPC style web services
 */
void SoapSerializer::serializeStartElementOfType( const AxisChar * pName, 
                                                  const AxisChar * pNamespace, 
                                                  const AxisChar * pPrefix)
{
    if( pPrefix)
    {
        serialize( "<",
                   pName,
                   " xsi:type=\"",
                   pPrefix,
                   ":",
                   pName,
                   "\" xmlns:",
                   pPrefix,
                   "=\"",
                   pNamespace,
                   "\">",
                   NULL);
    }
    else
        serialize( "<", pName, ">", NULL);
}

void SoapSerializer::serializeEndElementOfType( const AxisChar * pName)
{
    serialize( "</", pName, ">", NULL);
}

IHeaderBlock * SoapSerializer::
createHeaderBlock( const AxisChar * pachLocalName, 
                   const AxisChar * pachUri)
{
    logEntryEngine("SoapSerializer::createHeaderBlock")

    HeaderBlock * pHeaderBlock= new HeaderBlock( pachLocalName, pachUri);

    setHeaderBlock( pHeaderBlock);

    logExitWithPointer(pHeaderBlock)

    return pHeaderBlock;    
}

SoapMethod * SoapSerializer::
getSOAPMethod()
{
    logEntryEngine("SoapSerializer::getSOAPMethod")

    SoapMethod * returnValue = NULL;
    
    if ( m_pSoapEnvelope && (m_pSoapEnvelope->m_pSoapBody))
        returnValue = m_pSoapEnvelope->m_pSoapBody->m_pSoapMethod;
    
    logExitWithPointer(returnValue)
    
    return returnValue;
}

int SoapSerializer::
setSOAPMethodAttribute( Attribute * pAttribute)
{
    logEntryEngine("SoapSerializer::setSOAPMethodAttribute")
    
    int iStatus = AXIS_FAIL;

    if( m_pSoapEnvelope &&
        (m_pSoapEnvelope->m_pSoapBody) &&
        (m_pSoapEnvelope->m_pSoapBody->m_pSoapMethod))
    {
        m_pSoapEnvelope->m_pSoapBody->m_pSoapMethod->addAttribute( pAttribute);

        iStatus = AXIS_SUCCESS;  
    }

    logExitWithReturnCode(iStatus)

    return iStatus;
}
void SoapSerializer::
clearSOAPMethodAttributes()
{
    logEntryEngine("SoapSerializer::clearSOAPMethodAttributes")

    if (m_pSoapEnvelope && m_pSoapEnvelope->m_pSoapBody
            && m_pSoapEnvelope->m_pSoapBody->m_pSoapMethod)
        m_pSoapEnvelope->m_pSoapBody->m_pSoapMethod->clearAttributes();
    
    logExit()
}

int SoapSerializer::
serializeAnyObject( AnyType * pAnyObject)
{
    logEntryEngine("SoapSerializer::serializeAnyObject")

    for( int i = 0; i < pAnyObject->_size; i++)
        serialize( pAnyObject->_array[i], 0);

    logExitWithReturnCode(AXIS_SUCCESS)

    return AXIS_SUCCESS;  
}

int SoapSerializer::
addOutputAnyObject( AnyType * pAnyObject)
{
    logEntryEngine("SoapSerializer::addOutputAnyObject")

    Param * pParam = new Param();

    pParam->m_Type = XSD_ANY;
    pParam->m_Value.pAnyObject = pAnyObject;

    if( m_pSoapEnvelope &&
        (m_pSoapEnvelope->m_pSoapBody) &&
        (m_pSoapEnvelope->m_pSoapBody->m_pSoapMethod))
        m_pSoapEnvelope->m_pSoapBody->m_pSoapMethod->addOutputParam( pParam);

    logExitWithReturnCode(AXIS_SUCCESS)

    return AXIS_SUCCESS;  
}

IHeaderBlock * SoapSerializer::
getHeaderBlock( const AxisChar * pcName, 
                const AxisChar * pcNamespace)
{
    logEntryEngine("SoapSerializer::getHeaderBlock")
 
    IHeaderBlock * returnValue = NULL;
    
    // there has been no <Header> element so there can be no Header blocks    
    if (m_pSoapEnvelope && m_pSoapEnvelope->m_pSoapHeader)
        returnValue = m_pSoapEnvelope->m_pSoapHeader->getHeaderBlock( pcName, pcNamespace, false);
    
    logExitWithPointer(returnValue)

    return returnValue;
}

IHeaderBlock * SoapSerializer::getFirstHeaderBlock()
{
    return m_pSoapEnvelope->m_pSoapHeader->getFirstHeaderBlock();
}

IHeaderBlock * SoapSerializer::getNextHeaderBlock()
{
    return m_pSoapEnvelope->m_pSoapHeader->getNextHeaderBlock();
}

int SoapSerializer::
serializeAsChardata( void * pValue, XSDTYPE type)
{
    logEntryEngine("SoapSerializer::serializeAsChardata")

    char * pStr = m_Buf;

    IAnySimpleType* pSimpleType = AxisUtils::createSimpleTypeObject(pValue, type);
    pStr = pSimpleType->serialize();

    *this << pStr;

    delete pSimpleType;
    
    logExitWithReturnCode(AXIS_SUCCESS)

    return AXIS_SUCCESS;  
}

void SoapSerializer::
serializeAttachments( SoapSerializer &pSZ)
{
    logEntryEngine("SoapSerializer::serializeAttachments")

    /*serializing the attachments*/
    map<AxisXMLString, ISoapAttachment*>::iterator itCurrAttach= m_SoapAttachments.begin();
    while( itCurrAttach != m_SoapAttachments.end())
    {
        SoapAttachment *att = ((SoapAttachment *) ((*itCurrAttach).second));
        if (NULL != att->getBody())
        {
            serialize( "\r\n--" MIMEBOUNDARY, NULL);
            att->serialize(pSZ);
        }
        itCurrAttach++;
    }
    pSZ.serialize("\r\n--" MIMEBOUNDARY "--\r\n", NULL);
    
    logExit()
}

void SoapSerializer::
addAttachment( const AxisChar * achId, ISoapAttachment * pAttach)
{
    m_SoapAttachments[achId] = pAttach;
}

void SoapSerializer::
addAttachments(ISoapAttachment** pAttach, int iAttchArraySize)
{   
     for (int i=0; i < iAttchArraySize; i++)
    {
         const char *id = ((ISoapAttachment*)pAttach[i])->getAttachmentId();
         m_SoapAttachments[id] = pAttach[i];
    }
 
}

void SoapSerializer::
addAttachmentHeader(const AxisChar * achId,
                    const AxisChar * achHeaderName,
                    const AxisChar * achHeaderValue)
{

    if (m_SoapAttachments[achId] == NULL)
        m_SoapAttachments[achId] = new SoapAttachment(m_pContentIdSet);        

    m_SoapAttachments[achId]->addHeader( achHeaderName, achHeaderValue);
}

void SoapSerializer::
addAttachmentBody( const AxisChar * achId,
                   xsd__base64Binary * pAttchBody)
{
    if( m_SoapAttachments[achId] == NULL)
        m_SoapAttachments[achId] = new SoapAttachment(m_pContentIdSet);        

    m_SoapAttachments[achId]->addBody( pAttchBody);
}

void SoapSerializer::
addNamespaceToEnvelope( AxisChar * pachNamespaceURI,
                        AxisChar * pachPrefix)
{
    logEntryEngine("SoapSerializer::addNamespaceToEnvelope")

    std::list<Attribute*> attributeList;
    Attribute * pNameSpace = new Attribute( attributeList, pachPrefix, "xmlns", pachNamespaceURI);

    m_pSoapEnvelope->addNamespaceDecl( pNameSpace);

    addNamespaceToNamespaceList( pachNamespaceURI, pachPrefix);
    
    logExit()
}

void SoapSerializer::addNamespaceToNamespaceList( const AxisChar * pachNamespaceURI,
                                                  const AxisChar * pachPrefix)
{
    m_NsStack[pachNamespaceURI] = pachPrefix;
}

ISoapAttachment* SoapSerializer::createSoapAttachment()
{
    return new SoapAttachment(m_pContentIdSet);
}

void SoapSerializer::setContentIdSet(ContentIdSet *pContentIdSet) 
{
    m_pContentIdSet = pContentIdSet;
}

bool SoapSerializer::checkAttachmentAvailability()
{
    map<AxisXMLString, ISoapAttachment*>::iterator itCurrAttach= m_SoapAttachments.begin();

    if( itCurrAttach != m_SoapAttachments.end())
        return true;

    return false;
}

void SoapSerializer::addAttachmentParameter(ISoapAttachment* att, const char* pName, IAttribute **attributes, int nAttributes)
{
    if (NULL==att)
        att = static_cast<ISoapAttachment*>(new SoapAttachment(m_pContentIdSet));
    SoapAttachmentReference *ref = new SoapAttachmentReference(static_cast<SoapAttachment*>(att));
    m_attachmentRefs.push_back(ref);

    Param *pParam = new Param();
    pParam->m_Value.pAttachmentRef = ref;
    pParam->m_Type = ATTACHMENT;

    if (NULL!=attributes && nAttributes>0) 
        ref->addAttributes(attributes,nAttributes);
    
    if (m_pSoapEnvelope &&
        (m_pSoapEnvelope->m_pSoapBody) &&
        (m_pSoapEnvelope->m_pSoapBody->m_pSoapMethod)) 
        m_pSoapEnvelope->m_pSoapBody->m_pSoapMethod->addOutputParam(pParam);
        
    pParam->setName(pName);
    m_SoapAttachments[att->getAttachmentId()] = att;
}

IHeaderBlock * SoapSerializer::getCurrentHeaderBlock()
{
    return m_pSoapEnvelope->m_pSoapHeader->getCurrentHeaderBlock();
}

AxisXMLString SoapSerializer::getNamespaceURL( string sNameSpace)
{
    // Check that the namespace value is not empty.  If it is then return as
    // there is nothing to do!
    if( sNameSpace.empty())
        return "nothing to do";

    // Iterate through the namespace stack.  If the namespace can be found, then
    // return the associated uri.
    map <AxisXMLString, AxisXMLString>::iterator    iterator = m_NsStack.begin();

    while( iterator != m_NsStack.end())
    {
        AxisXMLString    sIt_URI = iterator->first;
        AxisXMLString    sIt_NameSpace = iterator->second;

        if( sNameSpace == sIt_NameSpace)
            return iterator->first;
        else
            iterator++;
    }

    if (NULL==m_pSoapEnvelope->m_pSoapHeader) return "";

    // Couldn't find the namespace in the namespace list.  Try trawling through the
    // SOAP headers looking to see if any of their children have defined any
    // namespaces.
    IHeaderBlock *    pHeaderBlock = m_pSoapEnvelope->m_pSoapHeader->getFirstHeaderBlock();

    while( pHeaderBlock != NULL)
    {
        for( int iChildIndex = 0; iChildIndex < pHeaderBlock->getNoOfChildren(); iChildIndex++)
        {
            BasicNode *    pChild = pHeaderBlock->getChild( iChildIndex + 1);

            if( pChild != NULL)
                if( !strcmp( sNameSpace.c_str(), pChild->getPrefix()))
                    return pChild->getURI();
        }

        pHeaderBlock = m_pSoapEnvelope->m_pSoapHeader->getNextHeaderBlock();
    }

    // Couldn't find the namespace in the namespace list or in children.  Try
    // trawling through the SOAP headers looking to see if any of their attributes
    // have defined any namespaces.
    char *    pszNameSpace = (char *) sNameSpace.c_str();
    char *    pszValue = NULL;

    pHeaderBlock = m_pSoapEnvelope->m_pSoapHeader->getFirstHeaderBlock();

    while( pHeaderBlock != NULL && pszValue == NULL)
    {
        pszValue = (char *) pHeaderBlock->getAttributeUri( "", pszNameSpace);
        pHeaderBlock = m_pSoapEnvelope->m_pSoapHeader->getNextHeaderBlock();
    }

    if( pszValue == NULL)
        return "";

    return pszValue;
}


int SoapSerializer::
deleteHeaderBlock( const AxisChar * pName, const AxisChar * pNamespace)
{
    logEntryEngine("SoapSerializer::deleteHeaderBlock")

    int iStatus = AXIS_SUCCESS;

    iStatus = m_pSoapEnvelope->m_pSoapHeader->deleteHeaderBlock( pName, pNamespace);

    //No remaining soap header blocks, so will delete the SoapHeader    
    if( iStatus == AXIS_NO_REMAINING_SOAP_HEADERS)     
    {
        delete m_pSoapEnvelope->m_pSoapHeader;
        m_pSoapEnvelope->m_pSoapHeader = NULL;
        iStatus = AXIS_SUCCESS;
    }

    logExitWithReturnCode(iStatus)

    return iStatus; 
}

void SoapSerializer::
reset()
{
    logEntryEngine("SoapSerializer::reset")

    m_nCounter = 0; // reset namespace prifix counter 

    if( m_pSoapEnvelope )
        m_pSoapEnvelope->reset();
    
    logExit()
}

AXIS_CPP_NAMESPACE_END
