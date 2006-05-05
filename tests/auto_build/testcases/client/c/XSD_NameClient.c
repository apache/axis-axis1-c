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
#include "XSD_Name.h"

int main(int argc, char* argv[])
{
    AXISCHANDLE ws;
        
    xsdc__Name input;
    xsdc__Name result;

    RequiredAttributeElement requiredAttributeInput;
    RequiredAttributeElement* requiredAttributeResult;   
    
    char emptyName[1] = "";
    char simpleName[25] = "xml.si-mple_nam:e";    
    
    char endpoint[256];
    const char* url="http://localhost:80/axis/XSD_Name";

    if(argc>1)
        url = argv[1];

    axiscAxisRegisterExceptionHandler(exceptionHandler);

    sprintf(endpoint, "%s", url);
    ws = get_XSD_Name_stub(endpoint);
    if (!ws)
    {
        printf("FAILED to get WS\n");
        return -1;
    }
  
    // Test non-nillable element
    result = asNonNillableElement(ws, simpleName);
    if (exceptionOccurred == C_TRUE
        || get_XSD_Name_Status(ws) == AXISC_FAIL )
        printf ("Failed\n");
                
    if (result)
    {
        if (*result)
            printf("non-nillable element=%s\n", result);
        else
            printf("non-nillable element=<empty>\n");
            
        axiscAxisDelete(result, XSDC_NAME);
    }
    else
        printf("non-nillable element=<nil>\n");


    // Test empty non-nillable element
    input = (xsdc__NCName)axiscAxisNew(XSDC_NAME, 1);
    strcpy (input, emptyName);
    
    result = asNonNillableElement(ws, input);
    if (exceptionOccurred == C_TRUE
        || get_XSD_Name_Status(ws) == AXISC_FAIL )
        printf ("Failed\n");

    if (result)
    {
        if (*result)
            printf("empty non-nillable element=%s\n", result);
        else
            printf("empty non-nillable element=<empty>\n");
            
        axiscAxisDelete(result, XSDC_NAME);
    }
    else
        printf("empty non-nillable element=<nil>\n");

    axiscAxisDelete(input, XSDC_NAME);

    // Test nillable element, with a value
    result = asNillableElement(ws, simpleName);
    if (exceptionOccurred == C_TRUE
        || get_XSD_Name_Status(ws) == AXISC_FAIL )
        printf ("Failed\n");

    if (result)
    {
        if (*result)
            printf("nillable element=%s\n", result);
        else
            printf("nillable element=<empty>\n");
            
        axiscAxisDelete(result, XSDC_NAME);
    }
    else
        printf("nillable element=<nil>\n");

    // Test empty nillable element
    result = asNillableElement(ws, emptyName);
    if (exceptionOccurred == C_TRUE
        || get_XSD_Name_Status(ws) == AXISC_FAIL )
        printf ("Failed\n");

    if (result)
    {
        if (*result)
            printf("empty nillable element=%s\n", result);
        else
            printf("empty nillable element=<empty>\n");

        axiscAxisDelete(result, XSDC_NAME);
    }
    else
        printf("empty nillable element=<nil>\n");

    // Test nillable element, with nil
    result = asNillableElement(ws, NULL);
    if (exceptionOccurred == C_TRUE
        || get_XSD_Name_Status(ws) == AXISC_FAIL )
        printf ("Failed\n");

    if (result)
    {
        if (*result)
            printf("nil element=%s\n", result);
        else
            printf("nil element=<empty>\n");
            
        axiscAxisDelete(result, XSDC_NAME);
    }
    else
        printf("nil element=<nil>\n");

    // Test required attribute
    requiredAttributeInput.requiredAttribute = simpleName;
    requiredAttributeResult = asRequiredAttribute(ws, &requiredAttributeInput);
    if (exceptionOccurred == C_TRUE
        || get_XSD_Name_Status(ws) == AXISC_FAIL )
        printf ("Failed\n");
    
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
    requiredAttributeInput.requiredAttribute = emptyName;
    requiredAttributeResult = asRequiredAttribute(ws, &requiredAttributeInput);
    if (exceptionOccurred == C_TRUE
        || get_XSD_Name_Status(ws) == AXISC_FAIL )
        printf ("Failed\n");
    
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

/*  Optional Attributes currently unsupported by WSDL2Ws
 * Exact coding of this section may change depending on chosen implementation
        // Test optional attribute, with a value
   {
        OptionalAttributeElement optionalAttributeInput;
        OptionalAttributeElement* optionalAttributeResult;
        
        optionalAttributeInput.optionalAttribute = simpleName;
        OptionalAttributeElement* optionalAttributeResult = asOptionalAttribute(ws, &optionalAttributeInput);
        if (optionalAttributeResult->optionalAttribute)
        {
            if (*(optionalAttributeResult->optionalAttribute))
                printf("optional attribute, with data=%s\n" , optionalAttributeResult->optionalAttribute);
            else
                printf("optional attribute, with data=<empty>\n");
        }
        else
            printf("optional attribute, with data=<not present>\n");

         Axis_Delete_OptionalAttributeElement(optionalAttributeResult, 0);

        // Test empty optional attribute
        optionalAttributeInput.optionalAttribute = emptyName;
        optionalAttributeResult = asOptionalAttribute(ws, &optionalAttributeInput);
        if (optionalAttributeResult->optionalAttribute)
        {
            if (*(optionalAttributeResult->optionalAttribute))
                printf("empty optional attribute=%s\n" , optionalAttributeResult->optionalAttribute);
            else
                printf("empty optional attribute=<empty>\n");
        }
        else
            printf("empty optional attribute=<not present>\n");

        Axis_Delete_OptionalAttributeElement(optionalAttributeResult, 0);

        // Test optional attribute, not present
        // optionalAttributeInput.setattribute();
        optionalAttributeResult = asOptionalAttribute(ws, &optionalAttributeInput);
        if (optionalAttributeResult->optionalAttribute)
        {
            if (*(optionalAttributeResult->optionalAttribute))
                printf("optional attribute, not present=%s\n" , optionalAttributeResult->optionalAttribute);
            else
                printf("optional attribute, not present=<empty>\n");
        }
        else
            printf("optional attribute, not present=<not present>\n");
            
        Axis_Delete_OptionalAttributeElement(optionalAttributeResult, 0);
    }
*/

    // Test array
    {
#define ARRAY_SIZE 2                    
        int i;
        xsdc__Name_Array arrayInput;
        xsdc__Name_Array* arrayResult;
        xsdc__Name array[ARRAY_SIZE]; 
        const xsdc__Name* output;
        int outputSize=0;
               
        for (i=0 ; i < ARRAY_SIZE; i++)
            array[i]= simpleName;

        arrayInput.m_Array = array;
        arrayInput.m_Size  = ARRAY_SIZE;
        arrayInput.m_Type  = XSDC_NAME;
    
        arrayResult = asArray(ws, &arrayInput);
        
        if (exceptionOccurred == C_TRUE
            || get_XSD_Name_Status(ws) == AXISC_FAIL )
            printf ("Failed\n");

        if (arrayResult)
        {
           output     = arrayResult->m_Array;
           outputSize = arrayResult->m_Size;
        }
        
        printf("array of %d elements\n", outputSize);
        for (i = 0; i < outputSize ; i++)
        {
            if (output!=NULL)
            {
                if (output[i]!=NULL)
                    printf("  element[%d]=%s\n", i, output[i]);
                else
                    printf("  element[%d]=<empty>\n", i);
             }
            else
                printf("  element[%d]=<nil>\n", i);
        }

        axiscAxisDelete(arrayResult, XSDC_ARRAY);    
    }


    // Test complex type
    {
        SimpleComplexType complexTypeInput;
        SimpleComplexType* complexTypeResult;
        
        complexTypeInput.complexTypeElement = simpleName;
        complexTypeResult = asComplexType(ws, &complexTypeInput);
        
        if (exceptionOccurred == C_TRUE
            || get_XSD_Name_Status(ws) == AXISC_FAIL )
            printf ("Failed\n");
        
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
    destroy_XSD_Name_stub(ws);

    printf("---------------------- TEST COMPLETE -----------------------------\n");
   
    return 0;
}
