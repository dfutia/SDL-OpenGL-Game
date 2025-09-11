#include "platform/gl/glrenderer.h"

#include <print>

GLShader::GLShader(GLenum type, const char* code)
{
	mShaderId = glCreateShader(type);

	glShaderSource(mShaderId, 1, &code, nullptr);
	glCompileShader(mShaderId);

	GLint success;

	glGetShaderiv(mShaderId, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		char infoLog[512];
		glGetShaderInfoLog(mShaderId, 512, nullptr, infoLog);
		std::printf("ERROR::SHADER::COMPILATION_FAILED\n%s\n", infoLog);
	}
}

GLShader::~GLShader()
{
	glDeleteShader(mShaderId);
}

GLProgram::GLProgram(GLShader* vertexShader, GLShader* fragmentShader)
{
	mProgramId = glCreateProgram();
	glAttachShader(mProgramId, vertexShader->getResourceID());
	glAttachShader(mProgramId, fragmentShader->getResourceID());
	glLinkProgram(mProgramId);

	GLint success;
	glGetProgramiv(mProgramId, GL_LINK_STATUS, &success);
	if (!success)
	{
		char infoLog[512];
		glGetProgramInfoLog(mProgramId, 512, nullptr, infoLog);
		std::printf("ERROR::PROGRAM::LINKING_FAILED\n%s\n", infoLog);
	}
}

GLProgram::~GLProgram()
{
	glDeleteProgram(mProgramId);
}