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


#if !defined(AXIS_ARRAYBEAN_H__INCLUDED_)
#define AXIS_ARRAYBEAN_H__INCLUDED_

#include "IArrayBean.h"
#include <axis/server/IParam.h>
#include <axis/server/BasicTypeSerializer.h>

#include <list>
using namespace std;

/**
    @class ArrayBean
    @brief interface for the ArrayBeanI class.

    This class is used inside Param class and wrapper classes only.

    @author Susantha Kumara (skumara@virtusa.com)
*/
class ArrayBean:public IArrayBean
{
    friend class Param;
    public:
        ArrayBean ();
        virtual ~ ArrayBean ();
        virtual int Serialize (SoapSerializer & pSZ);
        int GetArraySize ();

    public:
        XSDTYPE m_type;        //array element type
        int m_nSize;           //array size only one dimensional arrays
        AxisString m_ItemName; //name of an item like <item>34</item>
    union uAValue //this is useful only when Param is used as a return parameter
    {
        void *sta;                      //simple type array
        ComplexObjectHandler *cta;      //complex type array
    }
    m_value;
    private:
        AxisString m_TypeName;
        AxisString m_URI;
    public:                      //IArrayBean Interface
        void SetDimension (int nDim);
        void SetItemName (const AxisChar* sName);
        void SetTypeName (const AxisChar* sName);
        void SetUri (const AxisChar* sURI);
        void RemoveArrayPointer ();
};

#endif 
