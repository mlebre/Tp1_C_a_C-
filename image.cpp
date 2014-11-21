# include "image.h"
# include <math.h>
# include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

image::image(void)
{
  height=0;
  width=0;
  pix=NULL;
}

int image::Get_height(void) const
{
  return height;
}

int image::Get_width(void) const
{
  return width;
}





//===========================================================================================
//                                  Methods which use pictures
//===========================================================================================
// Read the image contained in plain RGB ppm file <file>
// into <data> and set <width> and <height> accordingly
// Warning: data is malloc_ed, don't forget to free it
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

