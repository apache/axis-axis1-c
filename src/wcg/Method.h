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

/*
 * @author Susantha Kumara (skumara@virtusa.com)
 *
 */
/* Method.h: interface for the Method class. */

#if !defined(AXIS_METHOD_H__INCLUDED_)
#define AXIS_METHOD_H__INCLUDED_

#include "Variable.h"
#include "File.h"
#include <list>
#include <string>

using namespace std;

class Method  
{
public:
    int GenerateOperationInBinding(File &file, string &sServiceName,
        int nBinding, int nStyle, string &sURI);
    int GenerateWSDLOperationInPortType(File& file);
    int GenerateWSDLMessages(File &file);
    int GenerateMethodImpl(string& sClassName, File& file);
    string& GetName();
    int GenerateMethodDef(File &file);
    void SetQualification(unsigned char sQualifier);
    void SetMethodName(string& sName);
    void AddParameter(Variable* pVar);
    void AddReturnType(Variable* pVar);
    Method();
    virtual ~Method();
private:
    string m_AuxStr;
    Variable* m_pReturnType;
    string m_Name;
    list<Variable*> m_Params;
    unsigned char m_Qualifier;
    /* private=1/protected=2/public=0/static=4/const=8/virtual=16 */
};

#endif
