#ifndef TEXTUREBASE_H
#define TEXTUREBASE_H

#include <glheader.h>

#include <iostream>

#include <stb_image.h>

class TextureBase
{
public:
    TextureBase();
    TextureBase(unsigned int wrap_S, unsigned int wrap_T, unsigned int filter_Min, unsigned int filter_Max);

    virtual void bind() const;

protected:
    unsigned int _ID;
    int _width;
    int _height;

   GLenum _format;

   GLuint Wrap_S; // Wrapping mode on S axis
   GLuint Wrap_T; // Wrapping mode on T axis
   GLuint Filter_Min; // Filtering mode if texture pixels < screen pixels
   GLuint Filter_Max; // Filtering mode if texture pixels > screen pixels

   void clearData();

public:
    //===========Interface================

    unsigned int id();
    int width() const;
    int height() const;

    GLenum format() const;

    void setFormat(unsigned int wrap_S, unsigned int wrap_T, unsigned int filter_Min, unsigned int filter_Max);
    unsigned int wrapSaxis();
    unsigned int wrapTaxis();
    unsigned int filterMin();
    unsigned int filterMax();

};

#endif // TEXTUREBASE_H
