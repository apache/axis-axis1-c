#if !defined(__AXIS_CONFIG_LIST__)

#define __AXIS_CONFIG_LIST__

typedef struct
{
	int				iCount;
	int				iMaxCount;
	void **			ppArray;
} LIST;

void * GetNextListElement( LIST * psList, int iElementLength);

#endif
