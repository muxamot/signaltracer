#pragma once

#include <iostream>

namespace sgtr
{

class Shaders
{
private:
    GLuint pshader_;
    std::string vs_;
    std::string fs_;

    void read(const std::string&, std::string&);
    void compile();
    void add(GLenum);

public:
    Shaders();

    GLuint setUniform(const std::string&);
};

} // namespace sgtr