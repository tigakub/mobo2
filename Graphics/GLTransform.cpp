#include "GLTransform.hpp"
#include "GLContext.hpp"

namespace mobo
{
    DERIVE_TYPE(GLTransform, "4877ad80-c68d-43b3-a5a9-3583efa364f4", {&GLPipeline::_type});

    GLTransform::GLTransform()
    : GLPipeline(), matrix(IDENTITY) { }

    bool GLTransform::submit(Context& iCtx)
    {
        GLContext& ctx = static_cast<GLContext&>(iCtx);
        mat4<GLfloat> mvMat(ctx.modelviewMatrix());
        mvMat *= matrix;
        ctx.pushModelviewMatrix(mvMat);
        return true;
    }

    bool GLTransform::retract(Context& iCtx)
    {
        GLContext& ctx = static_cast<GLContext&>(iCtx);
        ctx.popModelviewMatrix();
        return true;
    }

}