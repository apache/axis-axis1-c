/*
 *   Copyright 2003-2004 The Apache Software Foundation.
// (c) Copyright IBM Corp. 2004, 2005 All Rights Reserved
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

/**
 * @file ISoapFault.hpp
 *
 * @author Damitha Kumarage (damitha@opensource.lk, damitha@jkcsworld.com)
 *
 */

#ifdef WIN32
#pragma warning (disable : 4786)
#endif

#if !defined(_ISOAPFAULT_H____OF_AXIS_INCLUDED_)
#define _ISOAPFAULT_H____OF_AXIS_INCLUDED_

#include <axis/GDefine.hpp>
#include <iostream>

AXIS_CPP_NAMESPACE_START

using namespace std;

/**
 *  @class ISoapFault
 *  @brief Interface to represent SoapFault
 */
class ISoapFault  
{

public:
    /**
     * Destructor
     */
    virtual ~ISoapFault(){};

    /** 
      * When a complex fault arrives this method can be used to
      * get the name of that fault. This is useful because once 
      * we have the fault name we can pass the information necessary
      * to deserialize it, back to the SoapFault class.
      * 
      * @return name of the complex fault
      */
    virtual const AxisChar* getCmplxFaultObjectName() = 0;
    
    /** 
      * Once we know the complex fault name we can pass the information such as the
      * knowledge to deserialize the complex fault by calling this method.
      *
      * @param pDZFunct deserialize callback function pointer
      * @param pCreFunct create callback function
      * @param pDelFunct delete callback function
      * @param pName name
      * @param pNamespace url
      */
    virtual void* getCmplxFaultObject(void* pDZFunct, 
                                      void* pCreFunct, 
                                      void* pDelFunct, 
                                      const AxisChar* pName, 
                                      const AxisChar* pNamespace) = 0;

    /**
     * To retrieve a complex fault detail object
     * 
     *  @ return Complex fault detail object
     */
    virtual const void* getCmplxFaultObject() = 0;
    
    /** 
      * To retrieve a simple fault detail string
      *
      * @return Simple fault detail
      */
    virtual const AxisChar* getSimpleFaultDetail() = 0;

    /**
      * To retrieve the soap fault code
      *
      * @return fault code
      */
    virtual const AxisChar* getFaultcode() = 0;

    /**
      * To retrieve the soap fault string
      *
      * @return fault string
      */
    virtual const AxisChar* getFaultstring() = 0;

    /** 
      * To retrieve the soap fault actor
      *
      * @return fault actor
      */
    virtual const AxisChar* getFaultactor() = 0;

    /**
     * To set the soap fault code
     * 
     * @param sFaultcode fault code
     * @return status
     */
    virtual int setFaultcode(const AxisChar* sFaultcode) = 0;

    /**
     * To set the soap fault string
     * 
     * @param sFaultstring fault string
     * @return status
     */
    virtual int setFaultstring(const AxisChar* sFaultstring) = 0;

    /**
     * To set the soap fault actor
     * 
     * @param sFaultactor fault actor
     * @return status
     */
    virtual int setFaultactor(const AxisChar* sFaultactor) = 0;

    /**
     * To set the soap fault detail for simple text detail
     * 
     * @param sFaultdetail detail
     * @return status
     */
    virtual int setFaultDetail(const AxisChar* sFaultdetail) = 0;

    /**
     * To set the soap fault detail for complex detail
     * 
     * @param pCmplxFaultObject detail
     * @return status
     */
    virtual int setCmplxFaultObject(const void* pCmplxFaultObject) = 0;

};

AXIS_CPP_NAMESPACE_END

#endif 

