// Copyright 2003-2004 The Apache Software Foundation.
// (c) Copyright IBM Corp. 2004, 2005 All Rights Reserved
// 
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// 
//        http://www.apache.org/licenses/LICENSE-2.0
// 
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <stdlib.h>
#include <stdio.h>

#include "CommonClientTestCode.h"
#include "XSD_negativeInteger.h"


int main(int argc, char* argv[])
{
    AXISCHANDLE ws;
    
    xsdc__negativeInteger result;
    xsdc__negativeInteger input;
    xsdc__negativeInteger* nillableResult;
    
    char endpoint[256];
    const char* url="http://localhost:80/axis/XSD_negativeInteger";

    if(argc>1)
        url = argv[1];

    sprintf(endpoint, "%s", url);
    ws = get_XSD_negativeInteger_stub(endpoint);
    
    result = asNonNillableElement(ws, (xsdc__negativeInteger) LONGLONGVALUE(-9223372036854775808));
    printf( "non-nillable element=%lld\n" , result );
    
    result = asNonNillableElement(ws, (xsdc__negativeInteger)-1);
    printf( "non-nillable element=%lld\n" , result );
    

    result = asNonNillableElement(ws, (xsdc__negativeInteger)0);
    if (!(exceptionOccurred == C_TRUE
        || get_XSD_negativeInteger_Status(ws) == AXISC_FAIL ))
    {
        printf("non-nillable element=%llu\n" , result );
        exceptionOccurred = C_FALSE;
    }

    /* 
     * Test client correctly handles server response data beginning with '-'
     * which is also permitted for nonPositiveInteger.
     */
    result = asNonNillableElement(ws, (xsdc__negativeInteger)-123456789);
    printf( "non-nillable element=%lld\n" , result );

    // Test nillable element, with a value
    input = (xsdc__negativeInteger)-123456789;
    nillableResult = asNillableElement(ws, &input);
    if (nillableResult)
    {
        printf( "nillable element=%lld\n" , *(nillableResult) );
        axiscAxisDelete(nillableResult, XSDC_NEGATIVEINTEGER);
    }
    else
        printf( "nillable element=<nil>\n" );

    // Test nillable element, with nil
    nillableResult = asNillableElement(ws, NULL);
    if (nillableResult)
    {
        printf( "nil element=%lld\n" , *(nillableResult) );
        axiscAxisDelete(nillableResult, XSDC_NEGATIVEINTEGER);
    }
    else
        printf( "nil element=<nil>\n" );

    // Test required attribute
    {
        RequiredAttributeElement requiredAttributeInput;
        RequiredAttributeElement* requiredAttributeResult;
        
        requiredAttributeInput.requiredAttribute = -123456789;
        requiredAttributeResult = asRequiredAttribute(ws, &requiredAttributeInput);
        printf( "required attribute=%lld\n" , requiredAttributeResult->requiredAttribute );
        Axis_Delete_RequiredAttributeElement(requiredAttributeResult, 0);  
    } 

/* Optional Attributes currently unsupported by WSDL2Ws
 * Exact coding of this section may change depending on chosen implementation
        // Test optional attribute, with a value
        OptionalAttributeElement optionalAttributeInput;
        optionalAttributeInput.setoptionalAttribute(-123456789);
        OptionalAttributeElement* optionalAttributeResult = asOptionalAttribute(&optionalAttributeInput);
        if (optionalAttributeResult->getoptionalAttribute())
            printf( "optional attribute, with data=" , optionalAttributeResult->getoptionalAttribute() );
        else
            printf( "optional attribute, with data=<not present>\n" );
        delete optionalAttributeResult;

        // Test optional attribute, not present
        optionalAttributeInput.setattribute();
        optionalAttributeResult = asOptionalAttribute(&optionalAttributeInput);
        if (optionalAttributeResult->getoptionalAttribute())
            printf( "optional attribute, not present=" , optionalAttributeResult->getoptionalAttribute() );
        else
            printf( "optional attribute, not present=<not present>\n" );
        delete optionalAttributeResult;
*/

    // Test array
    {
#define ARRAY_SIZE 2                    
        int i, outputSize=0;
                
        xsdc__negativeInteger_Array arrayInput;
        xsdc__negativeInteger_Array* arrayResult;       
        const xsdc__negativeInteger ** output;        
        xsdc__negativeInteger * array[ARRAY_SIZE];
        
        input = -123456789;
        for (i=0 ; i < ARRAY_SIZE ; i++)
            array[i] = &input;
            
        arrayInput.m_Array = array;
        arrayInput.m_Size  = ARRAY_SIZE;
        arrayInput.m_Type  = XSDC_NEGATIVEINTEGER;
        
        arrayResult = asArray(ws, &arrayInput);

        if (arrayResult)
        {
           output     = arrayResult->m_Array;
           outputSize = arrayResult->m_Size;
        }
    
        printf("array of %d elements\n" , outputSize );
        for (i = 0; i < outputSize; i++)
            printf( "  element[%d]=%lld\n" , i, *((xsdc__negativeInteger*)(output[i])) );
        
        axiscAxisDelete(arrayResult, XSDC_ARRAY);
    }


    // Test complex type
    {
        SimpleComplexType complexTypeInput;
        SimpleComplexType* complexTypeResult;
        
        complexTypeInput.complexTypeElement = -123456789;
        complexTypeResult = asComplexType(ws, &complexTypeInput);
        printf( "within complex type=%lld\n" , complexTypeResult->complexTypeElement );
        Axis_Delete_SimpleComplexType(complexTypeResult, 0);
    }

    // Tests now complete
    destroy_XSD_negativeInteger_stub(ws);

    printf("---------------------- TEST COMPLETE -----------------------------\n");
   
    return 0;
}
