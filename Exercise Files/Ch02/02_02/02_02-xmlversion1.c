#include <stdio.h>
#include <stdlib.h>
#include <libxml/parser.h>

int main()
{
	const char filename[] = "02_02-sample1.xml";
	/* libxml2 variables */
	xmlDocPtr doc;

	/* parse the document */
	doc = xmlParseFile(filename);
	if( doc==NULL )
	{
		fprintf(stderr,"Unable to parse document %s\n",filename);
		exit(1);
	}

	/* Output the XML version stored in the document */
	if( doc->version!=NULL && doc->encoding!=NULL )
	{
		printf("%s is XML version %s with %s encoding\n",
				filename,
				doc->version,
				doc->encoding
			  );
	}
	else
	{
		printf("%s lacks either XML version of encoding information\n",
				filename
			  );
	}

	xmlFreeDoc(doc);

	return(0);
}

