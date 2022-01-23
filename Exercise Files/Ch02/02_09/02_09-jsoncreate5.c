#include <stdio.h>
#include <stdlib.h>
#include <json-c/json.h>

int main()
{
	json_object *jdata,*jnewobj;
	const char filename[] = "02_09-test1.json";

	/* I've removed the testing to compact the code */

	/* create a new json object */
	jdata = json_object_new_object();

	/* create a string json object */
	jnewobj = json_object_new_string( (const char *)"JSON file write");
	/* add the object field */
	json_object_object_add( jdata, (const char *)"Test", jnewobj );

	/* create a boolean object */
	jnewobj = json_object_new_boolean( (json_bool)1 );
	/* add the object field */
	json_object_object_add( jdata, (const char *)"Passed", jnewobj );

	/* save the object to a file */
	json_object_to_file(filename,jdata);
	printf("JSON data file %s written\n",filename);

	return(0);
}

