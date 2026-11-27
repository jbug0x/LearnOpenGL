#include "shaderClass.h"

std::string get_file_contents(const char* filename)
{
	std::ifstream in(filename, std::ios::binary);
	if (in)
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}
	throw(errno);
}

Shader::Shader(const char* vertexFile, const char* fragmnetFile)
{
	std::string vertexCode = get_file_contents(vertexFile);
	std::string fragmnetCode = get_file_contents(fragmnetFile);
	
	const char* vertexSource = vertexCode.c_str();
	const char* fragmentSource = fragmnetCode.c_str();

	// Crete Vertex Shader Object and get reference
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	// Attach Vertex Shader source to the Vertex Shader Object
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	// Compile the Vertex Shader into machine code
	glCompileShader(vertexShader);

	// Crete Fragment Shader Object and get reference
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	// Attach Fragment Shader source to the Fragment Shader Object
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	// Compile the Fragment Shader into machine code
	glCompileShader(fragmentShader);

	// Create Shader Program Object and get reference
	ID = glCreateProgram();
	// Attach Vertex shader and Fragment 
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	// Wrap-up/link all the shaders together into the Shader Program
	glLinkProgram(ID);

	// Delete the now useleess Vertex and Fragment
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Shader::Activate() 
{
	// Tell OpenGL which Shader Program we want to use
	glUseProgram(ID);
}

void Shader::Delete()
{
	glDeleteProgram(ID);
}