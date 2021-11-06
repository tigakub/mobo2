#include "GLContext.hpp"

#include <iostream>

using namespace std;

namespace mobo
{
    GLContext::GLContext()
    : Context(), programStack(), geometryStack(), materialStack()
    { }

    void GLContext::initialize()
    {
    }

    void GLContext::finalize()
    {
        glFinish();
        glutSwapBuffers();
    }
}
