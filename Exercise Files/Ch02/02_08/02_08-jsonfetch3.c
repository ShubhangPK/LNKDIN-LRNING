#include <stdio.h>
#include <stdlib.h>
#include <json-c/json.h>

int main()
{
	const char filename[] = "02_08-sample1.json";
	const char object_name[] = "lastName";
	const char *value;
	json_object *jdata,*objname;

	/* read JSON data into the json_object jdata */
	jdata = json_object_from_file(filename);
	if( jdata==NULL )
	{
		fprintf(stderr,"Unable to process %s\n",filename);
		exit(1);
	}

	/* Examine the named object to determine its data type */
	json_object_object_get_ex(jdata, object_name, &objname);
	/* return the key value for object name, knowing that
	   it's a string */
	value = json_object_get_string(objname);
	printf("%s's value is %s\n",object_name,value);

	return(0);
}

