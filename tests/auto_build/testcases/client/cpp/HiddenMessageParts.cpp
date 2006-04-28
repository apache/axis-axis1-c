#include "PruebaDatosCabecera.hpp"
#include "PruebasBugPortType.hpp"
#include "CommonClientTestCode.hpp"
#include <iostream>
#include <axis/AxisException.hpp>
#include <ctype.h>

#define WSDL_DEFAULT_ENDPOINT "http://localhost:80/axis/BasicAll"

void PrintUsage();

int
main (int argc, char *argv[])
{
    char *endpoint = WSDL_DEFAULT_ENDPOINT;
    bool endpoint_set = parse_args(&argc, argv, &endpoint); 
    
    int returnValue = 1;        // Assume Failure

        bool bSuccess = false;
    PruebasBugPortType* ws;
                try
                {
            if(endpoint_set) 
            {
              ws = new PruebasBugPortType(endpoint, APTHTTP1_1);
              free(endpoint);
              endpoint_set = false;
            } 
            else
            {
              ws = new PruebasBugPortType();
            }
          
            PruebaDatosCabecera* data = new PruebaDatosCabecera();
            data->setIdenOrgNac("23");
            data->setNumSec("12");
            
            cout <<"Sending................." << endl;
            xsd__int returnVal = ws->AbySend(data);
            cout << "result = "<<returnVal<<endl;
                        
                        bSuccess = true;
                        delete data;
                }
                catch (AxisException & e)
                {
                        bool bSilent = false;

                        cout << "AxisException : " << e.what() << endl;
                }
                catch (exception & e)
                {
                        cout << "Unexpected exception : " << e.what() << endl;
                }       
                catch (...)
                {
                        cout << "Unknown Exception occured." << endl;
                }


    cout <<
        "---------------------- TEST COMPLETE -----------------------------"
        << endl;

    return returnValue;
}
