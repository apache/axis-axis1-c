#include "HexCoder.h"

const static char s_HexToNumTable[128]=
{
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  //00  - 15
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  //16  - 31
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  //32  - 47
	0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 0, 0, 0, 0, 0,  //48  - 63
	0,10,11,12,13,14,15, 0, 0, 0, 0, 0, 0, 0, 0, 0,  //64  - 79
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  //80  - 95
	0,10,11,12,13,14,15, 0, 0, 0, 0, 0, 0, 0, 0, 0,  //96  - 111
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  //112 - 127
};
	
const static char s_NumToHexTable[16] =
{
	'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'
};

int Hex_Encode(char * coded_dst, const unsigned char *plain_src, int len_plain_src)
{
	const unsigned char *cur = plain_src;
	const unsigned char *end = cur + len_plain_src;
	while(cur < end)
	{
		*coded_dst = s_NumToHexTable[(*cur) >> 4];
		coded_dst++;
		*coded_dst = s_NumToHexTable[(*cur)& 0x0f];
		coded_dst++;
		cur++;
	}
	return 0;
}

int Hex_Decode(unsigned char * plain_dst, const char *coded_src)
{
	unsigned char* curr = plain_dst;
	while (*coded_src != '\0')
	{
		*curr = (s_HexToNumTable[*coded_src] << 4) | s_HexToNumTable[*(coded_src+1)];
		curr++;
		coded_src+=2;
	}
	return (int)(curr-plain_dst);
}
