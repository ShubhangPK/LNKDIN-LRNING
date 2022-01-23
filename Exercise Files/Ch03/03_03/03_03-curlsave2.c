#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>

int main()
{
	CURL *curl;
	CURLcode res;
	char address[] = "https://curl.haxx.se/logo/curl-logo.svg";
	char filename[] = "curl-logo.svg";
	FILE *output;

	/* open output file */
	output = fopen("curl-logo.svg","w");
	if( output==NULL )
	{
		fprintf(stderr,"Unable to create output file %s\n",filename);
		exit(1);
	}

	/* initialuze curl */
	curl = curl_easy_init();

	/* set options */
	curl_easy_setopt(curl, CURLOPT_URL, address);
	curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, NULL);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, output);
	
	/* read the address */
	res = curl_easy_perform(curl);
	if( res != CURLE_OK )
	{
		fprintf(stderr,"curl read failed: %s\n", curl_easy_strerror(res));
		exit(1);
	}
	
	/* cleanup and close */
	curl_easy_cleanup(curl);
	fclose(output);
	/* inform the user */
	printf("Data received. File '%s' written\n",filename);

	return(0);
}

