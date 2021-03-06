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
#include "XSD_gYearMonth.h"


int main(int argc, char* argv[])
{
    AXISCHANDLE ws;
    
    xsdc__gYearMonth result;
    xsdc__gYearMonth input;
    xsdc__gYearMonth* nillableResult;
    
    char returnString[50];
    time_t timeToTest;
    struct tm *temp;
    
    char endpoint[256];
    const char* url="http://localhost:80/axis/XSD_gYearMonth";

    axiscAxisRegisterExceptionHandler(exceptionHandler);

    if(argc>1)
        url = argv[1];

    sprintf(endpoint, "%s", url);
    ws = get_XSD_gYearMonth_stub(endpoint);

    timeToTest = 1100246323;
    temp = gmtime(&timeToTest);
    memcpy(&input, temp, sizeof(struct tm));

    // Test non-nillable element
    result = asNonNillableElement(ws, input);
    strftime(returnString, 50, "%b %Y", adjustTimeStruct(&result));
    printf( "non-nillable element=%s\n" , returnString );

    // Test nillable element, with a value
    nillableResult = asNillableElement(ws, &input);
    if (nillableResult)
    {
        strftime(returnString, 50, "%b %Y", adjustTimeStruct(nillableResult));
        printf( "nillable element=%s\n" , returnString );
        axiscAxisDelete(nillableResult, XSDC_GYEARMONTH);
    }
    else
        printf( "nillable element=<nil>\n" );

    // Test nillable element, with nil
    nillableResult = asNillableElement(ws, NULL);
    if (nillableResult)
    {
        strftime(returnString, 50, "%b %Y", adjustTimeStruct(nillableResult));
        printf( "nil element=%s\n" , returnString );
        axiscAxisDelete(nillableResult, XSDC_GYEARMONTH);
    }
    else
        printf( "nil element=<nil>\n" );

    // Test required attribute
    {
        RequiredAttributeElement requiredAttributeInput;
        RequiredAttributeElement* requiredAttributeResult;
        
        requiredAttributeInput.requiredAttribute = input;
        requiredAttributeResult = asRequiredAttribute(ws, &requiredAttributeInput);
        result = requiredAttributeResult->requiredAttribute;
        strftime(returnString, 50, "%b %Y", adjustTimeStruct(&result));
        printf( "required attribute=%s\n" , returnString );
        Axis_Delete_RequiredAttributeElement(requiredAttributeResult, 0);
    }

/* Optional Attributes currently unsupported by WSDL2Ws
 * Exact coding of this section may change depending on chosen implementation
        // Test optional attribute, with a value
        OptionalAttributeElement optionalAttributeInput;
        optionalAttributeInput.setoptionalAttribute(input);
        OptionalAttributeElement* optionalAttributeResult = asOptionalAttribute(&optionalAttributeInput);
        if (optionalAttributeResult->getoptionalAttribute())
        {
            strftime(returnString, 50, "%b %Y", optionalAttributeResult->getoptionalAttribute());
            printf( "optional attribute, with data=%s\n" , returnString );
        }
        else
            printf( "optional attribute, with data=<not present>\n" );
        delete optionalAttributeResult;

        // Test optional attribute, not present
        optionalAttributeInput.setattribute();
        optionalAttributeResult = asOptionalAttribute(&optionalAttributeInput);
        if (optionalAttributeResult->getoptionalAttribute())
        {
            strftime(returnString, 50, "%b %Y", optionalAttributeResult->getoptionalAttribute());
            printf( "optional attribute, not present=%s\n" , returnString );
        }
        else
            printf( "optional attribute, not present=<not present>\n" );
        delete optionalAttributeResult;
*/
    // Test array
    {
#define ARRAY_SIZE 2                    
        int i, outputSize=0;
                
        xsdc__gYearMonth_Array arrayInput;
        xsdc__gYearMonth_Array* arrayResult;
        xsdc__gYearMonth * array[ARRAY_SIZE];
        const xsdc__gYearMonth **output;
        
        for (i=0 ; i < ARRAY_SIZE ; i++)
            array[i] = &input;
                
        arrayInput.m_Array = array;
        arrayInput.m_Size  = ARRAY_SIZE;
        arrayInput.m_Type  = XSDC_GYEARMONTH;
        
        arrayResult = asArray(ws, &arrayInput);

        if (arrayResult)
        {
           output     = arrayResult->m_Array;
           outputSize = arrayResult->m_Size;
        }
    
        printf("array of %d elements\n" , outputSize );   

        for (i = 0; i < outputSize ; i++)
        {
            strftime(returnString, 50, "%b %Y", adjustTimeStruct((struct tm *)output[i]));
            printf( "  element[%d]=%s\n" , i, returnString );
        }

        axiscAxisDelete(arrayResult, XSDC_ARRAY);
    }


    // Test complex type
    {
        SimpleComplexType complexTypeInput;
        SimpleComplexType* complexTypeResult;
        
        complexTypeInput.complexTypeElement = input;
        complexTypeResult = asComplexType(ws, &complexTypeInput);
        result = complexTypeResult->complexTypeElement;
        strftime(returnString, 50, "%b %Y", adjustTimeStruct(&result));
        printf( "within complex type=%s\n" , returnString );
        Axis_Delete_SimpleComplexType(complexTypeResult, 0);
    }

    // Tests now complete
    destroy_XSD_gYearMonth_stub(ws);

    printf( "---------------------- TEST COMPLETE -----------------------------\n");
   
    return 0;
}
