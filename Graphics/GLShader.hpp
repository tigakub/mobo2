#ifndef __GLSHADER_HPP__
#define __GLSHADER_HPP__

#include "Debug.hpp"

#include "Context.hpp"
#include "Node.hpp"
#include "Type.hpp"

#ifndef GL_GLEXT_PROTOTYPES
#define GL_GLEXT_PROTOTYPES 1
#endif

#include <GL/freeglut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <string>

using namespace std;

namespace mobo
{
    class GLContext;

    class GLShader : public Node
    {
        DECLARE_TYPE
        public:
            GLShader(GLenum iShaderType);
            virtual ~GLShader();

            GLuint compileFromString(const string& iSource);

            virtual bool update(Context &iCtx);
            virtual bool attach(GLint iProg) { glAttachShader(iProg, shaderHandle); return true; }

        protected:
            GLint shaderHandle;
    };

    class GLVertexShader : public GLShader
    {
        DECLARE_TYPE
        public:
            GLVertexShader()
            : GLShader(GL_VERTEX_SHADER) { }
    };

    class GLFragmentShader : public GLShader
    {
        DECLARE_TYPE
        public:
            GLFragmentShader()
            : GLShader(GL_FRAGMENT_SHADER) { }
    };

}

#endif
