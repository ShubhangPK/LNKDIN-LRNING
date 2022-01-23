#include <stdio.h>
#include <stdlib.h>
#include <json-c/json.h>

int main()
{
	const char filename[] = "02_08-sample1.json";
	const char object_name[] = "lastName";
	json_object *jdata,*objname;
	enum json_type type;

	/* read JSON data into the json_object jdata */
	jdata = json_object_from_file(filename);
	if( jdata==NULL )
	{
		fprintf(stderr,"Unable to process %s\n",filename);
		exit(1);
	}

	/* Examine the named object to determine its data type */
	if( !json_object_object_get_ex(jdata, object_name, &objname))
	{
		fprintf(stderr,"Can't locate %s\n",object_name);
		exit(1);
	}
	printf("%s's type is ",object_name);
	/* compare the json_object returned to one of the seven
	   JSON data types */
	type = json_object_get_type(objname);
	switch(type)
	{
		case json_type_array:
			puts("Array");
			break;
		case json_type_boolean:
			puts("Boolean");
			break;
		case json_type_double:
			puts("Double");
			break;
		case json_type_int:
			puts("Integer");
			break;
		case json_type_null:
			puts("Null");
			break;
		case json_type_object:
			puts("Object");
			break;
		case json_type_string:
			puts("String");
			break;
		default:
			puts("Unrecognized");
	}

	return(0);
}

