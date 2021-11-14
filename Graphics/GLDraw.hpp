#ifndef __GLDRAW_HPP__
#define __GLDRAW_HPP__

#include "Debug.hpp"

#include "Context.hpp"
#include "GLPipeline.hpp"

#ifndef GL_GLEXT_PROTOTYPES
#define GL_GLEXT_PROTOTYPES 1
#endif

#include <GL/freeglut.h>
#include <GL/gl.h>
#include <GL/glu.h>

namespace mobo
{

    class GLDraw : public GLPipeline
    {
        DECLARE_TYPE

        public:
            GLDraw();

            virtual bool submit(Context& iCtx);
            virtual bool retract(Context &iCtx);

            virtual void draw();
   };

}

#endif