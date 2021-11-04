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
            #ifdef TRACE
            cout << "Linking program ... ";
            #endif
            vtxShader->attach(programHandle);
            frgShader->attach(programHandle);
            glLinkProgram(programHandle);
            GLint status;
            glGetProgramiv(programHandle, GL_LINK_STATUS, &status);
            if(status) {
                #ifdef TRACE
                cout << "success" << endl;
                #endif
                return status;
            #ifdef TRACE
            } else {
                cout << "failure" << endl;
            #endif
            }
        }
        return false;
    }

    bool GLProgram::submit(Context& iCtx)
    {
        #ifdef TRACE
        cout << "GLProgram::submit" << endl;
        #endif
        GLContext& ctx = static_cast<GLContext&>(iCtx);
        ctx.pushProgram(this);
        activate();
    }

    bool GLProgram::retract(Context& iCtx)
    {
        #ifdef TRACE
        cout << "GLProgram::retract" << endl;
        #endif
        GLContext& ctx = static_cast<GLContext&>(iCtx);
        GLProgram* prev = ctx.popProgram();
        if(prev) prev->activate();
    }

    bool GLProgram::activate()
    {
        glUseProgram(programHandle);
    }

    bool GLProgram::deactivate()
    {
        glUseProgram(0);
    }

}
