/* compile with
   clang -Wall -c 06_01-stringfunctions1.c
*/
#include <stdlib.h>
#include <string.h>

/* return a lowercase version of the string */
char *strtolc(char *string)
{
	static char *lc;
	int len,x;
	char ch;

	len = strlen(string);
	lc = (char *)malloc( sizeof(char) * len + 1 );
	if( lc==NULL )
		return(NULL);
	for(x=0; x<=len; x++)
	{
		ch = *(string+x);
		if( ch>='A' && ch<='Z' )
			ch = ch | 0x20;
		*(lc+x) = ch;
	}
	return(lc);
}

/* return an uppercase version of the string */
char *strtouc(char *string)
{
	static char *uc;
	int len,x;
	char ch;

	len = strlen(string);
	uc = (char *)malloc( sizeof(char) * len + 1 );
	if( uc==NULL )
		return(NULL);
	for(x=0; x<=len; x++)
	{
		ch = *(string+x);
		if( ch>='a' && ch<='z' )
			ch = ch & 0xdf;
		*(uc+x) = ch;
	}
	return(uc);
}

/* return a pointer to the leftmost 'offset' characters in the string */
char *strleft(char *string, int offset)
{
	static char *left;
	int len,x;

	len = strlen(string);
	if( offset>len || offset<1 )
		return(NULL);
	left = (char *)malloc(sizeof(char) * offset + 1);
	if( left==NULL )
		return(NULL);
	for(x=0; x<offset; x++)
		*(left+x) = *(string+x);
	*(left+x) = '\0';
	return(left);
}

/* return a pointer to the rightmost 'offset' characters in the string */
char *strright(char *string, int offset)
{
	static char *right;
	int len,x;

	len = strlen(string);
	if( offset>len || offset<1 )
		return(NULL);
	right = (char *)malloc(sizeof(char) * offset + 1);
	if( right==NULL )
		return(NULL);
	for(x=0; x<=offset; x++)
		*(right+x) = *(string+len-offset-1+x);
	return(right);
}

/* return a reversed version of the string */
char *strrev(char *string)
{
	static char *reverse;
	int len,x;

	len = strlen(string);
	reverse = (char *)malloc( sizeof(char) * len + 1);
	if( reverse==NULL )
		return(NULL);
	for(x=0; x<len; x++)
		*(reverse+x) = *(string+len-x-1);
	*(reverse+x) = '\0';
	return(reverse);
}

/* split the string into two chunks at offset */
int strsplit(char *original,int offset,char **s1,char **s2)
{
    int len;

    len = strlen(original);
    if(offset>len || offset<1 )
        return(0);
    *s1 = (char *)malloc(sizeof(char) * offset+1);
    *s2 = (char *)malloc(sizeof(char) * len-offset+1);
    if( s1==NULL || s2==NULL )
        return(0);
    strncpy(*s1,original,offset);
	*(*(s1)+offset) = '\0';
    strncpy(*s2,original+offset,len-offset);
	*(*(s2)+len-offset) = '\0';
    return(1);
}
