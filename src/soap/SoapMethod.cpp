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
 * @author Roshan Weerasuriya (roshan@opensource.lk, roshanw@jkcsworld.com)
 *
 */


#include "SoapMethod.h"
#include "Attribute.h"
#include <axis/GDefine.hpp>

AXIS_CPP_NAMESPACE_START

SoapMethod::SoapMethod()
{
}

SoapMethod::~SoapMethod()
{
    list<Param*>::iterator itParam;
    for (list<Attribute*>::iterator it = m_attributes.begin();
    it != m_attributes.end(); it++)
    {
        delete (*it);
    }
    for (itParam = m_OutputParams.begin(); 
    itParam != m_OutputParams.end(); itParam++)
    {
        delete (*itParam);
    }
    m_OutputParams.clear();
}

void SoapMethod::setPrefix(const AxisChar* prefix)
{
    m_strPrefix = prefix;
}

void SoapMethod::setLocalName(const AxisChar* localname)
{
    m_strLocalname = localname;
}

void SoapMethod::setURI(const AxisChar* uri)
{
    m_strUri = uri;
}

void SoapMethod::addOutputParam(Param *param)
{
    if (param)
    {
        m_OutputParams.push_back(param);
    }
}

/*
 * This method return AXIS_SUCCESS if it serialize the SoapMethod successfully.
 * If not it returns AXIS_FAIL. The caller of this method has to deal in a 
 * appropriate manner after calling this method.
 */
int SoapMethod::serialize(SoapSerializer& pSZ)
{    
    int iStatus= AXIS_SUCCESS;

    do
    {
        if(isSerializable())
        {
                    
            pSZ.serialize("<", m_strPrefix.c_str(), ":", m_strLocalname.c_str(),
                " xmlns:", m_strPrefix.c_str(),
                "=\"", m_strUri.c_str(), "\"", NULL);

			list<AxisChar*> lstTmpNameSpaceStack;

            iStatus= serializeAttributes(pSZ, lstTmpNameSpaceStack);
            if(iStatus==AXIS_FAIL)
            {
                break;
            }
            
            pSZ.serialize(">\n", NULL);

            // push the current NS to the NS stack
            pSZ.getNamespacePrefix(m_strUri.c_str());

            iStatus= serializeOutputParam(pSZ);

            // remove the current NS from the NS stack
            pSZ.removeNamespacePrefix(m_strUri.c_str());

            if(iStatus==AXIS_FAIL)
            {
                break;
            }
            
            pSZ.serialize("</", NULL);

            if(m_strPrefix.length() != 0)
            {                    
                pSZ.serialize(m_strPrefix.c_str(), ":", NULL);
            }
            
            pSZ.serialize(m_strLocalname.c_str(), ">\n", NULL);

			/*
			 * Removing the namespace list of this SOAPMethod from the stack.
			 */
			list<AxisChar*>::iterator itCurrentNamespace = 
				lstTmpNameSpaceStack.begin();
			while (itCurrentNamespace != lstTmpNameSpaceStack.end())
			{
				pSZ.removeNamespacePrefix(*itCurrentNamespace);
				itCurrentNamespace++;
			}

            iStatus= AXIS_SUCCESS;
        }
        else
        {
            iStatus= AXIS_FAIL;
        }
    } while(0);
            
    return iStatus;
}

/*
comm on 11/7/2003 9.10am
int SoapMethod::serialize(string& sSerialized)
{    
    
    int iStatus= AXIS_SUCCESS;

    do {
        if(isSerializable()) {

            sSerialized+= "<" + m_strPrefix+ ":"+ m_strLocalname+ " xmlns:"
            + m_strPrefix+ "=\""+ m_strUri+ "\"";
            
//            if(m_strPrefix.length() != 0) {
//                sSerialized+= m_strPrefix+ ":";
//            }

//            sSerialized+= m_strLocalname;

//            if(m_strPrefix.length() != 0) {
//                sSerialized+= " xmlns:"+ m_strPrefix+ "=\""+ m_strUri+ "\"";
//            }

            iStatus= serializeAttributes(sSerialized);
            if(iStatus==AXIS_FAIL) {
                break;
            }

            sSerialized+= ">";

            iStatus= serializeOutputParam(sSerialized);
            if(iStatus==AXIS_FAIL) {
                break;
            }

            sSerialized+= "</";

            if(m_strPrefix.length() != 0) {
                sSerialized+= m_strPrefix+ ":";            
            }

            sSerialized+= m_strLocalname+ ">"+ "\n";

            iStatus= AXIS_SUCCESS;
        } else {
            iStatus= AXIS_FAIL;
        }
    } while(0);
            
    return iStatus;
}
*/

int SoapMethod::serializeOutputParam(SoapSerializer& pSZ)
{    
    int nStatus;
    for (list<Param*>::iterator it = m_OutputParams.begin();
    it != m_OutputParams.end(); it++)
    {
        if (AXIS_SUCCESS != (nStatus = (*it)->serialize(pSZ)))
        {
            return nStatus;
        }
    }
    return AXIS_SUCCESS;
}

/*
comm on 11/7/2003 9.10am
int SoapMethod::serializeOutputParam(string& sSerialized)
{    
    return m_pOutputParam->serialize(sSerialized);
}
*/

const AxisChar* SoapMethod::getMethodName()
{
    return m_strLocalname.c_str();
}

bool SoapMethod::isSerializable()
{
    bool bStatus= true;    

    /* checking whether namespace qualified, if not return AXIS_FAIL */
    do
    {
        if(m_strPrefix.length() == 0)
        {            
            bStatus= false;        
            break;
        }
        else if(m_strUri.length() == 0)
        {
            bStatus= false;
            break;
        }
    } while(0);

    return bStatus;
}

int SoapMethod::addAttribute(Attribute *pAttribute)
{
    m_attributes.push_back(pAttribute);

    return AXIS_SUCCESS;
}

int SoapMethod::serializeAttributes(SoapSerializer& pSZ, 
        list<AxisChar*>& lstTmpNameSpaceStack)
{
    list<Attribute*>::iterator itCurrAttribute= m_attributes.begin();

    while(itCurrAttribute != m_attributes.end())
    {        
        (*itCurrAttribute)->serialize(pSZ, lstTmpNameSpaceStack);
        itCurrAttribute++;        
    }    

    return AXIS_SUCCESS;    
}

/*
comm on 11/7/2003 9.10am
int SoapMethod::serializeAttributes(string &sSerialized)
{
    list<Attribute*>::iterator itCurrAttribute= m_attributes.begin();

    while(itCurrAttribute != m_attributes.end()) {        
        (*itCurrAttribute)->serialize(sSerialized);
        itCurrAttribute++;        
    }    

    return AXIS_SUCCESS;    
}
*/

int SoapMethod::reset()
{
    m_strUri = "";
    m_strLocalname = "";
    m_strPrefix = "";
    m_OutputParams.clear();
    m_attributes.clear();

    return AXIS_SUCCESS;
}

AXIS_CPP_NAMESPACE_END

#ifdef UNIT_TESTING_ON
int SoapMethod::initializeForTesting()
{
    m_strPrefix = "mn";
    m_strLocalname = "add";
    m_strUri = "http://myurl.com";

    Attribute* pAttribute = new Attribute();
    pAttribute->initializeForTesting();
    addAttribute(pAttribute);

    /*
     * Param* pParam = new Param(100);
     * AddOutputParam(pParam);
     */

    return AXIS_SUCCESS;
}
#endif

