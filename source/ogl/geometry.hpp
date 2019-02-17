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
            
            virtual void Create();
            virtual void Bind();
            virtual void Unbind();
            virtual void Draw();

        protected:
            unsigned int mStride;
            unsigned int VBO;
            unsigned int VAO;
            std::vector<float> mVertexBuffer;
            std::vector<Attribute> mAttributes;
        };

        class IndexedGeometry : public Geometry
        {
            IndexedGeometry(const std::vector<float>& vertices, const std::vector<uint32_t>& indices, unsigned int stride, const std::vector<Attribute>& attributes);
            virtual ~IndexedGeometry();

            inline const std::vector<uint32_t>& GetIndexBuffer() const { return mIndexBuffer; }

            void Create();
            void Bind();
            void Unbind();
            void Draw();
        protected:
            unsigned int EBO;
            std::vector<uint32_t> mIndexBuffer;
        };
    }
}