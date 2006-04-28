#include <iostream>
#include "ChoiceTestSoap.hpp"

using namespace std;

int main(int argc, char *argv[])
{

    try
    {
        const char* url="http://localhost:80/axis/CombinedChoice";
        ChoiceComplexType* Value0=new ChoiceComplexType();
        ChoiceComplexType* Value1;
        Value0->NonChoiceIntValue = 5;
        Value0->IntValue = new int;
        *(Value0->IntValue) = 5;
        Value0->StringValue = NULL;
        Value0->NonChoiceStringValue = "NonChoiceStringValue";

        if ( argc > 1 )
            url = argv[1];

        ChoiceTestSoap ws(url);

        cout<< "Calling the Service..."<<endl;

        Value1=ws.echoChoice(Value0);

        cout<<"Value1->NonChoiceIntValue = "<<Value1->NonChoiceIntValue<<endl;
        cout<<"Value1->IntValue = "<<*(Value1->IntValue)<<endl;
        cout<<"Value1->NonChoiceStringValue = "<<Value1->NonChoiceStringValue<<endl;


    }
    catch (AxisException & e)
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




