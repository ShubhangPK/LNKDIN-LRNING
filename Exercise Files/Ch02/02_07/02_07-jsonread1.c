#include <stdio.h>
#include <stdlib.h>
#include <json-c/json.h>

int main()
{
	const char filename[] = "02_07-sample1.json";
	json_object *jdata;

	/* Create a json_object from the JSON data
	   stored in the named file */
	jdata = json_object_from_file(filename);
	if( jdata==NULL )
	{
		fprintf(stderr,"Unable to process %s\n",filename);
		exit(1);
	}

	printf("File %s opened\n",filename);

	return(0);
}

