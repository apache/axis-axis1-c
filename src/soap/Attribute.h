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

 /**
 * @file Attribute.h
 *
 *
 */
 
#if !defined(_ATTRIBUTE_H____OF_AXIS_INCLUDED_)
#define _ATTRIBUTE_H____OF_AXIS_INCLUDED_

#include <axis/GDefine.hpp>
#include <axis/IAttribute.hpp>
#include <list>
#include <string>

AXIS_CPP_NAMESPACE_START
using namespace std;

class SoapSerializer;

/**
 *   @class Attribute
 *   @brief interface for the Attribute class.
 *
 *   @author Roshan Weerasuriya (roshan@opensource.lk, roshanw@jkcsworld.com)
 *   @author Samisa Abeysinghe (sabeysinghe@virtusa.com)
 *   @author Susantha Kumara (susantha@opensource.lk, skumara@virtusa.com)
 *
 */

class Attribute : public IAttribute
{
public:        
#ifdef UNIT_TESTING_ON
    int initializeForTesting();
#endif
    int serialize(SoapSerializer& pSZ) const;
    int serialize(SoapSerializer& pSZ, list<AxisChar*>& lstTmpNameSpaceStack);

    Attribute();    
    Attribute(const AxisChar* localname, const AxisChar* prefix, 
        const AxisChar* uri, const AxisChar* value);
    Attribute(const AxisChar* localname, const AxisChar* prefix, 
        const AxisChar* value);
    Attribute(const Attribute& rCopy);   
    Attribute* clone(); 
    virtual ~Attribute();

    int setValue(const AxisChar* value);
    int setURI(const AxisChar* uri);
    int setPrefix(const AxisChar* prefix);
    int setLocalName(const AxisChar* localname);

    const AxisChar* getValue();
    const AxisChar* getURI();
    const AxisChar* getPrefix();
    const AxisChar* getLocalName();

private:    
    bool isSerializable() const;
    AxisString m_localname;
    AxisString m_prefix;
    AxisString m_uri;
    AxisString m_value;

};

AXIS_CPP_NAMESPACE_END

#endif

