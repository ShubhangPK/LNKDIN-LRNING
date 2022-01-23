#include <stdio.h>
#include <stdlib.h>
#include <json-c/json.h>

int main()
{
	const char filename[] = "02_07-sample1.json";
	json_object *jdata;
	const char *jstring;

	/* read JSON data into the json_object jdata */
	jdata = json_object_from_file(filename);
	if( jdata==NULL )
	{
		fprintf(stderr,"Unable to process %s\n",filename);
		exit(1);
	}

	/* convert the json object into a string */
	jstring = json_object_to_json_string( jdata );
	/* output the json object string */
	puts(jstring);	

	return(0);
}

