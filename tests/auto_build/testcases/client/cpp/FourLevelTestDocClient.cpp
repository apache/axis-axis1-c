// FourLevelTestDocClient.cpp : Defines the entry point for the console application.i
//
#include <string>
using namespace std;

#include "FourLevelTestDocInterface.hpp"
#include <axis/AxisException.hpp>

int main(int argc, char* argv[])
{
	int x;
	char buffer1[100];
	char endpoint[256];
	const char* url="http://localhost:80/axis/fourLevelTestDoc";
	const char* server="localhost";
	const char* port="80";
	url = argv[1];
		bool bSuccess = false;
		int	iRetryIterationCount = 3;

		do
		{
	try
	{
		sprintf(endpoint, "%s", url);
		FourLevelTestDocInterface ws(endpoint);

		FourthLevelElemType* fourth = new FourthLevelElemType();
		fourth->SampleString = strdup("abc");
		fourth->SampleInt = 1;

		FourthLevelElemType_Array* fourth_array = new FourthLevelElemType_Array();
		fourth_array->m_Array = fourth;
		fourth_array->m_Size = 1;

		ThirdLevelElemType* third = new ThirdLevelElemType();
		third->FourthLevelElem = *fourth_array;

		ThirdLevelElemType_Array* third_array = new ThirdLevelElemType_Array();
		third_array->m_Array = third;
		third_array->m_Size = 1;

		SecondLevelElemType* second = new SecondLevelElemType();
		second->ThirdLevelElem = *third_array;

		SecondLevelElemType_Array* second_array = new SecondLevelElemType_Array();
		second_array->m_Array = second;
		second_array->m_Size = 1;


//		SecondLevelElemType_Array in_array = new SecondLevelElemType_Array();
//		in_array.m_Array = second_arr;
//		in_array.m_Size = 1;
		
		SecondLevelElemType_Array out_array;

		out_array = ws.RetrieveTestDoc(*second_array);

		printf("Size = %d\n", out_array.m_Size);
		printf("String = %s\n", out_array.m_Array->ThirdLevelElem.m_Array->FourthLevelElem.m_Array->SampleString);

		bSuccess = true;
	}
	catch(AxisException& e)
	{
			bool bSilent = false;

			if( e.getExceptionCode() == CLIENT_TRANSPORT_OPEN_CONNECTION_FAILED)
			{
				if( iRetryIterationCount > 0)
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
	catch(exception& e)
	{
	    printf("Unknown exception has occured\n");
	}
	catch(...)
	{
	    printf("Unknown exception has occured\n");
	}
		iRetryIterationCount--;
		} while( iRetryIterationCount > 0 && !bSuccess);
	return 0;
}
