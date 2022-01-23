#include <stdio.h>
#include <stdlib.h>
#include <libxml/parser.h>

int main()
{
	const char filename[] = "02_04-sample2.xml";
	int r;
	/* libxml2 variables */
	xmlDocPtr doc;
	xmlNodePtr root;

	/* create a new XML document */
	doc = xmlNewDoc( (const xmlChar *)"1.0" );
	if( doc==NULL)
	{
		fprintf(stderr,"Unable to create new XML document\n");
		exit(1);
	}

	/* create a new node */
	root = xmlNewDocNode( doc, NULL, (const xmlChar *)"root", NULL );
	if( root==NULL )
	{
		fprintf(stderr,"Unable to create new node\n");
		exit(1);
	}

	/* set new node as root element */
	xmlDocSetRootElement( doc, root);

	/* write document */
	r = xmlSaveFormatFile( filename, doc, 1);
	if( r == -1 )
		printf("Unable to create %s\n",filename);
	else
		printf("%s created, %d bytes written\n",filename,r);


	/* cleanup */
	xmlFreeDoc(doc);	

	return(0);
}

