#include <iostream>
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
		xsd__int_Array * arrayIn = new xsd__int_Array();
		xsd__int ** array = new xsd__int*[5];		
		for (int x=0; x<5; x++)
		{
            array[x] = new xsd__int(x+1);			
		}
		arrayIn->set(array,5);
		Value0->setIntValue(arrayIn);
		url = argv[1];
		ChoiceTestSoap ws(url);

		Value1=ws.echoChoice(Value0);
		int outputSize=0;
		
		for(int i=0;i<5;i++)
			cout << "Value1->IntValue->m_Array[" << i << "] = " << *(Value1->IntValue->get(outputSize)[i]) << endl;
		  // Clear up input array        
        for (int deleteIndex = 0 ; deleteIndex < 5 ; deleteIndex++ )
        {
            delete [] array[deleteIndex];
        }

		delete arrayIn;
	
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




