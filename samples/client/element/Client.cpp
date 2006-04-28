
/*
 * Supported types are
  1 <element name="getBoolean">
  2 <element name="getByte">
  3 <element name="getUnsignedByte">
  4 <element name="getShort">
  5 <element name="getUnsignedShort">
  6 <element name="getInt">
  7 <element name="getUnsignedInt">
  8 <element name="getLong">
  9 <element name="getUnsignedLong">
 10 <element name="getFloat">
 11 <element name="getDouble">
 12 <element name="getDate">
 13 <element name="getDateTime">
 14 <element name="getTime">
 15 <element name="getDuration">
 16 <element name="getString">
 17 <element name="getInteger">
 18 <element name="getDecimal">
 19 <element name="getBase64Binary">
 20 <element name="getHexBinary">
 *
 */


#include "XSDElement.hpp"
#include <axis/AxisException.hpp>
#include <ctype.h>
#include <iostream>

#ifdef WIN32
  // Bug in MS Visual C++ 6.0. Fixed in Visual C++ .Net version.
  // Cannot print an __int64 number with cout without this overloading
/*
std::ostream & operator<< (std::ostream & os, __int64 i)
{
    char buf[20];
    sprintf (buf, "%I64d", i);
    os << buf;
    return os;
}
*/
#endif

static void usage( char * programName, char * defaultURL)
{
    cout << "Usage:" << endl
		 << programName << " [-? | service_url] " << endl
		 << "    -?              Show this help." << endl
		 << "    service_url     URL of the service." << endl
		 << "    Default service URL is assumed to be " << defaultURL << endl;
}

