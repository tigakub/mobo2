#include "GLCamera.hpp"
#include "GLContext.hpp"
#include "Math.hpp"

namespace mobo
{

    DERIVE_TYPE(GLCamera, "17393816-5c20-40d4-8b1b-ee05cb851fdd", {&Node::_type})

    bool GLCamera::submit(Context& iCtx)
    {
        GLContext& ctx = static_cast<GLContext&>(iCtx);
        GLfloat aspect = ((GLfloat) ctx.getViewport().size[0]) / ((GLfloat) ctx.getViewport().size[1]);
        GLfloat hFactor = 1.0;
        GLfloat vFactor = 1.0;
        if(aspect >=  1.0) {
            hFactor = aspect;
        } else {
            vFactor = 1.0 / aspect;
        }
        GLfloat left(-0.05 * hFactor), right(0.05 * hFactor), bottom(-0.05 * vFactor), top(0.05 * vFactor), near(0.1), far(20.0);
        mat4<GLfloat> projMat(PERSPECTIVE, left, right, bottom, top, near, far);
        ctx.pushProjectionMatrix(projMat);
        const mat4<GLfloat>& mvMat = ctx.modelviewMatrix();
        ctx.pushCameraMatrix(mvMat.reciprocal());
        return true;
    }

    bool GLCamera::retract(Context& iCtx) 
    {
        GLContext& ctx = static_cast<GLContext&>(iCtx);
        ctx.popCameraMatrix();
        ctx.popProjectionMatrix();
        return true;
    }

}