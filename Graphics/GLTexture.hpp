#ifndef __GLTEXTURE_HPP__
#define __GLTEXTURE_HPP__

#include "Debug.hpp"

#include "Node.hpp"
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

    template <int iTarget>
    class GLTextureT : Node
    {
        public:
            GLTextureT() : Node() textureHandle(0) { glGenTextures(1, &textureHandle); }
            virtual ~GLTextureT() { if(textureHandle) glDeleteTextures(1, &textureHandle); }

        protected:
            GLuint textureHandle;
    };

    class GL2DTexture : public GLTextureT<GL_TEXTURE_2D>
    {
        DECLARE_TYPE

    };

    class GLRectTexture : public GLTextureT<GL_TEXTURE_RECTANGLE>
    {
        DECLARE_TYPE

    };

    
}

#endif
