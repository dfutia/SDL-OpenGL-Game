#include "platform/gl/glrenderer.h"

GLTexture::GLTexture(unsigned int width, unsigned int height, bool isCubeMap)
{
	mWidth = width;
	mHeight = height;
	mIsCubeMap = isCubeMap;

	glGenTextures(1, &mTextureId);

	glBindTexture(GL_TEXTURE_2D, mTextureId);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);


	glBindTexture(GL_TEXTURE_2D, 0);
}

GLTexture::~GLTexture()
{
	glDeleteTextures(1, &mTextureId);
}