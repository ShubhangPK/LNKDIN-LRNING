#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>

int main()
{
	CURL *curl;
	CURLcode res;
	char address[] = "https://c-for-dummies.com/curl_test.txt";

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

	/* curl the resource */
	res = curl_easy_perform(curl);
	if( res!=CURLE_OK )
	{
		fprintf(stderr,"Unable to curl %s\n",address);
		exit(1);
	}

	/* cleanup */
	curl_easy_cleanup(curl);

	return(0);
}

