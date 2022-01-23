#include <stdio.h>
#include <stdlib.h>
#include <json-c/json.h>

int main()
{
	const char filename[] = "02_07-sample1.json";
	const char *jstring;
	json_object *jdata;

	/* read JSON data into the json_object jdata */
	jdata = json_object_from_file(filename);
	if( jdata==NULL )
	{
		fprintf(stderr,"Unable to process %s\n",filename);
		exit(1);
	}

	/* convert the json object to a string but with pretty formatting */
	jstring = json_object_to_json_string_ext( jdata, JSON_C_TO_STRING_PRETTY );
	puts(jstring);	

	return(0);
}

