#ifndef __GLCONTEXT_HPP__
#define __GLCONTEXT_HPP__

#include "Context.hpp"
#include "GLShader.hpp"
#include "GLProgram.hpp"

#ifndef GL_GLEXT_PROTOTYPES
#define GL_GLEXT_PROTOTYPES 1
#endif

#include <GL/freeglut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <vector>

using namespace std;

namespace mobo
{

    class GLContext : public Context
    {
        public:
            GLContext();
            virtual ~GLContext() { }

            virtual void initialize();
            virtual void finalize();

            void pushProgram(GLProgram* iProgram) { programStack.push_back(iProgram); }
            GLProgram* currentProgram() { if(programStack.size()) return static_cast<GLProgram*>(programStack.back()); return nullptr; }
            GLProgram* popProgram() { programStack.pop_back(); return currentProgram(); }

        protected:
            vector<SmartPtr<GLProgram>> programStack;
    };

}

#endif