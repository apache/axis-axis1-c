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

#if !defined(_IHANDLERSOAPSERIALIZER_H____OF_AXIS_INCLUDED_)
#define _IHANDLERSOAPSERIALIZER_H____OF_AXIS_INCLUDED_

#include "IWrapperSoapSerializer.h"
#include "SoapHeader.h"
class IHeaderBlock;
/*
 *   @class IHandlerSoapSerializer
 *   @brief interface for the IHandlerSoapSerializer class.
 * 
 *   @author Roshan Weerasuriya (roshan@jkcs.slt.lk, roshan@opensource.lk)
 */
class IHandlerSoapSerializer : public IWrapperSoapSerializer

{
public:        
    virtual ~IHandlerSoapSerializer() {};
    virtual IHeaderBlock* createHeaderBlock()=0;
    virtual IHeaderBlock*  createHeaderBlock(AxisChar *pachLocalName, 
		AxisChar *pachUri)=0;    
    virtual int AXISCALL addHeaderBlock(IHeaderBlock* pBlk)=0;
    virtual int setSoapHeader(SoapHeader* pSoapHeader)=0;
    virtual    int setSoapVersion(SOAP_VERSION)=0;
	virtual IHeaderBlock* getHeaderBlock() = 0;
	virtual IHeaderBlock* getHeaderBlock(const AxisChar *pcName, 
											 const AxisChar *pcNamespace) = 0;
        
    /*
     * A handler may get the entire soap body and encrypt/compress 
     * it and encode to either base64Binary or hexBinary before 
     * sending to the trasport. So any handler in the response message 
     * path may use following functions to get the entire soap 
     * body / set encrypted and/or compressed and then encoded soap body
     * back to the Serializer
     */

    virtual int AXISCALL setBodyAsHexBinary(xsd__hexBinary body)=0;
    virtual int AXISCALL setBodyAsBase64Binary(xsd__base64Binary body)=0;
    virtual const AxisChar* AXISCALL getBodyAsString()=0;
};

#endif 

