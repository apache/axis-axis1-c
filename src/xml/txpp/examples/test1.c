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

#include "../lib/xpp.h"

char *tn[] = {"START_TAG", "END_TAG", "EMPTY_ELEMENT_TAG", "PCDATA"};

int main()
{
        /* xpp_context_t* ct = (xpp_context_t*) parser_create("ISO-8859-1"); */
        xpp_context_t* ct = (xpp_context_t*) parser_create("UTF-8");
        /* xpp_context_t* ct = (xpp_context_t*) parser_create(NULL); */
        /* xpp_context_t* ct = (xpp_context_t*) parser_create("UTF-16"); */


        data_t* data;

        while(data = (data_t*) next(ct))
        {
                printf("\n%s\n", tn[data->type]);
                int ii = 0;
        char temp;
                while (ii < data->num_ptrs_utf8) 
                {
                        temp = data->utf8ptrs[ii+1][1];
                        data->utf8ptrs[ii+1][1] = '\0';
                        printf("%s\n", data->utf8ptrs[ii]);
                        data->utf8ptrs[ii+1][1] = temp;
                        
                        ii += 2;
                }


        }





        /* free(buff); */
        parser_free(ct);
        return 1;
}

