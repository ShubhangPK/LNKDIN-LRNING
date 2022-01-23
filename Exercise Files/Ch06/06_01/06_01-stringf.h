/*
	prototypes and declarations for the stringf library
*/

char *strtolc(char *string);
char *strtouc(char *string);
char *strleft(char *string, int offset);
char *strright(char *string, int offset);
char *strrev(char *string);
int strsplit(char *original,int offset,char **s1,char **s2);

