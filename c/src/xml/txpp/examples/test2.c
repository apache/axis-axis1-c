#include "../lib/xpp.h"

char *tn[] = {"START_TAG", "END_TAG", "EMPTY_ELEMENT_TAG", "PCDATA"};

int main()
{
        //xpp_context_t* ct = (xpp_context_t*) parser_create("ISO-8859-1");
        xpp_context_t* ct = (xpp_context_t*) parser_create("UTF-8");
        //xpp_context_t* ct = (xpp_context_t*) parser_create(NULL);
        //xpp_context_t* ct = (xpp_context_t*) parser_create("UTF-16");


        data_t* data;
	int* intError = (int*) malloc(sizeof(int));
	
	data = (data_t*) next(ct);
	data = (data_t*) next(ct);
        //printf("\n%s\n", tn[data->type]);	
	data = (data_t*) next(ct);
        //printf("\n%s\n", tn[data->type]);	
	data = (data_t*) next(ct);
        //printf("\n%s\n", tn[data->type]);	
	data = (data_t*) next(ct);
        //printf("\n%s\n", tn[data->type]);	
	int intTemp = get_next_element_as_int(ct, intError);
	printf("intTemp:%d\n", intTemp);


        //free(buff);
        parser_free(ct);
        return 1;
}
