#include <fstream>
#include <string>

#include "logger.hpp"
#include "opengl.hpp"
#include "shaders.hpp"


namespace sgtr
{

Shaders::Shaders()
{
    read("vertex.glsl", this->vs_);
    read("fragment.glsl", this->fs_);

    compile();

    LOG(INFO) << "Shaders initialized";
}

void Shaders::read(const std::string& filename, std::string& stringbuf)
{
    std::ifstream fs{filename};

    if (!fs)
    {
        LOG(ERROR) << "Failed to open shader file: " << filename;
        throw std::runtime_error("Error during file opening");
    }

    std::string line;

    while (fs && !fs.eof())
    {
        line.clear();
        std::getline(fs, line);
        stringbuf += (line + std::string("\n"));
    }

    fs.close();

    LOG(INFO) << "Loaded shader " << filename;
}

void Shaders::add(GLenum type)
{
    GLuint ShaderObj = glCreateShader(type);

    if (ShaderObj == 0)
    {
        LOG(ERROR) << "Error creating shader object!";
        throw std::runtime_error("Error during shader adding");
    }

    const GLchar* text;
    switch (type)
    {
    case GL_VERTEX_SHADER:
        text = vs_.c_str();
        break;
    case GL_FRAGMENT_SHADER:
        text = fs_.c_str();
        break;
    default:
        LOG(ERROR) << "Unknown shader type";
        throw std::runtime_error("Unknown shader type!");
        break;
    }

    GLint len;
    len = strlen(text);

    glShaderSource(ShaderObj, 1, &text, &len);
    glCompileShader(ShaderObj);

    GLint success;
    glGetShaderiv(ShaderObj, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        GLchar InfoLog[1024];
        glGetShaderInfoLog(ShaderObj, 1024, NULL, InfoLog);

        LOG(ERROR) << "Error compiling shader. Check your driver";
        LOG(ERROR) << type << " || " << InfoLog;
        throw std::runtime_error("Shader failed to compile");
    }

    glAttachShader(pshader_, ShaderObj);
}

void Shaders::compile()
{
    pshader_ = glCreateProgram();

    if (!pshader_)
    {
        LOG(ERROR) << "Shader program build error";
        throw std::runtime_error("Shader program build error");
    }

    add(GL_VERTEX_SHADER);
    add(GL_FRAGMENT_SHADER);
    LOG(INFO) << "Shaders added to pipeline";

    GLint Success = 0;
    GLchar ErrorLog[1024] = {0};

    glLinkProgram(pshader_);
    glGetProgramiv(pshader_, GL_LINK_STATUS, &Success);

    if (!Success)
    {
        glGetProgramInfoLog(pshader_, sizeof(ErrorLog), NULL, ErrorLog);
        LOG(ERROR) << "Shader program link error";
        LOG(ERROR) << ErrorLog;
        throw std::runtime_error("Shader program link error");
    }

    glValidateProgram(pshader_);
    glGetProgramiv(pshader_, GL_VALIDATE_STATUS, &Success);

    if (!Success)
    {
        glGetProgramInfoLog(pshader_, sizeof(ErrorLog), NULL, ErrorLog);
        LOG(ERROR) << "Shader program incorrect, OpenGL validation fail";
        LOG(ERROR) << ErrorLog;
        throw std::runtime_error("OpenGL validation fail");
    }

    glUseProgram(pshader_);
}

GLuint Shaders::setUniform(const std::string& name)
{
    GLuint loc = glGetUniformLocation(pshader_, name.c_str());

    if (loc == 0xFFFFFFFF)
    {
        LOG(ERROR) << name << " -- error, bad address given";
        throw std::runtime_error("bad address given");
    }

    return loc;
}
} // namespace sgtr
