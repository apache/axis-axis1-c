/*
 * This is written to test the functionality of setSOAPMethodAttribute() API 
 * in Stub class.
 */

#include "MathOps.hpp"
#include <iostream>

int main(int argc, char *argv[])
{
	char endpoint[256];
    const char* url="http://localhost:80/axis/MathOps";
    int iResult=0;

    url = argv[1];
    sprintf(endpoint, "%s", url);
    

		MathOps ws(endpoint);
		//setSOAPMethodAttribute call does not belong to Stub class any more
		//ws.setSOAPMethodAttribute("div","ns5","10");
		//ws.setSOAPMethodAttribute("add", "", "http://soapinteroptest.org", "value");
		

    cout << "invoking MathOps div..." << endl;
    
        try
        {
                
			iResult = ws.div(15,5);
			cout << "Result is = " << iResult << endl;
                

        }
        catch (AxisException& e)
        {
            cout << e.what() << endl;
        }
        catch(...)
        {
                cout << "Unknown exception" << endl;
        }

    cout<< "---------------------- TEST COMPLETE -----------------------------"<< endl;

    return 0;
}
                                                          
