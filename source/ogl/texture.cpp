#include "texture.hpp"
#include <glad/glad.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace exon
{
    namespace ogl
    {
        bool Texture::Read(GLenum type, const std::string & filename, Texture ** texture)
        {
            int width, height, nrChannels;
            unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nrChannels, 0);
            if (data != nullptr)
            {
                *texture = new Texture(type, width, height, nrChannels, data);
                return true;
            }

            return false;
        }

        Texture::Texture(GLenum type, int width, int height, int nrChannels, unsigned char *data)
            : mType(type)
            , mWidth(width)
            , mHeight(height)
            , mChannels(nrChannels)
            , mRawData(data)
        {
            unsigned int texture;
            glGenTextures(1, &texture);

            mId = texture;

            glBindTexture(GL_TEXTURE_2D, texture);

            // set the texture wrapping/filtering options (on the currently bound texture object)
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }

        Texture::~Texture()
        {
            stbi_image_free(mRawData);
        }

        void Texture::Bind()
        {
            glBindTexture(mType , mId);
        }
    }
}