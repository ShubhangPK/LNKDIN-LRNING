#include <stdio.h>
#include <stdlib.h>
#include <libxml/parser.h>

static void dump_elements(xmlNodePtr n);

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

	/* recursively display all elements in the file */
	dump_elements(node);

	/* cleanup */
	xmlFreeDoc(doc);

	return(0);
}

/*
 * Recursive function to plow through all the nodes
 * and child nodes. If the "type" attribute is found
 * output its value.
 */

static void dump_elements(xmlNodePtr n)
{
	xmlNodePtr current;
	xmlChar *attribute;

	for( current=n; current; current=current->next )
	{
		if( current->type==XML_ELEMENT_NODE )
		{
			/* display current node name */
			printf("Node: %s",current->name);
			/* fetch the "type" attribute */
			attribute = xmlGetProp(current,(const xmlChar *)"type");
			/* output the attribute if avilable */
			if( attribute!=NULL )
				printf(" Attribute: %s",attribute);
			xmlFree(attribute);
			putchar('\n');
		}
		/* recurse */
		dump_elements(current->children);
	}
}

