#include <stdio.h>
#include <stdlib.h>
#include <json-c/json.h>

int main()
{
	json_object *jdata,*jnewobj,*jelement;
	const char *jstring;
	int x;

	/* create a new json object */
	jdata = json_object_new_object();
	if( jdata==NULL )
	{
		fprintf(stderr,"Unable to create new object\n");
		exit(1);
	}

	/* create an array json object */
	jnewobj = json_object_new_array();
	if( jnewobj==NULL )
	{
		fprintf(stderr,"Unable to create new array object\n");
		exit(1);
	}

	/* loop to add the elements */
	for( x=100; x<600; x+=100 )
	{
		jelement = json_object_new_int(x);
		if( jelement==NULL )
		{
			fprintf(stderr,"Unable to create integer object\n");
			exit(1);
		}
		/* add the object to the array */
		json_object_array_add( jnewobj, jelement);
	}

	/* don't forget to add the array to the first object! */
	json_object_object_add( jdata, (const char *)"Numbers", jnewobj );

	/* output the object */
	jstring = json_object_to_json_string_ext( jdata, JSON_C_TO_STRING_PRETTY );
	puts(jstring);

	return(0);
}

