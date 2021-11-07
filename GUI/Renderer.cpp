#include "Renderer.hpp"

#include "lodepng.h"

namespace mobo
{
    void Renderer::init()
    {   
    }

    Renderer::~Renderer()
    { }

    void Renderer::render()
    {
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }
}
