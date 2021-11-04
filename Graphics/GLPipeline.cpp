#include "GLPipeline.hpp"

#include <iostream>

using namespace std;

namespace mobo
{
    DERIVE_TYPE(GLPipeline, "18f6e06f-1af9-4c09-a674-1e16ea159777", { &Node::_type })

    GLPipeline::GLPipeline()
    : Node()
    {
        addInput(GLPipeline::_type);
    }

    bool GLPipeline::submit(Context& iCtx)
    {
        #ifdef TRACE
        cout << "GLPipeline::submit" << endl;
        #endif
    }

    bool GLPipeline::retract(Context& iCtx)
    {
        #ifdef TRACE
        cout << "GLPipeline::retract" << endl;
        #endif
    }
}
