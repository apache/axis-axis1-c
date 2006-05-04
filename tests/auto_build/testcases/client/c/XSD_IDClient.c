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
#include "XSD_IDPort.h"


int main(int argc, char* argv[])
{
    AXISCHANDLE ws = NULL;
    xsdc__ID result = NULL;
    xsdc__ID input = NULL;
            
    RequiredAttributeElement requiredAttributeInput;
    RequiredAttributeElement* requiredAttributeResult;    
    
    char emptyID[1] = "";
    char simpleID[25] = "A simple test message!";
    char reservedCharactersID[] = "<>&\"\'";
    char whitespaceID[] = "  \t\r\nsome text \t\r\nmore text \t\r\n";
        
    char endpoint[256];
    const char* url="http://localhost:80/axis/XSD_IDPort";

    axiscAxisRegisterExceptionHandler(exceptionHandler);

    if(argc>1)
        url = argv[1];

    sprintf(endpoint, "%s", url);
    ws = get_XSD_IDPort_stub(url);    
    if (!ws)
    {
        printf("FAILED to get WS\n");
        return -1;
    }
  
    // Test non-nillable element
    input = (xsdc__ID)axiscAxisNew(XSDC_ID,25);
    strcpy (input, simpleID);

    result = asNonNillableElement(ws, input);
    
    if (exceptionOccurred == C_TRUE
        || get_XSD_IDPort_Status(ws) == AXISC_FAIL )
        printf ("Failed\n");
    
    if (result)
    {
        if (*result)
            printf("non-nillable element=%s\n", result);
        else
            printf("non-nillable element=<empty>\n");
        
        axiscAxisDelete(result, XSDC_ID);                
    }
    else
        printf("non-nillable element=<nil>\n");

    axiscAxisDelete(input, XSDC_ID);

    // Test empty non-nillable element
    input = (xsdc__ID)axiscAxisNew(XSDC_ID, 1);
    strcpy (input, emptyID);   
    result = asNonNillableElement(ws,input);
    if (exceptionOccurred == C_TRUE
        || get_XSD_IDPort_Status(ws) == AXISC_FAIL )
        printf ("Failed\n");
    
    if (result)
    {
        if (*result)
            printf("empty non-nillable element=%s\n", result);
        else
            printf("empty non-nillable element=<empty>\n");
        
        axiscAxisDelete(result, XSDC_ID);                
    }
    else
        printf("empty non-nillable element=<nil>\n");

    axiscAxisDelete(input, XSDC_ID);

    // Test non-nillable element with XML reserved characters
    input = reservedCharactersID;
    result = asNonNillableElement(ws,input);
    if (exceptionOccurred == C_TRUE
        || get_XSD_IDPort_Status(ws) == AXISC_FAIL )
        printf ("Failed\n");
    
    if (result)
    {
        if (*result)
            printf("non-nillable element with XML reserved characters=%s\n", result);
        else
            printf("non-nillable element with XML reserved characters=<empty>\n");
        
        axiscAxisDelete(result, XSDC_ID);                
    }
    else
        printf("non-nillable element with XML reserved characters=<nil>\n");

    // Test non-nillable element with XML reserved characters
    input = whitespaceID;
    result = asNonNillableElement(ws, input);
    if (exceptionOccurred == C_TRUE
        || get_XSD_IDPort_Status(ws) == AXISC_FAIL )
        printf ("Failed\n");
    
    if (result)
    {
        if (*result)
            printf("non-nillable element with whitespace characters=\"%s\"\n", result);
        else
            printf("non-nillable element with whitespace characters=<empty>\n");
        
        axiscAxisDelete(result, XSDC_ID);                
    }
    else
        printf("non-nillable element with whitespace characters=<nil>\n");

    // Test nillable element, with a value
    input = (xsdc__ID)axiscAxisNew(XSDC_ID,25);
    strcpy (input, simpleID);
    result = asNillableElement(ws, input);
    if (exceptionOccurred == C_TRUE
        || get_XSD_IDPort_Status(ws) == AXISC_FAIL )
        printf ("Failed\n");
    
    if (result)
    {
        if (*result)
            printf("nillable element=%s\n", result);
        else
            printf("nillable element=<empty>\n");
            
        axiscAxisDelete(result, XSDC_ID);
    }
    else
        printf("nillable element=<nil>\n");
    
    axiscAxisDelete(input, XSDC_ID);

    // Test empty nillable element
    input = (xsdc__ID)axiscAxisNew(XSDC_ID,1);
    strcpy (input, emptyID);
    result = asNillableElement(ws, input);
    if (exceptionOccurred == C_TRUE
        || get_XSD_IDPort_Status(ws) == AXISC_FAIL )
        printf ("Failed\n");
    
    if (result)
    {
        if (*result)
            printf("empty nillable element=%s\n", result);
        else
            printf("empty nillable element=<empty>\n");
            
        axiscAxisDelete(result, XSDC_ID);
    }
    else
        printf("empty nillable element=<nil>\n");

    axiscAxisDelete(input, XSDC_ID);

    // Test nillable element, with nil
    result = asNillableElement(ws, NULL);
    if (exceptionOccurred == C_TRUE
        || get_XSD_IDPort_Status(ws) == AXISC_FAIL )
        printf ("Failed\n");
    
    if (result)
    {
        if (*result)
            printf("nil element=%s\n", result);
        else
            printf("nil element=<empty>\n");
            
        axiscAxisDelete(result, XSDC_ID);
    }
    else
        printf("nil element=<nil>\n");

    // Test required attribute
    input = (xsdc__ID)axiscAxisNew(XSDC_ID,25);
    strcpy (input, simpleID);
    
    requiredAttributeInput.requiredAttribute = input;
    requiredAttributeResult = asRequiredAttribute(ws, &requiredAttributeInput);
    if (exceptionOccurred == C_TRUE
        || get_XSD_IDPort_Status(ws) == AXISC_FAIL )
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
    axiscAxisDelete(input, XSDC_ID);


    // Test empty required attribute
    input = (xsdc__ID)axiscAxisNew(XSDC_ID,1);
    strcpy (input, emptyID);

    requiredAttributeInput.requiredAttribute = input;
    requiredAttributeResult = asRequiredAttribute(ws, &requiredAttributeInput);
    if (exceptionOccurred == C_TRUE
        || get_XSD_IDPort_Status(ws) == AXISC_FAIL )
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
    axiscAxisDelete(input, XSDC_ID);

/* Optional Attributes currently unsupported by WSDL2Ws
 * Exact coding of this section may change depending on chosen implementation
        // Test optional attribute, with a value
        input = new char[25];
        strcpy (input, simpleID);
        OptionalAttributeElement optionalAttributeInput;
        optionalAttributeInput.setoptionalAttribute(input);
        OptionalAttributeElement* optionalAttributeResult = ws->asOptionalAttribute(&optionalAttributeInput);
        if (optionalAttributeResult->getoptionalAttribute())
        {
            if (*(optionalAttributeResult->getoptionalAttribute()))
                printf("optional attribute, with data=" << optionalAttributeResult->getoptionalAttribute() << endl;
            else
                printf("optional attribute, with data=<empty>\n");

        }
        else
            printf("optional attribute, with data=<not present>\n");

        delete [] input;
        delete optionalAttributeResult;

        // Test empty optional attribute
        emptyInput = new char[1];
        strcpy (emptyInput, emptyID);
        optionalAttributeInput.setoptionalAttribute(emptyInput);
        optionalAttributeResult = ws->asOptionalAttribute(&optionalAttributeInput);
        if (optionalAttributeResult->getoptionalAttribute())
        {
            if (*(optionalAttributeResult->getoptionalAttribute()))
                printf("empty optional attribute=" << optionalAttributeResult->getoptionalAttribute() << endl;
            else
                printf("empty optional attribute=<empty>\n");
        }
        else
            printf("empty optional attribute=<not present>\n");
        delete [] emptyInput;
        delete optionalAttributeResult;

        // Test optional attribute, not present
        // optionalAttributeInput.setattribute();
        optionalAttributeResult = ws->asOptionalAttribute(&optionalAttributeInput);
        if (optionalAttributeResult->getoptionalAttribute())
        {
            if (*(optionalAttributeResult->getoptionalAttribute()))
                printf("optional attribute, not present=" << optionalAttributeResult->getoptionalAttribute() << endl;
            else
                printf("optional attribute, not present=<empty>\n");
        }
        else
            printf("optional attribute, not present=<not present>\n");
        delete optionalAttributeResult;
*/

    // Test array
    {
#define ARRAY_SIZE 2                    
        int i;
        xsdc__ID_Array arrayInput;
        xsdc__ID_Array* arrayResult;
        xsdc__ID array[ARRAY_SIZE];  
        const xsdc__ID * output;
        int outputSize=0;
              
        for (i=0 ; i < ARRAY_SIZE; i++)
        {
            array[i]= (xsdc__ID)axiscAxisNew(XSDC_ID,25);
            strcpy (array[i], simpleID);
        }
        arrayInput.m_Array = array;
        arrayInput.m_Size  = ARRAY_SIZE;
        arrayInput.m_Type  = XSDC_ID;
        
        arrayResult = asArray(ws, &arrayInput);
        if (exceptionOccurred == C_TRUE
            || get_XSD_IDPort_Status(ws) == AXISC_FAIL )
            printf ("Failed\n");

        if (arrayResult)
        {
           output     = arrayResult->m_Array;
           outputSize = arrayResult->m_Size;
        }
        
        printf("array of %d elements\n", outputSize);
        for (i = 0; i < outputSize; i++)
        {
            if (output!=NULL)
            {
                if (output[i]!=NULL)
                    printf("  element[%d]=%s\n", i, output[i]);
                else
                    printf("  element[%d]=<empty>\n");
            }
            else
                printf("  element[%d]=<nil>\n");
        }
        
        // Clear up input array        
        for (i = 0 ; i < ARRAY_SIZE; i++ )
            axiscAxisDelete(array[i], XSDC_ID);
    
        axiscAxisDelete(arrayResult, XSDC_ARRAY);
    }

    // Test complex type
    {
        SimpleComplexType complexTypeInput;
        SimpleComplexType* complexTypeResult;
        
        input = (xsdc__ID)axiscAxisNew(XSDC_ID,25);
        strcpy (input, simpleID);

        complexTypeInput.complexTypeElement = input;
        complexTypeResult = asComplexType(ws, &complexTypeInput);
        
        if (exceptionOccurred == C_TRUE
            || get_XSD_IDPort_Status(ws) == AXISC_FAIL )
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
        
        axiscAxisDelete(input, XSDC_ID);
        Axis_Delete_SimpleComplexType(complexTypeResult, 0);
    }

    // Tests now complete

    destroy_XSD_IDPort_stub(ws);

    printf("---------------------- TEST COMPLETE -----------------------------\n");
   
    return 0;
}
