#include <stdio.h>
#include <stdlib.h>
#include <png.h>

#define SIGSIZE 8

/* structure to hold pixel data */
struct png_pixel {
	png_byte red;
	png_byte green;
	png_byte blue;
	png_byte alpha;
};

int main(int argc, char **argv)
{
	char input_file[] = "05_05-image1.png";
	char output_file[] = "05_05-image1-copy.png";
	FILE *infile,*outfile;
	unsigned char header[8];
	png_structp png_ptr;
	png_infop info_ptr;
	int x,y,width,height,number_of_passes;
	png_byte color_type,bit_depth;
	png_bytep *row_pointers;
	/* variables for drawing pixels */
	struct png_pixel black = { 0, 0, 0, 255 };
	struct png_pixel white = { 255, 255, 255, 255 };
	struct png_pixel *pixel_ptr;
	png_byte *current_row;

	/* open the png file */
	infile = fopen(input_file,"rb");
	if( infile==NULL )
	{
		fprintf(stderr,"Unable to open input file %s\n",input_file);
		exit(1);
	}

	/* read the magic number, the first 8 bytes (SIGSIZE) of storage in the file */
    fread(header, sizeof(unsigned char), SIGSIZE, infile);
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
    png_set_sig_bytes(png_ptr, SIGSIZE);
    png_read_info(png_ptr, info_ptr);

	/* obtain image info */
    width = png_get_image_width(png_ptr, info_ptr);
    height = png_get_image_height(png_ptr, info_ptr);
    color_type = png_get_color_type(png_ptr, info_ptr);
    bit_depth = png_get_bit_depth(png_ptr, info_ptr);
    number_of_passes = png_set_interlace_handling(png_ptr);
    png_read_update_info(png_ptr, info_ptr);

    /* read file */
    if ( setjmp(png_jmpbuf(png_ptr)) )
	{
		fprintf(stderr,"Error setting jump at Line %d\n",__LINE__);
		fclose(infile);
		exit(1);
	}
    row_pointers = (png_bytep *)malloc(sizeof(png_bytep) * height);
	if( row_pointers==NULL )
	{
		fprintf(stderr,"Unable to allocate row pointers\n");
		fclose(infile);
		exit(1);
	}
    for(y=0;y<height;y++)
	{
        *(row_pointers+y) = (png_byte *)malloc(png_get_rowbytes(png_ptr,info_ptr));
	}
    png_read_image(png_ptr, row_pointers);

	/* done with the input file */
    fclose(infile);

	/* image is stored in memory at row_pointers */

	/* confirm that image is of the right type for manipulation */
	if( color_type!=PNG_COLOR_TYPE_RGBA )
	{
		fprintf(stderr,"%s must be color type RGBA\n",input_file);
		exit(1);
	}

	/* draw a big X on the image using two colors */
		/* the X is symmetrical, assuming that the width>height */
	x = (width-height)>>1;
	for( y=2; y<height-2; y++ )
	{
		current_row = *(row_pointers+y);
		pixel_ptr = (struct png_pixel *)(current_row);
		if( x > width-2 )
			break;
		*(pixel_ptr+x) = black;
		*(pixel_ptr+x-1) = white;
		*(pixel_ptr+width-x) = black;
		*(pixel_ptr+width-x-1) = white;
		x++;
	}

	/* create output file */
	outfile = fopen(output_file,"wb");
	if( outfile==NULL )
	{
		fprintf(stderr,"Unable to create output file %s\n",output_file);
		exit(1);
	}

	/* initialize data structures for output */
	png_ptr = png_create_write_struct( PNG_LIBPNG_VER_STRING, NULL, NULL, NULL );
	info_ptr = png_create_info_struct( png_ptr );
    if( png_ptr==NULL || info_ptr==NULL )
	{
		fprintf(stderr,"Initialization error\n");
		fclose(outfile);
		exit(1);
	}
		/* hook the data into the open file */
	png_init_io( png_ptr, outfile );
	if( setjmp( png_jmpbuf(png_ptr)) )
	{
		fprintf(stderr,"Error stting jump at Line %d\n",__LINE__);
		fclose(outfile);
		exit(1);
	}

	/* output image data */
	png_set_IHDR( png_ptr, info_ptr, width, height,
					bit_depth, color_type, PNG_INTERLACE_NONE,
					PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE
			);
	png_write_info( png_ptr, info_ptr );
	png_write_image( png_ptr, row_pointers );
	if( setjmp( png_jmpbuf(png_ptr)) )
	{
		fprintf(stderr,"Error stting jump at Line %d\n",__LINE__);
		fclose(outfile);
		exit(1);
	}
	png_write_end( png_ptr, NULL );

	/* cleanup */
	fclose(outfile);
    for(y=0;y<height;y++)
	{
        free( *(row_pointers+y) );
	}
    free(row_pointers);
	printf("Duplicate image file %s created\n",output_file);

	return(0);
}

