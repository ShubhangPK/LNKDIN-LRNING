#include <stdio.h>
#include <stdlib.h>
#include <json-c/json.h>

int main()
{
	const char filename[] = "02_08-sample1.json";
	json_object *jdata,*keyname,*jelement;
	enum json_type type;
	struct lh_entry *entry;
	char *key;
	const char *jstring;
	int jint,jbool,elements,x;
	double jdouble;
	struct json_object *val;

	/* read JSON data into the json_object jdata */
	jdata = json_object_from_file(filename);
	if( jdata==NULL )
	{
		fprintf(stderr,"Unable to process %s\n",filename);
		exit(1);
	}

	/* fetch the first item located in the object. The
	   loop moves through each item, showing its type */
	entry=json_object_get_object(jdata)->head;
	while(entry)
	{
		key = (char *)entry->k;
		val = (struct json_object *)entry->v;
		/* Create an object for the item (key) found */
		json_object_object_get_ex(jdata, key, &keyname);
		printf("'%s' type is ",key);
		/* Get and display the key's data type */
		type = json_object_get_type(val);
		switch(type)
		{
			case json_type_array:
				/* First obtain the number elements in the array */
				elements = json_object_array_length(keyname);
				printf("array with %d elements:",elements);
				/* Use the elements count to loop through the array */
				for( x=0; x<elements; x++)
				{
					/* Create a new json_object for each element */
					jelement = json_object_array_get_idx( keyname, x);
					/* The elements are integers */
					printf(" %d",json_object_get_int(jelement));
				}
				putchar('\n');
				break;
			case json_type_boolean:
				jbool = json_object_get_boolean(keyname);
				printf("boolean, value: %s\n", (jbool?"TRUE":"FALSE") );
				break;
			case json_type_double:
				jdouble = json_object_get_double(keyname);
				printf("double, value: %f\n", jdouble);
				break;
			case json_type_int:
				jint = json_object_get_int(keyname);
				printf("integer, value: %d\n",jint);
				break;
			case json_type_null:
				/* No function needed to get the null */
				printf("null, value: NULL\n");
				break;
			case json_type_object:
				/* see Exercise File 02_07-jsonfetch5.c */
				puts("object");
				break;
			case json_type_string:
				jstring = json_object_get_string(keyname);
				printf("string, value: %s\n",jstring);
				break;
			default:
				puts("Unrecognized");
		}
		entry=entry->next;
	}

	return(0);
}

