#pragma once

#include "ogl.hpp"

namespace exon
{
    namespace ogl
    {
        class Vertex
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
            Vertex(size_t stride, const std::vector<Attribute> attributes);
            virtual ~Vertex() = delete;

            void Bind();

        protected:
            size_t mStride;
            std::vector<Attribute> mAttributes;
        };
    }
}