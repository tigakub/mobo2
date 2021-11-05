#include "GLMaterial.hpp"

using namespace std;

namespace mobo
{
    DERIVE_TYPE(GLMaterial, "e5c483ff-b4c0-4130-a45f-d2743e86826a", { &GLPipeline::_type })

    GLMaterial::GLMaterial()
    : GLPipeline()
    {
    }

    bool GLMaterial::update(Context& iCtx)
    {
        GLContext& ctx = static_cast<GLContext&>(iCtx);
        GLProgram *programNode = ctx.currentProgram();
        if(programNode) {
            for(auto link : dinputs) {
            }
        }

}