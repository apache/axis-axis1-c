#include <iostream.h>
#include <fstream.h>
#include <sys/time.h>
#include "gen_src/InteropTestPortType.h"

/////////////////////////////////////////////////////////////////////////////
//

struct timeval time1, time2;
struct timezone zone;

void tm_init()
{
	zone.tz_minuteswest = 0;
        zone.tz_dsttime = 0;
}
	
#define	tm_start()	gettimeofday(&time1, &zone);

int diff_time(struct timeval *time2, struct timeval *time1)
{
	return 1000000 * (time2->tv_sec - time1->tv_sec)
		+ time2->tv_usec - time1->tv_usec;
}

int inline tm_stop()
{
	gettimeofday(&time2, &zone);
	return diff_time(&time2, &time1);
}


/////////////////////////////////////////////////////////////////////////////
//

//#define	NUM_TEST_RUNS		5

#define	TEST_STRING_DATA
//#define	TEST_INT_DATA
//#define	TEST_FLOAT_DATA
//#define	TEST_STRUCT_DATA
/////////////////////////////////////////////////////////////////////////////
//

#define	MAX_LINE_LEN		256

//int test_rslt[NUM_TEST_RUNS];
int* test_rslt;
int next_elem;

#ifdef	TEST_STRING_DATA
#define	DATA_TYPE	char*
#define	DATA_FILE	"stringdata.txt"
xsd__string_Array testdata;
#else

#ifdef	TEST_INT_DATA
#define	DATA_TYPE	int
#define	DATA_FILE	"intdata.txt"
xsd__int_Array testdata;
#else

#ifdef	TEST_FLOAT_DATA
#define	DATA_TYPE	float
#define	DATA_FILE	"floatdata.txt"
xsd__float_Array testdata;
#else

#ifdef TEST_STRUCT_DATA
#define DATA_TYPE 	ns_SOAPStruct
#define DATA_FILE 	"structdata.txt"
SOAPStruct_Array testdata;
#endif
#endif	
#endif
#endif

////////////////////////////////////////////////////////////////////////////////
//
InteropTestPortType tester;

char *pchBuff;

void inittestdata(int array_sz)
{
	testdata.m_Size = array_sz;
#ifdef	TEST_STRING_DATA
        if( !(testdata.m_Array = new char *[array_sz]))
#else	
	if (!(testdata.m_Array = (DATA_TYPE *)malloc(sizeof(DATA_TYPE) * array_sz)))
#endif
		exit(-1);
	next_elem = 0;	
}
	

int storetestdata(char* pchBuff)
{
#ifdef	TEST_STRING_DATA
	//testdata.m_Array[next_elem] = pchBuff;
        testdata.m_Array[next_elem] = new char [strlen(pchBuff) + 2];
	strcpy(testdata.m_Array[next_elem], pchBuff);
	//printf("pchBuff:%s\n", pchBuff);
	//printf("testdata.m_Array:%s", testdata.m_Array[next_elem]);		
	//printf("next_elem:%d\n", next_elem);
	if (testdata.m_Array == NULL)
		exit(-1);
#else
#ifdef	TEST_INT_DATA
	testdata.m_Array[next_elem] = strtol(s, NULL, 10);
#else
#ifdef	TEST_FLOAT_DATA
	testdata.m_Array[next_elem] = strtof(s, NULL);
#else
#ifdef	TEST_STRUCT_DATA
	//	TODO
	printf("\nERROR: TODO!\n");
	exit(-1);	
#endif
#endif
#endif
#endif
	return ++next_elem < testdata.m_Size;
}


void gettestdata(int intMaxLineLen)
{
	FILE *filePtr = fopen(DATA_FILE, "rt");
	if (filePtr) {
                pchBuff = new char [intMaxLineLen];
		while (fgets(pchBuff, intMaxLineLen, filePtr))
                {
	            //printf("pchBuff:%s\n", pchBuff);
		    if (!storetestdata(pchBuff))
		        return;
                }
		fclose(filePtr);
	
		exit(-1);
	}
	
	perror("Error");
	exit(-1);
}


void test(int intNumRuns)
{
        test_rslt = new int[intNumRuns];	
	printf("\nStarting... (microseconds)\n");
	for (int ii = 0; ii < intNumRuns; ii++) {
		tm_start();
		
		if (tester.
#ifdef	TEST_STRING_DATA		
		echoStringArray
#else
#ifdef	TEST_INT_DATA
		echoIntegerArray
#else
#ifdef	TEST_FLOAT_DATA
		echoFloatArray
#else
#ifdef TEST_STRUCT_DATA
		echoStructArray
#endif
#endif
#endif
#endif
		(testdata).m_Array == NULL) {
                        printf("\nError: No data returned!\n");
			exit(-1);
                }
                
		test_rslt[ii] = tm_stop();		

		printf("\n%d\n", test_rslt[ii]);
	}

	printf("\nDone.\n");
}


void save_results(char *save_as, char *desc, int intNumRuns)
{
	FILE *s = fopen(save_as, "wt");
	if (s) {
		fprintf(s, "%s\n", desc);
		for (int ii = 0; ii < intNumRuns; ii++)
			fprintf(s, "%d\n", test_rslt[ii]);

		fclose(s);

		printf("\nResult saved as %s\n", save_as);
	}
	else {
		perror("Error");
		exit(-1);
	}
}



int main(int argc, char **argv)
{
	
	if (6 == argc) {
		int intNumElements = strtol(argv[1], NULL, 0);
                int intMaxLineLen = strtol(argv[2], NULL, 0);
                int intNumRuns = strtol(argv[3], NULL, 0);
		printf("\nArray size: %d\n", intNumElements);
		printf("\nMaximum line length: %d\n", intMaxLineLen);
		printf("\nNumber of runs: %d\n", intNumRuns);

		inittestdata(intNumElements);
		
		gettestdata(intMaxLineLen);

		test(intNumRuns);
		
		//	FIXME:
		save_results(argv[4], argv[5], intNumRuns);

		return 0;

	}
	
	printf("\nenter:largeArrays <array size> <maximum line length> <number of runs> <datafile> <comment>\n");
	return -1;
}
