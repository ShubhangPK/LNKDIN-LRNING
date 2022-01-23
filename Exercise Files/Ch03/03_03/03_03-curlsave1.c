#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>

int main()
{
	CURL *curl;
	CURLcode res;
	char address[] = "https://c-for-dummies.com/curl_test.txt";
	char filename[] = "curlout.txt";
	FILE *output;

	/* open output file */
	output = fopen(filename,"w");
	if( output==NULL )
	{
		fprintf(stderr,"Unable to create output file %s\n",filename);
		exit(1);
	}

	/* initialuze curl */
	curl = curl_easy_init();

	/* set options */
		/* web page to fetch */
	curl_easy_setopt(curl, CURLOPT_URL, address);
		/* handle redirects */
	curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
		/* set the function to capture data, though
		   with NULL specified, data is written to
		   a file, providing the next option is set */
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, NULL);
		/* write the incoming data to the file specified
		   for this option */
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, output);
	
	/* read the address */
	res = curl_easy_perform(curl);
	if( res != CURLE_OK )
	{
		/* use the return value to output a specific error message */
		fprintf(stderr,"curl read failed: %s\n",curl_easy_strerror(res));
		exit(1);
	}
	
	/* cleanup and close */
	curl_easy_cleanup(curl);
	fclose(output);
	/* let the user know what's going on */
	printf("Data received. File '%s' written\n",filename);

	return(0);
}

