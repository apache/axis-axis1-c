#ifndef __COMMONHEADERFILE
#define __COMMONHEADERFILE

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// Prototype
bool parse_args(int *argc, char *argv[], char **endpoint);
void shift_args_up(int i, int *argc, char *argv[]);

#ifdef WIN32
	#if defined(_MSC_VER) && (_MSC_VER < 1300)
	// Bug in MS Visual C++ 6.0. Fixed in Visual C++ .Net version.
	// Cannot print an __int64 number with cout without this overloading
		std::ostream& operator << (std::ostream& os, __int64 i)
		{
			char buf[32];

			sprintf( buf, "%I64d", i);

			os << buf;

			return os;
		}

		std::ostream& operator << (std::ostream& os, unsigned __int64 i)
		{
			char buf[32];

			sprintf(buf,"%I64u", i );

			os << buf;

			return os;
		}
	#endif

      #define LONGLONGVALUE(value) value##I64
      #define UNSIGNED_LONGLONGVALUE(value) value##UI64
#else
      #define LONGLONGVALUE(value) value##LL
      #define UNSIGNED_LONGLONGVALUE(value) value##ULL
#endif

// ==========================================================
// Following code is to take care of ebcdic/ascii issues.
// Some test cases relating to hex and binary and attachement
// send text strings. In order for these test cases to 
// pass we need to ensure that the data is in ascii. 
// In addition, if we are going to print out the data to cout,
// then we need to convert to ebcdic. For ascii-based systems,
// the macros used to do the conversions are identity macros. 
// ==========================================================
#ifdef __OS400__

/* conversion table generated by ebcdic 37 -> ascii 819 */
const char EBCDICtoASCII[256] = {
/* 0    1    2    3    4    5    6    7    8    9    A    B    C    D    E    F */
   0,   1,   2,   3, 156,   9, 134, 127, 151, 141, 142,  11,  12,  13,  14,  15,    
  16,  17,  18,  19, 157, 133,   8, 135,  24,  25, 146, 143,  28,  29,  30,  31,    
 128, 129, 130, 131, 132,  10,  23,  27, 136, 137, 138, 139, 140,   5,   6,   7,    
 144, 145,  22, 147, 148, 149, 150,   4, 152, 153, 154, 155,  20,  21, 158,  26,    
  32, 160, 226, 228, 224, 225, 227, 229, 231, 241, 162,  46,  60,  40,  43, 124,    
  38, 233, 234, 235, 232, 237, 238, 239, 236, 223,  33,  36,  42,  41,  59, 172,    
  45,  47, 194, 196, 192, 193, 195, 197, 199, 209, 166,  44,  37,  95,  62,  63,    
  248, 201, 202, 203, 200, 205, 206, 207, 204,  96,  58,  35,  64,  39,  61,  34,   
  216,  97,  98,  99, 100, 101, 102, 103, 104, 105, 171, 187, 240, 253, 254, 177,   
  176, 106, 107, 108, 109, 110, 111, 112, 113, 114, 170, 186, 230, 184, 198, 164,   
  181, 126, 115, 116, 117, 118, 119, 120, 121, 122, 161, 191, 208, 221, 222, 174,   
   94, 163, 165, 183, 169, 167, 182, 188, 189, 190,  91,  93, 175, 168, 180, 215,   
  123,  65,  66,  67,  68,  69,  70,  71,  72,  73, 173, 244, 246, 242, 243, 245,   
  125,  74,  75,  76,  77,  78,  79,  80,  81,  82, 185, 251, 252, 249, 250, 255,   
   92, 247,  83,  84,  85,  86,  87,  88,  89,  90, 178, 212, 214, 210, 211, 213,   
   48,  49,  50,  51,  52,  53,  54,  55,  56,  57, 179, 219, 220, 217, 218, 159
};
 
/* conversion table generated by ascii 819 -> ebcdic 37 */
const char ASCIItoEBCDIC[256] = {
/* 0    1    2    3    4    5    6    7    8    9    A    B    C    D    E    F */
   0,   1,   2,   3,  55,  45,  46,  47,  22,   5,  37,  11,  12,  13,  14,  15,      
  16,  17,  18,  19,  60,  61,  50,  38,  24,  25,  63,  39,  28,  29,  30,  31,
  64,  90, 127, 123,  91, 108,  80, 125,  77,  93,  92,  78, 107,  96,  75,  97,
 240, 241, 242, 243, 244, 245, 246, 247, 248, 249, 122,  94,  76, 126, 110, 111,
 124, 193, 194, 195, 196, 197, 198, 199, 200, 201, 209, 210, 211, 212, 213, 214,
 215, 216, 217, 226, 227, 228, 229, 230, 231, 232, 233, 186, 224, 187, 176, 109,      
 121, 129, 130, 131, 132, 133, 134, 135, 136, 137, 145, 146, 147, 148, 149, 150,
 151, 152, 153, 162, 163, 164, 165, 166, 167, 168, 169, 192,  79, 208, 161,   7,
  32,  33,  34,  35,  36,  21,   6,  23,  40,  41,  42,  43,  44,   9,  10,  27,      
  48,  49,  26,  51,  52,  53,  54,   8,  56,  57,  58,  59,   4,  20,  62, 255,      
  65, 170,  74, 177, 159, 178, 106, 181, 189, 180, 154, 138,  95, 202, 175, 188,      
 144, 143, 234, 250, 190, 160, 182, 179, 157, 218, 155, 139, 183, 184, 185, 171,      
 100, 101,  98, 102,  99, 103, 158, 104, 116, 113, 114, 115, 120, 117, 118, 119,      
 172, 105, 237, 238, 235, 239, 236, 191, 128, 253, 254, 251, 252, 173, 174,  89,      
  68,  69,  66,  70,  67,  71, 156,  72,  84,  81,  82,  83,  88,  85,  86,  87,      
 140,  73, 205, 206, 203, 207, 204, 225, 112, 221, 222, 219, 220, 141, 142, 223   
};

