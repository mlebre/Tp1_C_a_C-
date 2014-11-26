#include <cstdio>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "image.h"


//============================================================================
//                                  Main
//============================================================================
int main(int argc, char* argv[])
{
  //--------------------------------------------------------------------------
  // Read file "gargouille.ppm" into image (width and height)
  //--------------------------------------------------------------------------
  image photo=image();
  char name[]="gargouille.ppm";

  photo.ppm_read_from_file(name);


  //--------------------------------------------------------------------------
  // Create a desaturated (B&W) copy of the image we've just read and
  // write it into "gargouille_BW.ppm"
  //--------------------------------------------------------------------------
  // Copy image into image_bw
  image photo_bw=image(photo);


  // Desaturate image_bw
  photo_bw.ppm_desaturate();

  // Write the desaturated image into "gargouille_BW.ppm"
  char name_bw[]="gargouille_BW.ppm"; 
  photo_bw.ppm_write_to_file(name_bw);

  // Free the desaturated image
  delete(photo_bw.Get_pix());


  //--------------------------------------------------------------------------
  // Create a resized copy of the image and
  // write it into "gargouille_small.ppm"
  //--------------------------------------------------------------------------
  // Copy image into image_small
  image photo_small=image(photo);

  // Shrink image_small size 2-fold
  photo_small.ppm_shrink(2);

  // Write the small image into "gargouille_small.ppm"
  char name_small[]="gargouille_small.ppm";
  photo_small.ppm_write_to_file(name_small);

  // Free the not yet freed images
  delete(photo_small.Get_pix());
  delete(photo.Get_pix());

  return 0;
}

