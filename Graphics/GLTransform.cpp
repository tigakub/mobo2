#include "GLTransform.hpp"
#include "GLContext.hpp"

namespace mobo
{
    DERIVE_TYPE(GLTransform, "4877ad80-c68d-43b3-a5a9-3583efa364f4", {&GLPipeline::_type});
    DERIVE_TYPE(GLUVMatrix, "b9d3a91f-9945-4e9e-9ced-83486c17285b", {&GLPipeline::_type});
    DERIVE_TYPE(GLModelViewMatrix, "a9dbe28e-1cee-43d9-9622-6aaf8dabe00c", {&GLPipeline::_type});
    DERIVE_TYPE(GLProjectionMatrix, "d1f0fd2b-7f79-441c-a926-21bdb85eceac", {&GLPipeline::_type});

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

    GLUVMatrix::GLUVMatrix()
    : GLPipeline(), matrix(IDENTITY) { }

    bool GLUVMatrix::submit(Context& iCtx)
    {
        GLContext& ctx = static_cast<GLContext&>(iCtx);
        mat3<GLfloat> uvMat(ctx.uvMatrix());
        uvMat *= matrix;
        ctx.pushUVMatrix(uvMat);
        return true;
    }

    bool GLUVMatrix::retract(Context& iCtx)
    {
        GLContext& ctx = static_cast<GLContext&>(iCtx);
        ctx.popUVMatrix();
        return true;
    }

    GLModelViewMatrix::GLModelViewMatrix()
    : GLPipeline(), matrix(IDENTITY) { }

    bool GLModelViewMatrix::submit(Context& iCtx)
    {
        GLContext& ctx = static_cast<GLContext&>(iCtx);
        mat4<GLfloat> mvMat(ctx.modelviewMatrix());
        mvMat *= matrix;
        ctx.pushModelviewMatrix(mvMat);
        return true;
    }

    bool GLModelViewMatrix::retract(Context& iCtx)
    {
        GLContext& ctx = static_cast<GLContext&>(iCtx);
        ctx.popModelviewMatrix();
        return true;
    }

    GLProjectionMatrix::GLProjectionMatrix()
    : GLPipeline(), matrix(IDENTITY) { }

    bool GLProjectionMatrix::submit(Context& iCtx)
    {
        GLContext& ctx = static_cast<GLContext&>(iCtx);
        mat4<GLfloat> mvMat(ctx.projectionMatrix());
        mvMat *= matrix;
        ctx.pushProjectionMatrix(mvMat);
        return true;
    }

    bool GLProjectionMatrix::retract(Context& iCtx)
    {
        GLContext& ctx = static_cast<GLContext&>(iCtx);
        ctx.popProjectionMatrix();
        return true;
    }

}