#pragma once
#include "Texture2D.h"
/**
* A very thin wrapper around OpenGL Frame Buffer Objects, intended for
* 2D purposes. This uses GL_FRAMEBUFFER_EXT for GL 2.1 compatibility.
*
* @author davedes
*/
class FrameBuffer :
	public Texture2D
{
public:
	FrameBuffer();
	~FrameBuffer();

	/** The ID of the FBO in use */
	GLuint id;
	Texture2D texture;
	bool ownsTexture;

	FrameBuffer(Texture2D texture) 
	{
		this->texture = texture;
		this->ownsTexture = ownsTexture;

		texture.Bind();
		glGenFramebuffersEXT(1, &id);
		glBindFramebufferEXT(GL_FRAMEBUFFER, id);
		glFramebufferTexture2DEXT(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
			0, texture.ID, 0);
		int result = glCheckFramebufferStatusEXT(GL_FRAMEBUFFER);
		if (result != GL_FRAMEBUFFER_COMPLETE) {
			glBindFramebufferEXT(GL_FRAMEBUFFER, 0);
			glDeleteFramebuffers(1, &id);
		}
		glBindFramebufferEXT(GL_FRAMEBUFFER, 0);
	}
};


