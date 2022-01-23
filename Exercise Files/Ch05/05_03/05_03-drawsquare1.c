#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <jpeglib.h>

/* square to place in the image */
struct square {
	unsigned char *buffer;	/* raw image data */
	struct jpeg_decompress_struct info;	/* structure referencing image data */
	/* box coordinates */
	int row;
	int col;
	int width;
	int height;
};
/* pixel reference for scanline/row data */
struct color {
	unsigned char r;
	unsigned char g;
	unsigned char b;
};

/* given the square structure and color value, draw a square
   in the raw image data */
void draw_square(struct square bc,struct color c)
{
	unsigned char *top_row_base,*bottom_row_base;
	int tbref,lref,rref;
	int i; 

	/* column is three times wider given the number of bytes per pixel */
	bc.col *= 3;
	top_row_base = bc.buffer+(bc.info.output_width * 3 * bc.row);
	bottom_row_base = bc.buffer+(bc.info.output_width * 3 * (bc.row+bc.height));
	/* draw the top and bottom lines */
	for(i=0; i<bc.width*3; i+=3)
	{
		tbref = bc.col+i;
		/* top */
		*(top_row_base+tbref+0) = c.r;			/* red */
		*(top_row_base+tbref+1) = c.g;			/* green */
		*(top_row_base+tbref+2) = c.b;			/* blue */
		/* bottom */
		*(bottom_row_base+tbref+0) = c.r;		/* red */
		*(bottom_row_base+tbref+1) = c.g;		/* green */
		*(bottom_row_base+tbref+2) = c.b;		/* blue */
	}
	/* draw the left and right sides */
	for(i=0;i<bc.height;i++)
	{
		lref = bc.info.output_width*3*i+bc.col;
		rref = bc.info.output_width*3*i+bc.col+bc.width*3;
		/* left */
		*(top_row_base+lref+0) = c.r;			/* red */
		*(top_row_base+lref+1) = c.g;			/* green */
		*(top_row_base+lref+2) = c.b;			/* blue */
		/* right */
		*(top_row_base+rref+0) = c.r;			/* red */
		*(top_row_base+rref+1) = c.g;			/* blue */
		*(top_row_base+rref+2) = c.b;			/* green */
	}	
}

/* draw three nested boxes */
void highlight_square(struct square b)
{
	/* configure pixel color data */
	struct color black = { 0, 0, 0 };
	struct color white = { 255, 255, 255 };

	/* check bounds */
	if(b.col+b.width > b.info.output_width || b.row+b.height > b.info.output_height)
	{
		fprintf(stderr,"Square is off the grid\n");
		exit(1);
	}
	/* check box size */
	if(b.width < 10 || b.height < 10)
	{
		fprintf(stderr,"Square is too small\n");
		exit(1);
	}

	/* draw the outer box */
	draw_square(b,black);
	/* resize for the middle box */
	b.row++;
	b.col++;
	b.width-=2;
	b.height-=2;
	/* draw middle box */
	draw_square(b,white);
	/* resize for the center box */
	b.row++;
	b.col++;
	b.width-=2;
	b.height-=2;
	/* draw center box */
	draw_square(b,black);
}

/* main function - similar to other jpeg reading/writing examples */
int main(int argc, char *argv[])
{
	char input_file[] = "05_03-image1.jpg";
	char output_file[] = "05_03-image1-box.jpg";
	FILE *original,*boxcopy;
	struct jpeg_decompress_struct dcinfo;
	struct jpeg_compress_struct cinfo;
	struct jpeg_error_mgr dcjerr,cjerr;
	unsigned char *raw_image;
	JSAMPROW row_pointer[1];
	int row_stride,width,height,bytes_per_pixel;
	struct square box;

	/* read input file */
	original = fopen(input_file,"rb");
	if( original==NULL )
	{
		fprintf(stderr,"Unable to read image file %s\n",input_file);
		exit(1);
	}
	
	/* configure for decompression */
	dcinfo.err = jpeg_std_error(&dcjerr);
	jpeg_create_decompress(&dcinfo);
	jpeg_stdio_src(&dcinfo,original);
	jpeg_read_header(&dcinfo,TRUE);

	/* decompress the image file */
	jpeg_start_decompress(&dcinfo);

	/* gather basic info */
	width = dcinfo.output_width;
	height = dcinfo.output_height;
	bytes_per_pixel = dcinfo.output_components;
	/* confirm that image is in color */
	if( bytes_per_pixel != 3 )
	{
		fprintf(stderr,"This program works only on color JPEG images\n");
		fclose(original);
		exit(1);
	}
	
	/* create buffer for the uncompressed data */
	raw_image = (unsigned char *)malloc( bytes_per_pixel * width * height );
	if(raw_image==NULL)
	{
		fprintf(stderr,"Unable to allocate memory for image\n");
		fclose(original);
		exit(1);
	}
	
	/* loop to read each scanline */
	row_stride = width * bytes_per_pixel;
	while(dcinfo.output_scanline < dcinfo.output_height)
	{
		row_pointer[0] = &raw_image[dcinfo.output_scanline*row_stride];
		jpeg_read_scanlines(&dcinfo,row_pointer,1);
	}

	/* raw image is stored in the buffer raw_image */

	/* cleanup decompression and close */
	jpeg_finish_decompress(&dcinfo);
	jpeg_destroy_decompress(&dcinfo);
	fclose(original);

	/* Draw a box at a given location */
	box.buffer = raw_image;
	box.info = dcinfo;
	box.row = 200;
	box.col = 550;
	box.width = 465;
	box.height = 465;
	highlight_square(box);

	
	/* compress the modified raw image and save it to the output file */

	/* open output file */
	boxcopy = fopen(output_file,"wb");
	if( boxcopy==NULL )
	{
		fprintf(stderr,"Unable to create output image file %s\n",output_file);
		exit(1);
	}

	/* configure for compression */
	cinfo.err = jpeg_std_error(&cjerr);
	jpeg_create_compress(&cinfo);
	jpeg_stdio_dest(&cinfo,boxcopy);
	cinfo.image_width = width;
	cinfo.image_height = height;
	cinfo.input_components = bytes_per_pixel;
	cinfo.in_color_space = JCS_RGB;
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
	fclose(boxcopy);
	free(raw_image);
	printf("Output file '%s' created\n",output_file);

	return(0);
}

