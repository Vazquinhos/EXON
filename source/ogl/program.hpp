#pragma once

#include "ogl.hpp"

namespace exon
{
    namespace ogl
    {
        class Shader;
        class Program : public OglEntity
        {
        public:
            Program(const std::vector<Shader*>& shaders);
            virtual ~Program();

            void Bind();
        protected:

            const std::vector<Shader*> mShaders;
        };
    }
}