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

#include "Calculator.hpp"
#include <axis/AxisException.hpp>
#include <axis/GDefine.hpp>
#include <ctype.h>
#include <iostream>
#include <signal.h>

void sig_handler(int);
void PrintUsage();
bool IsNumber(const char* p);
void callCalculatorAndPrintProperties(Calculator& calculator, int, int);

int main(int argc, char* argv[])
{
        char endpoint[256];
        const char* url="http://localhost:80/axis/Calculator";
        const char* op = 0;
        int i1=0, i2=0;

        signal(SIGILL, sig_handler);
        signal(SIGABRT, sig_handler);
        signal(SIGSEGV, sig_handler);
        //signal(SIGQUIT, sig_handler);
        //signal(SIGBUS, sig_handler);
        signal(SIGFPE, sig_handler);

        url = argv[1];

        try
        {
                sprintf(endpoint, "%s", url);
                Calculator ws(endpoint);

                op = "add";
                i1 = 2;
                i2 = 3;

        ws.setMaintainSession(true);
        cout << "Calling calculator for the first time and expecting Set-Cookie back"<<endl;
        callCalculatorAndPrintProperties(ws, i1, i2);
        
        // get the cookies
        cout <<"Storing the cookies so I can give them to the next web service"<<endl;
        int currentCookieKey=0;
        string cookieKeys[3];
        const char* key = ws.getFirstTransportPropertyKey();
        string keyString(key);
        if(key)
        {
            if(keyString.compare("Set-Cookie")==0)
            {
             string valueString(ws.getCurrentTransportPropertyValue());
             cookieKeys[currentCookieKey++] = valueString;
            }
        }
        // then the rest
        while(key = ws.getNextTransportPropertyKey())
        {
            string nextKeyString(key);
            if(nextKeyString.compare("Set-Cookie")==0)
            {
             string valueString(ws.getCurrentTransportPropertyValue());
            cookieKeys[currentCookieKey++] = valueString;
            }
        }
        
        cout << "Calling calculator for the second time and expecting to send the cookies back"<<endl;
        callCalculatorAndPrintProperties(ws, i1, i2);
        
        // Now create a new instance of the service and the cookies should be lost
        cout <<"Use a new instance of calculator and ensure that the old cookies are lost"<<endl;
        Calculator calculator(endpoint);
        calculator.setMaintainSession(true);
        callCalculatorAndPrintProperties(calculator, i1, i2);
        // OK, Now add the previously saved cookie on to this new service.
        cout << "Add the cookies from the previous web service to the new web service"<<endl;
        currentCookieKey=0;
        while(currentCookieKey< 3)
        {
            calculator.setTransportProperty("Cookie", cookieKeys[currentCookieKey++].c_str());
        }
        cout <<"Completed adding cookies"<<endl;
        // Call the service again twice to ensure that the key has been set as a cookie
        cout <<"Call the calculator service twice and ensure that the cookies remain"<<endl;
        callCalculatorAndPrintProperties(calculator, i1, i2);
        callCalculatorAndPrintProperties(calculator, i1, i2);
        // Delete one of the cookies
        cout <<"Deleting the LtpaToken2 cookie"<<endl;
        calculator.deleteTransportProperty("LtpaToken2");
        cout << "Calling the service and not expecting the LtpaToken2 in the cookie header"<<endl;
        callCalculatorAndPrintProperties(calculator, i1, i2);
        // OK, now remove all the cookie remaining 
        cout <<"Removing all the cookies by using the 'deleteTransportProperty(Cookie)' method"<<endl;
        calculator.deleteTransportProperty("Cookie");
        cout <<"Calling the service and expecting no cookies to be there"<<endl;
        callCalculatorAndPrintProperties(calculator, i1, i2);
        }
        catch(AxisException& e)
        {
                        cout << "Exception : " << e.what() << endl;
        }
        catch(exception& e)
        {
            cout << "Unknown exception has occured : " << e.what() << endl;
        }
        catch(...)
        {
            cout << "Unknown exception has occured" << endl;
        }
  cout<< "---------------------- TEST COMPLETE -----------------------------"<< endl;
        
        return 0;
}

void callCalculatorAndPrintProperties(Calculator& calculator, int i1, int i2)
{
 
        int iResult = calculator.add(i1, i2);
        // get the HTTP properties that were sent out
        cout <<"----------------------------------------------------------"<<endl;
        cout << "Properties that were sent out"<<endl;
        const char* key = calculator.getFirstTransportPropertyKey(false);
        if(key)
        {
            cout << key;
            cout << "="<<calculator.getCurrentTransportPropertyValue(false)<<endl;
        }
        // then the rest
        while(key = calculator.getNextTransportPropertyKey(false))
        {
            cout << key;
            cout << "="<<calculator.getCurrentTransportPropertyValue(false)<<endl;
        }
        cout <<"----------------------------------------------------------"<<endl;
        cout << "Properties that were received"<<endl;
        key = calculator.getFirstTransportPropertyKey();
        if(key)
        {
            cout << key;
            cout << "="<<calculator.getCurrentTransportPropertyValue()<<endl;
        }
        // then the rest
        while(key = calculator.getNextTransportPropertyKey())
        {
            cout << key;
            cout << "="<<calculator.getCurrentTransportPropertyValue()<<endl;
        }
        cout <<"----------------------------------------------------------"<<endl;
        
        
 
}

void PrintUsage()
{
        printf("Usage :\n Calculator <url>\n\n");
        exit(1);
}

bool IsNumber(const char* p)
{
        for (int x=0; x < (int) strlen(p); x++)
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

