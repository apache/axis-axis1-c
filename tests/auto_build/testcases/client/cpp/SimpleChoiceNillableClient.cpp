#include <iostream>
#include "ChoiceTestSoap.hpp"

using namespace std;

int main(int argc, char *argv[])
{
	
	try
	{
		const char* url="http://localhost:80/axis/SimpleChoice";
		ChoiceComplexType* Value0=new ChoiceComplexType();
		ChoiceComplexType* Value1;
		int* a = NULL;
		Value0->IntValue = &a;
		Value0->StringValue=NULL;
        
		if(argc>1)
			url = argv[1];
		
		cout<< "Calling the Service..."<<endl;
		ChoiceTestSoap ws(url);

		Value1=ws.echoChoice(Value0);
		
		if ( !(*(Value1->IntValue)))
			cout<<"The Value is NULL"<<endl;
		
	}catch (AxisException & e)
    {
	printf ("Exception : %s\n", e.what ());
    }
    catch (exception & e)
    {
	printf ("Unknown exception has occured\n");
    }
    catch (...)
    {
	printf ("Unknown exception has occured\n");
    }

	return 0;

}




