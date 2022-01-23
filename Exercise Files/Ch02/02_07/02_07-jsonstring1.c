#include <stdio.h>
#include <stdlib.h>
#include <json-c/json.h>

int main()
{
	const char jstring[] = "{\"station\":\"KCOE\",\"date\":{\"month\":2,\"day\":23,\"year\":2014},\"temperatures\":{\"high\":2.1,\"low\":-1.4}}";
	json_object *jdata;
	const char *s;

	/* convert string into json object */
	jdata = json_tokener_parse(jstring);
	if( jdata==NULL )
	{
		fprintf(stderr,"Unable to tokenize string\n");
		exit(1);
	}

	/* output the processed object */
	s = json_object_to_json_string_ext( jdata, JSON_C_TO_STRING_PRETTY );
	puts(s);

	return(0);
}

