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

void usage( char * pszProgramName, char * pszDefaultURL);
int findMyEndpoint( int argc, char * argv[], char * pszEndpoint);
bool IsNumber( const char * pszNumber);

int main (int argc, char *argv[])
{
    char	pszEndpoint[256];
    char *	pszServer = "localhost";
    int		iPort = 9080;
	int		iReturnValue = 1;

    // Set default service URL
	sprintf( pszEndpoint, "http://%s:%d/axis/Calculator", pszServer, iPort);

    try
    {
		if( (iReturnValue = findMyEndpoint( argc, argv, pszEndpoint)) == 2)
		{
			return iReturnValue;
		}

		Calculator		ws( pszEndpoint);
		const char *	pszOperation = argv[1];
		const char *	pszNumber1 = argv[2];
		const char *	pszNumber2 = argv[3];
		int				iNumber1 = 0;
		int				iNumber2 = 0;
		int				iResult;
		int				iExpectedResult;

		if( !IsNumber( pszNumber1))
		{
			cout << "Invalid value for first <parameter> " << pszNumber1 << endl;

			usage (argv[0], pszEndpoint);

			return 2;
		}

		if( !IsNumber( pszNumber2))
		{
			cout << "Invalid value for second <parameter> " << pszNumber2 << endl;

			usage (argv[0], pszEndpoint);

			return 2;
		}

		iNumber1 = atoi( pszNumber1);
		iNumber2 = atoi( pszNumber2);

		if( !strcmp( pszOperation, "add"))
		{
			iResult = ws.add( iNumber1, iNumber2);

			iExpectedResult = iNumber1 + iNumber2;
		}
		else if( !strcmp( pszOperation, "sub"))
		{
			iResult = ws.sub( iNumber1, iNumber2);

			iExpectedResult = iNumber1 - iNumber2;
		}
		else if( !strcmp( pszOperation, "mul"))
		{
			iResult = ws.mul( iNumber1, iNumber2);

			iExpectedResult = iNumber1 * iNumber2;
		}
		else if( !strcmp( pszOperation, "div"))
		{
			iResult = ws.div( iNumber1, iNumber2);

			iExpectedResult = iNumber1 / iNumber2;
		}
		else
		{
			cout << "Invalid operation " << pszOperation << endl << endl;

			usage (argv[0], pszEndpoint);

			return 2;
		}
		
		cout << iResult << endl;

		if( iResult == iExpectedResult)
		{
			iReturnValue = 0;
		}
    }
    catch( AxisException & e)
    {
		cout << "Exception : " << e.what() << endl;
    }
    catch( exception & e)
    {
		cout << "Unknown exception has occurred : " << e.what() << endl;
    }
    catch( ...)
    {
		cout << "Unknown exception has occurred" << endl;
    }

	return iReturnValue;
}

void usage( char * pszProgramName, char * pszDefaultURL)
{
    cout << endl << "Usage:" << endl
		 << pszProgramName << " [-? | operator number1 number2 [service_url]] " << endl
		 << "\t-?              Show this help." << endl
		 << "\tservice_url     URL of the service." << endl
		 << "\tDefault service URL is assumed to be " << pszDefaultURL << endl;
}

bool IsNumber( const char * pszNumber)
{
    for( int iDigitCount = 0; iDigitCount < (int) strlen( pszNumber); iDigitCount++)
    {
		if( !isdigit( pszNumber[iDigitCount]))
		{
			return false;
		}
    }

    return true;
}

int findMyEndpoint( int argc, char * argv[], char * pszEndpoint)
{
    if( argc == 0 ||
		argc != 5 ||
		(argc > 0 && *argv[1] == '-'))		// Watch for special case help request
		{									// Check for - only so that it works for
		    usage( argv[0], pszEndpoint);	// -?, -h or --help; -anything
	    
			return 2;
		}

	sprintf( pszEndpoint, argv[4]);
	    
	return 1;
}