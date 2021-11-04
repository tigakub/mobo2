#ifndef __RENDERER_HPP__
#define __RENDERER_HPP__

#ifndef GL_GLEXT_PROTOTYPES
#define GL_GLEXT_PROTOTYPES 1
#endif

#include "MovingAverage.hpp"

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
            Renderer() : prog(0) { }
            virtual ~Renderer();

            void didReshape(int w, int h);

            virtual void init();
            virtual void render();

        protected:
            GLint prog;
            GLuint vbo[3];
            GLuint tex;
            GLuint samp;

    };
}

#endif
