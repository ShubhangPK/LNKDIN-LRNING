/* compile with:
   clang -Wall -L. -lstringf 06_01-stringlibtest1.c
*/
#include <stdio.h>
#include "06_01-stringf.h"

int main()
{
	char sample[] = "This is the sample string I will use as a test.\n";
	char *stringa,*stringb;
	int r;

	printf("Sample string original:\n\t%s\n",sample);

	/* test stringtolc() */
	printf("Lowercase version:\n\t%s\n",strtolc(sample) );
	/* test stringtouc() */
	printf("Uppercase version:\n\t%s\n",strtouc(sample) );
	/* strleft(), 10 characters */
	printf("10 left-most characters:\n\t%s\n",strleft(sample,10));
	/* strright(), 10 characters */
	printf("10 right-most characters:\n\t%s\n",strright(sample,10));
	/* reverse the string */
	printf("String reversed:\n\t%s\n",strrev(sample));
	/* split the string into two chunks */
	r = strsplit(sample,22,&stringa,&stringb);
	if( r==0 )
		puts("Unable to split the string");
	else
		printf("String split in two:\n\t%s\n\t%s\n",stringa,stringb);

	return(0);
}

