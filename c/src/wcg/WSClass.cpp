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

/* WSClass.cpp: implementation of the WSClass class. */

#ifdef WIN32
#pragma warning (disable : 4786)
#endif

#include "WSClass.h"

WSClass::WSClass()
{
    m_Name = "";
    m_pDestructor = NULL;
}

WSClass::~WSClass()
{
    for(list<Variable*>::iterator it = m_Variables.begin(); 
    it != m_Variables.end(); it++)
    {    
        delete *it;
    }
    list<Method*>::iterator it1;
    for( it1 = m_Constructors.begin(); it1 != m_Constructors.end(); it1++)
    {    
        delete *it1;
    }
    for (it1 = m_Methods.begin(); it1 != m_Methods.end(); it1++)
    {
        delete *it1;
    }
    if (m_pDestructor) delete m_pDestructor;

}

void WSClass::SetClassName(string &sName)
{
    m_AWSName = sName;
    m_Name = sName + "Wrapper";
}

void WSClass::AddVariable(Variable *pVar)
{
    m_Variables.push_back(pVar);
}

void WSClass::AddConstructor(Method *pMethod)
{
    m_Constructors.push_back(pMethod);
}

void WSClass::AddMethod(Method *pMethod)
{
    m_Methods.push_back(pMethod);
}

void WSClass::SetDestructor(Method *pMethod)
{
    m_pDestructor = pMethod;
}

const string& WSClass::GetName()
{
    return m_Name;
}

int WSClass::GenerateClassDef(File &file)
{
    try {
        /* add wrapper class */
        file << "class " << m_Name << " : public WrapperClassHandler" << endl 
            << "{" << endl;
        file << "public:" << endl;
        /* default constructor */
        file << "\t" << m_Name << "();" << endl; 
        /* destructor */
        file << "\tvirtual ~" << m_Name << "();" << endl; 
        file << "public:" << "//implementation of WrapperClassHandler \
            interface" << endl;    
        file << "\tint Invoke(IMessageData* mc);" << endl;         
        file << "\tvoid OnFault(IMessageData* pMsg);" << endl;         
        file << "\tint Init();" << endl;         
        file << "\tint Fini();" << endl;     
        file << "private:" << "//Methods corresponding to the web service \
            methods" << endl;
        file << "\tint SetResponseMethod(IMessageData* mc, \
            const AxisChar* name);" << endl;             
        /* wrapper methods for each webservice method */
        for (list<Method*>::iterator it = m_Methods.begin(); 
        it != m_Methods.end(); it++)
        {
            (*it)->GenerateMethodDef(file);
        }
        file << "private:" << "// Actual web service object" << endl;
        file << "\t" << m_AWSName << " *pWs;" << endl; 
        file << "};" << endl;    
    }
    catch(...) /* any exception */
    {
        return 1;
    }
    return 0; /* success */
}

int WSClass::GenerateClassImpl(File &file)
{
    try {
        /* default constructor */
        file << m_Name << "::" << m_Name << "()" << endl;
        file << "{" << endl;
        file << "\tpWs = new " << m_AWSName << "();" << endl;
        file << "}" << endl;
        file << endl;
        /* destructor */
        file << m_Name << "::~" << m_Name << "()" << endl;
        file << "{" << endl;
        file << "\tdelete pWs;" << endl; 
        file << "}" << endl;
        file << endl;

        /* implementation of WrapperClassHandler interface */
        file << "// Implementation of WrapperClassHandler interfaces." << endl;
        file << "int " << m_Name << "::Invoke(IMessageData* mc)" << endl;         
        file << "{" << endl;
        file << "\tIWrapperSoapDeSerializer* pIWSDZ = NULL;" << endl;
        file << "\tmc->getSoapDeSerializer(&pIWSDZ);" << endl;
        file << "\tif (!pIWSDZ) return AXIS_FAIL;" << endl;
        file << "\tconst AxisChar* method = pIWSDZ->GetMethodName();" << endl;
        bool tab = true;
        list<Method*>::iterator it;
        for (it = m_Methods.begin(); it != m_Methods.end(); it++)
        {    
            if (tab)
            {
                file << "\t";
                tab = false;
            }
            file << "if (0 == strcmp(method, \"" << (*it)->GetName() << "\"))" 
                << endl;
            file << "\t\treturn " << (*it)->GetName() << "(mc);" << endl;
            file << "\telse ";
        }
        file << "return AXIS_FAIL;" << endl;
        file << "}" << endl;
        file << endl;

        file << "void " << m_Name << "::OnFault(IMessageData* pMsg)" << endl;         
        file << "{" << endl;
        file << "}" << endl;
        file << endl;

        file << "int " << m_Name << "::Init()" << endl;         
        file << "{" << endl;
        file << "\treturn 0;" << endl; 
        file << "}" << endl;
        file << endl;

        file << "int " << m_Name << "::Fini()" << endl;     
        file << "{" << endl;
        file << "\treturn 0;" << endl; 
        file << "}" << endl;
        file << endl;

        file << "int " << m_Name << "::SetResponseMethod(IMessageData* mc, \
            const AxisChar* name)" << endl;             
        file << "{" << endl;
        file << "\tAxisString method = name;" << endl;
        file << "\tIWrapperSoapSerializer* pIWSSZ = NULL;" << endl;
        file << "\tmc->getSoapSerializer(&pIWSSZ);" << endl;
        file << "\tif (!pIWSSZ) return AXIS_FAIL;" << endl;
        file << "\tISoapMethod* pMethod = pIWSSZ->createSoapMethod();" << endl;
        file << "\tpMethod->setLocalName(name);" << endl;
        file << "\tpMethod->setPrefix(pIWSSZ->getNewNamespacePrefix());"<<endl; 
        file << "\tpMethod->setUri(\"" << g_ClassNamespaces[m_AWSName] 
            << "\");"<< endl;
        /* http://www.opensource.lk will come from wsdd */
        file << "\treturn AXIS_SUCCESS;" << endl; 
        file << "}" << endl;
        file << endl;

        /* wrapper methods for each webservice method */
        for (it = m_Methods.begin(); it != m_Methods.end(); it++)
        {
            (*it)->GenerateMethodImpl(m_Name, file);
        }
    }
    catch(...) /* any exception */
    {
        return 1;
    }
    return 0; /* success */
}

int WSClass::GenerateWSDLMessages(File &file)
{
    for (list<Method*>::iterator it = m_Methods.begin(); 
    it != m_Methods.end(); it++)
    {
        if ((*it)->GenerateWSDLMessages(file)) return 1; /* error occured; */
    }
    return 0; /* success; */
}

int WSClass::GenerateWSDLPortTypes(File &file, string& sServiceName)
{
    file << "<portType name=\"" << sServiceName << "PortType\">" << endl;
    for (list<Method*>::iterator it = m_Methods.begin(); 
    it != m_Methods.end(); it++)
    {
        if ((*it)->GenerateWSDLOperationInPortType(file)) return 1;
        /* error occured; */
    }
    file << "</portType>" << endl;
    return 0; /* success; */
}


int WSClass::GenerateOperationsInBinding(File &file, string &sServiceName, 
                                         int nBinding, int nStyle, 
                                         string &sURI)
{
    for (list<Method*>::iterator it = m_Methods.begin(); it != m_Methods.end();
    it++)
    {
        if ((*it)->GenerateOperationInBinding(file, sServiceName, nBinding, 
            nStyle, sURI)) return 1; /* error occured; */
    }
    return 0; /* success */
}
