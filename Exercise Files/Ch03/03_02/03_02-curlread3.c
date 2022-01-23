#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>

int main()
{
	CURL *curl;
	CURLcode res;
	char address[] = "https://c-for-dummies.com/curl_test.txt";
	char error_buffer[CURL_ERROR_SIZE];

	/* Initialize easy curl */
	curl = curl_easy_init();
	if( curl == NULL)
	{
		fprintf(stderr,"Unable to initialize curl\n");
		exit(1);
	}

	/* set options */
		/* set the URL/web page address */
	curl_easy_setopt(curl, CURLOPT_URL, address);
		/* follow any redirects */
	curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
		/* output detailed error */
	curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, error_buffer);

	/* curl the resource */
	res = curl_easy_perform(curl);
	if( res!=CURLE_OK )
	{
		fprintf(stderr,"Unable to curl %s\n",address);
		fprintf(stderr,"Curl error: %s\n",error_buffer);
		exit(1);
	}

	/* cleanup */
	curl_easy_cleanup(curl);

	return(0);
}

