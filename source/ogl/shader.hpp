#pragma once

#include "ogl.hpp"

namespace exon
{
    namespace ogl
    {
        class Shader : public OglEntity
        {
        public:
            static bool Read(GLenum type, const std::string& filename, Shader** shader);
        public:
            Shader(GLenum type, const char* shaderSource, int length);
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