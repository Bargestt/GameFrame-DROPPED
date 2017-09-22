#include "framebuffer.h"




FrameBuffer::FrameBuffer()
{

}

void FrameBuffer::genBuffer()
{
    if(m_ID != 0)
        clearBuffer();
    glGenFramebuffers(1, &m_ID);
    glBindFramebuffer(GL_FRAMEBUFFER, m_ID);
}

void FrameBuffer::clearBuffer()
{
    glDeleteFramebuffers(1, &m_ID);
    glDeleteTextures(1, &m_Texture);
    glDeleteTextures(1, &m_DepthTexture);
    glDeleteRenderbuffers(1, &m_DepthBuffer);
}

void FrameBuffer::bind()
{
    glBindFramebuffer(GL_FRAMEBUFFER, m_ID);
}

void FrameBuffer::unBind()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FrameBuffer::createTextureAttachment( int width, int height)
{
    if(m_Texture != 0)
        glDeleteTextures(1, &m_Texture);
    glGenTextures(1, &m_Texture);
    glBindTexture(GL_TEXTURE_2D, m_Texture);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_Texture, 0);
}

void FrameBuffer::createDepthTextureAttachment(int width, int height)
{
    if(m_Texture != 0)
        glDeleteTextures(1, &m_DepthTexture);
    glGenTextures(1, &m_DepthTexture);
    glBindTexture(GL_TEXTURE_2D, m_DepthTexture);

    glTexImage2D(
                  GL_TEXTURE_2D, 0,
                  GL_DEPTH_COMPONENT32,
                  width, height, 0,
                  GL_DEPTH_COMPONENT,
                  GL_FLOAT, NULL);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_DepthTexture, 0);

}

void FrameBuffer::createDepthBufferAttachment(int width, int height)
{
    if(m_DepthBuffer != 0)
        glDeleteRenderbuffers(1, &m_DepthBuffer);
    glGenRenderbuffers(1, &m_DepthBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, m_DepthBuffer);

    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH, width, height);

    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH, GL_RENDERBUFFER, m_DepthBuffer);
}

void FrameBuffer::checkError()
{
    glBindFramebuffer(GL_FRAMEBUFFER, m_ID);
    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FrameBuffer::initReflection(int width, int height)
{
    genBuffer();
    createTextureAttachment(width, height);
    createDepthBufferAttachment(width, height);

    checkError();
}
