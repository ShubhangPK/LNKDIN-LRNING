#include <stdio.h>
#include <stdlib.h>
#include <libxml/parser.h>

int main()
{
	const char filename[] = "02_03-sample1.xml";
	/* libxml2 variables */
	xmlDocPtr doc;
	xmlNodePtr node;
	xmlChar *key;

	/* parse the document */
	doc = xmlParseFile(filename);
	if( doc==NULL )
	{
		fprintf(stderr,"Unable to parse documemnt %s\n",filename);
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

	/* fetch a specific node */
	node = node->children;
	while( node != NULL )
	{
		if( (!xmlStrcmp(node->name, (const xmlChar *)"notes")) )
		{
			key = xmlNodeListGetString(doc, node->children, 1);
			printf("Value of 'notes': %s\n",key);
			xmlFree(key);
		}
		node = node->next;
	}

	/* clean-up */
	xmlFreeDoc(doc);

	return(0);
}

