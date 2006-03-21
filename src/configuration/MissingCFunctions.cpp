#include "MissingCFunctions.hpp"

bool StringCompare( char * pszString1, char * pszString2)
{
	bool	bSame = false;

	if( pszString1 == NULL || pszString2 == NULL)
	{
		return bSame;
	}

	if( strlen( pszString1) != strlen( pszString2))
	{
		return bSame;
	}

	if( strlen( pszString1) == 0)
	{
		bSame = true;
	}
	else
	{
		char *	psString1 = pszString1;
		char *	psString2 = pszString2;

		do
		{
			bSame = (toupper( *psString1++) == toupper( *psString2++));
		} while( bSame && *psString1 != '\0');
	}

	return bSame;
}

void StringToUpper( char * pszString)
{
	if( pszString != NULL)
	{
		char *	pc = pszString;

		while( *pc != '\0')
		{
			*pc = toupper( *pc);

			pc++;
		}
	}
}

char * TimeNow()
{
#if WIN32
#if defined(_MSC_VER) && _MSC_VER >= 1300	// Start MSVC verison number > 7.0
	__time64_t	ltime;

	_time64( &ltime);

	return _ctime64( &ltime);
#else										// Else !(MSVC verison number > 7.0)
	time_t sTimeNow;

    sTimeNow = time( NULL);

	return asctime( localtime( &sTimeNow));
#endif										// End MSVC verison number
#else
	time_t	sTimeNow;

	sTimeNow = time( NULL);

	return asctime( localtime( &sTimeNow));
#endif
}
