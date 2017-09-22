#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include <glheader.h>

#include <iostream>
class FrameBuffer
{
    public:
    GLuint m_ID = 0;

    GLuint m_Texture;
    GLuint m_DepthTexture;
    GLuint m_DepthBuffer;


    FrameBuffer();

    void genBuffer();
    void clearBuffer();

    void bind();
    void unBind();

    void createTextureAttachment(int width, int height);
    void createDepthTextureAttachment(int width, int height);
    void createDepthBufferAttachment(int width, int height);

    void checkError();

    void initReflection(int width, int height);
};



#endif // FRAMEBUFFER_H