static char* stringToAscii( char *string )
{
   char* pch = string;
   if( string == NULL ) return NULL;
 
   /* while not EOL... */
   while( *pch != (char)0 )
   {
         *pch = EBCDICtoASCII[*pch];
         pch++;
   }
   return string;
}

static char* asciiToString( char *string )
{
   char* pch = string;
   if( string == NULL ) return NULL;
 
   /* while not EOL... */
   while( *pch != (char)0 )
   {
         *pch = ASCIItoEBCDIC[*pch];
         pch++;
   }
   return string;
}

static char * asciiToStringOfLength( char * pString, int iLength)
{
   char *	pch = pString;

   if( pString == NULL)
   {
	   return NULL;
   }
 
   /* while not EOL... */
   int iCount = 0;

   while( *pch != '\0' && iCount < iLength)
   {
         *pch = ASCIItoEBCDIC[*pch];
         pch++;
		 iCount++;
   }

   *pch = '\0';

   return pString;
}

#else

#define asciiToString( x ) ( x )
#define stringToAscii( x ) ( x )

char * asciiToStringOfLength( char * pString, int iLength)
{
   if( pString == NULL)
   {
	   return NULL;
   }
 
   pString[iLength] = '\0';

   return pString;
}

#endif
/* Spin through args list and check for -e -p and -s options.
   Option values are expected to follow the option letter as the next
   argument.
 
   These options and values are removed from the arg list.
   If both -e and -s and or -p, then -e takes priority
*/
bool parse_args(int *argc, char *argv[], char **endpoint) {

    // We need at least 2 extra arg after program name
    if(*argc < 3)
        return false;

    char *server = "localhost";
    int  port = 80;
    bool ep_set = false;
    bool server_set = false;
    bool port_set = false;

    for(int i=1; i<*argc; i++) {
        if(*argv[i] == '-') {
            switch(*(argv[i]+1)) {
            case 'e':
                *endpoint = strdup(argv[i+1]);
                ep_set = true;
                shift_args_up(i, argc, argv);
                i--;
                break;
            case 's':
                server = strdup(argv[i+1]);
                server_set = true;
                shift_args_up(i, argc, argv);
                i--;
                break;
            case 'p':
                port = atoi(argv[i+1]);
                if(port >80) port_set = true;
                shift_args_up(i, argc, argv);
                i--;
                break;
            default:
                break;
            }
        }
    }

    // use the supplied server and/or port to build the endpoint
    if(ep_set == false && (server_set || port_set)) {
        // Set p to the location of the first '/' after the http:// (7 chars)
        // e.g. from http://localhost:80/axis/base gets /axis/base
        char *ep_context = strpbrk(&(*endpoint)[7], "/");

        // http://:/ is 9 characters + terminating NULL character so add 10.
        // Allow space for port number upto 999999 6 chars
        *endpoint = (char *)calloc(1, 10 + strlen(ep_context) + strlen(server) + 6);
        sprintf(*endpoint, "http://%s:%d/%s", server, port, ep_context+1);
        if(server_set) free(server);
        ep_set = true;
    }

    return ep_set;
}
void shift_args_up(int i, int *argc, char *argv[]) {
    for(int j=i, k=i+2; j<*(argc)-2; j++, k++)
        argv[j]=argv[k];
    *argc-=2;
}

// Following functions adjust the tm structure by taking in consideration
// daylight saving time...so that when we spit out the results it will
// match what is expected (which is not with daylight saving time)

bool isDSTInEffect()
{
    time_t currentTime;
    struct tm *ts;

    (void)time(&currentTime);
    ts = localtime(&currentTime);

    if (ts->tm_isdst > 0)
        return true;

    return false;
}

struct tm * adjustTimeStruct(struct tm *t)
{


    if (0)
    {
      printf("tm_hour:  %d\n",t->tm_hour);
      printf("tm_min:  %d\n",t->tm_min);
      printf("tm_sec:  %d\n",t->tm_sec);
      printf("tm_mon:  %d\n",t->tm_mon);
      printf("tm_mday:  %d\n",t->tm_mday);
      printf("tm_year:  %d\n",t->tm_year);
      printf("tm_yday:  %d\n",t->tm_yday);
      printf("tm_wday:  %d\n",t->tm_wday);
      printf("tm_isdst:  %d\n",t->tm_isdst);
    }

    if (isDSTInEffect())
    {
        --(t->tm_hour);

       if (t->tm_hour < 0)
            mktime (t);
    }

    if (0)
    {
     printf("===After\n");

     printf("tm_hour:  %d\n",t->tm_hour);
     printf("tm_min:  %d\n",t->tm_min);
     printf("tm_sec:  %d\n",t->tm_sec);
     printf("tm_mon:  %d\n",t->tm_mon);
     printf("tm_mday:  %d\n",t->tm_mday);
     printf("tm_year:  %d\n",t->tm_year);
     printf("tm_yday:  %d\n",t->tm_yday);
     printf("tm_wday:  %d\n",t->tm_wday);
     printf("tm_isdst:  %d\n",t->tm_isdst);
    }

    return t;
}



#endif
