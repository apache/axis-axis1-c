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

/* WSClass.h: interface for the WSClass class. */


#if !defined(AXIS_WSCLASS_H__OF_AXIS_INCLUDED_)
#define AXIS_WSCLASS_H__OF_AXIS_INCLUDED_

#include "Variable.h"
#include "Method.h"
#include "File.h"

#include <list>
using namespace std;

class WSClass  
{
public:
    int GenerateOperationsInBinding(File& file, string& sServiceName, 
        int nBinding, int nStyle, string& sURI);
    int GenerateWSDLPortTypes(File& file, string& sServiceName);
    int GenerateWSDLMessages(File& file);
    int GenerateClassImpl(File& file);
    int GenerateClassDef(File& file);
    const string& GetName();
    void SetDestructor(Method* pMethod);
    void AddMethod(Method* pMethod);
    void AddConstructor(Method* pMethod);
    void AddVariable(Variable* pVar);
    void SetClassName(string& sName);
    WSClass();
    virtual ~WSClass();
private:
    string m_AWSName;
    string m_Name;
    list<Variable*> m_Variables;
    list<Method*> m_Constructors;
    Method* m_pDestructor;
    list<Method*> m_Methods;
};

#endif
