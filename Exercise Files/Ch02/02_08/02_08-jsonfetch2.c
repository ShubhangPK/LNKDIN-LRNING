#include <stdio.h>
#include <stdlib.h>
#include <json-c/json.h>

int main()
{
	const char filename[] = "02_08-sample1.json";
	json_object *jdata;
	enum json_type type;
	struct lh_entry *entry;
	char *key;
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
		/* Output the key name */
		printf("%s type is ",key);
		/* Get and display the key's data type */
		type = json_object_get_type(val);
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
		/* as with a linked list, go to the next item
		   in the object */
		entry=entry->next;
	}

	return(0);
}

