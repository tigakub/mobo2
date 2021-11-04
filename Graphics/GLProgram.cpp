#include "GLContext.hpp"
#include "GLProgram.hpp"

#include <iostream>

using namespace std;

namespace mobo
{

    DERIVE_TYPE(GLProgram, "d7ea0fc4-5596-4312-ba92-e781281d3c8a", { &GLPipeline::_type })

    GLProgram::GLProgram()
    : GLPipeline(), programHandle(glCreateProgram())
    {
        addInput(GLVertexShader::_type);
        addInput(GLFragmentShader::_type);
    }

    GLProgram::~GLProgram()
    {
        if(programHandle) glDeleteProgram(programHandle);
    }

    bool GLProgram::update(Context& iCtx)
    {
        GLint status;
        GLVertexShader* vtxShader = getInput<GLVertexShader>(1);
        GLFragmentShader* frgShader = getInput<GLFragmentShader>(2);
        if(vtxShader && frgShader) {
            #ifdef DEBUG_OPENGL
            cout << "Linking program ... ";
            #endif
            vtxShader->attach(programHandle);
            frgShader->attach(programHandle);
            glLinkProgram(programHandle);
            GLint status;
            glGetProgramiv(programHandle, GL_LINK_STATUS, &status);
            if(status) {
                #ifdef DEBUG_OPENGL
                cout << "success" << endl;
                #endif
                return status;
            #ifdef DEBUG_OPENGL
            } else {
                cout << "failure" << endl;
            #endif
            }
        }
        return false;
    }

    bool GLProgram::submit(Context& iCtx)
    {
        #ifdef DEBUG_OPENGL
        cout << "GLProgram::submit" << endl;
        #endif
        GLContext& ctx = static_cast<GLContext&>(iCtx);
        ctx.pushProgram(this);
        activate();
        return true;
    }

    bool GLProgram::retract(Context& iCtx)
    {
        #ifdef DEBUG_OPENGL
        cout << "GLProgram::retract" << endl;
        #endif
        deactivate();
        #ifdef DEBUG_OPENGL
        cout << "GLProgram::deactivated" << endl;
        #endif
        GLContext& ctx = static_cast<GLContext&>(iCtx);
        #ifdef DEBUG_OPENGL
        cout << "GLProgram::context" << endl;
        #endif
        GLProgram* prev = ctx.popProgram();
        #ifdef DEBUG_OPENGL
        cout << "GLProgram::popProgram" << endl;
        #endif
        if(prev) prev->activate();
        #ifdef DEBUG_OPENGL
        cout << "GLProgram::retracted" << endl;
        #endif
        return true;
    }

    bool GLProgram::activate()
    {
        glUseProgram(programHandle);
        return true;
    }

    bool GLProgram::deactivate()
    {
        glUseProgram(0);
        return true;
    }

}
