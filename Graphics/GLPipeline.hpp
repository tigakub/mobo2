#ifndef __GLPIPELINE_HPP__
#define __GLPIPELINE_HPP__

#include "Debug.hpp"

#include "Node.hpp"

#ifndef GL_GLEXT_PROTOTYPES
#define GL_GLEXT_PROTOTYPES 1
#endif

#include <GL/freeglut.h>
#include <GL/gl.h>
#include <GL/glu.h>

namespace mobo
{
    class GLPipeline : public Node
    {
        DECLARE_TYPE

        public:
            GLPipeline();
            virtual ~GLPipeline() { }

            virtual bool submit(Context& iCtx);
            virtual bool retract(Context &iCtx);

    };
}

#endif
