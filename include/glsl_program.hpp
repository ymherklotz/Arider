#ifndef GLSL_PROGRAM_HPP
#define GLSL_PROGRAM_HPP

#include <GL/glew.h>
#include <string>

class GlslProgram
{
private:
    GLuint program_id_ = 0;
    GLuint vertex_shader_id_ = 0;
    GLuint fragment_shader_id_ = 0;

    void compileShader(const GLuint &shader, const std::string &file_path);
public:
    GlslProgram();
    ~GlslProgram();

    void compileShaders(const std::string &vertex_shader_path, const std::string &fragment_shader_path);
    void linkShaders();
};


#endif
