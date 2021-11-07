#include "GLContext.hpp"

#include <iostream>

using namespace std;

namespace mobo
{
    GLContext::GLContext()
    : Context(), programStack(), geometryStack(), materialStack(), viewport(), projectionMatrixStack(), cameraMatrixStack(), modelviewMatrixStack()
    { }

    void GLContext::initialize()
    {
        GLfloat aspect = ((GLfloat) viewport.size[0]) / ((GLfloat) viewport.size[1]);
        GLfloat hFactor = 1.0;
        GLfloat vFactor = 1.0;
        if(aspect >=  1.0) {
            hFactor = aspect;
        } else {
            vFactor = 1.0 / aspect;
        }
        GLfloat left(-0.5 * hFactor), right(0.5 * hFactor), bottom(-0.5 * vFactor), top(0.5 * vFactor), near(1.0), far(20.0);
        mat4<GLfloat> projMat(PERSPECTIVE, left, right, bottom, top, near, far);
        mat4<GLfloat> camMat(TRANSLATION, 0.0, 0.0, 3.0);
        camMat *= mat4<GLfloat>(ROTATION, -0.0625 * M_PI, 0.0, 1.0, 0.0);
        mat4<GLfloat> mvMat(ROTATION, 0.25 * M_PI, 0.0, 1.0, 0.0);
        pushProjectionMatrix(projMat);
        pushCameraMatrix(camMat.reciprocal());
        pushModelviewMatrix(mvMat);

        glViewport(viewport.origin[0], viewport.origin[1], viewport.size[0], viewport.size[1]);
    }

    void GLContext::finalize()
    {
        glFinish();
        glutSwapBuffers();
        popModelviewMatrix();
        popProjectionMatrix();
    }
}
