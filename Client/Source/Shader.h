#ifndef SHADER_H
#define SHADER_H

#include "stdafx.h"


// General purpsoe shader object. Compiles from file, generates
// compile/link-time error messages and hosts several utility 
// functions for easy management.
class Shader
{
public:
	// State
	GLuint ID;
	// Constructor
	Shader() { }
	// Sets the current shader as active
	Shader  &Use();
	// Compiles the shader from given source code
	void    Compile(const GLchar *vertexSource, const GLchar *fragmentSource, const GLchar *geometrySource = nullptr); // Note: geometry source code is optional 
	void    SetBool(const GLchar *name, GLboolean value, GLboolean useShader = false);																										   // Utility functions
	void    SetFloat(const GLchar *name, GLfloat value, GLboolean useShader = false);
	void    SetInteger(const GLchar *name, GLint value, GLboolean useShader = false);
	void    SetVector2f(const GLchar *name, GLfloat x, GLfloat y, GLboolean useShader = false);
	void    SetVector2f(const GLchar *name, const glm::vec2 &value, GLboolean useShader = false);
	void    SetVector3f(const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLboolean useShader = false);
	void    SetVector3f(const GLchar *name, const glm::vec3 &value, GLboolean useShader = false);
	void    SetVector4f(const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLfloat w, GLboolean useShader = false);
	void    SetVector4f(const GLchar *name, const glm::vec4 &value, GLboolean useShader = false);
	void    SetMatrix4(const GLchar *name, const glm::mat4 &matrix, GLboolean useShader = false);
	void    SetVectorOfVector2f(const GLchar *name, const std::vector<glm::vec2>& vectors, GLboolean useShader = false);
	void    SetVectorOfVector3f(const GLchar *name, const std::vector<glm::vec3>& vectors, GLboolean useShader = false);
	void    SetVectorOfVector4f(const GLchar *name, const std::vector<glm::vec4>& vectors, GLboolean useShader = false);
	void	SetTextureLocation(const GLchar *name, GLuint value);
private:
	// Checks if compilation or linking failed and if so, print the error logs
	void    checkCompileErrors(GLuint object, std::string type);
};

#endif
