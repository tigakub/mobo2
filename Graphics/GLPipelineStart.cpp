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
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glDisable(GL_ALPHA_TEST);
        glDepthFunc(GL_LESS);
        glClearColor(0.125, 0.0, 0.25, 1.0);
        glClearDepth(1.0f);
        return true;
    }

    bool GLPipelineStart::submit(Context& iCtx)
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        return true;
    }

    bool GLPipelineStart::retract(Context& iCtx)
    {
        GLContext& ctx = static_cast<GLContext&>(iCtx);
        return true;
    }
}
