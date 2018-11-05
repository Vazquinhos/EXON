#include "program.hpp"
#include "shader.hpp"
#include <glad/glad.h>

namespace exon
{
    namespace ogl
    {
        Program::Program(const std::vector<Shader*>& shaders)
            : mShaders(shaders)
        {
            int shaderProgram = glCreateProgram();

            for (Shader* s : shaders)
            {
                glAttachShader(shaderProgram, s->GetId());
            }

            glLinkProgram(shaderProgram);

            mId = shaderProgram;

#ifdef  _DEBUG

            // check for linking errors
            int success;
            glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
            if (!success)
            {
                char infoLog[512];
                glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
                OutputDebugString(infoLog);

            }
            CheckErrors();

#endif //  _DEBUG
        }

        Program::~Program()
        {
            glDeleteProgram(mId);
        }

        void Program::Bind()
        {
            glUseProgram(mId);
        }
    }
}