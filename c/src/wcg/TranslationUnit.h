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

#ifdef WIN32
#pragma warning (disable : 4786)
#endif


/* TranslationUnit.h: interface for the TranslationUnit class. */


#if !defined(AXIS_HEADERFILE_H__INCLUDED_)
#define AXIS_HEADERFILE_H__INCLUDED_

#include "WSClass.h"
#include "BeanClass.h"

#include <string>
#include <list>
using namespace std;

class TranslationUnit  
{
public:
    int GenerateWSDLBinding(File& file, string& sServiceName, int nBinding,
        int nStyle, int nTransport, string& sURI);
    int GenerateServiceFile(string& sServiceFile);
    void SetWsFileName(const char* sFileName);
    void AddBeanClass(BeanClass* pClass);
    void SetWSClass(WSClass* pClass);
    void AddNSDecl(string& sNSDecl);
    void AddInclude(string& sInclude);
    int GenerateWrapperClassImpl();
    int GenerateWrapperClassDef();
    int GenerateWSDL(string& sServiceFile, string& sURI);
    TranslationUnit();
    virtual ~TranslationUnit();
private:
    string m_sWsFileName;
    list<string> m_includes;
    list<string> m_nsdecls;
    WSClass *m_pWSClass;
    /* there can be only one web service class per header file. */
    list<BeanClass*> m_Beans;
};

#endif
