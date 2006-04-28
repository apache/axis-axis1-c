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

#include "MinOccursIsZero.hpp"
#include "CommonClientTestCode.hpp"
#include <axis/AxisException.hpp>
#include <ctype.h>
#include <iostream>
#include <signal.h>

void sig_handler(int);
void PrintUsage();
bool IsNumber(const char* p);

int main(int argc, char* argv[])
{
        char endpoint[256];
        const char* url="http://localhost:80/axis/MinOccursIsZero";

        signal(SIGILL, sig_handler);
        signal(SIGABRT, sig_handler);
        signal(SIGSEGV, sig_handler);
        //signal(SIGQUIT, sig_handler);
        //signal(SIGBUS, sig_handler);
        signal(SIGFPE, sig_handler);

        url = argv[1];

        bool bSuccess = false;
        int     iRetryIterationCount = 3;

        do
        {
                try
                {
                        sprintf(endpoint, "%s", url);
                        MinOccursIsZero ws(endpoint);

                        // Optional parameters with values
                        cout << "Optional parameters with values" << endl;
                        {
                                // Prepare input parameters
                                xsd__string stringElement = new char[7];
                                strcpy(stringElement, "Hello!");
                                xsd__integer * integerElement = new xsd__integer(123);
                                SimpleComplexType * complexType = new SimpleComplexType();
                                xsd__string stringElement2 = new char[9];
                                strcpy(stringElement2, "Goodbye!");
                                complexType->setstringElement(stringElement2);
                                xsd__integer * integerElement2 = new xsd__integer(234);
                                complexType->setintegerElement(integerElement2);
                                BasicComplexType * basicComplexType = new BasicComplexType();
                                xsd__string stringElement3 = new char[9];
                                strcpy(stringElement3, "Welcome!");
                                basicComplexType->setstringElement(stringElement3);
                                xsd__integer * integerElement3 = new xsd__integer(345);
                                basicComplexType->setintegerElement(integerElement3);
                                complexType->setcomplexType(basicComplexType);

                                
                                // Prepare output parameters
                                xsd__string outStringElement = NULL;
                                xsd__integer * outIntegerElement = NULL;
                                SimpleComplexType * outComplexType = NULL;

                                // Invoke web service
                                ws.optionalElements(stringElement, integerElement, complexType, &outStringElement, &outIntegerElement, &outComplexType);

                                // Print results
                                if (outStringElement != NULL)
                                {
                                        cout << "String element = " << outStringElement << endl;
                                }
                                else
                                {
                                        cout << "String element = NULL" << endl;
                                }
                                if (outIntegerElement != NULL)
                                {
                                        cout << "Integer element = " << *outIntegerElement << endl;
                                }
                                else
                                {
                                        cout << "Integer element = NULL" << endl;
                                }
                                if (outComplexType != NULL)
                                {
                                        cout << "ComplexType" << endl;
                                        if (outComplexType->stringElement != NULL)
                                        {
                                                cout << " String element = " << outComplexType->stringElement << endl;
                                        }
                                        else
                                        {
                                                cout << " String element = NULL" << endl;
                                        }
                                        if (outComplexType->integerElement != NULL)
                                        {
                                                cout << " Integer element = " << *outComplexType->integerElement << endl;
                                        }
                                        else
                                        {
                                                cout << " Integer element = NULL" << endl;
                                        }
                                        if (outComplexType->complexType != NULL)
                                        {
                                                cout << " ComplexType" << endl;
                                                if (outComplexType->complexType->stringElement != NULL)
                                                {
                                                        cout << "  String element = " << outComplexType->complexType->stringElement << endl;
                                                }
                                                else
                                                {
                                                        cout << "  String element = NULL" << endl;
                                                }
                                                if (outComplexType->complexType->integerElement != NULL)
                                                {
                                                        cout << "  Integer element = " << *outComplexType->complexType->integerElement << endl;
                                                }
                                                else
                                                {
                                                        cout << "  Integer element = NULL" << endl;
                                                }
                                        }
                                        else
                                        {
                                                cout << " ComplexType = NULL" << endl;
                                        }
                                }
                                else
                                {
                                        cout << "ComplexType = NULL" << endl;
                                }
                        }


                        // Optional parameters with no values in complex type
                        cout << "Optional parameters with no values in complex type" << endl;
                        {
                                // Prepare input parameters
                                xsd__string stringElement = new char[7];
                                strcpy(stringElement, "Hello!");
                                xsd__integer * integerElement = new xsd__integer(123);
                                SimpleComplexType * complexType = new SimpleComplexType();
                                complexType->setstringElement(NULL);
                                complexType->setintegerElement(NULL);
                                complexType->setcomplexType(NULL);

                                
                                // Prepare output parameters
                                xsd__string outStringElement = NULL;
                                xsd__integer * outIntegerElement = NULL;
                                SimpleComplexType * outComplexType = NULL;

                                // Invoke web service
                                ws.optionalElements(stringElement, integerElement, complexType, &outStringElement, &outIntegerElement, &outComplexType);

                                // Print results
                                if (outStringElement != NULL)
                                {
                                        cout << "String element = " << outStringElement << endl;
                                }
                                else
                                {
                                        cout << "String element = NULL" << endl;
                                }
                                if (outIntegerElement != NULL)
                                {
                                        cout << "Integer element = " << *outIntegerElement << endl;
                                }
                                else
                                {
                                        cout << "Integer element = NULL" << endl;
                                }
                                if (outComplexType != NULL)
                                {
                                        cout << "ComplexType" << endl;
                                        if (outComplexType->stringElement != NULL)
                                        {
                                                cout << " String element = " << outComplexType->stringElement << endl;
                                        }
                                        else
                                        {
                                                cout << " String element = NULL" << endl;
                                        }
                                        if (outComplexType->integerElement != NULL)
                                        {
                                                cout << " Integer element = " << *outComplexType->integerElement << endl;
                                        }
                                        else
                                        {
                                                cout << " Integer element = NULL" << endl;
                                        }
                                        if (outComplexType->complexType != NULL)
                                        {
                                                cout << " ComplexType" << endl;
                                                if (outComplexType->complexType->stringElement != NULL)
                                                {
                                                        cout << "  String element = " << outComplexType->complexType->stringElement << endl;
                                                }
                                                else
                                                {
                                                        cout << "  String element = NULL" << endl;
                                                }
                                                if (outComplexType->complexType->integerElement != NULL)
                                                {
                                                        cout << "  Integer element = " << *outComplexType->complexType->integerElement << endl;
                                                }
                                                else
                                                {
                                                        cout << "  Integer element = NULL" << endl;
                                                }
                                        }
                                        else
                                        {
                                                cout << " ComplexType = NULL" << endl;
                                        }
                                }
                                else
                                {
                                        cout << "ComplexType = NULL" << endl;
                                }
                        }

                        // Optional parameters with no values
                        cout << "Optional parameters with no values" << endl;
                        {                       
                                // Prepare output parameters
                                xsd__string outStringElement = NULL;
                                xsd__integer * outIntegerElement = NULL;
                                SimpleComplexType * outComplexType = NULL;

                                // Invoke web service
                                ws.optionalElements(NULL, NULL, NULL, &outStringElement, &outIntegerElement, &outComplexType);

                                // Print results
                                if (outStringElement != NULL)
                                {
                                        cout << "String element = " << outStringElement << endl;
                                }
                                else
                                {
                                        cout << "String element = NULL" << endl;
                                }
                                if (outIntegerElement != NULL)
                                {
                                        cout << "Integer element = " << *outIntegerElement << endl;
                                }
                                else
                                {
                                        cout << "Integer element = NULL" << endl;
                                }
                                if (outComplexType != NULL)
                                {
                                        cout << "ComplexType" << endl;
                                        if (outComplexType->stringElement != NULL)
                                        {
                                                cout << " String element = " << outComplexType->stringElement << endl;
                                        }
                                        else
                                        {
                                                cout << " String element = NULL" << endl;
                                        }
                                        if (outComplexType->integerElement != NULL)
                                        {
                                                cout << " Integer element = " << *outComplexType->integerElement << endl;
                                        }
                                        else
                                        {
                                                cout << " Integer element = NULL" << endl;
                                        }
                                        if (outComplexType->complexType != NULL)
                                        {
                                                cout << " ComplexType" << endl;
                                                if (outComplexType->complexType->stringElement != NULL)
                                                {
                                                        cout << "  String element = " << outComplexType->complexType->stringElement << endl;
                                                }
                                                else
                                                {
                                                        cout << "  String element = NULL" << endl;
                                                }
                                                if (outComplexType->complexType->integerElement != NULL)
                                                {
                                                        cout << "  Integer element = " << *outComplexType->complexType->integerElement << endl;
                                                }
                                                else
                                                {
                                                        cout << "  Integer element = NULL" << endl;
                                                }
                                        }
                                        else
                                        {
                                                cout << " ComplexType = NULL" << endl;
                                        }
                                }
                                else
                                {
                                        cout << "ComplexType = NULL" << endl;
                                }
                        }

                        bSuccess = true;
                }
                catch(AxisException& e)
                {
                        bool bSilent = false;

                        if( e.getExceptionCode() == CLIENT_TRANSPORT_OPEN_CONNECTION_FAILED)
                        {
                                if( iRetryIterationCount > 0)
                                {
                                        bSilent = true;
                                }
                        }
                        else
                        {
                                iRetryIterationCount = 0;
                        }

            if( !bSilent)
                        {
                                cout << "Exception : " << e.what() << endl;
                        }
                }
                catch(exception& e)
                {
                        cout << "Unknown exception has occured" << endl;
                }
                catch(...)
                {
                        cout << "Unknown exception has occured" << endl;
                }
        iRetryIterationCount--;
        } while( iRetryIterationCount > 0 && !bSuccess);

        cout<< "---------------------- TEST COMPLETE -----------------------------"<< endl;
        
        return 0;
}

void PrintUsage()
{
        printf("Usage :\n Calculator <url>\n\n");
        exit(1);
}

bool IsNumber(const char* p)
{
        for (int x=0; x < strlen(p); x++)
        {
                if (!isdigit(p[x])) return false;
        }
        return true;
}

void sig_handler(int sig) {
        signal(sig, sig_handler);
    cout << "SIGNAL RECEIVED " << sig << endl;
        exit(1);
}

