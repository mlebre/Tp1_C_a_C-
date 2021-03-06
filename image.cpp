#include "image.h"
#include <math.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//===========================================================================================
//                                     Constructors 
//===========================================================================================

// Constructor of default
image::image(void)
{
  height=0;
  width=0;
  pix=NULL;
}

//Copy constructor 
image::image(const image& model)
{
  width=model.Get_width();
  height=model.Get_height();
  pix=new u_char [3 * (height) * (width)];
  memcpy(pix, model.Get_pix(), 3* (height) * (width) * sizeof(*pix));
}


//===========================================================================================
//                                     Destructors 
//===========================================================================================
image::~image(void)
{
  delete [] pix;
  pix=NULL;
}


//===========================================================================================
//                                     Getters 
//===========================================================================================


int image::Get_height(void) const
{
  return height;
}

int image::Get_width(void) const
{
  return width;
}

u_char * image::Get_pix(void) const
{
  return pix;
}



//===========================================================================================
//                                  Methods which use pictures
//===========================================================================================
// Read the image contained in plain RGB ppm file <file>
// into <data> and set <width> and <height> accordingly
// Warning: data is new_ed, don't forget to free it
void image::ppm_read_from_file(const char * title)
{
  FILE * fi=NULL;
  fi=fopen(title, "rb");

  //Make sure that picture sent exists
  if(fi!=NULL)
  {
  // Read file header
  fscanf(fi, "P6\n%d %d\n255\n", &width, &height);

  // Allocate memory according to width and height
  pix = new u_char [3 * (width) * (height)];
  // Read the actual image data
  fread(pix, 3, (width) * (height), fi);
  fclose(fi);
  }
  else
  {
    printf("Undefine reference to %s \n", title);
  }
}

// Desaturate (transform to B&W) <image> (of size <width> * <height>)
void image::ppm_desaturate(void)
{
	 int x, y;

  // For each pixel ...
  for (x = 0 ; x < width ; x++)
  {
    for (y = 0 ; y < height ; y++)
    {
      u_int grey_lvl = 0;
      int rgb_canal;

      // Compute the grey level
      for (rgb_canal = 0 ; rgb_canal < 3 ; rgb_canal++)
      {
        grey_lvl += pix[ 3 * (y * width + x) + rgb_canal ];
      }
      grey_lvl /= 3;
      assert(grey_lvl >= 0 && grey_lvl <=255);

      // Set the corresponding pixel's value in new_image
      memset(&pix[3 * (y * width + x)], grey_lvl, 3);
    }
  }
}

// Write the image contained in <data> (of size <width> * <height>)
// into plain RGB ppm file <file>
void image::ppm_write_to_file(const char *title)
{
  FILE *fi=NULL;
  fi=fopen(title, "wb");

  //Make sure that name matches to a real picture
  if(fi!=NULL)
  {
    // Write header
    fprintf(fi, "P6\n%d %d\n255\n", width, height);

    // Write pixels
    fwrite(pix, 3, width*height, fi);
    fclose(fi);
  }

}

// Shrink image (of original size <width> * <height>) by factor <factor>
// <width> and <height> are updated accordingly
void image::ppm_shrink(const int factor)
{
// Compute new image size and allocate memory for the new image
  int new_width   = (width) / factor;
  int new_height  = (height) / factor;
  u_char* new_image = new u_char [3 * (new_width) * (new_height) ];

  // Precompute factor^2 (for performance reasons)
  int factor_squared = factor * factor;

  // For each pixel of the new image...
  int x, y;
  for (x = 0 ; x < new_width ; x++)
  {
    for (y = 0 ; y < new_height ; y++)
    {
      // ... compute the average RGB values of the set of pixels (a square of side factor)
      // that correspond to the pixel we are creating.

      // Initialize RGB values for the new image's pixel
      u_int red   = 0;
      u_int green = 0;
      u_int blue  = 0;

      // Compute coordinates and index of the first (top-left) pixel from the
      // model image corresponding to the pixel we are creating
      int x0 = x * factor;
      int y0 = y * factor;
      int i0 = 3 * (y0 * (width) + x0);

      // Compute RGB values for the new pixel
      int dx, dy;
      for (dx = 0 ; dx < factor ; dx++)
      {
        for (dy = 0 ; dy < factor ; dy++)
        {
          // Compute the offset of the current pixel (in the model image)
          // with regard to the top-left pixel of the current "set of pixels"
          int delta_i = 3 * (dy * (width) + dx);
//Segmentation fault
          // Accumulate RGB values
          red   += (pix)[i0+delta_i];     
          green += (pix)[i0+delta_i+1];
          blue  += (pix)[i0+delta_i+2];
        }
      }

      // Divide RGB values to get the mean values
      red   /= factor_squared;
      green /= factor_squared;
      blue  /= factor_squared;

      // Set new pixel's RGB values
      new_image[ 3 * (y * new_width + x) ]     = red;
      new_image[ 3 * (y * new_width + x) + 1 ] = green;
      new_image[ 3 * (y * new_width + x) + 2 ] = blue;
    }
  }

  // Update image size
  width  = new_width;
  height = new_height;

  // Update image
  delete [] pix;
  pix = new_image;

}