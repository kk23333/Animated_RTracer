//
// Created by KK on 16/9/15.
//

#ifndef RTRACER_TEXTURE_H
#define RTRACER_TEXTURE_H


/*----------------------------------------------------------------------
  File:    texture.h
  Purpose: Stuff concerning textures
           reads PPM files (only in P6 format, i.e., RGB binary)
----------------------------------------------------------------------*/

struct Texture
{
    int mWidth;
    int mHeight;
    unsigned char *mRGB; /* the size is 3*mWidth*mHeight */
};

struct Texture *viReadPPM(char *filename);
int viWritePPM(char *filename, int width, int height, unsigned char *pixels);





#endif //RTRACER_TEXTURE_H
