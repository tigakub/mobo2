#ifndef __GLTEXTURE_HPP__
#define __GLTEXTURE_HPP__

#include "lodepng.h"
#include "Debug.hpp"

#include "Node.hpp"
#include "DataSourceNode.hpp"
#include "ImageNode.hpp"

#ifndef GL_GLEXT_PROTOTYPES
#define GL_GLEXT_PROTOTYPES 1
#endif

#include <GL/freeglut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <iostream>
#include <string>

using namespace std;

namespace mobo
{
    class GLContext;

    class GLTexture : public Node
    {
        DECLARE_TYPE
        
        public:
            GLTexture()
            : Node(), textureHandle(0), uniformName(), internalFormat(GL_RGBA8), format(GL_RGBA), imgWidth(0), imgHeight(0),
              textureCreated(false)
            {
                addInput(FrameSourceNode::_type);
                glGenTextures(1, &textureHandle);
                #ifdef DEBUG_OPENGL
                CHECK_OPENGL_ERROR(glGenTextures)
                #endif
            }
            virtual ~GLTexture() {
                if(textureHandle) glDeleteTextures(1, &textureHandle);
            }
            
            virtual GLuint texHandle() const { return textureHandle; }
            virtual GLenum target() const = 0;

            void loadFromPNG(const string& iFilename);

            virtual void loadFromBuffer(const uint8_t* iBuffer) = 0;

            void setUnifName(const string& iName) { uniformName = iName; }
            const string& unifName() const { return uniformName; }

            virtual bool update(Context& iCtx);

        protected:
            GLuint textureHandle;
            string uniformName;
            unsigned imgWidth, imgHeight;
            bool textureCreated;
            GLenum internalFormat;
            GLenum format;
    };

    template <int iTarget>
    class GLTextureT : public GLTexture
    {
        public:
            GLTextureT() : GLTexture() { }

            virtual GLenum target() const { return iTarget; }
    };

    class GL2DTexture : public GLTextureT<GL_TEXTURE_2D>
    {
        DECLARE_TYPE
        
        public:
            GL2DTexture() : GLTextureT<GL_TEXTURE_2D>() { }
            virtual void loadFromBuffer(const uint8_t* iBuffer);
    };

    class GLRectTexture : public GLTextureT<GL_TEXTURE_RECTANGLE>
    {
        DECLARE_TYPE

        public:
            GLRectTexture() : GLTextureT<GL_TEXTURE_RECTANGLE>() { }
            virtual void loadFromBuffer(const uint8_t* iBuffer);
    };
    
}

#endif
