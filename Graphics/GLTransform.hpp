#ifndef __GLTRANSFORM_HPP__
#define __GLTRANSFORM_HPP__

#include "Debug.hpp"
#include "Node.hpp"
#include "Context.hpp"
#include "Math.hpp"
#include "GLPipeline.hpp"

#ifndef GL_GLEXT_PROTOTYPES
#define GL_GLEXT_PROTOTYPES 1
#endif

#include <GL/freeglut.h>
#include <GL/gl.h>
#include <GL/glu.h>

namespace mobo
{

    class GLTransform : public GLPipeline
    {
        DECLARE_TYPE
        
        public:
            GLTransform();

            virtual GLTransform& operator=(const mat4<GLfloat>& iMat) { matrix = iMat; return *this; }
            virtual GLTransform& operator*=(const mat4<GLfloat>& iMat) { matrix *= iMat; return *this; }

            virtual bool submit(Context& iCtx);
            virtual bool retract(Context& iCtx);

        protected:
            mat4<GLfloat> matrix;
    };

    class GLUVMatrix : public GLPipeline
    {
        DECLARE_TYPE

        public:
            GLUVMatrix();

            virtual GLUVMatrix& operator=(const mat3<GLfloat>& iMat) { matrix = iMat; return *this; }
            virtual GLUVMatrix& operator*=(const mat3<GLfloat>& iMat) { matrix *= iMat; return *this; }

            virtual bool submit(Context& iCtx);
            virtual bool retract(Context& iCtx);

        protected:
            mat3<GLfloat> matrix;
    };

    class GLModelViewMatrix : public GLPipeline
    {
        DECLARE_TYPE

        public:
            GLModelViewMatrix();

            virtual GLModelViewMatrix& operator=(const mat4<GLfloat>& iMat) { matrix = iMat; return *this; }
            virtual GLModelViewMatrix& operator*=(const mat4<GLfloat>& iMat) { matrix *= iMat; return *this; }

            virtual bool submit(Context& iCtx);
            virtual bool retract(Context& iCtx);

        protected:
            mat4<GLfloat> matrix;
    };

    class GLProjectionMatrix : public GLPipeline
    {
        DECLARE_TYPE

        public:
            GLProjectionMatrix();

            virtual GLProjectionMatrix& operator=(const mat4<GLfloat>& iMat) { matrix = iMat; return *this; }
            virtual GLProjectionMatrix& operator*=(const mat4<GLfloat>& iMat) { matrix *= iMat; return *this; }

            virtual bool submit(Context& iCtx);
            virtual bool retract(Context& iCtx);

        protected:
            mat4<GLfloat> matrix;
    };
    
}

#endif