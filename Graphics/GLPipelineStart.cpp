#include "GLPipelineStart.hpp"

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
        glClearColor(0.5, 0.0, 1.0, 1.0);
        glClearDepth(1.0f);
        return true;
    }

    bool GLPipelineStart::submit(Context& iCtx)
    {
        #ifdef DEBUG_OPENGL
        //cout << "GLPipelineStart::submit" << endl;
        #endif
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        return true;
    }

    bool GLPipelineStart::retract(Context& iCtx)
    {
        #ifdef DEBUG_OPENGL
        //cout << "GLPipelineStart::retract" << endl;
        #endif
        return true;
    }
}
