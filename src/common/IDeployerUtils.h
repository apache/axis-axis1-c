/* -*- C++ -*- */
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
 */


#if !defined(AXIS_IDEPLOYERUTILS_H__OF_AXIS_INCLUDED_)
#define AXIS_IDEPLOYERUTILS_H__OF_AXIS_INCLUDED_

#include <axis/server/AxisUserAPI.h>

/*
 *   @class IDeployerUtils
 *   @brief interface for the IDeployerUtils class.
 *
 *
 *   @author Roshan Weerasuriya (roshan@jkcs.slt.lk, roshan@opensource.lk)
 */

class IDeployerUtils
{
    public:
        virtual int UpdateWSDD () = 0;
        virtual int unDeploy (string sServiceName) = 0;
        virtual int deploy (string sServiceName, string sDllPath,
            Axis_Array inArray) = 0;
        virtual ~ IDeployerUtils ()
        {
        };
};

#endif 
