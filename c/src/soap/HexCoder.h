#if !defined(_HEXCODER_H____INCLUDED_)
#define _HEXCODER_H____INCLUDED_

int Hex_Encode(char * coded_dst, const unsigned char *plain_src, int len_plain_src);
int Hex_Decode(unsigned char * plain_dst, const char *coded_src);

#endif
