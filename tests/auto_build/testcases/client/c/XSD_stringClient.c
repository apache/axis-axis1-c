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
#include "XSD_string.h"


int main(int argc, char* argv[])
{
    AXISCHANDLE ws;

    xsdc__string input;
    xsdc__string result;
    
    RequiredAttributeElement requiredAttributeInput;
    RequiredAttributeElement* requiredAttributeResult;

    char emptyString[1] = "";
    char simpleString[25] = "A simple test message!";
    char reservedCharactersString[] = "<>&\"\'";
    char whitespaceString[] = "  \t\r\nsome text \t\r\nmore text \t\r\n";

    char endpoint[256];
    const char* url="http://localhost:80/axis/XSD_string";

    axiscAxisRegisterExceptionHandler(exceptionHandler);

    if(argc>1)
        url = argv[1];

    sprintf(endpoint, "%s", url);
    ws = get_XSD_string_stub(endpoint);

    // Test non-nillable element
    result = asNonNillableElement(ws, simpleString);
    if (result)
    {
        if (*result)
            printf("non-nillable element=%s\n", result);
        else
            printf("non-nillable element=<empty>\n");
        axiscAxisDelete(result, XSDC_STRING);
    }
    else
        printf("non-nillable element=<nil>\n");

    // Test empty non-nillable element
    result = asNonNillableElement(ws, emptyString);
    if (result)
    {
        if (*result)
            printf("empty non-nillable element=%s\n", result);
        else
            printf("empty non-nillable element=<empty>\n");
        axiscAxisDelete(result, XSDC_STRING);
    }
    else
        printf("empty non-nillable element=<nil>\n");

    // Test non-nillable element with XML reserved characters
    result = asNonNillableElement(ws, reservedCharactersString);
    if (result)
    {
        if (*result)
            printf("non-nillable element with XML reserved characters=%s\n", result);
        else
            printf("non-nillable element with XML reserved characters=<empty>\n");
        axiscAxisDelete(result, XSDC_STRING);
    }
    else
        printf("non-nillable element with XML reserved characters=<nil>\n");

    // Test non-nillable element with XML reserved characters
    result = asNonNillableElement(ws, whitespaceString);
    if (result)
    {
        if (*result)
            printf("non-nillable element with whitespace characters=\"%s\"\n", result);
        else
            printf("non-nillable element with whitespace characters=<empty>\n");
        axiscAxisDelete(result, XSDC_STRING);
    }
    else
        printf("non-nillable element with whitespace characters=<nil>\n");

    // Test nillable element, with a value
    result = asNillableElement(ws, simpleString);
    if (result)
    {
        if (*result)
            printf("nillable element=%s\n", result);
        else
            printf("nillable element=<empty>\n");
        axiscAxisDelete(result, XSDC_STRING);
    }
    else
        printf("nillable element=<nil>\n");

    // Test empty nillable element
    result = asNillableElement(ws, emptyString);
    if (result)
    {
        if (*result)
            printf("empty nillable element=%s\n", result);
        else
            printf("empty nillable element=<empty>\n");
        axiscAxisDelete(result, XSDC_STRING);
    }
    else
        printf("empty nillable element=<nil>\n");

    // Test nillable element, with nil
    result = asNillableElement(ws, NULL);
    if (result)
    {
        if (*result)
            printf("nil element=%s\n", result);
        else
            printf("nil element=<empty>\n");
        axiscAxisDelete(result, XSDC_STRING);
    }
    else
        printf("nil element=<nil>\n");

    // Test required attribute
    requiredAttributeInput.requiredAttribute = simpleString;
    requiredAttributeResult = asRequiredAttribute(ws, &requiredAttributeInput);
    
    if (requiredAttributeResult->requiredAttribute)
    {
        if (*(requiredAttributeResult->requiredAttribute))
            printf("required attribute=%s\n", requiredAttributeResult->requiredAttribute);
        else
            printf("required attribute=<empty>\n");
    }
    else
        printf("required attribute=<nil>\n");
    Axis_Delete_RequiredAttributeElement(requiredAttributeResult, 0);

    // Test empty required attribute
    requiredAttributeInput.requiredAttribute = emptyString;
    requiredAttributeResult = asRequiredAttribute(ws, &requiredAttributeInput);
    if (requiredAttributeResult->requiredAttribute)
    {
        if (*(requiredAttributeResult->requiredAttribute))
            printf("empty required attribute=%s\n", requiredAttributeResult->requiredAttribute);
        else
            printf("empty required attribute=<empty>\n");
    }
    else
        printf("empty required attribute=<nil>\n");
    Axis_Delete_RequiredAttributeElement(requiredAttributeResult, 0);

/* Optional Attributes currently unsupported by WSDL2Ws
 * Exact coding of this section may change depending on chosen implementation
        // Test optional attribute, with a value
        input = new char[25];
        strcpy (input, simpleString);
        OptionalAttributeElement optionalAttributeInput;
        optionalAttributeInput.setoptionalAttribute(input);
        OptionalAttributeElement* optionalAttributeResult = ws->asOptionalAttribute(&optionalAttributeInput);
        if (optionalAttributeResult->getoptionalAttribute())
        {
            if (*(optionalAttributeResult->getoptionalAttribute()))
                printf("optional attribute, with data=", optionalAttributeResult->getoptionalAttribute());
            else
                printf("optional attribute, with data=<empty>\n");
        }
        else
            printf("optional attribute, with data=<not present>\n");
        delete optionalAttributeResult;

        // Test empty optional attribute
        input = new char[1];
        strcpy (input, emptyString);
        optionalAttributeInput.setoptionalAttribute(input);
        optionalAttributeResult = ws->asOptionalAttribute(&optionalAttributeInput);
        if (optionalAttributeResult->getoptionalAttribute())
        {
            if (*(optionalAttributeResult->getoptionalAttribute()))
                printf("empty optional attribute=", optionalAttributeResult->getoptionalAttribute());
            else
                printf("empty optional attribute=<empty>\n");
        }
        else
            printf("empty optional attribute=<not present>\n");
        delete optionalAttributeResult;

        // Test optional attribute, not present
        // optionalAttributeInput.setattribute();
        optionalAttributeResult = ws->asOptionalAttribute(&optionalAttributeInput);
        if (optionalAttributeResult->getoptionalAttribute())
        {
            if (*(optionalAttributeResult->getoptionalAttribute()))
                printf("optional attribute, not present=", optionalAttributeResult->getoptionalAttribute());
            else
                printf("optional attribute, not present=<empty>\n");
        }
        else
            printf("optional attribute, not present=<not present>\n");
        delete optionalAttributeResult;
*/

    // Test arrays
    {
#define ARRAY_SIZE 2                    
        int i, outputSize=0;
        
        xsdc__string_Array arrayInput;
        xsdc__string_Array * arrayResult;
        xsdc__string array[ARRAY_SIZE];
        xsdc__string* output;
         
        for (i = 0 ; i < ARRAY_SIZE ; i++)
            array[i] =  simpleString;

        arrayInput.m_Array = array;
        arrayInput.m_Size  = ARRAY_SIZE;
        arrayInput.m_Type  = XSDC_STRING;
        
        arrayResult = asArray(ws, &arrayInput);
        
        if (exceptionOccurred == C_TRUE
            || get_XSD_string_Status(ws) == AXISC_FAIL )
            printf ("Failed\n");

        if (arrayResult)
        {
           output     = arrayResult->m_Array;
           outputSize = arrayResult->m_Size;
        }
        
        printf("array of %d elements\n", outputSize);
        if (output != NULL)
        {
            for (i = 0 ; i < outputSize ; i++)
                printf("  element[%d]=%s\n", i, output[i] ? output[i] : "NULL");
        }
        else
            printf("NULL array");

        // Clean up        
        axiscAxisDelete(arrayResult, XSDC_ARRAY);
    }



        
    // Test complex type
    {
        SimpleComplexType complexTypeInput;
        SimpleComplexType* complexTypeResult;
        
        complexTypeInput.complexTypeElement = simpleString;
        complexTypeResult = asComplexType(ws, &complexTypeInput);
        if (complexTypeResult->complexTypeElement)
        {
            if (*(complexTypeResult->complexTypeElement))
                printf("within complex type=%s\n", complexTypeResult->complexTypeElement);
            else
                printf("within complex type=<empty>\n");
        }
        else
            printf("within complex type=<nil>\n");
        Axis_Delete_SimpleComplexType(complexTypeResult, 0);
    }

    // Tests now complete

    destroy_XSD_string_stub(ws);


    printf( "---------------------- TEST COMPLETE -----------------------------\n");
   
    return 0;
}
