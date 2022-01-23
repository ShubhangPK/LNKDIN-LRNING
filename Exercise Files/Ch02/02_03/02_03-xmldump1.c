#include <stdio.h>
#include <stdlib.h>
#include <libxml/parser.h>

int main()
{
	const char filename[] = "02_03-sample1.xml";
	/* libxml2 variables */
	xmlDocPtr doc;
	xmlNodePtr node;

	/* open the document for parsing */
	doc = xmlParseFile(filename);
	if( doc==NULL )
	{
		fprintf(stderr,"Unable to process %s\n",filename);
		exit(1);
	}

	/* fetch the root element */
	node = xmlDocGetRootElement(doc);
	if( node==NULL )
	{
		fprintf(stderr,"Document %s is empty\n",filename);
		xmlFreeDoc(doc);
		exit(1);
	}
	printf("root node is %s\n",node->name);

	/* cleanup */
	xmlFreeDoc(doc);

	return(0);
}

