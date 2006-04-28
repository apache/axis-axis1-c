#include <iostream>
#include "ChoiceTestSoap.hpp"
#include "ChoiceComplexType.hpp"


using namespace std;

int main(int argc, char *argv[])
{
        
        try
        {
                const char* url="http://localhost:80/axis/UnboundedStringChoice";
                ChoiceComplexType* Value0;
                ChoiceComplexType* Value1;
                Value0 = new    ChoiceComplexType();
                
                cout<< "Calling the Service..."<<endl;

                xsd__string_Array * arrayIn =new xsd__string_Array();
                xsd__string *array = new xsd__string[5];                
        array[0] = "a"; 
                array[1] = "b";
                array[2] = "c";
                array[3] = "d";
                array[4] = "e";         
                arrayIn->set(array,5);
                Value0->setStringValue(arrayIn);
        
                if ( argc > 1 )
            url = argv[1];
                
                ChoiceTestSoap ws(url);

                Value1 = ws.echoChoice(Value0);
                int outputSize =0;
                
                for (int i=0;i<5;i++)
                        cout << "Value1->StringValue->m_Array[" << i << "] = " << *(Value1->StringValue->get(outputSize)[i]) << endl;

                  // Clear up input array        
        for (int deleteIndex = 0 ; deleteIndex < 5 ; deleteIndex++ )
        {
            delete [] array[deleteIndex];
        }
        delete [] array;
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




