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

/* Method.cpp: implementation of the Method class. */

#ifdef WIN32
#pragma warning (disable : 4786)
#endif

#include <axis/wcg/Method.h>


/*
 * Features:
 * Limitations:
 *    1. All basic types are passed/returned to/from web service methods 
 *       by value.
 *    2. All user types are passed/returned to/from web service methods 
 *       by reference (pointers)
 *    3. No arrays can be passed or returned from web service methods.
 *    4. 
 *    5.
 */
Method::Method()
{
    m_Qualifier=0;
    m_Name="";
    m_pReturnType = NULL;
}

Method::~Method()
{
    if (m_pReturnType) delete m_pReturnType;
    for (list<Variable*>::iterator it = m_Params.begin(); 
    it != m_Params.end(); it++)
    {
        delete *it;
    }
}

void Method::AddReturnType(Variable *pVar)
{
    m_pReturnType = pVar;
}

void Method::AddParameter(Variable *pVar)
{
    m_Params.push_back(pVar);
}

void Method::SetMethodName(string &sName)
{
    m_Name = sName;
}

void Method::SetQualification(unsigned char sQualifier)
{
    m_Qualifier|=sQualifier;
}

/* generates wrapper method declaration  */
int Method::GenerateMethodDef(File &file)
{
    try 
    {
        file << "\tint" << " " << m_Name << "(IMessageData* mc);" << endl;
    }
    catch(...) /* any exception */
    {
        return 1;
    }
    return 0; /* success */
}

string& Method::GetName()
{
    return m_Name;
}

int Method::GenerateMethodImpl(string& sClassName, File &file)
{
    file << "int " << sClassName << "::" << m_Name << "(IMessageData* mc)" 
        << endl;     
    file << "{" << endl;
    file << "\tIWrapperSoapSerializer* pIWSSZ = NULL;" << endl;
    file << "\tmc->getSoapSerializer(&pIWSSZ);" << endl;
    file << "\tif (!pIWSSZ) return AXIS_FAIL;" << endl;
    file << "\tIWrapperSoapDeSerializer* pIWSDZ = NULL;" << endl;
    file << "\tmc->getSoapDeSerializer(&pIWSDZ);" << endl;
    file << "\tif (!pIWSDZ) return AXIS_FAIL;" << endl;
    file << "\tSetResponseMethod(mc, \"" << m_Name << "Response\");" << endl;
    int nParam = 0;
    for (list<Variable*>::iterator it = m_Params.begin(); 
    it != m_Params.end(); it++)
    {
        file << endl;
        file << "\tIParam *param" << nParam << " = pIWSDZ->GetParam();" 
            << endl;
        if ((*it)->IsComplexType())
        {
            file << "\t" << (*it)->GetTypeName() << "* v" << nParam << 
                " = new " << (*it)->GetTypeName() << "();" << endl;
            file << "\tparam" << nParam << "->" << "SetUserType(" << "v" 
                << nParam <<
                ", (AXIS_DESERIALIZE_FUNCT)Axis_DeSerialize_" << 
                (*it)->GetTypeName() <<
                ", (AXIS_OBJECT_DELETE_FUNCT)Axis_Delete_" << 
                (*it)->GetTypeName() << ");" << endl; 
            file <<    "\tpIWSDZ->Deserialize(param" << nParam << ",0);" 
                << endl; /* 0 should be changed to 1 if multiref to be used */
        }
        else if ((*it)->IsArrayType())
        {
            
        }
        else /* basic types */
        {
            file << "\t" << (*it)->GetTypeName() << " v" << nParam << " = " << 
                "param" << nParam << "->" << 
                Variable::GetParamGetMethod((*it)->GetType()) << "();" << endl;
        }
        nParam++;
    }
    file << endl;
    file << "\t//Call actual web service method with appropriate parameters" 
        << endl;
    file << "\t" << m_pReturnType->GetTypeName();
    if (m_pReturnType->IsComplexType()) 
    {
        file << "*";
        /* this is because of the convention that all user types return by 
         * reference (pointer)
         */
    }
    file << " ret = pWs->" << m_Name << "(";
    for (int n=0; n<nParam;)
    {
        file << "v" << n++;
        if (n<nParam) file << ", ";
    }
    file << ");" << endl;
    file << endl;
    if (m_pReturnType->IsComplexType()) 
    {
        file << "\tIParam* pRetParam = pIWSSZ->AddOutputParam(ret, 
            (AXIS_SERIALIZE_FUNCT)Axis_Serialize_" <<
        m_pReturnType->GetTypeName() << ", 
        (AXIS_OBJECT_DELETE_FUNCT)Axis_Delete_" << m_pReturnType->GetTypeName()
        << ");" << endl;        
    }
    else
    {
        file << "\tuParamValue value;" << endl;
        file << "\tvalue." << m_pReturnType->GetCorrespondingUnionMemberName() 
            << " = ret";
        if (m_pReturnType->GetType() == VAR_STRING)
        {
            file << ".c_str()";
        }
        file <<    ";" << endl;
        file << "\tIParam* pRetParam = pIWSSZ->AddOutputParam(" << 
            m_pReturnType->GetTypeEnumStr() << ", value);" << endl;
    }
    file << "\tpRetParam->SetName(\"" << m_Name << "Return\");" << endl;
    file << "\treturn AXIS_SUCCESS;" << endl; 
    file << "}" << endl;
    file << endl;
    return 0;
}