int main( int argc, char *argv[])
{
    char	endpoint[256];
    char *	url = "http://localhost:80/axis/element";
    char	dateTime[50];

    sprintf( endpoint, "%s", url);

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

    xsd__boolean		boolResult = (xsd__boolean) 1;
    xsd__byte			bResult = (xsd__byte) 0;
    xsd__unsignedByte	ubResult = (xsd__unsignedByte) 0;
    xsd__short			sResult = (xsd__short) 0;
    xsd__unsignedShort	usResult = (xsd__unsignedShort) 0;
    xsd__int			iResult = (xsd__int) 0;
    xsd__unsignedInt	uiResult = (xsd__unsignedInt) 0;
    xsd__long			lResult = (xsd__long) 0;
    xsd__unsignedLong	ulResult = (xsd__unsignedLong) 0;
    xsd__float			fResult = (xsd__float) 0;
    xsd__double			dResult = (xsd__double) 0;
    xsd__date			dateResult;	// typedef of struct tm
    xsd__dateTime		dateTimeResult;	// typedef of struct tm
//    xsd__time			timeResult;	// typedef of struct tm
    xsd__duration		durationResult = (xsd__duration) 0;
    xsd__string			strResult = (xsd__string) 0;
    xsd__integer		intResult = (xsd__integer) 0;
    xsd__decimal		decResult = (xsd__decimal) 0;
    xsd__base64Binary	b64Result;
    xsd__hexBinary		hexResult;
    xsd__base64Binary	b64Test;
    xsd__hexBinary		hexTest;
    xsd__unsignedByte *	testUB = (xsd__unsignedByte *) "<test><xml>some dod&y string</xml></test>";

	b64Test.set( testUB, (xsd__int) 41);
    hexTest.set( testUB, (xsd__int) 41);

    time_t	timeToTest;

    timeToTest = 1100246323;

    xsd__date *	temp = gmtime( &timeToTest);
    xsd__date	testDate;

    memcpy( &testDate, temp, sizeof( xsd__date));

    bool	bSuccess = false;
    int		iRetryIterationCount = 3;

    do
    {
		try
		{
			XSDElement *	ws = new XSDElement( endpoint);

			ws->setTransportProperty( "SOAPAction", "element#setGetDataBoolean");

			boolResult = ws->setGetDataBoolean( (xsd__boolean) 1);

			cout << "bool=" << boolResult << endl;

			ws->setTransportProperty( "SOAPAction", "element#setGetDataByte");
			
			bResult = ws->setGetDataByte( 31);

			cout << "byte=" << bResult << endl;

			ws->setTransportProperty( "SOAPAction", "element#setGetDataUnsignedByte");

			ubResult = ws->setGetDataUnsignedByte( 32);

			cout << "unsigned byte=" << ubResult << endl;

			ws->setTransportProperty( "SOAPAction", "element#setGetDataShort");

			sResult = ws->setGetDataShort( 7);

			cout << "short=" << sResult << endl;

			ws->setTransportProperty( "SOAPAction", "element#setGetDataUnsignedShort");

			usResult = ws->setGetDataUnsignedShort( 14);

			cout << "unsigned short=" << usResult << endl;

			ws->setTransportProperty( "SOAPAction", "element#setGetDataInt");

			iResult = ws->setGetDataInt( 21);

			cout << "int=" << iResult << endl;

			ws->setTransportProperty( "SOAPAction", "element#setGetDataUnsignedInt");

			uiResult = ws->setGetDataUnsignedInt( 28);

			cout << "unsigned int=" << uiResult << endl;

			ws->setTransportProperty( "SOAPAction", "element#setGetDataLong");

			lResult = ws->setGetDataLong( (xsd__long) 35);

			cout << "long=" << lResult << endl;

			ws->setTransportProperty( "SOAPAction", "element#setGetDataUnsignedLong");

			ulResult = ws->setGetDataUnsignedLong( (xsd__unsignedLong) 42);

			cout << "unsigned long=" << ulResult << endl;

			ws->setTransportProperty( "SOAPAction", "element#setGetDataFloat");

			fResult = ws->setGetDataFloat( (xsd__float) 35.3535888888);

			cout << "float=" << fResult << endl;

			ws->setTransportProperty( "SOAPAction", "element#setGetDataDouble");

			dResult = ws->setGetDataDouble( (xsd__double) 70.7175888888);

			printf( "double = %.5f\n", dResult);
			fflush (stdout);

			ws->setTransportProperty( "SOAPAction", "element#setGetDataDurationType");

			durationResult = ws->setGetDataDurationType( (xsd__duration) 123456789);

			cout << "duration=" << durationResult << endl;

			ws->setTransportProperty( "SOAPAction", "element#setGetDateType");

			dateResult = ws->setGetDateType (testDate);

			strftime( dateTime, 50, "%a %b %d %Y", &dateResult);

			cout << "date=" << dateTime << endl;

			ws->setTransportProperty( "SOAPAction", "element#setGetDateTimeType");

			dateTimeResult = ws->setGetDateTimeType( testDate);

			strftime( dateTime, 50, "%a %b %d %H:%M:%S %Y", &dateTimeResult);

			cout << "dateTime=" << dateTime << endl;

			ws->setTransportProperty( "SOAPAction", "element#setGetDataString");

			strResult = ws->setGetDataString( "never odd or even");

			cout << "string=" << strResult << endl;
			
			strResult = ws->setGetDataString( "m");

			cout << "small string=" << strResult << endl;

			ws->setTransportProperty( "SOAPAction", "element#setGetIntegerType");

			intResult = ws->setGetIntegerType( 919191919);

			cout << "integer=" << intResult << endl;

			ws->setTransportProperty ("SOAPAction", "element#setGetDecimalType");

			decResult = ws->setGetDecimalType( 929292929.5555555555555);

			printf( "decimal=%.5f\n", decResult);
			fflush( stdout);

			ws->setTransportProperty( "SOAPAction", "element#setGetBase64BinaryType");

			b64Result = ws->setGetBase64BinaryType( b64Test);

			cout << "base64Binary size=" << b64Result.getSize() << endl;

			if( b64Result.getSize() > 0)
			{
				xsd__int	iSize;

				cout << "base64Binary data=" << b64Result.get( iSize) << endl;
			}

			ws->setTransportProperty( "SOAPAction", "element#setGetHexBinary");

			hexResult = ws->setGetHexBinary( hexTest);

			xsd__int	iSize = hexResult.getSize();

			cout << "hexBinary size=" << iSize << endl;

			if( iSize > 0)
			{
				cout << "hexBinary data=" << hexResult.get( iSize) << endl;
			}

			bSuccess = true;

			delete ws;
		}
		catch( AxisException & e)
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
				cout << "Exception : " << e.what() << endl;
			}
		}
		catch( exception & e)
		{
			cout << "Unknown exception has occurred" << e.what() << endl;
		}
		catch( ...)
		{
			cout << "Unknown exception has occurred" << endl;
		}
	
		iRetryIterationCount--;
	} while( iRetryIterationCount > 0 && !bSuccess);

    cout << "---------------------- TEST COMPLETE -----------------------------" << endl;

    cout << "successful" << endl;

    return 0;
}
