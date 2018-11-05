#include "vertex.hpp"
namespace exon
{
    namespace ogl
    {
        Vertex::Vertex(size_t stride, const std::vector<Attribute> attributes)
            : mStride(stride)
            , mAttributes(attributes)
        {
        }

        void Vertex::Bind()
        {
            
        }
    }
}