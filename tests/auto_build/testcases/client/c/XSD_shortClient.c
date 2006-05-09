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
#include "XSD_short.h"

int main(int argc, char* argv[])
{
    AXISCHANDLE ws;
    
    xsdc__short result;
    xsdc__short  nillableInput;
    xsdc__short* nillableResult;
    
    char endpoint[256];
    const char* url="http://localhost:80/axis/XSD_short";

    axiscAxisRegisterExceptionHandler(exceptionHandler);

    if(argc>1)
        url = argv[1];
    
    sprintf(endpoint, "%s", url);
    ws = get_XSD_short_stub(endpoint);

    result = asNonNillableElement(ws, (xsdc__short)32767);
    printf("non-nillable element=%hd\n", result);
    
    result = asNonNillableElement(ws, (xsdc__short)1);
    printf("non-nillable element=%hd\n", result);
    
    result = asNonNillableElement(ws, (xsdc__short)-32768);
    printf("non-nillable element=%hd\n", result);
    
    result = asNonNillableElement(ws, (xsdc__short)-1);
    printf("non-nillable element=%hd\n", result);
    
    result = asNonNillableElement(ws, (xsdc__short)0);
    printf("non-nillable element=%hd\n", result);


    // Test nillable element, with a value
    nillableInput = (xsdc__short)12345;
    nillableResult = asNillableElement(ws, &nillableInput);
    if (nillableResult)
    {
        printf("nillable element=%hd\n", *(nillableResult));
        delete nillableResult;
    }
    else
        printf("nillable element=<nil>\n");

    // Test nillable element, with nil
    nillableResult = asNillableElement(ws, NULL);
    if (nillableResult)
    {
        printf("nil element=%hd\n", *(nillableResult));
        delete nillableResult;
    }
    else
        printf("nil element=<nil>\n");

    // Test required attribute
    {
        RequiredAttributeElement requiredAttributeInput;
        RequiredAttributeElement* requiredAttributeResult;
        
        requiredAttributeInput.requiredAttribute = 12345;
        requiredAttributeResult = asRequiredAttribute(ws, &requiredAttributeInput);
        printf("required attribute=%hd\n", requiredAttributeResult->requiredAttribute);
        Axis_Delete_RequiredAttributeElement(requiredAttributeResult, 0);
    }

/* Optional Attributes currently unsupported by WSDL2Ws
 * Exact coding of this section may change depending on chosen implementation
        // Test optional attribute, with a value
        OptionalAttributeElement optionalAttributeInput;
        optionalAttributeInput.setoptionalAttribute(12345);
        OptionalAttributeElement* optionalAttributeResult = ws->asOptionalAttribute(&optionalAttributeInput);
        if (optionalAttributeResult->getoptionalAttribute())
        {
            printf("optional attribute, with data=" << optionalAttributeResult->getoptionalAttribute());
        }
        else
        {
            printf("optional attribute, with data=<not present>\n");
        }
        delete optionalAttributeResult;

        // Test optional attribute, not present
        optionalAttributeInput.setattribute();
        optionalAttributeResult = ws->asOptionalAttribute(&optionalAttributeInput);
        if (optionalAttributeResult->getoptionalAttribute())
        {
            printf("optional attribute, not present=" << optionalAttributeResult->getoptionalAttribute());
        }
        else
        {
            printf("optional attribute, not present=<not present>\n");
        }
        delete optionalAttributeResult;
*/

    // Test array
    {
#define ARRAY_SIZE 2                    
        int i, outputSize=0;
        
        xsdc__short_Array arrayInput;
        xsdc__short_Array* arrayResult;
        xsdc__short * array[ARRAY_SIZE];
        xsdc__short ** output;
        
        for (i=0 ; i < ARRAY_SIZE ; i++)
        {
            array[i] = (xsdc__short *)axiscAxisNew(XSDC_SHORT,0);
            *array[i]= 12345;
        }

        arrayInput.m_Array = array;
        arrayInput.m_Size  = ARRAY_SIZE;
        arrayInput.m_Type  = XSDC_SHORT;
        
        arrayResult = asArray(ws, &arrayInput);
        
        if (exceptionOccurred == C_TRUE
            || get_XSD_short_Status(ws) == AXISC_FAIL )
            printf ("Failed\n");

        if (arrayResult)
        {
           output     = arrayResult->m_Array;
           outputSize = arrayResult->m_Size;
        }
        
        printf("array of %d elements\n", outputSize);
        for (i = 0; i < outputSize ; i++)
            printf("  element[%d]=%hd\n", i, *((xsdc__short*)(output[i])));
        
        // Clear up input array        
        for (i = 0 ; i < ARRAY_SIZE ; i++ )
            axiscAxisDelete(array[i], XSDC_SHORT);
        axiscAxisDelete(arrayResult, XSDC_ARRAY);
    }


        
    // Test complex type
    {
        SimpleComplexType complexTypeInput;
        SimpleComplexType* complexTypeResult;
        
        complexTypeInput.complexTypeElement = 12345;
        complexTypeResult = asComplexType(ws, &complexTypeInput);
        printf("within complex type=%hd\n", complexTypeResult->complexTypeElement);
        Axis_Delete_SimpleComplexType(complexTypeResult, 0);
    }

    // Tests now complete
    destroy_XSD_short_stub(ws);

    printf( "---------------------- TEST COMPLETE -----------------------------\n");
   
    return 0;
}
