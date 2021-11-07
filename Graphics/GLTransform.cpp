#include "GLTransform.hpp"
#include "GLContext.hpp"

namespace mobo
{

    GLTransform::GLTransform()
    : Node() { }

    bool GLTransform::submit(Context& iCtx)
    {
        GLContext& ctx = static_cast<GLContext&>(iCtx);
        mat4<GLfloat> mvMat(ctx.modelviewMatrix());
        mvMat *= matrix;
        ctx.pushModelviewMatrix(mvMat);
        return true;
    }

    bool retract(Context& iCtx)
    {
        GLContext& ctx = static_cast<GLContext&>(iCtx);
        ctx.popModelviewMatrix();
        return true;
    }

}