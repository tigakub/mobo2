#include "GLDraw.hpp"
#include "GLContext.hpp"
#include "GLProgram.hpp"

namespace mobo
{
    DERIVE_TYPE(GLDraw, "6ba4bafa-5cfd-4b51-9987-c5763cd68411", {&GLPipeline::_type});

    GLDraw::GLDraw()
    : GLPipeline()
    { }

    bool GLDraw::submit(Context& iCtx)
    {
        GLContext& ctx = static_cast<GLContext&>(iCtx);
        GLProgram* prog = ctx.currentProgram();
        if(prog) {
            const GLProgram::UniformInfo& projInfo = prog->getUniformInfo("project");
            const GLProgram::UniformInfo& cameraInfo = prog->getUniformInfo("camera");
            const GLProgram::UniformInfo& mvInfo = prog->getUniformInfo("modelview");
            glUniformMatrix4fv(projInfo.location, 1, true, (const GLfloat*) &ctx.projectionMatrix());
            #ifdef DEBUG_OPENGL
            CHECK_OPENGL_ERROR(glUniformMatrix4fv)
            #endif
            glUniformMatrix4fv(cameraInfo.location, 1, true, (const GLfloat*) &ctx.cameraMatrix());
            #ifdef DEBUG_OPENGL
            CHECK_OPENGL_ERROR(glUniformMatrix4fv)
            #endif
            glUniformMatrix4fv(mvInfo.location, 1, true, (const GLfloat*) &ctx.modelviewMatrix());
            #ifdef DEBUG_OPENGL
            CHECK_OPENGL_ERROR(glUniformMatrix4fv)
            #endif

            draw();
        }
        return true;
    }

    bool GLDraw::retract(Context &iCtx)
    {
        GLContext& ctx = static_cast<GLContext&>(iCtx);
        
        return true;
    }

    void GLDraw::draw()
    {
        glDrawArrays(GL_QUAD_STRIP, 0, 4);
        #ifdef DEBUG_OPENGL
        CHECK_OPENGL_ERROR(glDrawArrays)
        #endif
    }

}
