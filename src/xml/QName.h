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
 * @author Roshan Weerasuriya (roshan@jkcs.slt.lk)
 *
 */


#if !defined(AXIS_QNAME_H__OF_AXIS_INCLUDED_)
#define AXIS_QNAME_H__OF_AXIS_INCLUDED_

#include <axis/GDefine.hpp>

/*
 *    Qualified name according to "Namespaces in XML" specification.
 *    
 *    QName      ::=  (Prefix ':')? LocalPart          <br>
 *    Prefix      ::=  NCName                          <br>
 *    LocalPart ::=  NCName                            <br>
 *    NCName      ::=  (Letter | '_') (NCNameChar)*  ;  
 *    An XML Name, minus the ":"                       <br>
 *    NCNameChar ::=  Letter | Digit | '.' | '-' | '_' etc.   <br>
 *    The Prefix provides the namespace prefix part of the qualified name,
 *    and must 
 *    be associated with a namespace URI reference in a namespace declaration. 
 *    The LocalPart provides the local part of the qualified name. 
 *    Note that the prefix functions only as a placeholder 
 *    for a namespace name. 
 *    Applications should use the namespace name, not the prefix, 
 *    in constructing 
 *    names whose scope extends beyond the containing document.
 *
 *    
 *    @brief    Qualified name according to "Namespaces in XML" specification
 */

#define NAMESPACESEPARATOR 0x03 /* Heart */

class QName  
{
public:
    const XML_Ch* uri;
    const XML_Ch* localname;

public:
    QName();
    virtual ~QName();
    void splitQNameString(const XML_Ch* qname, XML_Ch sep);
    void mergeQNameString(XML_Ch sep);
};

#endif 


