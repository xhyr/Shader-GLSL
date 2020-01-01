#include "program.h"


#include<cassert>
#include<iostream>
#include<fstream>
#include<sstream>


__XHY_BEGIN

Program::Program(const ShaderVec& shaders)
{
	m_program = glCreateProgram();
	if (0 == m_program)
	{
		std::cerr << "[ERROR] creating program" << "!!!" << std::endl;
		exit(1);
	}
	for (const auto& shader_info : shaders)
	{
		GLint shader = CompileShader(shader_info);
		assert(shader != -1);
		glAttachShader(m_program, shader);
		glDeleteShader(shader);
	}
	glLinkProgram(m_program);
	bool success = CheckLinkResult(m_program);
	assert(success);
}


Program::~Program()
{
	if(glIsProgram(m_program))
		glDeleteProgram(m_program);
}

GLint Program::CompileShader(const ShaderInfo& shader_info)
{
	GLuint shader = glCreateShader(shader_info.type);
	if (0 == shader)
	{
		std::cerr << "[ERROR] creating " << shader_info.description <<"!!!"<< std::endl;
		return -1;
	}
	String code;
	std::ifstream code_file;
	code_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		code_file.open(shader_info.path);
		std::stringstream shader_stream;
		shader_stream << code_file.rdbuf();
		code_file.close();
		code = shader_stream.str();
	}
	catch (const std::ifstream::failure& e)
	{
		std::cerr << "[ERROR] shader file " << shader_info.path << "cann't be read!!!" << std::endl;
		return -1;
	}

	const char* code_str = code.c_str();
	glShaderSource(shader, 1, &code_str, NULL);
	glCompileShader(shader);
	CheckCompileResult(shader, shader_info.description);

	return shader;
}

bool Program::CheckCompileResult(GLuint shader, const String& description)
{
	GLint success = 0;
	char info[1024] = { 0 };
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader, 1024, NULL, info);
		std::cerr << "[ERROR] compiling shader " << description.c_str() << "\n" << info << std::endl;
	}
	return success;
}

bool Program::CheckLinkResult(GLuint program)
{
	GLint success = 0;
	char info[1024] = { 0 };
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(program, 1024, NULL, info);
		std::cerr << "[ERROR] linking program " << "\n" << info << std::endl;
	}
	return success;
}



__XHY_END