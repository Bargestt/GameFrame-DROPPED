#include "texturebase.h"

TextureBase::TextureBase():
    _width( 0 ),
    _height( 0 ),
    _format( GL_RGB ),

    Wrap_S( GL_REPEAT ),
    Wrap_T( GL_REPEAT ),

    Filter_Min ( GL_LINEAR ),
    Filter_Max( GL_LINEAR )
{
    glGenTextures(1,&_ID);
}
TextureBase::TextureBase(unsigned int wrap_S, unsigned int wrap_T, unsigned int filter_Min, unsigned int filter_Max):
    _width(0),
    _height(0),
    _format(GL_RGB),

    Wrap_S(wrap_S),
    Wrap_T(wrap_T),

    Filter_Min(filter_Min),
    Filter_Max(filter_Max)
{
    glGenTextures(1,&_ID);
}


void TextureBase::bind() const
{
    glBindTexture(GL_TEXTURE_2D,_ID);
}

void TextureBase::clearData()
{
    glDeleteTextures(1,&_ID);
    _width =0;
    _height =0;
    _ID = 0;
}



//=======================

unsigned int TextureBase::id()
{
    return _ID;
}

int TextureBase::width()const
{
    return _width;
}

int TextureBase::height()const
{
    return _height;
}

GLenum TextureBase::format() const
{
    return _format;
}

void TextureBase::setFormat(unsigned int wrap_S, unsigned int wrap_T, unsigned int filter_Min, unsigned int filter_Max)
{
    Wrap_S = wrap_S;
    Wrap_T= wrap_T;
    Filter_Min= filter_Min;
    Filter_Max= filter_Max;
}

unsigned int TextureBase::wrapSaxis()
{
    return Wrap_S;
}
unsigned int TextureBase::wrapTaxis()
{
    return Wrap_T;
}
unsigned int TextureBase::filterMin()
{
    return Filter_Min;
}
unsigned int TextureBase::filterMax()
{
    return Filter_Max;
}
