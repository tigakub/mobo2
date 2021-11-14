#include "GLPipelineStart.hpp"
#include "GLContext.hpp"
#include "Math.hpp"

#include <iostream>

using namespace std;

namespace mobo
{
    DERIVE_TYPE(GLPipelineStart, "cafab51b-4cd9-4c8a-aae0-5c8610fdcbf7", { &GLPipeline::_type })

    GLPipelineStart::GLPipelineStart()
    : GLPipeline()
    {
    }

    bool GLPipelineStart::update(Context& iCtx)
    {
        glEnable(GL_DEPTH_TEST);
        #ifdef DEBUG_OPENGL
        CHECK_OPENGL_ERROR(glEnable)
        #endif
        glEnable(GL_BLEND);
        #ifdef DEBUG_OPENGL
        CHECK_OPENGL_ERROR(glEnable)
        #endif
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        #ifdef DEBUG_OPENGL
        CHECK_OPENGL_ERROR(glBlendFunc)
        #endif
        glDisable(GL_ALPHA_TEST);
        #ifdef DEBUG_OPENGL
        CHECK_OPENGL_ERROR(glDisable)
        #endif
        glDepthFunc(GL_LESS);
        #ifdef DEBUG_OPENGL
        CHECK_OPENGL_ERROR(glDepthFunc)
        #endif
        glClearColor(0.125, 0.125, 0.125, 1.0);
        #ifdef DEBUG_OPENGL
        CHECK_OPENGL_ERROR(glClearColor)
        #endif
        glClearDepth(1.0f);
        #ifdef DEBUG_OPENGL
        CHECK_OPENGL_ERROR(glClearDepth)
        #endif
        return true;
    }

    bool GLPipelineStart::submit(Context& iCtx)
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        #ifdef DEBUG_OPENGL
        CHECK_OPENGL_ERROR(glClear)
        #endif
        return true;
    }

    bool GLPipelineStart::retract(Context& iCtx)
    {
        GLContext& ctx = static_cast<GLContext&>(iCtx);
        return true;
    }
}
