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
 */

#if !defined(AXIS_AXISSOCKETUTILS_H__OF_AXIS_INCLUDED_)
#define AXIS_AXISSOCKETUTILS_H__OF_AXIS_INCLUDED_

/*
 *  @class AxisSocketUtils
 *  @brief interface for the AxisSocketUtils class.
 *
 *
 *  @author Roshan Weerasuriya (roshan@jkcs.slt.lk, roshan@opensource.lk)
*/

class AxisSocketUtils
{
    public:
        /*
	 * Prints the description of the related socket error
	 */
        static int printSocketErrorDescription ();
        AxisSocketUtils ();
        virtual ~ AxisSocketUtils ();
};

#endif 
