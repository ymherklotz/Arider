#include "glsl_program.hpp"

#include <fstream>
#include <stdexcept>
#include <vector>

GlslProgram::GlslProgram()
{}

GlslProgram::~GlslProgram()
{
    if(fragment_shader_id_ != 0)
	glDeleteShader(fragment_shader_id_);
    
    if(vertex_shader_id_ != 0)
	glDeleteShader(vertex_shader_id_);
    
    if(program_id_ != 0)
	glDeleteProgram(program_id_);
}

void GlslProgram::compileShader(const GLuint &shader, const std::string &file_path)
{
    std::ifstream file(file_path);
    if(!file.is_open())
	throw std::runtime_error("Failed to open '"+file_path+"'");

    std::string content = "";
    std::string line;

    while(std::getline(file, line))
	content+=line+"\n";
    file.close();

    const char *vertex_char = content.c_str();
    glShaderSource(shader, 1, &vertex_char, nullptr);
    glCompileShader(shader);

    GLint is_compiled = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &is_compiled);

    if(is_compiled == GL_FALSE)
    {
	GLint max_length = 0;
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &max_length);
 
	std::vector<char> error_log(max_length);
	glGetShaderInfoLog(shader, max_length, &max_length, &error_log[0]);
	std::string error_log_str(&error_log[0]);
	
	throw std::runtime_error("Couldn't compile "+file_path+" : "+error_log_str);
    }
}

void GlslProgram::compileShaders(const std::string &vertex_shader_path, const std::string &fragment_shader_path)
{
    // create the program that will be run on GPU
    program_id_ = glCreateProgram();
    
    vertex_shader_id_ = glCreateShader(GL_VERTEX_SHADER);
    if(vertex_shader_id_ == 0)
	throw std::runtime_error("Vertex shader failed to be created");
    
    fragment_shader_id_ = glCreateShader(GL_VERTEX_SHADER);
    if(fragment_shader_id_ == 0)
	throw std::runtime_error("Fragment shader failed to be created");

    std::string vertex_shader_content;
    std::string fragment_shader_content;

    compileShader(vertex_shader_id_, vertex_shader_path);
    compileShader(fragment_shader_id_, fragment_shader_path);    
}
