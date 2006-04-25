/*
 *   Copyright 2006-2006 The Apache Software Foundation.
// (c) Copyright IBM Corp. 2006, 2006 All Rights Reserved
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

#if !defined(_AXISOBJECTCONVERTER_HPP_OF_AXIS_INCLUDED_)
#define _AXISOBJECTCONVERTER_HPP_OF_AXIS_INCLUDED_

#include <axis/AxisUserAPI.hpp>
#include <axis/AxisUserAPI.h>

 /**
  * @file AxisObjectConverter.hpp
  * This file contains static methods to convert C++ objects into C objects and
  * vice-versa.  Probably the best way would have been to add methods to the 
  * C++ objects in order to do the conversion to C objects, but decision was 
  * made to keep the C++ engine clean of C support. 
  */
AXIS_CPP_NAMESPACE_START
class AxisObjectConverter
{
public :

    /**
     * Generate an AnyType C structure from the C++ object AnyType.  
     * 
     * @param objAnyType  - Pointer to C++ object AnyType. 
     * @param cAnyType    - Pointer to C AnyType. If NULL, one will be allocated. 
     * @param deleteObj   - Boolean value indicating whether C++ object should be 
     *                      deleted after C equivalent has been generated.
     * 
     * @return            - Pointer to C AnyType.  If cAnyType is not NULL, then
     *                      that is returned; otherwise, a new C AnyType will be returned.
     */
    static AxiscAnyType *cppAnyTypeToC(AnyType *objAnyType, 
                                       AxiscAnyType *cAnyType, 
                                       bool deleteObj=false);

    /**
     * Generate a C array from the C++ object array.  
     * 
     * @param objArray    - Pointer to C++ array. 
     * @param cArray      - Pointer to C array. If NULL, one will be allocated. 
     * @param deleteObj   - Boolean value indicating whether C++ object should be 
     *                      deleted after C equivalent has been generated.
     * 
     * @return            - Pointer to C array.  If cArray is not NULL, then
     *                      that is returned; otherwise, a new C array will be returned.
     */
    static Axisc_Array *cppArrayToC(Axis_Array *objArray, 
                                    Axisc_Array *cArray, 
                                    bool deleteObj=false);
                                    
    /**
     * Generate a base64Binary C structure from the C++ object base64Binary.  
     * 
     * @param objBase64Bin- Pointer to C++ object base64Bin. 
     * @param cBase64Bin  - Pointer to C base64Bin. If NULL, one will be allocated. 
     * @param deleteObj   - Boolean value indicating whether C++ object should be 
     *                      deleted after C equivalent has been generated.
     * 
     * @return            - Pointer to C base64Binary.  If cBase64Bin is not NULL, then
     *                      that is returned; otherwise, a new C base64Bin will be returned.
     */
 
    static xsdc__base64Binary *cppBase64BinaryToC(xsd__base64Binary *objBase64Bin, 
                                                  xsdc__base64Binary *cBase64Bin, 
                                                  bool deleteObjArray=false);   
                                           
    /**
     * Generate a hexBinary C structure from the C++ object hexBinary.  
     * 
     * @param objHexBin   - Pointer to C++ object hexBinary. 
     * @param cHexBin     - Pointer to C hexBinary. If NULL, one will be allocated. 
     * @param deleteObj   - Boolean value indicating whether C++ object should be 
     *                      deleted after C equivalent has been generated.
     * 
     * @return            - Pointer to C hexBinary.  If cHexBinary is not NULL, then
     *                      that is returned; otherwise, a new C hexBinary will be returned.
     */
    static xsdc__hexBinary *cppHexBinaryToC(xsd__hexBinary *objHexBin, 
                                            xsdc__hexBinary *cHexBin, 
                                            bool deleteObj=false);
};

AXIS_CPP_NAMESPACE_END

#endif
