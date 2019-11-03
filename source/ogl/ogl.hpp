#pragma once
#include <vector>
#include <glad/glad.h>
#include <glm/glm.hpp>

namespace exon
{
    namespace ogl
    {
        class OglEntity
        {
        public:
            OglEntity() = default;
            inline int GetId() const { return mId; }
        protected:
            int mId;
        };

        void CheckErrors();
    }
}