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

/**
 * @file IAdminUtils.h
 *
 * This file contains all the special functionalities that the Admin Web
 * service is provided by the Axis Engine.
 *
 * @author Susantha Kumara (susantha@opensource.lk, skumara@virtusa.com)
 */
 
#if !defined(_IADMINUTILS_H____OF_AXIS_INCLUDED_)
#define _IADMINUTILS_H____OF_AXIS_INCLUDED_

#include <axis/AxisUserAPI.hpp>

/**
 * @interface IAdminUtils
 *
 * This interface contains all the special functionalities that the Admin Web
 * service is provided by the Axis Engine. Such as deploying and undeploying
 * services/handlers dynamically.
 *
 * @brief  This Interface contains the Server side administration
 *         functionalities
 * @author Suasntha Kumara (skumara@virtusa.com, susantha@opensource.lk)
 */

AXIS_CPP_NAMESPACE_START

class IAdminUtils  
{
public:
    virtual ~IAdminUtils(){};
    /**
     * Updates the WSDD information of the Axis Engine. This functions is
     * called by the Admin Web service when the Admin Client is used to
     * deploy a web service.
     *
     * @brief Updates the WSDD information of Axis Engine.
     * @param wsdd A character buffer containing xml of the new wsdd.
     * @return AXIS_SUCCESS if the WSDD update successful, AXIS_FAIL otherwise.
     */
    virtual int updateWSDD(AxisChar* wsdd)=0;
};

AXIS_CPP_NAMESPACE_END

#endif 

