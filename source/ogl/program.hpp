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
			void SetMatrix(const glm::mat4& matrix, const std::string& attributeName);
			void SetMatrix(const glm::mat4& matrix, unsigned int location);
        protected:

            const std::vector<Shader*> mShaders;
        };
    }
}