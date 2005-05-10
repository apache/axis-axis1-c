#include <iostream.h>
#include "ChoiceTestSoap.hpp"
#include "ChoiceComplexType.hpp"


using namespace std;

int main(int argc, char *argv[])
{
	
	try
	{
		const char* url="http://localhost:80/axis/UnboundedChoice";
		ChoiceComplexType* Value0;
		ChoiceComplexType* Value1;
		
		Value0=new	ChoiceComplexType();
		Value0->StringValue=NULL;
		
		cout<< "Calling the Service..."<<endl;
		
		Value0->IntValue->m_Array=new xsd__int*[5];
		xsd__int * intArray = new xsd__int[5];
		Value0->IntValue->m_Size = 5;
		for (int x=0; x<5; x++)
		{
            intArray[x] = x+1;
			Value0->IntValue->m_Array[x] = &intArray[x];
		}


		url = argv[1];
		ChoiceTestSoap ws(url);

		Value1=ws.echoChoice(Value0);
		
		for(int i=0;i<5;i++)
			cout<<"Value1->IntValue->m_Array["<<i<<"] = "<<*(Value1->IntValue->m_Array[i])<<endl;
	
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




