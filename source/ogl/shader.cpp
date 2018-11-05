#include "shader.hpp"
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