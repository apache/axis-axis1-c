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
 */

#if !defined(_SOAPHEADER_H____OF_AXIS_INCLUDED_)
#define _SOAPHEADER_H____OF_AXIS_INCLUDED_

#include "HeaderBlock.h"
#include "SoapEnvVersions.h"
#include "ISoapHeader.h"

/*
 * @class SoapHeader
 * @brief    The Header element information item according to SOAP 
 *           1.2 specification
 * 
 * The Header element information item according to SOAP 1.2 specification.
 * The Header element information item has:
 *  1) A [local name] of Header.
 *  2) A [namespace name] of "http://www.w3.org/2003/05/soap-envelope".
 *  3) Zero or more namespace qualified attribute information items 
 *     in its [attributes] property.
 *  4) Zero or more namespace qualified element information items 
 *     in its [children] property.
 *
 * Each child element information item of the SOAP Header is called 
 * a SOAP header block.
 *
 *
 * @author Roshan Weerasuriya (roshan@jkcs.slt.lk, roshan@opensource.lk)
 */ 

typedef enum 
{ 
    HEADER_LEVEL=0, HEADER_BLOCK_LEVEL, HEADER_BLOCK_INSIDE_LEVEL
} HEADER_LEVELS;

class SoapHeader : public ISoapHeader
{
private:    
    int serializeNamespaceDecl(SoapSerializer& pSZ);
    /* int serializeNamespaceDecl(string&); */
    int serializeAttributes(SoapSerializer& pSZ);
    /* int serializeAttributes(string&); */
    list<Attribute*> m_attributes;
    list<Attribute*> m_namespaceDecls;
    list<HeaderBlock*> m_headerBlocks;
    /* string m_strHeaderSerialized; */
    const char* m_pcPrefix;
public:
    IHeaderBlock* getHeaderBlock(const AxisChar* pName, 
        const AxisChar* pNamespace);
    int setPrefix(const char* pcPrefix);
    /*
     * Removes the next HeaderBlock from the list and returns it. 
     * But will not delete it. @return The removed HeaderBlock of the list.
     */
    IHeaderBlock* getHeaderBlock();
    int addNamespaceDecl(Attribute* pAttribute);
    int addAttribute(Attribute* pAttribute);
    /* string& serialize(); */
    int serialize(SoapSerializer& pSZ, SOAP_VERSION eSoapVersion);
    /* int serialize(string&, SOAP_VERSION eSoapVersion); */
    void addHeaderBlock(HeaderBlock* headerBlock);

    SoapHeader();
    virtual ~SoapHeader();

};

#endif 

