/*
 *   Copyright 2003-2004 The Apache Software Foundation.
 *
 *   Licensed under the Apache License, Version 2.0 (the "License");
 *   you may not use this file except in compliance with the License.
 *   You may obtain a copy of the License at
 *
 *       http://www.apache.org/licenses/LICENSE-2.0
 *
 *   Unless required by applicable law or agreed to in writing, software
 *   distributed under the License is distributed on an "AS IS" BASIS,
 *   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *   See the License for the specific language governing permissions and
 *   limitations under the License.
 */

#include "../../src/spp.h"

char *tn[] = {"START_TAG", "END_TAG", "EMPTY_ELEMENT_TAG", "PCDATA"};

int main()
{
        /* SPPParser* ct = (SPPParser*) parserCreate("ISO-8859-1"); */
        SPPParser* ct = (SPPParser*) parserCreate("UTF-8");
        /* SPPParser* ct = (SPPParser*) parserCreate(NULL); */
        /* SPPParser* ct = (SPPParser*) parserCreate("UTF-16"); */


        TokDataStruct* data;
        parseProlog(ct);
        while(data = (TokDataStruct*) next(ct))
        {
                printf("\n%s\n", tn[data->type]);
                int ii = 0;
        char temp;
                while (ii < data->numOfPtrs) 
                {
                        temp = data->ptrBuff[ii+1][1];
                        data->ptrBuff[ii+1][1] = '\0';
                        printf("%s\n", data->ptrBuff[ii]);
                        data->ptrBuff[ii+1][1] = temp;
                        
                        ii += 2;
                }


        }





        /* free(buff); */
        parserFree(ct);
        return 1;
}

