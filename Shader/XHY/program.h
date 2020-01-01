#pragma once

#include<vector>

#include"../global.h"
#include"../GL/gl_core_4_3.h"

__XHY_BEGIN

struct ShaderInfo
{
	ShaderInfo(GLenum _type, const String& _path, const String& _description):
		type(_type), path(_path), description(_description)
	{}
	GLenum type;
	String path;
	String description;
};

class Program
{
public:
	using ShaderVec = std::vector<ShaderInfo>;

	Program(const ShaderVec& shaders);

	~Program();

	void Use()
	{
		glUseProgram(m_program);
	}

private:
	GLint m_program;

	GLint CompileShader(const ShaderInfo& shader_info);

	bool CheckCompileResult(GLuint shader, const String& description);
	bool CheckLinkResult(GLuint program);
private:
	Program(const Program&) = delete;
	Program& operator=(const Program&) = delete;
};

__XHY_END
