#include <iostream.h>
#include "ChoiceTestSoap.hpp"
#include "ChoiceComplexType.hpp"


using namespace std;

void main(int argc, char *argv[])
{
	
	try
	{
		const char* url="http://localhost:80/axis/UnboundedStringChoice";
		ChoiceComplexType* Value0;
		ChoiceComplexType* Value1;
		Value0 = new	ChoiceComplexType();
		
		cout<< "Calling the Service..."<<endl;
		
		Value0->StringValue->m_Array = new xsd__string[5];
		xsd__string * StringArray = new xsd__string[5];
		Value0->StringValue->m_Size = 5;
		
        StringArray[0] = "a";
		Value0->StringValue->m_Array[0] = StringArray[0];
 
		StringArray[1] = "b";
		Value0->StringValue->m_Array[1] = StringArray[1];
		
		StringArray[2] = "c";
		Value0->StringValue->m_Array[2] = StringArray[2];

		StringArray[3] = "d";
		Value0->StringValue->m_Array[3] = StringArray[3];

		StringArray[4] = "e";
		Value0->StringValue->m_Array[4] = StringArray[4];
	
		if ( argc > 1 )
            url = argv[1];
		
		ChoiceTestSoap ws(url);

		Value1 = ws.echoChoice(Value0);
		
		for (int i=0;i<5;i++)
			cout<<"Value1->StringValue->m_Array["<<i<<"] = "<<*(Value1->StringValue->m_Array[i])<<endl;
	//	cout<<"Value1->IntValue = "<<(Value1->StringValue)<<endl;

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