int Method::GenerateWSDLMessages(File &file)
{
    file << "<message name=\"" << m_Name << "Request\">" << endl;
    for (list<Variable*>::iterator it = m_Params.begin(); it != m_Params.end();
    it++)
    {
        (*it)->GenerateWSDLPartInMessage(file, true);
    }
    file << "</message>" << endl;
    if (m_pReturnType)
    {
        file << "<message name=\"" << m_Name << "Response\">" << endl;
        m_pReturnType->GenerateWSDLPartInMessage(file, false);
        file << "</message>" << endl;
    }
    return 0; /* success */
}

int Method::GenerateWSDLOperationInPortType(File &file)
{
    file << "<operation name=\"" << m_Name << "\">" << endl;
    file << "<input message=\"impl:" << m_Name << "Request\" />" << endl; 
    file << "<output message=\"impl:" << m_Name << "Response\" />" << endl; 
    file << "</operation>" << endl;
    return 0;
}

int Method::GenerateOperationInBinding(File &file, string &sServiceName,
                                       int nBinding, int nStyle, string &sURI)
{
    file << "<operation name=\"" << m_Name << "\">" << endl;
    switch (nBinding)
    {
    case SOAP_BINDING: 
    {
        file << "<soap:operation soapAction=\"" << sServiceName << 
            "\" style=\""; /* service name should be in soapAction */
        switch (nStyle)
        {
        case SOAP_RPC: 
        {    
            file << "rpc\" />" << endl;
            file << "<input>" << endl;
            file << "<soap:body use=\"encoded\" namespace=\"http://" <<
                sURI << "/\" encodingStyle=\
                \"http://schemas.xmlsoap.org/soap/encoding/\" />" 
                << endl;
            file << "</input>" << endl;
            file << "<output>" << endl;
            file << "<soap:body use=\"encoded\" namespace=\"http://" 
                << sURI << "/\" encodingStyle=\
                \"http://schemas.xmlsoap.org/soap/encoding/\" />" 
                << endl; 
            file << "</output>" << endl;
        }
        break;
        case SOAP_DOCUMENT: 
        {
            file << "document\" />" << endl; 
            file << "<input>" << endl;
            file << "<soap:body use=\"literal\" />" << endl; 
            file << "</input>" << endl;
            file << "<output>" << endl;
            file << "<soap:body use=\"literal\" />" << endl; 
            file << "</output>" << endl;
        }
        break;
        default: return 1; /* error */
        }
    }
        break;
    case HTTP_BINDING: 
    {
            
    }
    break;
    default: return 1; /* error */
    }
    file << "</operation>" << endl;
    return 0;
}
