#pragma once

#include "ogl.hpp"

namespace exon
{
    namespace ogl
    {
        class Texture : public OglEntity
        {
        public:
            static bool Read(GLenum type, const std::string& filename, Texture** texture);
        public:
            Texture(GLenum type, int width, int height, int nrChannels, unsigned char *data);
            virtual ~Texture();

            void Bind();

        protected:
            GLenum mType;
            int mWidth;
            int mHeight;
            int mChannels;
            unsigned char* mRawData;
        };
    }
}