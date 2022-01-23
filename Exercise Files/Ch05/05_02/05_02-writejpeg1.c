#include <stdio.h>
#include <stdlib.h>
#include <jpeglib.h>

int main()
{
	char filename[] = "05_02-image1.jpg";
	char duplicate[] = "05_02-imageduplicate1.jpg";
	FILE *jinput,*joutput;
	struct jpeg_decompress_struct dcinfo;
	struct jpeg_compress_struct cinfo;
	struct jpeg_error_mgr dcjerr, cjerr;
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
	dcinfo.err = jpeg_std_error( &dcjerr );
	jpeg_create_decompress( &dcinfo );
	jpeg_stdio_src( &dcinfo, jinput );
	jpeg_read_header( &dcinfo, TRUE );

	/* decompress the image file */
	jpeg_start_decompress( &dcinfo );

	/* gather some basic image info */
	width = dcinfo.output_width;
	height = dcinfo.output_height;
	bytes_per_pixel = dcinfo.output_components;
	printf("Image is %d pixels wide by %d pixels tall\n",width,height);
	printf("Image has %d bytes per pixel\n",bytes_per_pixel);

	/* create buffer for the uncompressed data */
	raw_image = (unsigned char *)malloc( bytes_per_pixel * width * height );
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

	/* cleanup decompression and close the file */
	jpeg_finish_decompress( &dcinfo );
	jpeg_destroy_decompress( &dcinfo );
	fclose( jinput );

	/* compress the raw image data and save it to the output file */

	/* open the output file */
	joutput = fopen(duplicate,"wb");
	if( joutput==NULL )
	{
		fprintf(stderr,"Unable to create output file %s\n",duplicate);
		exit(1);
	}
	printf("Duplicate file open for compression\n");

	/* configure for compression */
		/* setup error handler */
	cinfo.err = jpeg_std_error( &cjerr );
		/* creat the compression structure */
	jpeg_create_compress( &cinfo );
		/* assign the output file */
	jpeg_stdio_dest( &cinfo, joutput );

	/* configure image information */
	cinfo.image_width = width;
	cinfo.image_height = height;
	cinfo.input_components = bytes_per_pixel;
	cinfo.in_color_space = JCS_RGB;
	jpeg_set_defaults( &cinfo );

	/* compress */
	jpeg_start_compress( &cinfo, TRUE );
		/* write the buffer */
	while(cinfo.next_scanline < cinfo.image_height )
	{
		row_pointer[0] = &raw_image[cinfo.next_scanline*row_stride];
		jpeg_write_scanlines(&cinfo,row_pointer,1 );
	}
	printf("Image compressed\n");

	/* clean up */
	jpeg_finish_compress( &cinfo );
	jpeg_destroy_compress( &cinfo );
	fclose(joutput);
		/* free memory */
	free(raw_image);
	printf("Duplicate image %s created\n",duplicate);

	return(0);
}

