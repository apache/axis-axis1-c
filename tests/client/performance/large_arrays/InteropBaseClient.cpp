#define	AXIS

#ifndef	AXIS
#include "soapH.h"
#include "soapinterop2.nsmap"
#else
#include "InteropTestPortType.h"
#endif

#include <sys/time.h>
#include <iostream.h>
#include <fstream.h>
#include <stdlib.h>

#define	MAX_LINE_LEN		10
#define	NUM_TEST_RUNS		10
#define	STRING_DATA_FILE	"/home/damitha/projects/axiscppclient_prof/data/stringdata.txt"

#ifndef	AXIS
char **
#else
string *
#endif
gettestdata(char *filename, int size)
{
	FILE *s = fopen(filename, "rt");
	
	if (s) {
		int ii = 0;
		char buffer[MAX_LINE_LEN] = "";
		
#ifndef	AXIS
		char **testdata = new (char *)[size];
#else
		string *testdata = new string[size];
#endif		
		if (!testdata)
			return NULL;
		
		while (ii < size && fgets(buffer, MAX_LINE_LEN, s)) {
			int len = strlen(buffer);
			buffer[len-1] = 0;
	
#ifndef	AXIS			
			testdata[ii] = strdup(buffer);
			if (!testdata[ii]) {
				do
					free(testdata[ii--]);
				while (!(ii < 0));
				delete [] testdata;
				return NULL;
			}
	
#else
			testdata[ii] = buffer;
#endif
			ii++;
		}
		
		fclose(s);

		return testdata;	
	}
	
	perror("Error");

	return NULL;
}


int diff_time2(struct timeval *time2, struct timeval *time1)
{
	return 1000000 * (time2->tv_sec - time1->tv_sec)
		+ time2->tv_usec - time1->tv_usec;
}


int *dotest(int array_sz)
{
	ArrayOfstring arrstr;
#ifndef	AXIS
	arrstr.__size = array_sz;
	arrstr.__offset = 0;
#else
	arrstr.m_Size = array_sz;
#endif
	
        struct timeval time1, time2;
        struct timezone zone;
        zone.tz_minuteswest = 0;
        zone.tz_dsttime = 0;

#ifndef	AXIS
	struct soap soap;
	soap_init(&soap);
#else	
	InteropTestPortType ws;
#endif
	
	int *tst_res = (int *)malloc(sizeof(int) * NUM_TEST_RUNS);

#ifndef	AXIS
	if (!(arrstr.__ptr
#else	
	if (!(arrstr.m_Array 
#endif
		= gettestdata(STRING_DATA_FILE, array_sz)))
		return NULL;
	
	printf("\nStarting... (microseconds)");
			
	for (int ii = 0; ii < NUM_TEST_RUNS; ii++) {
		gettimeofday(&time1, &zone);
	
#ifndef	AXIS
		tns__echoStringArrayResponse out;
		if (soap_call_tns__echoStringArray(&soap, "http://127.0.0.1:1190/soap",
			"http://soapinterop.org/", &arrstr, &out) != SOAP_OK) {
#else	
		if (!(ws.echoStringArray(arrstr).m_Array)) {
#endif
                        printf("Error: Service failed.\n");
                        return NULL;
                }
		
		gettimeofday(&time2, &zone);
	
		tst_res[ii] = diff_time2(&time2, &time1);

		printf("\n\t%5d) %10d", ii, tst_res[ii]);
	}

	printf("\nDone.");
	
	return tst_res;
}


int save_res(char *save_as, int *tst_res, char *desc)
{
	FILE *s = fopen(save_as, "wt");
	if (s) {
		fprintf(s, "%s\n", desc);
		for (int ii = 0; ii < NUM_TEST_RUNS; ii++)
			fprintf(s, "%d\n", tst_res[ii]);

		fclose(s);

		return 0;
	}
	else
		perror("Error");

	return -1;
}



int main2(int argc, char **argv)
{
	if (2 == argc) {
		//	FIXME:
		int *tst_res = dotest(strtol(argv[1], NULL, 10));
		if (tst_res)
			save_res("test-1.dat", tst_res, "#\ttest data set1");

		return 0;
	}
	else {
		printf("Incorrect number of arguments in call to...");
		
		return -1;
	}
}
