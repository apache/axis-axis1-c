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

#include <axis/wcg/BeanClass.h>


BeanClass::BeanClass()
{

}

BeanClass::~BeanClass()
{
    for (list<Variable*>::iterator it = m_Variables.begin(); 
    it != m_Variables.end(); it++)
    {
        delete *it;
    }
}

void BeanClass::AddVariable(Variable *pVar)
{
    m_Variables.push_back(pVar);
}

void BeanClass::SetClassName(string &sName)
{
    m_Name = sName;
}

int BeanClass::GenerateSerializerAndDeSerializerImpl(File &file)
{
    list<Variable*>::iterator it;
    file << "//Parameters and wrapper methos to manipulate Point" << endl;
    file << "static const AxisChar* Axis_URI_" << m_Name << 
        " = \"http://www.opensource.lk/" << m_Name << "\";" << endl;
    file << "static const AxisChar* Axis_TypeName_" << m_Name << 
        " = \"" << m_Name << "\";" << endl;
    file << endl;
    file << "int Axis_DeSerialize_" << m_Name << "(" << m_Name << 
        "* p, IWrapperSoapDeSerializer *pDZ)" << endl;
    file << "{" << endl;
    for (it = m_Variables.begin(); it != m_Variables.end(); it++)
    {
        (*it)->GenerateDeserializerImpl(file);
    }    
    file << "\treturn AXIS_SUCCESS;" << endl;
    file << "}" << endl;
    file << endl;

    file << "int Axis_Serialize_" << m_Name <<  "(" << m_Name << 
        "* p, IWrapperSoapSerializer& pSZ, bool bArray = false)" << endl;
    file << "{" << endl;
    file << "\tif (bArray)" << endl;
    file << "\t{" << endl;
    file << "\tpSZ << \"<\" << Axis_TypeName_" << m_Name << " << \">\";" 
        << endl;
    file << "\t}" << endl;
    file << "\telse" << endl;
    file << "\t{" << endl;
    file << "\t\tconst AxisChar* sPrefix = pSZ.getNewNamespacePrefix();" 
        << endl;
/*    file << "\tm_URI = \"" << g_ClassNamespaces[m_Name] << "\";" << endl; */
    file << "\t\tpSZ << \"<\" << Axis_TypeName_" << m_Name << 
        "<< \" xsi:type=\\\"\" << sPrefix <<\":\" << Axis_TypeName_" 
        << m_Name << " << \" xmlns:\" << sPrefix << \"=\\\"\" << Axis_URI_" 
        << m_Name << " << \"\\\">\";" << endl;
    file << "\t}" << endl;
    for (it = m_Variables.begin(); it != m_Variables.end(); it++)
    {
        (*it)->GenerateSerializerImpl(file);
    }    
    file << "\tpSZ << \"</\" << Axis_TypeName_" << m_Name << " << \">\";" << 
        endl;
    file << "\treturn AXIS_SUCCESS;" << endl;
    file << "}" << endl;
    file << endl;
    file << "int Axis_GetSize_" << m_Name << "(" << m_Name << "* p)" << endl;
    file << "{" << endl;
    file << "\treturn sizeof(" << m_Name <<");" << endl;
    file << "}" << endl;
    file << endl;
    file << "void Axis_Delete_" << m_Name << "(" << m_Name 
        << "* p, bool bArray = false, int nSize=0)" << endl;
    file << "{" << endl;
    file << "\tif (bArray)" << endl;
    file << "\t\tdelete [] p;" << endl;
    file << "else" << endl;
    file << "delete p;" << endl;
    file << "}" << endl;
    return 0;
}

int BeanClass::GenerateWSDLSchema(File &file)
{
    file << "<complexType name=\"" << m_Name << "\">" << endl;
    file << "<all>"<< endl;
    for (list<Variable*>::iterator it = m_Variables.begin(); 
    it != m_Variables.end(); it++)
    {
        (*it)->GenerateWSDLSchema(file);
    }        
    file << "</all>" << endl;
    file << "</complexType>" << endl;
    return 0;
}
