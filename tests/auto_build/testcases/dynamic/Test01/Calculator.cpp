/*
* This is a manually edited version of the Generated stub code for CaluclatorDoc.wsdl
* to simplify the code to allow the cpp file to be edited to be used as a dynamic client
* perryan@uk.ibm.com
*/

#include "Calculator.hpp"
#include <axis/AxisWrapperAPI.hpp>

Calculator::Calculator (const char *pcEndpointUri,
                        AXIS_PROTOCOL_TYPE eProtocol)
{
  m_pCall = new Call ();
  m_pCall->setProtocol (eProtocol);
  m_pCall->setEndpointURI (pcEndpointUri);
}

Calculator::Calculator ()
{
  m_pCall = new Call ();
  m_pCall->setEndpointURI ("http://localhost/axis/Calculator");
}

Calculator::~Calculator ()
{
}

/*
* A new test method which is called from elsewhere in the code. New test 
* methods can be used to keep things clean. perryan@uk.ibm.com 
*/
void
Calculator::printProtocolType ()
{
  printf ("protocol type = %d\n", m_pCall->getProtocol ());
}

/*
* This method wrap the service methoddiv
*/
xsd__int Calculator::div (xsd__int Value0, xsd__int Value1)
{
  xsd__int
    Ret = 0;
  const char *
    pcCmplxFaultName;

#define DEFAULT_WSDL_ENDPOINT "http://localhost/axis/Calculator"

  try
  {
    if (AXIS_SUCCESS != m_pCall->initialize (CPP_DOC_PROVIDER))
      return Ret;

    m_pCall->setTransportProperty (SOAPACTION_HEADER, "Calculator#div");
    m_pCall->setSOAPVersion (SOAP_VER_1_1);
    m_pCall->setOperation ("div", DEFAULT_WSDL_ENDPOINT);

    printProtocolType ();

    includeSecure ();
    char
      cPrefixAndParamName0[17];
    sprintf (cPrefixAndParamName0, "%s:arg_0_3",
             m_pCall->getNamespacePrefix (DEFAULT_WSDL_ENDPOINT));
    m_pCall->addParameter ((void *) &Value0, cPrefixAndParamName0, XSD_INT);
    char
      cPrefixAndParamName1[17];
    sprintf (cPrefixAndParamName1, "%s:arg_1_3",
             m_pCall->getNamespacePrefix (DEFAULT_WSDL_ENDPOINT));
    m_pCall->addParameter ((void *) &Value1, cPrefixAndParamName1, XSD_INT);

    if (AXIS_SUCCESS == m_pCall->invoke ())
      {
        if (AXIS_SUCCESS ==
            m_pCall->checkMessage ("divResponse", DEFAULT_WSDL_ENDPOINT))
          {
            Ret = m_pCall->getElementAsInt ("divReturn", 0);
          }

      }
    m_pCall->unInitialize ();
    return Ret;
  }
  catch (AxisException & e)
  {
    throw;
  }
}

/*
* Methods for supporting SecureChannel
*/

void
Calculator::SetSecure (char *pszArguments, ...)
{
  char **ppszArgPtr = &pszArguments;
  int iArgIndex = 0;

  while (*ppszArgPtr != NULL)
    {
      sArguments[iArgIndex] = *ppszArgPtr;

      iArgIndex++;
      ppszArgPtr++;
    }
}

void
Calculator::includeSecure ()
{
  m_pCall->setTransportProperty (SECURE_PROPERTIES,
                                 (const char *) &sArguments);
}


// Main added to allow the modified generated stub to be used as a dynamic 
// 
// client
// perryan@uk.ibm.com
int
main (int argc, char *argv[])
{
  char endpoint[256];
  const char *url = "http://localhost:9080/Calculator/services/Calculator";
  const char *op = 0;
  int i1 = 100, i2 = 20;
  int iResult;
  url = argv[1];
  try
  {
    sprintf (endpoint, "%s", url);
    Calculator ws (endpoint);
    iResult = ws.div (i1, i2);

// Call new test method
// doesn't neccessarily need to be called from main()
// perryan@uk.ibm.com
    ws.printProtocolType ();

    printf ("%d\n", iResult);
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
    printf ("Unspecified exception has occured\n");
  }
  return 0;
}
