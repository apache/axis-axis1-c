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


#if !defined(_IHANDLERSOAPDESERIALIZER_H____OF_AXIS_INCLUDED_)
#define _IHANDLERSOAPDESERIALIZER_H____OF_AXIS_INCLUDED_

#include "IWrapperSoapDeSerializer.h"
#include "IHeaderBlock.h"
#include "AxisUserAPI.h"
/**
    @class IHandlerSoapDeSerializer
    @brief interface for the IHandlerSoapDeSerializer class.


    @author Roshan Weerasuriya (roshan@jkcs.slt.lk, roshan@opensource.lk)
*/
#ifdef __cplusplus

class IHandlerSoapDeSerializer : public IWrapperSoapDeSerializer
{
public:
	virtual ~IHandlerSoapDeSerializer() {};
	virtual int AXISCALL addHeaderBlock(IHeaderBlock* pBlk)=0;
	/**
	 * The soap body may be encrypted/compressed and a handler in the request message 
	 * path may decode and then decrypt and/or decompress whole soap body and set the
	 * XML to the Deserializer. In such a case a handler will use following functions 
	 * to get soap body and set back the XML. If this process goes throgh several
	 * handlers the intermediate binary data (unencrypted/uncompressed body) may be kept 
	 * in the IMessageData until it is converted to XML. A handler usually converts it 
	 * to XML and use SetNewSoapBody(..) function to set the new SoapBody back to the 
	 * Deserializer.
	 */
	virtual xsd__hexBinary AXISCALL getBodyAsHexBinary()=0;
	virtual xsd__base64Binary AXISCALL getBodyAsBase64Binary()=0;
	virtual int AXISCALL setNewSoapBody(AxisChar* pNewSoapBody)=0;
	virtual IHeaderBlock* getHeaderBlock(const AxisChar* pName, const AxisChar* pNamespace) = 0;
};

#else

typedef struct { 
	void* unused; /* this corresponds to C++ virtual function pointer which is ignored in C */ 
	void* unused_; /* this corresponds to IWrapperSoapDeSerializerFunctions pointer */
	IHandlerSoapDeSerializerFunctions* __vfptr;
} IHandlerSoapDeSerializer;

#endif

#endif // !defined(_IHANDLERSOAPDESERIALIZER_H____OF_AXIS_INCLUDED_)
