#include "../lib/xpp.h"

char *tn[] = {"START_TAG", "END_TAG", "EMPTY_ELEMENT_TAG", "PCDATA"};

int main()
{
        //xpp_context_t* ct = (xpp_context_t*) parser_create("ISO-8859-1");
        xpp_context_t* ct = (xpp_context_t*) parser_create("UTF-8");
        //xpp_context_t* ct = (xpp_context_t*) parser_create(NULL);
        //xpp_context_t* ct = (xpp_context_t*) parser_create("UTF-16");


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





        //free(buff);
        parser_free(ct);
        return 1;
}
