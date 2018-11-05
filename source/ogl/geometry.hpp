#pragma once

#include "ogl.hpp"

namespace exon
{
    namespace ogl
    {
        class Geometry 
        {
        public:
            class Attribute
            {
            public:
                GLint Size;
                GLint Offset;
                GLboolean IsNormalized;
            };
        public:
            Geometry(const std::vector<float>& vertices, unsigned int stride, const std::vector<Attribute>& attributes);
            virtual ~Geometry();

            inline const std::vector<float>& GetVertexBuffer() const { return mVertexBuffer; }

            void Bind();
            void Unbind();
            void Draw();

        protected:
            unsigned int mStride;
            unsigned int VBO;
            unsigned int VAO;
            std::vector<float> mVertexBuffer;
            std::vector<Attribute> mAttributes;
        };
    }
}