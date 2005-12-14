#include "nillableComplexType.hpp"
#include <iostream>

int main(int argc, char* argv[])
{
	try
	{
		char *  pszEndpoint = "http://whaler.hursley.ibm.com:9090/CalculatorDoc/services/CalculatorDoc";

		if( argc > 0)
		{
			pszEndpoint = argv[1];
		}

		nillableComplexType * pwsnillableComplexType = new nillableComplexType( pszEndpoint);
	
		xsd__string			sValue = "Hello";
		xsd__base64Binary * pb64Value = new xsd__base64Binary();
		xsd__NMTOKEN		nmValue = 0;
		char *				psz64BitValue = "FRED";

        pb64Value->set((unsigned char *) psz64BitValue, strlen(psz64BitValue));

		xsd__string  sResult = pwsnillableComplexType->Report( sValue, pb64Value, nmValue);

		cout << "The result is " << sResult << endl;

		delete pwsnillableComplexType;
	}
	catch( SoapFaultException& sfe)
	{
		// Catch any other SOAP faults
		cout << "SoapFaultException: " << sfe.getFaultCode() << " " << sfe.what() << endl;
	}
	catch( AxisException& e)
	{
		// Catch an AXIS exception
	cout << "AxisException: " << e.getExceptionCode() << " " << e.what() << endl;
	}
	catch( exception& e)
	{
		// Catch a general exception
	cout << "Unknown Exception: " << e.what() << endl;
	}
	catch( ...)
	{
		// Catch any other exception
	cout << "Unspecified Exception: " << endl;
	}

    cout << "---------------------- TEST COMPLETE -----------------------------" << endl;

    // Exit.
    return 0;
}
