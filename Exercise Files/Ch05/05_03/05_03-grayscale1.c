#include <stdio.h>
#include <stdlib.h>
#include <jpeglib.h>

int main()
{
	char input_file[] = "05_03-image1.jpg";
	char output_file[] = "05_03-image1-grayscale.jpg";
	FILE *original,*graycopy;
	struct jpeg_decompress_struct dcinfo;
	struct jpeg_compress_struct cinfo;
	struct jpeg_error_mgr dcjerr, cjerr;
	unsigned char *raw_image;
	JSAMPROW row_pointer[1];
	int row_stride,width,height,bytes_per_pixel;

	/* read input file */
	original = fopen(input_file,"rb");
	if(!original)
	{
		fprintf(stderr,"Unable to read image file.\n");
		exit(1);
	}
	printf("File '%s' read\n",input_file);

	/* configure for decompression */
	dcinfo.err = jpeg_std_error(&dcjerr);
	jpeg_create_decompress(&dcinfo);
	jpeg_stdio_src(&dcinfo,original);
	jpeg_read_header(&dcinfo,TRUE);
		/* decompress as grayscale image */
	dcinfo.out_color_space = JCS_GRAYSCALE;
		
	/* decompress the image file */
	jpeg_start_decompress(&dcinfo);

	/* gather some basic info */
	width = dcinfo.output_width;
	height = dcinfo.output_height;
	bytes_per_pixel = dcinfo.output_components;
		
	/* create buffer for the uncompressed data */
	raw_image = (unsigned char *)malloc(bytes_per_pixel*width*height);
	if(raw_image==NULL)
	{
		fprintf(stderr,"Unable to allocate memory for image\n");
		fclose(original);
		exit(1);
	}

	/* loop to read each scanline */
	row_stride = width * bytes_per_pixel;
	while(dcinfo.output_scanline < height)
	{
		row_pointer[0] = &raw_image[dcinfo.output_scanline*row_stride];
		jpeg_read_scanlines(&dcinfo,row_pointer,1);
	}

	/* raw image is stored in the buffer raw_image */

	/* cleanup decompression and close */
	jpeg_finish_decompress(&dcinfo);
	jpeg_destroy_decompress(&dcinfo);
	fclose(original);

	/* compress the raw image and save it to the output file */

	/* open output file */
	graycopy = fopen(output_file,"wb");
	if( graycopy==NULL )
	{
		fprintf(stderr,"Unable to create output file %s\n",output_file);
		exit(1);
	}

	/* configure for compression */
	cinfo.err = jpeg_std_error(&cjerr);
	jpeg_create_compress(&cinfo);
	jpeg_stdio_dest(&cinfo,graycopy);
	cinfo.image_width = width;
	cinfo.image_height = height;
	cinfo.input_components = bytes_per_pixel;
		/* set output to grayscale */
	cinfo.in_color_space = JCS_GRAYSCALE;
	jpeg_set_defaults(&cinfo);

	/* begin compression */
	jpeg_start_compress(&cinfo,TRUE);
	while(cinfo.next_scanline < cinfo.image_height)
	{
		row_pointer[0] = &raw_image[cinfo.next_scanline*row_stride];
		jpeg_write_scanlines(&cinfo,row_pointer,1);
	}

	/* clean-up */
	jpeg_finish_compress(&cinfo);
	jpeg_destroy_compress(&cinfo);
	fclose(graycopy);
	free(raw_image);
	printf("Grayscale output file '%s' created\n",output_file);

	return(0);
}

