#include "shader.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <glad/glad.h>

namespace exon
{
    namespace ogl
    {
        Shader::Shader(GLenum type, const GLchar* shaderSource, GLint length)
        {
            int shaderId = glCreateShader(type);
            glShaderSource(shaderId, 1, &shaderSource, &length);
            glCompileShader(shaderId);

#ifdef _DEBUG
            int  success;
            char infoLog[512];
            glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);

            if (!success)
            {
                glGetShaderInfoLog(shaderId, 512, NULL, infoLog);
                OutputDebugString("ERROR::SHADER::COMPILATION_FAILED\n");
                OutputDebugString(infoLog);
            }
#endif 

            mId = shaderId;

            CheckErrors();
        }
        bool Shader::Read(GLenum type, const std::string & filename, Shader** shader)
        {
            std::stringstream stream;
            try
            {
                std::ifstream shaderFile;
                shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
                shaderFile.open(filename);
                stream << shaderFile.rdbuf();
                shaderFile.close();
            }
            catch (std::ifstream::failure e)
            {
                std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
                return false;
            }

            std::string codeStr = stream.str();
            switch (type)
            {
            case GL_VERTEX_SHADER:
                *shader = new VertexShader(codeStr.c_str(), codeStr.length());
                break;
            case GL_FRAGMENT_SHADER:
                *shader = new FragmentShader(codeStr.c_str(), codeStr.length());
                break;
            default:
                throw "Not implemented";
            }

            return true;
        }
        Shader::~Shader()
        {
            glDeleteShader(mId);
        }

        VertexShader::VertexShader(const GLchar* shaderSource, GLint length)
            : Shader(GL_VERTEX_SHADER, shaderSource, length)
        {
        }

        VertexShader::~VertexShader()
        {
        }

        FragmentShader::FragmentShader(const GLchar * shaderSource, GLint length)
            : Shader(GL_FRAGMENT_SHADER, shaderSource, length)
        {
        }

        FragmentShader::~FragmentShader()
        {
        }
    }
}