#include <stdio.h>
#include <stdlib.h>
#include <jpeglib.h>

int main()
{
	char filename[] = "05_02-image1.jpg";
	FILE *jinput;
	struct jpeg_decompress_struct dcinfo;
	struct jpeg_error_mgr dcjerr;
	unsigned char *raw_image;
	JSAMPROW row_pointer[1];
	int row_stride,width,height,bytes_per_pixel;

	/* read the input file */
	jinput = fopen( filename, "rb");
	if( jinput==NULL )
	{
		fprintf(stderr,"Unable to open %s\n",filename);
		exit(1);
	}
	printf("File %s opened\n",filename);

	/* configure for decompression */
		/* configure the library to handle errors */
	dcinfo.err = jpeg_std_error( &dcjerr );
		/* initialize decompression */
	jpeg_create_decompress( &dcinfo );
		/* specify the input file as the source */
	jpeg_stdio_src( &dcinfo, jinput );
		/* obtain image information */
	jpeg_read_header( &dcinfo, TRUE );

	/* decompress the image file */
	jpeg_start_decompress( &dcinfo );

	/* gather basic image info */
	width = dcinfo.output_width;
	height = dcinfo.output_height;
	bytes_per_pixel = dcinfo.output_components;
	printf("Image is %d pixels wide by %d pixels tall\n",width,height);
	printf("Image has %d bytes per pixel\n",bytes_per_pixel);

	/* create buffer for the uncompressed data */
		/* raw_image holds the entire image data */
	raw_image = (unsigned char *)malloc( bytes_per_pixel * width * height );
		/* confirm that buffer is created */
	if(raw_image==NULL)
	{
		fprintf(stderr,"Unable to allocate memory for image\n");
		fclose(jinput);
		exit(1);
	}
	printf("Buffer created\n");

	/* read each scanline into the raw_image memory buffer */
	row_stride = width * bytes_per_pixel;
	while( dcinfo.output_scanline < height )
	{
		row_pointer[0] = &raw_image[dcinfo.output_scanline*row_stride];
		jpeg_read_scanlines(&dcinfo,row_pointer,1);
	}
	printf("Scanlines read\n");

	/* raw image is stored in the buffer */
		/* at this point it can be manipulated or examined */

	/* cleanup decompression and close the file */
	jpeg_finish_decompress( &dcinfo );
	jpeg_destroy_decompress( &dcinfo );
		/* close the open file */
	fclose( jinput );
		/* free memory */
	free(raw_image);
	printf("Clean up and close\n");

	return(0);
}

