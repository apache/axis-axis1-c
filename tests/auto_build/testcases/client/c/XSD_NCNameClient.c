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
#include "XSD_NCName.h"


int main(int argc, char* argv[])
{
    AXISCHANDLE ws;
    
    xsdc__NCName input;
    xsdc__NCName result;
    
    RequiredAttributeElement requiredAttributeInput;
    RequiredAttributeElement* requiredAttributeResult;
    
    char endpoint[256];
    const char* url="http://localhost:80/axis/XSD_NCName";

    char emptyNCName[1] = "";
    char simpleNCName[25] = "xml.si-mple_name ";    

    if(argc>1)
        url = argv[1];

    axiscAxisRegisterExceptionHandler(exceptionHandler);

    sprintf(endpoint, "%s", url);
    ws = get_XSD_NCName_stub(endpoint);
    if (!ws)
    {
        printf("FAILED to get WS\n");
        return -1;
    }
  
    // Test non-nillable element
    result = asNonNillableElement(ws, simpleNCName);
    if (exceptionOccurred == C_TRUE
        || get_XSD_NCName_Status(ws) == AXISC_FAIL )
        printf ("Failed\n");
    
    if (result)
    {
        if (*result)
            printf("non-nillable element=%s\n", result );
        else
            printf("non-nillable element=<empty>\n" );
        
        axiscAxisDelete(result, XSDC_NCNAME);    
    }
    else
        printf("non-nillable element=<nil>\n" );

    // Test empty non-nillable element
    input = (xsdc__NCName)axiscAxisNew(XSDC_NCNAME, 1);
    strcpy (input, emptyNCName);
    
    result = asNonNillableElement(ws, input);
    if (exceptionOccurred == C_TRUE
        || get_XSD_NCName_Status(ws) == AXISC_FAIL )
        printf ("Failed\n");
    
    if (result)
    {
        if (*result)
            printf("empty non-nillable element=%s\n", result );
        else
            printf("empty non-nillable element=<empty>\n" );
            
        axiscAxisDelete(result, XSDC_NCNAME);
    }
    else
        printf("empty non-nillable element=<nil>\n" );

    axiscAxisDelete(input, XSDC_NCNAME);
    
    // Test nillable element, with a value
    input = simpleNCName;
    result = asNillableElement(ws, input);
    if (exceptionOccurred == C_TRUE
        || get_XSD_NCName_Status(ws) == AXISC_FAIL )
        printf ("Failed\n");
    
    if (result)
    {
        if (*result)
            printf("nillable element=%s\n", result );
        else
            printf("nillable element=<empty>\n" );

        axiscAxisDelete(result, XSDC_NCNAME);
    }
    else
        printf("nillable element=<nil>\n" );

    // Test empty nillable element
    input = emptyNCName;
    result = asNillableElement(ws, input);
    if (exceptionOccurred == C_TRUE
        || get_XSD_NCName_Status(ws) == AXISC_FAIL )
        printf ("Failed\n");
    
    if (result)
    {
        if (*result)
            printf("empty nillable element=%s\n", result );
        else
            printf("empty nillable element=<empty>\n" );

        axiscAxisDelete(result, XSDC_NCNAME);
    }
    else
        printf("empty nillable element=<nil>\n" );

    // Test nillable element, with nil
    result = asNillableElement(ws, NULL);
    if (exceptionOccurred == C_TRUE
        || get_XSD_NCName_Status(ws) == AXISC_FAIL )
        printf ("Failed\n");
    
    if (result)
    {
        if (*result)
            printf("nil element=%s\n", result );
        else
            printf("nil element=<empty>\n" );

        axiscAxisDelete(result, XSDC_NCNAME);
    }
    else
        printf("nil element=<nil>\n" );

    // Test required attribute
    requiredAttributeInput.requiredAttribute = simpleNCName;
    requiredAttributeResult = asRequiredAttribute(ws, &requiredAttributeInput);
    if (exceptionOccurred == C_TRUE
        || get_XSD_NCName_Status(ws) == AXISC_FAIL )
        printf ("Failed\n");
    
    if (requiredAttributeResult->requiredAttribute)
    {
        if (*(requiredAttributeResult->requiredAttribute))
            printf("required attribute=%s\n", requiredAttributeResult->requiredAttribute);
        else
            printf("required attribute=<empty>\n" );
    }
    else
        printf("required attribute=<nil>\n" );
        
    Axis_Delete_RequiredAttributeElement(requiredAttributeResult, 0);            

    // Test empty required attribute
    requiredAttributeInput.requiredAttribute = emptyNCName;
    requiredAttributeResult = asRequiredAttribute(ws, &requiredAttributeInput);
    if (exceptionOccurred == C_TRUE
        || get_XSD_NCName_Status(ws) == AXISC_FAIL )
        printf ("Failed\n");
                       
    if (requiredAttributeResult->requiredAttribute)
    {
        if (*(requiredAttributeResult->requiredAttribute))
            printf("empty required attribute=%s\n", requiredAttributeResult->requiredAttribute);
        else
            printf("empty required attribute=<empty>\n" );
    }
    else
        printf("empty required attribute=<nil>\n" );

    Axis_Delete_RequiredAttributeElement(requiredAttributeResult, 0);            

/* Optional Attributes currently unsupported by WSDL2Ws
 * Exact coding of this section may change depending on chosen implementation
        // Test optional attribute, with a value
        input = new char[25];
        strcpy (input, simpleNCName);
        OptionalAttributeElement optionalAttributeInput;
        optionalAttributeInput.setoptionalAttribute(input);
        OptionalAttributeElement* optionalAttributeResult = ws->asOptionalAttribute(&optionalAttributeInput);
        if (optionalAttributeResult->getoptionalAttribute())
        {
            if (*(optionalAttributeResult->getoptionalAttribute()))
                printf("optional attribute, with data=%s\n", optionalAttributeResult->getoptionalAttribute() );
            else
                printf("optional attribute, with data=<empty>" );
        }
        else
            printf("optional attribute, with data=<not present>" );

        delete [] input;
        delete optionalAttributeResult;

        // Test empty optional attribute
        input = new char[1];
        strcpy (input, emptyNCName);
        optionalAttributeInput.setoptionalAttribute(input);
        optionalAttributeResult = ws->asOptionalAttribute(&optionalAttributeInput);
        if (optionalAttributeResult->getoptionalAttribute())
        {
            if (*(optionalAttributeResult->getoptionalAttribute()))
                printf("empty optional attribute=%s\n", optionalAttributeResult->getoptionalAttribute() );
            else
                printf("empty optional attribute=<empty>" );
        }
        else
            printf("empty optional attribute=<not present>" );

        delete [] input;
        delete optionalAttributeResult;

        // Test optional attribute, not present
        // optionalAttributeInput.setattribute();
        optionalAttributeResult = ws->asOptionalAttribute(&optionalAttributeInput);
        if (optionalAttributeResult->getoptionalAttribute())
        {
            if (*(optionalAttributeResult->getoptionalAttribute()))
                printf("optional attribute, not present=%s\n", optionalAttributeResult->getoptionalAttribute() );
            else
                printf("optional attribute, not present=<empty>" );
        }
        else
            printf("optional attribute, not present=<not present>" );
        delete optionalAttributeResult;
*/

    // Test array
    {
#define ARRAY_SIZE 2                    
        int i;
        xsdc__NCName_Array arrayInput;
        xsdc__NCName_Array* arrayResult;
        xsdc__NCName array[ARRAY_SIZE]; 
        const xsdc__NCName* output;
        int outputSize=0;
               
        for (i=0 ; i < ARRAY_SIZE; i++)
            array[i]= simpleNCName;

        arrayInput.m_Array = array;
        arrayInput.m_Size  = ARRAY_SIZE;
        arrayInput.m_Type  = XSDC_NCNAME;

        arrayResult = asArray(ws, &arrayInput);
        
        if (exceptionOccurred == C_TRUE
            || get_XSD_NCName_Status(ws) == AXISC_FAIL )
            printf ("Failed\n");

        if (arrayResult)
        {
           output     = arrayResult->m_Array;
           outputSize = arrayResult->m_Size;
        }

        printf("array of %d elements\n", outputSize);
        for (i = 0; i < outputSize ; i++)
        {
            if (output !=NULL)
            {
                if (output[i]!=NULL)
                    printf("  element[%d]=%s\n", i, output[i] );
                else
                    printf("  element[%d]=<empty>\n", i );
            }
            else
                printf("  element[%d]=<nil>\n", i );
        }
    
        axiscAxisDelete(arrayResult, XSDC_ARRAY);
    }

    // Test complex type
    {
        SimpleComplexType complexTypeInput;
        SimpleComplexType* complexTypeResult;
        
        complexTypeInput.complexTypeElement = simpleNCName;
        complexTypeResult = asComplexType(ws, &complexTypeInput);
        
        if (exceptionOccurred == C_TRUE
            || get_XSD_NCName_Status(ws) == AXISC_FAIL )
            printf ("Failed\n");
                   
        if (complexTypeResult->complexTypeElement)
        {
            if (*(complexTypeResult->complexTypeElement))
                printf("within complex type=%s\n", complexTypeResult->complexTypeElement);
            else
                printf("within complex type=<empty>\n" );
        }
        else
            printf("within complex type=<nil>\n" );
    
        Axis_Delete_SimpleComplexType(complexTypeResult, 0);
    }

    // Tests now complete

    destroy_XSD_NCName_stub(ws);

    printf("---------------------- TEST COMPLETE -----------------------------\n");
   
    return 0;
}
