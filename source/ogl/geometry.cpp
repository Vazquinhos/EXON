#include "geometry.hpp"
#include <glad/glad.h>

namespace exon
{
    namespace ogl
    {
        Geometry::Geometry(const std::vector<float>& vertices, unsigned int stride, const std::vector<Attribute>& attributes)
            : mVertexBuffer(vertices)
            , mAttributes(attributes)
            , mStride(stride)
        {
        }

        Geometry::~Geometry()
        {
            glDeleteVertexArrays(1, &VAO);
            glDeleteBuffers(1, &VBO);
        }

        void Geometry::Create()
        {
            glGenVertexArrays(1, &VAO);
            glGenBuffers(1, &VBO);
            // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
            glBindVertexArray(VAO);

            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(mVertexBuffer.size() * sizeof(float)), mVertexBuffer.data(), GL_STATIC_DRAW);

            for (GLuint i = 0, numAttributes = mAttributes.size(); i < numAttributes; ++i)
            {
                Attribute& a = mAttributes[i];
                glEnableVertexAttribArray(i);
                glVertexAttribPointer(
                    i,
                    a.Size,
                    GL_FLOAT,
                    a.IsNormalized ? GL_TRUE : GL_FALSE,
                    mStride * sizeof(float),
                    ((GLvoid*)(a.Offset * sizeof(GLfloat)))
                );
            }

            // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
            glBindBuffer(GL_ARRAY_BUFFER, 0);

            // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
            // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
            glBindVertexArray(0);

            CheckErrors();
        }

        void Geometry::Bind()
        {
            glBindVertexArray(VAO);
        }

        void Geometry::Unbind()
        {
            glBindVertexArray(0);
        }
        
        void Geometry::Draw()
        {
            glDrawArrays(GL_TRIANGLES, 0, 3);
        }

        IndexedGeometry::IndexedGeometry(const std::vector<float>& vertices, const std::vector<uint32_t>& indices, unsigned int stride, const std::vector<Attribute>& attributes)
            : Geometry(vertices, stride, attributes)
            , mIndexBuffer(indices)
        {
        }

        IndexedGeometry::~IndexedGeometry()
        {
            glDeleteBuffers(1, &EBO);
        }

        void IndexedGeometry::Create()
        {
            glGenVertexArrays(1, &VAO);
            glGenBuffers(1, &VBO);
            // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
            glBindVertexArray(VAO);

            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(mVertexBuffer.size() * sizeof(float)), mVertexBuffer.data(), GL_STATIC_DRAW);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
            glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(mIndexBuffer.size() * sizeof(uint32_t)), mIndexBuffer.data(), GL_STATIC_DRAW);

            for (GLuint i = 0, numAttributes = mAttributes.size(); i < numAttributes; ++i)
            {
                Attribute& a = mAttributes[i];
                glEnableVertexAttribArray(i);
                glVertexAttribPointer(
                    i,
                    a.Size,
                    GL_FLOAT,
                    a.IsNormalized ? GL_TRUE : GL_FALSE,
                    mStride * sizeof(float),
                    ((GLvoid*)(a.Offset * sizeof(GLfloat)))
                );
            }

            // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
            glBindBuffer(GL_ARRAY_BUFFER, 0);

            // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
            // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
            glBindVertexArray(0);

            CheckErrors();
        }

        void IndexedGeometry::Bind()
        {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        }

        void IndexedGeometry::Unbind()
        {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        }

        void IndexedGeometry::Draw()
        {
            glDrawElements(GL_TRIANGLES, mIndexBuffer.size(), GL_UNSIGNED_INT, 0);
        }
    }
}