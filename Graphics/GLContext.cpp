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
        mat4<GLfloat> projMat(IDENTITY);
        mat4<GLfloat> camMat(IDENTITY);
        mat4<GLfloat> mvMat(IDENTITY);
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
        popCameraMatrix();
        popProjectionMatrix();
    }
}
