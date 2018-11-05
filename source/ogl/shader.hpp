#pragma once

#include "ogl.hpp"

namespace exon
{
    namespace ogl
    {
        class Shader : public OglEntity
        {
        public:
        public:
            Shader(unsigned int type, const char* shaderSource, int length);
            virtual ~Shader();

        protected:
        };

        class VertexShader : public Shader
        {
        public:
            VertexShader(const char* shaderSource, int length);
            virtual ~VertexShader();

        protected:
        };

        class FragmentShader : public Shader
        {
        public:
            FragmentShader(const char* shaderSource, int length);
            virtual ~FragmentShader();

        protected:
        };
    }
}