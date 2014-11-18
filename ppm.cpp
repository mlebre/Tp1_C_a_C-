#include <cstdio>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ppm_file.h"



//============================================================================
//                            Struct declaration
//============================================================================

typedef struct 
{
  int height;
  int width;
  u_char * image;

} img;





//============================================================================
//                                  Main
//============================================================================
int main(int argc, char* argv[])
{
  //--------------------------------------------------------------------------
  // Read file "gargouille.ppm" into image (width and height)
  //--------------------------------------------------------------------------
  img photo;
  char name[20]="gargouille.ppm";
  photo.image = NULL;
  ppm_read_from_file(name,photo.width, photo.height, &photo.image);

  //--------------------------------------------------------------------------
  // Create a desaturated (B&W) copy of the image we've just read and
  // write it into "gargouille_BW.ppm"
  //--------------------------------------------------------------------------
  // Copy image into image_bw
  img photo_bw;
  photo_bw.width=photo.width;
  photo_bw.height=photo.height;
  photo_bw.image=  new u_char [3 * photo_bw.width * photo_bw.height];
  memcpy(photo_bw.image, photo.image, 3 * photo_bw.width * photo_bw.height);

  // Desaturate image_bw
  ppm_desaturate(photo_bw.image, photo_bw.width, photo_bw.height);

  // Write the desaturated image into "gargouille_BW.ppm"
  char name_bw[30]="gargouille_BW.ppm";
  ppm_write_to_file(name_bw, photo_bw.width, photo_bw.height, photo_bw.image);
  // Free the desaturated image
  free(photo_bw.image);


  //--------------------------------------------------------------------------
  // Create a resized copy of the image and
  // write it into "gargouille_small.ppm"
  //--------------------------------------------------------------------------
  // Copy image into image_small
  img photo_small;
  photo_small.width= photo.width;
  photo_small.height= photo.height;
  photo_small.image= new u_char [3 * photo_small.width * photo_small.height];
  memcpy(photo_small.image, photo.image, 3 * photo_small.width * photo_small.height * sizeof(*photo_small.image));

  // Shrink image_small size 2-fold
  ppm_shrink(&photo_small.image, photo_small.width, photo_small.height, 2);

  // Write the desaturated image into "gargouille_small.ppm"
  char name_small[30]="gargouille_small.ppm";
  ppm_write_to_file(name_small, photo_small.width, photo_small.height, photo_small.image);

  // Free the not yet freed images
  delete(photo.image);
  delete(photo_small.image);

  return 0;
}



//============================================================================
//                           Function declarations
//============================================================================





































