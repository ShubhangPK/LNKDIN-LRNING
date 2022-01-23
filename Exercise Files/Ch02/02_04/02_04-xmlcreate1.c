#include <stdio.h>
#include <stdlib.h>
#include <libxml/parser.h>

int main()
{
	/* libxml2 variables */
	xmlDocPtr doc;

	/* create a new XML document */
	doc = xmlNewDoc( (const xmlChar *)"1.0" );
	if( doc==NULL)
	{
		fprintf(stderr,"Unable to create new XML document\n");
		exit(1);
	}

	/* write document */
	xmlSaveFormatFile( "-", doc, 0);

	/* cleanup */
	xmlFreeDoc(doc);	

	return(0);
}

