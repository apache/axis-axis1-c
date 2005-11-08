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


#include "XSD_double.hpp"
#include <axis/AxisException.hpp>
#include <ctype.h>
#include <iostream>


int main(int argc, char* argv[])
{
  char endpoint[256];
   const char* url="http://localhost:80/axis/XSD_double";

   if(argc>1)
        url = argv[1];

      // bool bSuccess = false;

   try
   {
     sprintf(endpoint, "%s", url);
     XSD_double* ws = new XSD_double(endpoint);

        // Test non-nillable element
      xsd__double result = ws->asNonNillableElement((xsd__double)70.7175888888);
      printf("non-nillable element=%.5f\n", result);
        fflush(stdout);

     // Test nillable element, with a value
        xsd__double* nillableInput = new xsd__double();
     *(nillableInput) = (xsd__double)70.7175888888;
     xsd__double* nillableResult = ws->asNillableElement(nillableInput);
        if (nillableResult)
       {
         printf("nillable element=%.5f\n", *(nillableResult));
            fflush(stdout);
            delete nillableResult;
        }
     else
      {
         cout << "nillable element=<nil>" << endl;
     }
       delete nillableInput;

     // Test nillable element, with nil
        nillableResult = ws->asNillableElement(NULL);
     if (nillableResult)
       {
         printf("nil element=%.5f\n", *(nillableResult));
            fflush(stdout);
         delete nillableResult;
        }
     else
      {
         cout << "nil element=<nil>" << endl;
      }

       // Test required attribute
        RequiredAttributeElement requiredAttributeInput;
      requiredAttributeInput.setrequiredAttribute((xsd__double)70.7175888888);
       RequiredAttributeElement* requiredAttributeResult = ws->asRequiredAttribute(&requiredAttributeInput);
     printf("required attribute=%.5f\n", requiredAttributeResult->getrequiredAttribute());
        fflush(stdout);
        delete requiredAttributeResult;

/* Optional Attributes currently unsupported by WSDL2Ws
 * Exact coding of this section may change depending on chosen implementation
     // Test optional attribute, with a value
      OptionalAttributeElement optionalAttributeInput;
      optionalAttributeInput.setoptionalAttribute(70.7175888888);
       OptionalAttributeElement* optionalAttributeResult = ws->asOptionalAttribute(&optionalAttributeInput);
     if (optionalAttributeResult->getoptionalAttribute())
      {
         printf("optional attribute, with data=%.5f\n", *(optionalAttributeResult->getoptionalAttribute()));
            fflush(stdout);
      }
     else
      {
         cout << "optional attribute, with data=<not present>" << endl;
        }
     delete optionalAttributeResult;

     // Test optional attribute, not present
       //optionalAttributeInput.setattribute();
      optionalAttributeResult = ws->asOptionalAttribute(&optionalAttributeInput);
       if (optionalAttributeResult->getoptionalAttribute())
      {
         printf("optional attribute, not present=%.5f\n", *(optionalAttributeResult->getoptionalAttribute()));
            fflush(stdout);
        }
     else
      {
         cout << "optional attribute, not present=<not present>" << endl;
      }
     delete optionalAttributeResult;
*/

     // Test array
        xsd__double_Array arrayInput;
		int arraySize=2;
		xsd__double **array =new xsd__double*[arraySize];        
        for (int inputIndex=0 ; inputIndex < 2 ; inputIndex++)
        {
            array[inputIndex] =new xsd__double(70.7175888888);          
        }
		arrayInput.set(array,arraySize);
        xsd__double_Array arrayResult = ws->asArray(arrayInput);
		int outputSize=0;
		const xsd__double ** output=arrayResult.get(outputSize);
        cout << "array of " << outputSize << " elements" << endl;
        for (int index = 0; index < outputSize ; index++)
         {
         printf("  element[%i]=%.5f\n", index,  *(output[index]));
            fflush(stdout);
        }
	  // Clear up input array        
        for (int deleteIndex = 0 ; deleteIndex < arraySize ; deleteIndex++ )
        {
            delete array[deleteIndex];
        }
        delete [] array;

      // Test complex type
      SimpleComplexType complexTypeInput;
       complexTypeInput.setcomplexTypeElement((xsd__double) 70.7175888888);
       SimpleComplexType* complexTypeResult = ws->asComplexType(&complexTypeInput);
      printf("within complex type=%.5f\n", complexTypeResult->getcomplexTypeElement());
        fflush(stdout);
        delete complexTypeResult;

       // Tests now complete

       delete ws;
    }
 catch(AxisException& e)
   {
     cout << "Exception : " << e.what() << endl;
   }
 catch(exception& e)
   {
     cout << "Unknown exception has occured: " << e.what() << endl;
    }
 catch(...)
    {
     cout << "Unknown exception has occured" << endl;
  }

   cout<< "---------------------- TEST COMPLETE -----------------------------"<< endl;
   
  return 0;
}
