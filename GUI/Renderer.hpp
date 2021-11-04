#ifndef __RENDERER_HPP__
#define __RENDERER_HPP__

#include "Debug.hpp"

#include "MovingAverage.hpp"

#ifndef GL_GLEXT_PROTOTYPES
#define GL_GLEXT_PROTOTYPES 1
#endif

#include <GL/freeglut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <chrono>

using namespace std;
using namespace std::chrono;

namespace mobo
{
    class Renderer
    {
        public:
            Renderer() { }
            virtual ~Renderer();

            void didReshape(int w, int h);

            virtual void init();
            virtual void render();

        protected:
            GLuint tex;
            GLuint samp;

    };
}

#endif
