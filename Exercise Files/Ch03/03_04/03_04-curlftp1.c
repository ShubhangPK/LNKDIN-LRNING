#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

#define BUFFER_SIZE 2048

/* this callback function must be prototyped as shown here */
static size_t read_callback(void *ptr, size_t size, size_t nmemb, void *user_data);

/* memory buffer structure, used to store data for the upload */
struct data_chunk {
	char *buffer;
	size_t size;
};

int main()
{
	char ftp_upload[] = "ftp://128.0.0.0/image1.jpg";
	char username_password[] = "username:password";
	char upload_filename[] = "image1.jpg";
	char input_buffer[BUFFER_SIZE];
	CURL *curl;
	CURLcode res;
	struct data_chunk ftp_buffer;
	FILE *input;
	int c;

	/* read file to upload into memory buffer */
		/* open the file */
	input = fopen( upload_filename, "r");
	if( input==NULL)
	{
		fprintf(stderr,"Unable to read from %s\n",upload_filename);
		exit(1);
	}
		/* initialize the memory buffer */
	ftp_buffer.buffer = malloc(1);
	ftp_buffer.size = 0;
	if( ftp_buffer.buffer==NULL )
	{
		fprintf(stderr,"Unable to initialize buffer\n");
		/* don't forget to close the file */
		fclose(input);
		exit(1);
	}
		/* read data from the file into the buffer */
	while(1)
	{
		/* read a chunk of data from the file */
		c = fread( input_buffer, sizeof(char), BUFFER_SIZE, input);
		/* re-size the buffer to accomodate the chunk read */
		ftp_buffer.buffer = realloc( ftp_buffer.buffer, ftp_buffer.size+c+1);
		if( ftp_buffer.buffer==NULL )
		{
			fprintf(stderr,"Unable to resize buffer\n");
			exit(1);
		}
		/* append the new chunk to the buffer */
		memcpy( &ftp_buffer.buffer[ftp_buffer.size], input_buffer, c );
		/* adjust buffer size */
		ftp_buffer.size += c;
		/* append null character/zero to the buffer */
		ftp_buffer.buffer[ftp_buffer.size] = 0;
		/* if fewer bytes were read than requested, the file can close */
		if( c < BUFFER_SIZE)
			break;
	}
		/* close the file */
	fclose(input);

	/* initialize curl */
	curl = curl_easy_init();
	
	printf("Preparing FTP...");
	/* set options for FPT upload */
	curl_easy_setopt(curl, CURLOPT_URL, ftp_upload);
	curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
	curl_easy_setopt(curl, CURLOPT_USERPWD, username_password);
	curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);
	curl_easy_setopt(curl, CURLOPT_READFUNCTION, read_callback);
	curl_easy_setopt(curl, CURLOPT_READDATA, &ftp_buffer);
	curl_easy_setopt(curl, CURLOPT_INFILESIZE_LARGE, (curl_off_t)ftp_buffer.size);
	
	/* request-send upload */
	res = curl_easy_perform(curl);
	if( res!=CURLE_OK )
	{
		fprintf(stderr,"curl upload failed: %s\n",curl_easy_strerror(res));
		exit(1);
	}

	/* cleanup */
	curl_easy_cleanup(curl);
	/* inform the user */
	puts("FTP upload complete");
	
	return(0);
}

/* the standard memory-upload function, documented in the libcurl API */
static size_t read_callback(void *ptr, size_t size, size_t nmemb, void *user_data)
{
	struct data_chunk *upload;	/* local pointer to reference stored data */
	size_t max;
	
	/* initialize local pointer */
	upload = (struct data_chunk *)user_data;
	/* calculate number of bytes to write */
	max = size*nmemb;
	
	/* if nothing to write, return zero */
	if(max<1)
		return(0);
	
	/* move the data chunk into the buffer */
	if(upload->size)
	{
		if(max > upload->size)
			max = upload->size;
		memcpy(ptr, upload->buffer,max);
		upload->buffer += max;
		upload->size -= max;

		return(max);
	}
	
	return(0);
}

