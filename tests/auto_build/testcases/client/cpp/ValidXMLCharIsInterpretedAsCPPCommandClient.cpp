// Copyright 2003-2004 The Apache Software Foundation.
// (c) Copyright IBM Corp. 2004, 2005 All Rights Reserved
// 
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// 
//        http://www.apache.org/licenses/LICENSE-2.0
// 
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <iostream>
#include "ValidXMLCharIsInterpretedAsCPPCommand.hpp"

int main( int argc, char * argv[])
{
        bool    bSuccess = false;
        int             iRetryIterationCount = 3;

        do
        {
                try
                {
                        const char *    pszURL = "http://localhost:9090/axis/ValidXMLCharIsInterpretedAsCPPCommand";

                        pszURL = argv[1];

                        ValidXMLCharIsInterpretedAsCPPCommand * pWS = new ValidXMLCharIsInterpretedAsCPPCommand( pszURL, APTHTTP1_1);
                        test1Punctuation *                                              pTest1Punctuation = new test1Punctuation();
//                      test2Logical *                                                  pTest2Logical = new test2Logical();
//                      test3Mathematical *                                             pTest3Mathematical = new test3Mathematical();
//                      test4Miscellaneous *                                    pTest4Miscellaneous = new test4Miscellaneous();

                        pTest1Punctuation->setarg_WithADot( 1);
                        pTest1Punctuation->setarg_WithAnUnderscore( 2);
                        pTest1Punctuation->setarg_WithAHyphen( 3);
                        pTest1Punctuation->setarg_WithAColon( 4);
            pTest1Punctuation->setarg__WithTwoUnderscores( 5);
            pTest1Punctuation->setarg_With_TwoDots( 6);
            pTest1Punctuation->setarg__WithTwoDotsInline( 7);
           
//                      pTest1Punctuation->setarg_name5( 5);

            cout <<"About to invoke test1"<<endl;                       
                        xsd__int iResult1 = pWS->test1( pTest1Punctuation);
            if( iResult1 == 1 + 2 + 3 + 4 + 5+6+7)
            {
              cout <<"Got result from test1 "<<iResult1<<endl;
              // don't print anything
              // just do the next test
              cout <<"About to invoke Test1WithComplexResponse"<<endl;
              test1Punctuation* pTest1PunctuationResponse = pWS->Test1WithComplexResponse(pTest1Punctuation);
              cout << "Done invoke now getting the result"<<endl;
              cout << "argWithADot="<<pTest1PunctuationResponse->getarg_WithADot()<<endl;
              cout << "argWithAnUnderscore="<<pTest1PunctuationResponse->getarg_WithAnUnderscore()<<endl;
              cout << "argWithAHyphen="<<pTest1PunctuationResponse->getarg_WithAHyphen()<<endl;
              cout << "argWithAColon="<<pTest1PunctuationResponse->getarg_WithAColon()<<endl;
              cout << "argWithTwoUnderscores="<<pTest1PunctuationResponse->getarg__WithTwoUnderscores()<<endl;
              cout << "argWithTwoDots="<<pTest1PunctuationResponse->getarg_With_TwoDots()<<endl;
              cout << "argWithTwoDotsInline="<<pTest1PunctuationResponse->getarg__WithTwoDotsInline()<<endl;
        
                bSuccess=true;
            }
            else
            {
              cout << "Results should have been 1+2+3+4+5+6+7="<<(1+2+3+4+5+6+7)<<" but was "<<iResult1<<endl;
            }

/*                      if( iResult1 == 1 + 2 + 3 + 4 + 5)
                        {
                                pTest2Logical->setarg_name1( 6);

                                xsd__int iResult2 = pWS->test2( pTest2Logical);

                                if( iResult2 == 6)
                                {
                                        pTest3Mathematical->setarg_name1( 7);
                                        pTest3Mathematical->setarg_name2( 8);
                                        pTest3Mathematical->setarg_name3( 9);
                                        pTest3Mathematical->setarg_name4( 10);
                                        pTest3Mathematical->setarg_name5( 11);
                                        pTest3Mathematical->setarg_name6( 12);

                                        xsd__int iResult3 = pWS->test3( pTest3Mathematical);

                                        if( iResult3 == 7 + 8 + 9 + 10 + 11 + 12)
                                        {
                                                pTest4Miscellaneous->setarg_name1_( 13);
                                                pTest4Miscellaneous->setarg_name2_( 14);
                                                pTest4Miscellaneous->setarg_name3_( 15);
                                                pTest4Miscellaneous->setarg_name4( 16);
                                                pTest4Miscellaneous->setarg_name5( 17);
                                                pTest4Miscellaneous->setarg_name6( 18);

                                                xsd__int iResult4 = pWS->test4( pTest4Miscellaneous);

                                                if( iResult4 == 13 + 14 + 15 + 16 + 17 + 18)
                                                {
                                                        bSuccess = true;
                                                }
                                        }
                                }
                        }
        */              
                        if( !bSuccess)
                        {
                                cout << "Unexpected result." << endl;
                        }

                        delete pTest1Punctuation;
//                      delete pTest2Logical;
//                      delete pTest3Mathematical;
//                      delete pTest4Miscellaneous;

                        delete pWS;
                }
                catch( AxisException& e)
                {
                        bool bSilent = false;

                        if( e.getExceptionCode() == CLIENT_TRANSPORT_OPEN_CONNECTION_FAILED)
                        {
                                if( iRetryIterationCount > 0)
                                {
                                        bSilent = true;
                                }
                        }
                        else
                        {
                                iRetryIterationCount = 0;
                        }

                        if( !bSilent)
                        {
                                cout << "Exception : " << e.what() << endl;
                        }
                }
                catch( exception& e)
                {
                        cout << "Unknown exception has occured : " << e.what() << endl;
                }
                catch(...)
                {
                        cout << "Unknown exception has occured" << endl;
                }

                iRetryIterationCount--;
        } while( iRetryIterationCount > 0 && !bSuccess);

        if( bSuccess)
        {
                cout << "---------------------- TEST COMPLETED SUCCESSFULLY -----------------------------" << endl;
        }
        else
        {
                cout << "---------------------- TEST DID NOT COMPLETE -----------------------------" << endl;
        }
        return 0;
}