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
#include "XSD_language.h"


int main(int argc, char* argv[])
{
    AXISCHANDLE ws;
    
    xsdc__language input;
    xsdc__language result;
    
    RequiredAttributeElement requiredAttributeInput;
    RequiredAttributeElement* requiredAttributeResult;
    
    char emptylanguage[1] = "";
    char simplelanguage[25] = "A simple test message!";
    char reservedCharacterslanguage[] = "<>&\"\'";
    char whitespacelanguage[] = "  \t\r\nsome text \t\r\nmore text \t\r\n";
    
    char endpoint[256];
    const char* url="http://localhost:80/axis/XSD_language";

    if(argc>1)
        url = argv[1];

    sprintf(endpoint, "%s", url);
    ws = get_XSD_language_stub(endpoint);

    // Test non-nillable element
    input = simplelanguage;
    result = asNonNillableElement(ws, input);
    if (result)
    {
        if (*result)
            printf( "non-nillable element=%s\n" , result );
        else
            printf( "non-nillable element=<empty>\n" );
        axiscAxisDelete(result, XSDC_LANGUAGE);
    }
    else
        printf( "non-nillable element=<nil>\n" );

    // Test empty non-nillable element
    input = emptylanguage;        
    result = asNonNillableElement(ws, input);
    if (result)
    {
        if (*result)
            printf( "empty non-nillable element=%s\n" , result );
        else
            printf( "empty non-nillable element=<empty>\n" );
        axiscAxisDelete(result, XSDC_LANGUAGE);
    }
    else
        printf( "empty non-nillable element=<nil>\n" );

    // Test non-nillable element with XML reserved characters       
    result = asNonNillableElement(ws, reservedCharacterslanguage);
    if (result)
    {
        if (*result)
            printf( "non-nillable element with XML reserved characters=%s\n" , result );
        else
            printf( "non-nillable element with XML reserved characters=<empty>\n" );
        axiscAxisDelete(result, XSDC_LANGUAGE);
    }
    else
        printf( "non-nillable element with XML reserved characters=<nil>\n" );

    // Test non-nillable element with XML reserved characters
    result = asNonNillableElement(ws, whitespacelanguage);
    if (result)
    {
        if (*result)
            printf( "non-nillable element with whitespace characters=\"%s\"\n" , result);
        else
            printf( "non-nillable element with whitespace characters=<empty>\n" );
        axiscAxisDelete(result, XSDC_LANGUAGE);
    }
    else
        printf( "non-nillable element with whitespace characters=<nil>\n" );

    // Test nillable element, with a value
    input = simplelanguage;
    result = asNillableElement(ws, input);
    if (result)
    {
        if (*result)
            printf( "nillable element=%s\n" , result );
        else
            printf( "nillable element=<empty>\n" );
        axiscAxisDelete(result, XSDC_LANGUAGE);
    }
    else
        printf( "nillable element=<nil>\n" );

    // Test empty nillable element
    result = asNillableElement(ws, emptylanguage);
    if (result)
    {
        if (*result)
            printf( "empty nillable element=%s\n" , result );
        else
            printf( "empty nillable element=<empty>\n" );
        axiscAxisDelete(result, XSDC_LANGUAGE);
    }
    else
        printf( "empty nillable element=<nil>\n" );

    // Test nillable element, with nil
    result = asNillableElement(ws, NULL);
    if (result)
    {
        if (*result)
            printf( "nil element=%s\n" , result );
        else
            printf( "nil element=<empty>\n" );
        axiscAxisDelete(result, XSDC_LANGUAGE);
    }
    else
        printf( "nil element=<nil>\n" );

    // Test required attribute
    requiredAttributeInput.requiredAttribute = simplelanguage;
    requiredAttributeResult = asRequiredAttribute(ws, &requiredAttributeInput);
    if (requiredAttributeResult->requiredAttribute)
    {
        if (*(requiredAttributeResult->requiredAttribute))
            printf( "required attribute=%s\n" , requiredAttributeResult->requiredAttribute );
        else
            printf( "required attribute=<empty>\n" );
    }
    else
        printf( "required attribute=<nil>\n" );
    Axis_Delete_RequiredAttributeElement(requiredAttributeResult, 0);

    // Test empty required attribute
    requiredAttributeInput.requiredAttribute = emptylanguage;
    requiredAttributeResult = asRequiredAttribute(ws, &requiredAttributeInput);
    if (requiredAttributeResult->requiredAttribute)
    {
        if (*(requiredAttributeResult->requiredAttribute))
            printf( "empty required attribute=%s\n" , requiredAttributeResult->requiredAttribute );
        else
            printf( "empty required attribute=<empty>\n" );
    }
    else
        printf( "empty required attribute=<nil>\n" );
    Axis_Delete_RequiredAttributeElement(requiredAttributeResult, 0);

/* Optional Attributes currently unsupported by WSDL2Ws
 * Exact coding of this section may change depending on chosen implementation
        // Test optional attribute, with a value
        input = new char[25];
        strcpy (input, simplelanguage);
        OptionalAttributeElement optionalAttributeInput;
        optionalAttributeInput.setoptionalAttribute(input);
        OptionalAttributeElement* optionalAttributeResult = asOptionalAttribute(&optionalAttributeInput);
        if (optionalAttributeResult->getoptionalAttribute())
        {
            if (*(optionalAttributeResult->getoptionalAttribute()))
            {
                printf( "optional attribute, with data=" , optionalAttributeResult->getoptionalAttribute() );
            }
            else
            {
                printf( "optional attribute, with data=<empty>\n" );
            }
        }
        else
        {
            printf( "optional attribute, with data=<not present>\n" );
        }
        delete [] input;
        delete optionalAttributeResult;

        // Test empty optional attribute
        emptyInput = new char[1];
        strcpy (emptyInput, emptylanguage);
        optionalAttributeInput.setoptionalAttribute(emptyInput);
        optionalAttributeResult = asOptionalAttribute(&optionalAttributeInput);
        if (optionalAttributeResult->getoptionalAttribute())
        {
            if (*(optionalAttributeResult->getoptionalAttribute()))
                printf( "empty optional attribute=" , optionalAttributeResult->getoptionalAttribute() );
            else
                printf( "empty optional attribute=<empty>\n" );
        }
        else
            printf( "empty optional attribute=<not present>\n" );
        delete [] emptyInput;
        delete optionalAttributeResult;

        // Test optional attribute, not present
        // optionalAttributeInput.setattribute();
        optionalAttributeResult = asOptionalAttribute(&optionalAttributeInput);
        if (optionalAttributeResult->getoptionalAttribute())
        {
            if (*(optionalAttributeResult->getoptionalAttribute()))
                printf( "optional attribute, not present=" , optionalAttributeResult->getoptionalAttribute() );
            else
                printf( "optional attribute, not present=<empty>\n" );
        }
        else
            printf( "optional attribute, not present=<not present>\n" );
        delete optionalAttributeResult;
*/

    // Test array
    {
#define ARRAY_SIZE 2                    
        int i, outputSize=0;
        
        xsdc__language_Array arrayInput;
        xsdc__language_Array* arrayResult;
        xsdc__language array[ARRAY_SIZE];  
        xsdc__language *output;  
            
        for (i=0 ; i < ARRAY_SIZE ; i++)
            array[i] = simplelanguage;
                
        arrayInput.m_Array = array;
        arrayInput.m_Size  = ARRAY_SIZE;
        arrayInput.m_Type  = XSDC_LANGUAGE;
        
        arrayResult = asArray(ws, &arrayInput);

        if (arrayResult)
        {
           output     = arrayResult->m_Array;
           outputSize = arrayResult->m_Size;
        }
    
        printf("array of %d elements\n" , outputSize );   
        for (i = 0; i < outputSize ; i++)
            printf( "  element[%d]=%s\n", i , output[i] ? output[i] : "<empty>" );

        axiscAxisDelete(arrayResult, XSDC_ARRAY);
    }

    // Test complex type
    {
        SimpleComplexType complexTypeInput;
        SimpleComplexType* complexTypeResult;
        
        complexTypeInput.complexTypeElement = simplelanguage;
        complexTypeResult = asComplexType(ws, &complexTypeInput);
        if (complexTypeResult->complexTypeElement)
        {
            if (*(complexTypeResult->complexTypeElement))
                printf( "within complex type=%s\n" , complexTypeResult->complexTypeElement );
            else
                printf( "within complex type=<empty>\n" );
        }
        else
            printf( "within complex type=<nil>\n" );
        Axis_Delete_SimpleComplexType(complexTypeResult, 0);
    }

        // Tests now complete

        destroy_XSD_language_stub(ws);

    printf("---------------------- TEST COMPLETE -----------------------------\n");
   
    return 0;
}
