#include "AxisBench.hpp"
#include <iostream>
#include <time.h>

#ifndef WIN32
#include "sys/time.h"
#else
#include "sys/timeb.h"
#endif

#include <stdlib.h> // For malloc(), calloc(), strdup() and free()
#include <iostream>

  // Bug in MS Visual C++ 6.0. Fixed in Visual C++ .Net version.
  // Cannot print an __int64 number with cout without this overloading
std::ostream & operator << (std::ostream & os, __int64 i)
{
    char	buf[20];

    sprintf( buf, "%I64d", i);

    os << buf;

    return os;
}

#define WSDL_DEFAULT_ENDPOINT "http://localhost:80/axis/bench"

static char * asciiToString( char * string);

static void usage( char * programName, char * defaultURL)
{
    cout << "Usage:" << endl
		 << programName << " [-? | service_url] " << endl
		 << "    -?              Show this help." << endl
		 << "    service_url     URL of the service." << endl
		 << "    Default service URL is assumed to be " << defaultURL << endl;
}

int main( int argc, char * argv[])
{
    char				endpoint[256];
    int					returnValue = 1;	// Assume Failure
    bool				bSuccess = false;
    int					iRetryIterationCount = 3;
	AxisBench *			ws = NULL;
	BenchDataType *		input = NULL;
    BenchDataType *		output = NULL;

    sprintf( endpoint, "%s", WSDL_DEFAULT_ENDPOINT);

    if( argc > 1)
    {
	// Watch for special case help request
	// Check for - only so that it works for
	//-?, -h or --help; -anything
		if( !strncmp( argv[1], "-", 1))
		{
		    usage( argv[0], endpoint);
	
			return 2;
		}

		sprintf( endpoint, argv[1]);
    }

	do
	{
		try
		{
			int				request = 1;
		    
			input = new BenchDataType();
			ws = new AxisBench( endpoint, APTHTTP1_1);

			input->setcount( (xsd__int) 10);

			BenchBasicDataType **		ppBBDT = new BenchBasicDataType* [input->getcount()];
            BenchBasicDataType_Array	arrayIn;

#ifdef WIN32
			__int64 ll = 10000;
#else
			long long ll = 10000;
#endif

			time_t	tim;

			tim = 1100246323;

			struct tm *	temp = gmtime( &tim);
			struct tm	lt;

			memcpy( &lt, temp, sizeof( struct tm));

		    xsd__unsignedByte *	buffer = (xsd__unsignedByte *) calloc( 1, input->getcount() + 2);

			strcpy( (char *) buffer, "A");

			for( int i = 0; i < (int) input->getcount(); i++)
			{
				BenchBasicDataType *	type = new BenchBasicDataType();

				type->StringType = "StringType";
				type->IntegerType = 10 * (i + 1);
				type->DoubleType = 11.111 * (i + 1);
				type->BooleanType = true_;
				type->DateTimeType = lt;
				type->TimeType = lt;
				type->DateType = lt;
				type->IntType = (i + 1);
				type->ByteType = '1';
				type->DecimalType = 10 * (i + 1);
				type->FloatType = (float) ((float) (11 * (i + 1)) / (float) 2.0);
				type->LongType = ll;
				type->QNameType = "toto";
				type->ShortType = (i + 1);
				type->Base64BinaryType.set( (xsd__unsignedByte *) buffer, (xsd__int) i);
				type->HexBinary.set( (xsd__unsignedByte *) buffer, (xsd__int) i);

				*ppBBDT = type;

				ppBBDT++;

				if( ll == 0)
				{
					ll = 1;
				}
				else
				{
					ll += 10000;
				}

				strcat( (char *) buffer, "A");
			}

			arrayIn.set( ppBBDT, (int) input->getcount());

			input->setinfos( &arrayIn);

			int	t1;
			int	t2;

#ifndef WIN32
			struct timeval mstart;
			struct timeval mstop;

			gettimeofday( &mstart, NULL);
#else
			struct timeb mstart;
			struct timeb mstop;
			ftime( &mstart);
#endif

			ws->setTransportProperty ("SOAPAction",	"AxisBench#doBenchRequest");

            for( int ii = 0; ii < request; ii++)
            {
                if( output)
                { // Samisa: memory management BP
                    int						outputSize = 0;
                    BenchBasicDataType **	outArray = output->infos->get( outputSize); 
                    
					for( int i = 0; i < outputSize; i++)
					{
                        delete outArray[i];
					}

                    delete output;

                    output = NULL;
                }

                output = ws->doBenchRequest( input);
            }

			free( buffer);

#ifndef WIN32
			gettimeofday( &mstop, NULL);

			t1 = mstart.tv_sec * 1000 + mstart.tv_usec / 1000;
			t2 = mstop.tv_sec * 1000 + mstop.tv_usec / 1000;
#else
			ftime( &mstop);

			t1 = mstart.time * 1000 + mstart.millitm;
			t2 = mstop.time * 1000 + mstop.millitm;
#endif

			int total = t2 - t1;

			if( ws->getStatus () == AXIS_FAIL)
			{
				cout << "Failed" << endl;
			}
			else
			{
				char	dateTime[50];
				int		i = 0;

				bSuccess = true;

				if (argc > 1)
				{
					i = output->count - 1;
				}

				cout << "Input Count : " << input->count << endl;
				cout << "Count : " << output->count << endl;

				for (; i < (int) output->getcount(); i++)
				{
	                int						outputSize = 0;
		            BenchBasicDataType **	outArray = output->infos->get( outputSize);

                    if( outArray[i] != NULL)
					{
                        cout << " ----------------------------------------------" << endl;
                        cout << " StringType " << outArray[i]->StringType << endl;
                        cout << " IntType " << outArray[i]->IntType << endl;
//                        cout << " IntegerType " << outArray[i]->IntegerType << endl;
                        cout << " DoubleType " << outArray[i]->DoubleType << endl;
                        cout << " BooleanType " << outArray[i]->BooleanType << endl;
                        strftime(dateTime, 50, "%a %b %d %H:%M:%S %Y", &outArray[i]->DateTimeType);
                        cout << " DateTimeType " << dateTime << endl;
                        strftime(dateTime, 50, "%a %b %d %Y", &outArray[i]->DateType);
                        cout << " DateType " << dateTime << endl;
// This is being removed due to problem in some servers.
// See XSDTime or XSDTimeNil testcases for full validation of the xsd:time type
//                      strftime(dateTime, 50, "%H:%M:%S", &output->infos.m_Array[i]->TimeType);
//                      cout << " TimeType " << dateTime << endl;

// Following check for os/400 - the mock server will return ascii char which needs to be converted
#ifdef __OS400__
                        if( outArray[i]->ByteType == 0x31) 
                            outArray[i]->ByteType = '1';
#endif
                        cout << " ByteType " << outArray[i]->ByteType << endl;
                        cout << " DecimalType " << outArray[i]->DecimalType << endl;
                        cout << " FloatType " << outArray[i]->FloatType << endl;
//                        cout << " LongType " << outArray[i]->LongType << endl;
                        cout << " QNameType " << outArray[i]->QNameType << endl;
                        cout << " ShortType " << outArray[i]->ShortType << endl;

                        int					size = 0;
                        xsd__unsignedByte *	base64BinaryData = outArray[i]->Base64BinaryType.get( size);

                        cout << " Base64BinaryType " << size << endl;

                        if( size > 0)
                        {
                            cout << " Base64BinaryType " << asciiToString( (char *)base64BinaryData) << endl;
                        }

                        size = 0;

                        xsd__unsignedByte * hexBinaryData = outArray[i]->HexBinary.get(size);

                        cout << " HexBinaryType " << size << endl;

                        if( size > 0)
                        {
                            cout << " HexBinaryType " << asciiToString( (char *) hexBinaryData) << endl;
                        }
                    }
				}

			returnValue = 0;
			}
		}
	catch (AxisException & e)
	{
	    bool bSilent = false;

	    if( e.getExceptionCode () == CLIENT_TRANSPORT_OPEN_CONNECTION_FAILED)
	    {
			if( iRetryIterationCount > 1)
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
			cout << "Exception : " << e.what () << endl;
	    }
	}
	catch( ...)
	{
	    cerr << "Unknown Exception occured." << endl;
	}

	// make sure we clean up memory allocated
	try
	{
		delete ws; 
		delete input;

		if( output)
		{
			delete output;
		}
	}
	catch( AxisException & e)
	{
	    cerr << e.what() << endl;
	}
	catch( exception & e)
	{
	    cout << "Exception : " << e.what () << endl;
	}
	catch (...)
	{
	    cout << "Unknown exception on clean up: " << endl;
	}
	iRetryIterationCount--;
    }
    while (iRetryIterationCount > 0 && !bSuccess);
    cout <<
	"---------------------- TEST COMPLETE -----------------------------"
	<< endl;
    printf ("successful \n");
    return returnValue;

}

static char * asciiToString( char * string)
{
   char * pch = string;

   if( string == NULL)
   {
	   return NULL;
   }
 
   /* while not EOL... */
   while( *pch != '\0')
   {
		pch++;
   }

   return string;
}
