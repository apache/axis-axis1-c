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


#if !defined(_IHANDLERSOAPDESERIALIZER_H____OF_AXIS_INCLUDED_)
#define _IHANDLERSOAPDESERIALIZER_H____OF_AXIS_INCLUDED_

/**
 * @file IHandlerSoapDeSerializer.hpp
 */

#include <axis/IWrapperSoapDeSerializer.hpp>
#include <axis/IHeaderBlock.hpp>
#include <axis/AxisUserAPI.hpp>

/**
 *  @class IHandlerSoapDeSerializer
 *  @brief interface for the IHandlerSoapDeSerializer class.
 *
 */

AXIS_CPP_NAMESPACE_START

class IHandlerSoapDeSerializer : public IWrapperSoapDeSerializer
{
public:
    virtual ~IHandlerSoapDeSerializer() {};
    
    /*
     * The soap body may be encrypted/compressed and a handler in the request message
     * path may decode and then decrypt and/or decompress whole soap body and set the
     * XML to the Deserializer. In such a case a handler will use following functions
     * to get soap body and set back the XML. If this process goes throgh several
     * handlers the intermediate binary data (unencrypted/uncompressed body) may be kept
     * in the IMessageData until it is converted to XML. A handler usually converts it
     * to XML and use SetNewSoapBody(..) function to set the new SoapBody back to the Deserializer.
     */

    /**
     * Gets and returns the SOAP body as HexBinary data.
     * 
     * @return SOAP Body as HexBinary data
     */
    virtual xsd__hexBinary AXISCALL getBodyAsHexBinary()=0;
    
    /**
     * Gets and returns the SOAP boday as Base64Binary data.
     * 
     * @return SOAP body as Base64Binary data.
     */
    virtual xsd__base64Binary AXISCALL getBodyAsBase64Binary()=0;
    
    /**
     * Gets and returns the SOAP body as a string.
     * 
     * @return SOAP body as a string.
     */
    virtual AxisChar* AXISCALL getBodyAsChar()=0;
    
    /**
     * Sets a new SOAP body from a string
     * 
     * @param pNewSoapBody new SOAP body as a string.
     * @return status
     */
    virtual int AXISCALL setNewSoapBody(AxisChar* pNewSoapBody)=0;

    /**
     * Gets and returns the Header Block of the given local name and 
     * namespace uri. After returning the Header Block pointer, it will be
     * removed from the available Header Block list of the DeSerializer.
     * It is the responsibilty of the caller of this method to delete the
     * returned pointer object, to avoid memory leaks.
     * 
     * @param pName local name of header block.
     * @param pNamespace namespare URI of header block.
     * @return HeaderBlock
     */
    virtual IHeaderBlock* getHeaderBlock(const AxisChar* pName, const AxisChar* pNamespace) = 0;
};

AXIS_CPP_NAMESPACE_END

#endif 


