#ifndef __GLTRANSFORM_HPP__
#define __GLTRANSFORM_HPP__

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

            virtual bool submit(Context& iCtx);
            virtual bool retract(Context& iCtx);

        protected:
            mat4<GLfloat> matrix;
    };
    
}

#endif