#include "GLContext.hpp"

#include <iostream>

using namespace std;

namespace mobo
{
    GLContext::GLContext()
    : Context()
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
