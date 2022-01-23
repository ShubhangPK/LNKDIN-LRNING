#include <stdio.h>
#include <stdlib.h>
#include <json-c/json.h>

void parse_json_object(json_object *jobj, struct lh_entry *ent, int indent);

int main()
{
	const char filename[] = "02_08-sample1.json";
	json_object *jdata;
	struct lh_entry *entry;

	/* read JSON data into the json_object jdata */
	jdata = json_object_from_file(filename);
	if( jdata==NULL )
	{
		fprintf(stderr,"Unable to process %s\n",filename);
		exit(1);
	}

	/* configure entry into the function */
	entry=json_object_get_object(jdata)->head;
	/* The function requires a json_object, lh_entry structure
	   (used for the linked-list aspect of finding keys), and
	   an indent item, which helps reading output */
	parse_json_object(jdata,entry,0);

	return(0);
}

/* This function outputs an entry's key and value for the
   named json_data object. If nested objects are encountered,
   the code is recursively called to process the new level */
void parse_json_object(json_object *jobj, struct lh_entry *ent, int indent)
{
	json_object *keyname,*jelement;
	enum json_type type;
	char *key;
	const char *jstring;
	int jint,jbool,elements,x;
	struct json_object *val;
	struct lh_entry *e;

	while(ent)
	{
		key = (char *)ent->k;
		val = (struct json_object *)ent->v;
		json_object_object_get_ex(jobj, key, &keyname);
		printf("%*c'%s' type is ",indent*4,' ',key);
		type = json_object_get_type(val);
		switch(type)
		{
			case json_type_array:
				elements = json_object_array_length(keyname);
				printf("array with %d elements:",elements);
				for( x=0; x<elements; x++)
				{
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
				puts("Double");
				break;
			case json_type_int:
				jint = json_object_get_int(keyname);
				printf("integer, value: %d\n",jint);
				break;
			case json_type_null:
				puts("Null");
				break;
			case json_type_object:
				puts("JSON object:");
				/* obtain the lh_entry structure for the nested object */
				e = json_object_get_object(keyname)->head;
				/* recursively call this function, with an increased indent value */
				parse_json_object(keyname,e,indent+1);
				break;
			case json_type_string:
				jstring = json_object_get_string(keyname);
				printf("string, value: %s\n",jstring);
				break;
			default:
				puts("Unrecognized");
		}
		ent=ent->next;
	}
}

