#include <iostream.h>
#include "ChoiceTestSoap.hpp"
#include <ctype.h>


using namespace std;

void main()
{
	
	try
	{
	
		ChoiceComplexType* Value0=new ChoiceComplexType();
		ChoiceComplexType* Value1;
		Value0->name0="Choice Test";
		Value0->name1=NULL;
        
		//char* url = argv[1];
		ChoiceTestSoap ws("http://localhost:90/axis/Choice");

		cout<< "Calling the Service..."<<endl;
		
		Value1=ws.echoChoice(Value0);

		cout<<"Value1->name0 = "<<Value1->name0<<endl;

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

}




