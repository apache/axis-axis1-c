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


#if !defined(_ATTRIBUTE_H____OF_AXIS_INCLUDED_)
#define _ATTRIBUTE_H____OF_AXIS_INCLUDED_

#include "GDefine.h"

#ifdef __cplusplus
#include <string>
#include <list>

using namespace std;

class SoapSerializer;

#endif

/**
 *   @class Attribute
 *   @brief interface for the Attribute class.
 *
 *   @author Roshan Weerasuriya (roshan@opensource.lk, roshan@jkcs.slt.lk)
 *   @author Samisa Abeysinghe (sabeysinghe@virtusa.com)
 *   @author Susantha Kumara (susantha@opensource.lk, skumara@virtusa.com)
 *
 */

/*
 * Revision 1.1  2004/05/25 samisa
 * Added copy constructor
 */

/*
 * Revision 1.11  2004/06/13 susantha
 * Added support for writing C web services and handlers
 */

typedef struct {
	void (AXISCALL* setValue)(void* pObj, const AxisChar* value);
	/*add all other API functions here*/
} AttributeFunctions;

#ifdef __cplusplus

class Attribute  
{
public:        
	static AttributeFunctions ms_VFtable;
	static bool bInitialized;

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

    void setValue(const AxisChar* value);
    void setUri(const AxisChar* uri);
    void setPrefix(const AxisChar* prefix);
    void setLocalName(const AxisChar* localname);    

private:    
    bool isSerializable() const;
    AxisString m_localname;
    AxisString m_prefix;
    AxisString m_uri;
    AxisString m_value;

};

#endif

typedef struct { 
	void* _object; /* this will be C++ Call Object */
	AttributeFunctions* _functions; /* this is the static function table */
} Attribute_C;

#ifndef __cplusplus
typedef Attribute_C Attribute; 
#endif

#endif
