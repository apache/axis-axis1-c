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

/* Variable.h: interface for the Variable class. */

#ifdef WIN32
#pragma warning (disable : 4786)
#endif

#if !defined(AXIS_VARIABLE_H__INCLUDED_)
#define AXIS_VARIABLE_H__INCLUDED_

#include "File.h"

#include <string>
#include <list>
#include <map>

using namespace std;

enum VARTYPE { VAR_UNKNOWN=0, VAR_INT=1, VAR_FLOAT, VAR_STRING, VAR_LONG, \
               VAR_SHORT, VAR_CHAR, VAR_DOUBLE, VAR_BOOL, VAR_UNSIGNEDLONG, \
               VAR_UNSIGNEDINT, VAR_UNSIGNEDSHORT, VAR_UNSIGNED_CHAR, \
               VAR_USER };
enum WSDL_BINDINGS { SOAP_BINDING=1, HTTP_BINDING };
enum BINDING_STYLES { SOAP_RPC=1, SOAP_DOCUMENT, HTTP_GET, HTTP_POST};
enum WSDL_TRANSPORT { HTTP_TRANSPORT=1 };

/* Qualifiers */
const unsigned char Q_PRIVATE = 0x01;
const unsigned char Q_PROTECTED = 0x02;
const unsigned char Q_STATIC = 0x04;
const unsigned char Q_CONST = 0x08;
const unsigned char Q_VIRTUAL = 0x10;
const unsigned char Q_REFTYPE = 0x20;
const unsigned char Q_PTRTYPE = 0x40;
const unsigned char Q_PTRPTRTYPE = 0x80;

class Variable  
{
public:    
    int GenerateWSDLPartInMessage(File& file, bool bInput);
    int GenerateWSDLSchema(File &file);
    static string& GetParamGetMethod(int nType);
    int GenerateDeserializerImpl(File& file);
    int GenerateSerializerImpl(File& file);
    string& GetTypeEnumStr();
    string& GetCorrespondingUnionMemberName();
    void Reset();
    int GetType();
    bool IsArrayType();
    bool IsComplexType();
    string& GetVarName();
    string& GetTypeName();
    void SetVarName(string& sVarName);
    void SetType(int nType, string sType="");
    void SetQualification(unsigned char cQualifier);
    Variable();
    Variable(Variable& Var);
    virtual ~Variable();
private:
    static string m_sAuxStr;
    void SetBasicTypeName();
    int m_Type;
    string m_TypeName; /* if m_Type is user type */
    string m_VarName;
    list<int> m_ArrayIndexes;
    unsigned char m_Qualifier;
    /* private=1/protected=2/public=0/static=4/const=8/reference 
     * type=16/pointer type=32/pointer to pointer type=64 
     */
};

extern map<string, string> g_ClassNamespaces;

#endif
