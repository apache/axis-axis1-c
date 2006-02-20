// Copyright 2003-2004 The Apache Software Foundation.
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
#include <iostream>

bool IsNumber( const char *p);

static void usage( char * programName, char * defaultURL)
{
    cout << "\nUsage:\n"
	<< programName << " [-? | div number1 number2 [service_url]]\n"
	<< "    -?             Show this help.\n"
	<< "    service_url    URL of the service.\n"
	<< "    Default service URL is assumed to be " << defaultURL << endl;
}

int main( int argc, char * argv[])
{
    char *	pszURL = "http://localhost/axis/calculator";

    // Set default service URL

    try
    {
		if( argc == 1)
		{
			usage( argv[0], pszURL);
	    
			return 2;
		}

		if( argc > 1)
		{
			if( argv[1] == "-")
			{
// Check for - only so that it works for -?, -h or --help; -anything 

				usage( argv[0], pszURL);
		
				return 2;
			}

// Less than minimum number of args OR greater than maximum number of args
			else if( argc < 4 || argc > 5)
			{
				usage( argv[0], pszURL);
			
				return 2;
			}
			else if( argc == 5)
			{
				pszURL = argv[4];
			}
		}

//		cout << endl << " Using service at " << pszURL << endl << endl;
	
		Calculator ws( pszURL);

		char *	pszOperation = argv[1];
		char *	pValue1 = argv[2];
		char *	pValue2 = argv[3];

		if( !IsNumber( pValue1))
		{
			cout << "Invalid value for first <parameter> " << pValue1 << endl << endl;

            usage( argv[0], pszURL);
	    
			return 2;
		}

		if( !IsNumber( pValue2))
		{
			cout << "Invalid value for second <parameter> " << pValue2 << endl << endl;

            usage( argv[0], pszURL);
	    
			return 2;
		}

		int	iValue1 = atoi( pValue1);
		int	iValue2 = atoi( pValue2);

		if( strcmp( pszOperation, "add") == 0)
		{
		    cout << ws.add( iValue1, iValue2) << endl;
		}
		else if( strcmp( pszOperation, "sub") == 0)
		{
		    cout << ws.sub( iValue1, iValue2) << endl;
		}
		else if( strcmp( pszOperation, "mul") == 0)
		{
		    cout << ws.mul( iValue1, iValue2) << endl;
		}
		else if( strcmp( pszOperation, "div") == 0)
		{
		    cout << ws.div( iValue1, iValue2) << endl;
		}
		else
		{
		    cout << "Invalid operation " << pszOperation << endl << endl;

			usage( argv[0], pszURL);

			return 2;
		}
    }
    catch (AxisException & e)
    {
		cout << "Exception : " << e.what () << endl;
    }
    catch (exception & e)
    {
		cout << "Unknown exception has occurred : " << e.what () << endl;
    }
    catch (...)
    {
		cout << "Unknown exception has occurred" << endl;
    }

    return 0;
}

bool IsNumber( const char * p)
{
    for( int x = 0; x < (int) strlen( p); x++)
    {
		if( !isdigit( p[x]))
		{
			return false;
		}
    }

    return true;
}
