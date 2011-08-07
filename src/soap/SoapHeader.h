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

#if !defined(_SOAPHEADER_H____OF_AXIS_INCLUDED_)
#define _SOAPHEADER_H____OF_AXIS_INCLUDED_

#include "Attribute.h"
#include "HeaderBlock.h"
#include <list>
using namespace std;

typedef enum
{
    HEADER_LEVEL=0, HEADER_BLOCK_LEVEL, HEADER_BLOCK_INSIDE_LEVEL
} HEADER_LEVELS;

AXIS_CPP_NAMESPACE_START
class Attribute;

/**
 * @class SoapHeader
 * @brief    The Header element information item according to SOAP 1.2 specification
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
 * Each child element information item of the SOAP Header is called a SOAP header block.
 *
 */ 

class SoapHeader
{
private:    
    int serializeNamespaceDecl(SoapSerializer& pSZ);
    
    int serializeAttributes(SoapSerializer& pSZ);
    
    list<Attribute*> m_attributes;
    list<Attribute*> m_namespaceDecls;
    list<IHeaderBlock*> m_headerBlocks;
    list<IHeaderBlock*>::iterator m_itHeaderBlocks;
    
    const char* m_pcPrefix;
public:
    IHeaderBlock* getCurrentHeaderBlock();
    /**
      * Gets and returns the Header Block, of the given name.
      *
      * @param pName The local name of the requested Header Block.
      * @param pNamespace The namespace uri of the requested Header Block.
      * @return A pointer to the requested Header Block will be returned if
      * found or else if not found a NULL pointer will be retured. In case of
      * the requested Header Block is found, also it will be removed from the
      * list of Header Blocks of this Soap Header, before returning a pointer.
      */
    IHeaderBlock* getHeaderBlock(const AxisChar* pName, const AxisChar* pNamespace, bool bRemoveOrNot);
 
     /**
      * Returns the first header block
      */
     IHeaderBlock* getFirstHeaderBlock();
 
     /**
      * Returns the next header block, or null if there are no more
      */
     IHeaderBlock* getNextHeaderBlock();

    /**
      * Sets the Prefix of the Header Block.
      *
      * @param pcPrefix The prefix to set.
      */
    int setPrefix(const char* pcPrefix);

    /**
     * Removes the next HeaderBlock from the list and returns it. 
     * But will not delete it.
     * @return The removed HeaderBlock of the list.
     */
    IHeaderBlock* getHeaderBlock(bool bRemoveOrNot);

    /**
      * Sets the namespace declaration of the Soap Header.  Object will be owned by the class.
      *
      * @param pAttribute The Attribute pointer which points to a valid 
      * namespace declartion Attribute.
      * @return AXIS_SUCCESS to indicate successfull operation. Return 
      *  AXIS_FAIL to indicate unsuccessfull operation.
      */
    int addNamespaceDecl(Attribute* pAttribute);

    /**
      * Adds a Attribute to this Soap Header. Object will be owned by the class.
      *
      * @param attr The Attribute to be added.
      * @return AXIS_SUCCESS to indicate successfull operation. Return
      *  AXIS_FAIL to indicate unsuccessfull operation.
      */
    int addAttribute(Attribute* pAttribute);
    
    /**
     * Serialize the SOAP header.
     */
    int serialize(SoapSerializer& pSZ, SOAP_VERSION eSoapVersion);
    
    /**
      * Adds a Header Block to this Soap Header. Note that the object is still owned
      * by the caller and will not be deleted by this class.
      *
      * @param headerBlock The Header Block to be added.
      */
    void addHeaderBlock(IHeaderBlock* headerBlock);

    /**
      * Removes a header block from the header block list.
      */
    int deleteHeaderBlock(const AxisChar *pName, const AxisChar *pNamespace);

    /**
      * The Constructor.
      */
    SoapHeader();

    /**
      * The Destructor.
      */
    virtual ~SoapHeader();

    /**
     * Clears all previously set information by calling clearHeaderBlocks(),
     * clearAttributes(), and clearNamespaceDecls().
     */
    void clear();

    /**
     * Clears header blocks. Note that the header blocks are not deleted, just cleared from
     * the instance.
     */
    void clearHeaderBlocks();

    /**
     * Clears any attributes by actually deleting the objects representing the attributes.
     */
    void clearAttributes();

    /**
     * Clears any namespace declarations by deleting the objects representing the namespace
     * declarations.
     */
    void clearNamespaceDecls();
};
AXIS_CPP_NAMESPACE_END
#endif 

