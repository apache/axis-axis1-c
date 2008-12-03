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

#if !defined(SOAPATTACHMENTREFERENCE_H__INCLUDED_)
#define SOAPATTACHMENTREFERENCE_H__INCLUDED_

#include <axis/GDefine.hpp>
#include <axis/IAttribute.hpp>
#include "SoapAttachment.hpp"
#include <list>

using namespace std;

AXIS_CPP_NAMESPACE_START

class SoapSerializer;
class Attribute;

class SoapAttachmentReference
{
private:    
    SoapAttachment *m_attachment;
    list<Attribute*> m_attributes;

public:    
    SoapAttachmentReference(SoapAttachment *att);
    virtual ~SoapAttachmentReference();    
    SoapAttachment* getAttachment();
    void serialize(SoapSerializer& pSZ, const char *name);
    void addAttributes(IAttribute **attributes, int nAttributes);
};

AXIS_CPP_NAMESPACE_END

#endif // !defined(SOAPATTACHMENTREFERENCE_H__INCLUDED_)

