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


#include "XSD_base64Binary.hpp"
#include <axis/AxisException.hpp>
#include <ctype.h>
#include <iostream>
#include "CommonClientTestCode.hpp"


int main(int argc, char* argv[])
{
        char endpoint[256];
        const char* url="http://localhost:80/axis/XSD_base64Binary";

        if(argc>1)
                url = argv[1];

                // bool bSuccess = false;

        try
        {
                int count = 0;
                sprintf(endpoint, "%s", url);
                XSD_base64Binary* ws = new XSD_base64Binary(endpoint);

        xsd__base64Binary input;

                xsd__unsignedByte binaryStream[] = {255, 1, 254, 2, 127, 0};

        xsd__unsignedByte* testUB = binaryStream;

        input.set(testUB, 6);
        
                // Test complex type
                SimpleComplexType complexTypeInput;
                complexTypeInput.setcomplexTypeElement(input);
                SimpleComplexType* complexTypeResult = ws->asComplexType(&complexTypeInput);
                cout << "within received complex type" << endl;
                xsd__base64Binary complexTypeElement = complexTypeResult->getcomplexTypeElement();
        int size = 0;
        const xsd__unsignedByte * data = complexTypeElement.get(size);
        cout << " size = " << size << endl;
                cout << " data = { ";
                for (count = 0 ; count < size ; count ++)
                {
                        if (count != 0)
                        {
                                cout << ", ";
                        }
                        cout << (unsigned int) data[count];
                }
                cout << " }" << endl;

                
                delete ws;

                // Check if everything is there after deleting the web service
                cout << "within received complex type after deleting web service" << endl;
        cout << " size = " << size << endl;
                cout << " data = { ";
                for (count = 0 ; count < size ; count ++)
                {
                        if (count != 0)
                        {
                                cout << ", ";
                        }
                        cout << (unsigned int) data[count];
                }
                cout << " }" << endl;

                // Re-run the web service, to try and ensure it blats anything it's going to blat
                ws = new XSD_base64Binary(endpoint);

        xsd__unsignedByte binaryStream2[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 255, 254, 253, 252, 251, 250};

        testUB = binaryStream2;

        input.set(testUB, 16);

                // Test complex type
                complexTypeInput.setcomplexTypeElement(input);
                SimpleComplexType* complexTypeResult2 = ws->asComplexType(&complexTypeInput);

                // Check if everything is there after re-creating and invoking web service
                cout << "within received complex type after re-creating and invoking web service" << endl;
        cout << " size = " << size << endl;
                cout << " data = { ";
                for (count = 0 ; count < size ; count ++)
                {
                        if (count != 0)
                        {
                                cout << ", ";
                        }
                        cout << (unsigned int) data[count];
                }
                cout << " }" << endl;

                delete ws;
                delete complexTypeResult2;
                delete complexTypeResult;
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

