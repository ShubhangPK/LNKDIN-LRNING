#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

/* this callback function must be prototyped as shown here */
static size_t write_mem(void *ptr, size_t size, size_t nmemb, void *userdata);

/* memory buffer structure, used to store retrieved data */
struct web_data {
	char *buffer;
	size_t size;
};

int main()
{
	CURL *curl;
	CURLcode res;
	char address[] = "https://c-for-dummies.com/curl_test.txt";
	struct web_data page;

	/* initialize storage structure */
		/* give it one byte somewhere */
	page.buffer = malloc(1);
		/* set the initial size to zero */
	page.size = 0;

	/* initialuze curl */
	curl = curl_easy_init();

	/* set options */
	curl_easy_setopt(curl, CURLOPT_URL, address);
	curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
		/* write_mem() is our callback function */
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_mem);
		/* &page is the data structure to which information is stored */
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &page);
	
	/* read the address */
	res = curl_easy_perform(curl);
	if( res != CURLE_OK )
	{
		fprintf(stderr,"curl read failed: %s\n", curl_easy_strerror(res));
		exit(1);
	}
	
	/* cleanup */
	curl_easy_cleanup(curl);

	/* display results */
		/* data is read from the structure, first bytes */
	printf("Read %ld bytes:\n", page.size);
		/* next output the data itself */
	printf("%s",page.buffer);

	return(0);
}

/* the standard memory-writing function, documented in the libcurl API */
	/* this function is static so that its values are retained between
	   calls. */
static size_t write_mem(void *ptr, size_t size, size_t nmemb, void *userdata)
{
	size_t realsize;		/* actual number of bytes read */
	struct web_data *mem;	/* local pointer used to reference stored data */

	/* update the number of bytes fetched */
	realsize = size * nmemb;
	/* initialize the local pointer */
	mem = (struct web_data *)userdata;

	/* resize the memory buffer to reflect the number of bytes read */
	mem->buffer = realloc(mem->buffer, mem->size + realsize + 1);
	if( mem->buffer==NULL )
	{
		fprintf(stderr,"Unable to reallocate buffer\n");
		exit(1);
	}

	/* append the new data read to the end of the existing buffer */
	memcpy( &(mem->buffer[mem->size]), ptr, realsize);
	/* update the size */
	mem->size += realsize;
	/* cap the string with a null character/zero */
	mem->buffer[mem->size] = 0;

	return(realsize);
}

