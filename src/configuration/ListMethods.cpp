#include "ListMethods.hpp"
#include "AxisConfiguration.hpp"

void * GetNextListElement( LIST * psList, int iElementLength)
{
	if( psList->ppArray == NULL)
	{
		psList->iMaxCount = 1;

		psList->ppArray = (void **) malloc( sizeof( void *));
	}

	if( psList->iCount >= psList->iMaxCount)
	{
		psList->iMaxCount = psList->iMaxCount * 2;

		psList->ppArray = (void **) realloc( psList->ppArray, sizeof( void *) * psList->iMaxCount);

		for( int iNewIndex = psList->iCount; iNewIndex < psList->iMaxCount; iNewIndex++)
		{
			psList->ppArray[iNewIndex] = NULL;
		}
	}

	psList->ppArray[psList->iCount] = malloc( iElementLength);

	memset( psList->ppArray[psList->iCount], 0, iElementLength);

	psList->iCount++;

	return psList->ppArray[psList->iCount - 1];
}
