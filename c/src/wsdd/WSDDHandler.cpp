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
 * @author Sanjaya Singharage
 *
 */



#include <axis/server/WSDDHandler.h>


WSDDHandler::WSDDHandler()
{
    m_nLibId = 0;
    m_nScope = AH_REQUEST; /* default */
    m_Params = NULL;
    m_sDescription = "No description provided";
    m_file = 0;
}

WSDDHandler::~WSDDHandler()
{
    if (m_Params) delete m_Params;
}

void WSDDHandler::SetLibName(const AxisChar* sLibName)
{
    m_sLibName = sLibName;
}

void WSDDHandler::SetLibId(int nLibId)
{
    m_nLibId = nLibId;
}

void WSDDHandler::SetName(const AxisChar* sName)
{
    m_sName = sName;
}

int WSDDHandler::GetLibId() const
{
    return m_nLibId;
}

const AxisChar* WSDDHandler::GetLibName() const
{
    return m_sLibName.c_str();
}

int WSDDHandler::GetScope() const
{
    return m_nScope;
}

void WSDDHandler::SetScope(const AxisChar* sScope)
{
    if (0 == strcmp(sScope, kw_scope_app))
        m_nScope = AH_APPLICATION;    
    else if (0 == strcmp(sScope,kw_scope_ses))
        m_nScope = AH_SESSION;    
    else
        m_nScope = AH_REQUEST;    
}

const AxisChar* WSDDHandler::GetParameter(const AxisChar* sKey) const
{
    if (m_Params->find(sKey) != m_Params->end())
        return (*m_Params)[sKey].c_str();
    return NULL;
}

void WSDDHandler::AddParameter(const AxisChar* sKey, const AxisChar* sValue)
{
    if (!m_Params) m_Params = new map<AxisString, AxisString>;
    (*m_Params)[sKey] = sValue; 
}

const map<AxisString, AxisString>* WSDDHandler::GetParameterList() const
{
    return m_Params;
}

void WSDDHandler::SetDescription(const AxisChar* sDescription)
{
    m_sDescription = sDescription;
}

const AxisChar* WSDDHandler::GetDescription() const
{
    return m_sDescription.c_str();
}

int WSDDHandler::UpdateWSDD(FILE* wsddfile, int tabcount)
{
    m_file = wsddfile;
    PrintTabs(tabcount); *this << "<handler name=\"" << m_sName.c_str() << 
        "\" type=\"" << m_sLibName.c_str() << "\">\n";
    if (m_Params)
    {
        map<AxisString, AxisString>::iterator itr;
        for (itr = m_Params->begin(); itr != m_Params->end(); itr++)
        {
            PrintTabs(tabcount+1); *this << "<parameter name=\"" << 
                (*itr).first.c_str() << "\" value=\"" << (*itr).second.c_str() 
                << "\" />\n";
        }
    }
    PrintTabs(tabcount); *this << "</handler>\n";
    m_file = 0;
    return AXIS_SUCCESS;
}

WSDDHandler& WSDDHandler::operator << (const char* str)
{
    fputs(str, m_file);
    return *this;
}

void WSDDHandler::PrintTabs(int count)
{
    for (int x=0; x<count; x++) *this << "\t";
}


