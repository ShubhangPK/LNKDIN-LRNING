#include <stdio.h>
#include <stdlib.h>
#include <png.h>

#define SIGSIZE 8

int main(int argc, char **argv)
{
	char input_file[] = "05_04-image1.png";
	FILE *infile;
	unsigned char header[8];
	png_structp png_ptr;
	png_infop info_ptr;
	int y,width,height,number_of_passes;
	png_byte color_type,bit_depth;
	png_bytep *row_pointers;

	/* open the png file */
	infile = fopen(input_file,"rb");
	if( infile==NULL )
	{
		fprintf(stderr,"Unable to open input file %s\n",input_file);
		exit(1);
	}

	/* read the magic number, the first 8 bytes (SIGSIZE) of storage in the file */
    fread(header, sizeof(unsigned char), SIGSIZE, infile);
		/* check the header */
    if( png_sig_cmp(header, 0, SIGSIZE) )
	{
		fprintf(stderr,"File %s isn't recognized as a PNG image",input_file);
		fclose(infile);
		exit(1);
	}

    /* initialize and allocate the png_struct and png_info structures */
    png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    info_ptr = png_create_info_struct(png_ptr);
    if( png_ptr==NULL || info_ptr==NULL )
	{
		fprintf(stderr,"Initialization error\n");
		fclose(infile);
		exit(1);
	}

	/* tell libpng about the open image file */
    png_init_io(png_ptr, infile);
		/* remind the library that 8 (SIGSIZE) bytes have been read */
    png_set_sig_bytes(png_ptr, SIGSIZE);
		/* fill the structures */
    png_read_info(png_ptr, info_ptr);

	/* obtain image info */
    width = png_get_image_width(png_ptr, info_ptr);
    height = png_get_image_height(png_ptr, info_ptr);
    color_type = png_get_color_type(png_ptr, info_ptr);
    bit_depth = png_get_bit_depth(png_ptr, info_ptr);
    number_of_passes = png_set_interlace_handling(png_ptr);
    png_read_update_info(png_ptr, info_ptr);

    /* read file */
		/* allow error handle a chance to break out */
    if ( setjmp(png_jmpbuf(png_ptr)) )
	{
		fprintf(stderr,"Error setting jump\n");
		fclose(infile);
		exit(1);
	}
		/* allocate storage for each row of image data */
    row_pointers = (png_bytep *)malloc(sizeof(png_bytep) * height);
	if( row_pointers==NULL )
	{
		fprintf(stderr,"Unable to allocate row pointers\n");
		fclose(infile);
		exit(1);
	}
		/* assign values to the row pointers */
    for(y=0;y<height;y++)
	{
        *(row_pointers+y) = (png_byte *)malloc(png_get_rowbytes(png_ptr,info_ptr));
	}
		/* read the image data */
    png_read_image(png_ptr, row_pointers);
		/* output info */
	printf("PNG image file %s read into memory\n",input_file);
	printf("Image is %d pixels wide by %d pixels tall\n",width,height);

	/* cleanup */
    	/* cleanup heap allocation */
    for (y=0; y<height; y++)
	{
        free(row_pointers[y]);
	}
    free(row_pointers);
		/* and close the file */
    fclose(infile);

	return(0);
}

