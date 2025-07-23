#pragma once
#include <GL/glew.h>
#include <GL/GL.h>
class ShaderLoader
{
	SINGLE(ShaderLoader)
private:
	GLuint m_ShaderID;
public:
	GET(GLuint, ShaderID)
	void init();
	GLuint LoadShaderFromFile(wstring vertexPath, wstring fragmentPath);
};

